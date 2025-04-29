/*
   Copyright 2022 Bruno Rodrigues Ferreira

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

   http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include <boost/log/trivial.hpp>
#include <boost/url.hpp>
#include "output_factory.h"
#include "output_file.h"
#include "output_google_cloud_storage.h"
#include "output_stdout.h"

std::shared_ptr<output> output_factory::make(const std::string &path)
{
    // path - is a special case to stdout
    if (path == "-") {
        return std::make_shared<output_stdout>();
    }

    // If colon is not present then try as a file
    if (path.find_first_of(':') == std::string::npos) {
        auto file = std::make_shared<output_file>();
        if (!file->open(path)) {
            BOOST_LOG_TRIVIAL(fatal) << "could not open output file";
            return {};
        }
        return file;
    }

    auto parse_result = boost::urls::parse_uri(path);
    if (parse_result.has_error()) {
        BOOST_LOG_TRIVIAL(fatal) << "could not parse output path: " << parse_result.error().message();
        return {};
    }

    auto uri = parse_result.value();

    if (uri.scheme() == "file") {
        auto file = std::make_shared<output_file>();
        if (uri.path().empty()) {
            BOOST_LOG_TRIVIAL(fatal) << "empty filename";
            return {};
        }
        if (!file->open(uri.path())) {
            BOOST_LOG_TRIVIAL(fatal) << "could not open output file";
            return {};
        }
        return file;
    }
    if (uri.scheme() == "gs") {
        return std::make_shared<output_google_cloud_storage>(uri);
    }

    return {};
}

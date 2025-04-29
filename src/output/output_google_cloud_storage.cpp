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

#include "output_google_cloud_storage.h"
#include "google/cloud/storage/well_known_headers.h"

#include <boost/log/trivial.hpp>

output_google_cloud_storage::output_google_cloud_storage(const boost::urls::url_view &uri_view)
    : uri(uri_view) {

}

void output_google_cloud_storage::write(const std::string &data) {
    auto bucket_name = uri.host();
    auto file_name = uri.path();
    if (file_name.empty()) {
        BOOST_LOG_TRIVIAL(error) << "empty file name, upload cancelled";
        return;
    }
    file_name.erase(0, 1);

    BOOST_LOG_TRIVIAL(info) << "bucket name: " << bucket_name;
    BOOST_LOG_TRIVIAL(info) << "file name: " << file_name;

    auto writer = client.WriteObject(bucket_name, file_name, google::cloud::storage::ContentType("text/plain"));
    writer << data;
    writer.Close();

    if (writer.metadata()) {
        BOOST_LOG_TRIVIAL(info) << "Successfully created object: " << *writer.metadata();
    } else {
        BOOST_LOG_TRIVIAL(error) << "Error creating object: " << writer.metadata().status();
    }
}

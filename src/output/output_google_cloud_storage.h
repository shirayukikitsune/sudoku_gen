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

#pragma once

#include <boost/url.hpp>
#include "output.h"
#include "google/cloud/storage/client.h"

class output_google_cloud_storage : public output {
public:
    explicit output_google_cloud_storage(const boost::urls::url_view &uri_view);
    ~output_google_cloud_storage() override = default;

    void write(const std::string& data) final;
private:
    ::google::cloud::storage::Client client;
    boost::urls::url uri;
};

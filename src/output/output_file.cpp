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

#include "output_file.h"

output_file::~output_file()
{
    if (outstream.is_open()) {
        outstream.close();
    }
}

bool output_file::open(const std::string &filename)
{
    outstream.open(filename, std::ios::trunc);
    return outstream.is_open() && outstream.good();
}

void output_file::write(const std::string &data)
{
    outstream << data << std::endl;
}

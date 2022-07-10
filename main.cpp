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

#include <fstream>
#include <iostream>
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/manipulators/add_value.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/program_options.hpp>

#include "board.h"
#include "board_generator.h"
#include "digger.h"
#include "solver.h"

namespace po = boost::program_options;

int main(int argc, char** argv)
{
    po::options_description desc("Allowed options");
    desc.add_options()
            ("help,h", "produce help message")
            ("loglevel,l", po::value<int>()->default_value(boost::log::trivial::info), "set default log level")
            ("output,o", po::value<std::string>()->default_value("-"), "set output file [- to print to stdout]")
            ("difficulty,d", po::value<int>()->default_value(5), "set generated difficulty [1 (very easy) to 5 (very hard)]")
            ("sequence,s", po::value<int>()->default_value(2), "set sequence generator [1 (random), 2 (incremental)]");
    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help")) {
        std::cout << desc << "\n\n";
        std::cout << "   Copyright 2022 Bruno Rodrigues Ferreira\n"
                     "\n"
                     "Licensed under the Apache License, Version 2.0 (the \"License\");\n"
                     "you may not use this file except in compliance with the License.\n"
                     "You may obtain a copy of the License at\n"
                     "\n"
                     "   http://www.apache.org/licenses/LICENSE-2.0\n"
                     "\n"
                     "Unless required by applicable law or agreed to in writing, software\n"
                     "distributed under the License is distributed on an \"AS IS\" BASIS,\n"
                     "WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.\n"
                     "See the License for the specific language governing permissions and\n"
                     "limitations under the License.\n";
        return 0;
    }

    if (vm.count("loglevel")) {
        boost::log::core::get()->set_filter(boost::log::trivial::severity >= vm["loglevel"].as<int>());
    }

    board b;
    board_generator g;
    solver s;
    digger d;
    sequence::sequence* seq = nullptr;
    difficulty::difficulty* dif = nullptr;

    if (vm.count("difficulty")) {
        switch (vm["difficulty"].as<int>()) {
        case 1:
            dif = new difficulty::very_easy;
            break;
        case 2:
            dif = new difficulty::easy;
            break;
        case 3:
            dif = new difficulty::medium;
            break;
        case 4:
            dif = new difficulty::hard;
            break;
        case 5:
            dif = new difficulty::very_hard;
            break;
        default:
            BOOST_LOG_TRIVIAL(fatal) << "Invalid difficulty value " << vm["difficulty"].as<int>();
            return 2;
        }
    }

    BOOST_LOG_TRIVIAL(info) << "Using " << dif->name() << " difficulty";

    if (vm.count("sequence")) {
        switch (vm["sequence"].as<int>()) {
        case 1:
            seq = new sequence::random;
            break;
        case 2:
            seq = new sequence::incremental;
            break;
        default:
            BOOST_LOG_TRIVIAL(fatal) << "Invalid sequence value " << vm["sequence"].as<int>();
            return 3;
        }
    }

    BOOST_LOG_TRIVIAL(info) << "Using " << seq->name() << " sequence generator";

    boost::log::add_common_attributes();
    g.generate(&b);

    BOOST_LOG_TRIVIAL(debug) << boost::log::add_value("Board", b.to_string()) << "generated initial seed";

    s.solve(&b);
    BOOST_LOG_TRIVIAL(debug) << boost::log::add_value("Board", b.to_string()) << "generated complete board";

    d.dig(&b, seq, dif);
    BOOST_LOG_TRIVIAL(debug) << boost::log::add_value("Board", b.to_string()) << "dig complete";

    std::ostream *output = &std::cout;
    std::string filename = vm["output"].as<std::string>();
    std::ofstream filestream;
    if (filename != "-") {
        filestream.open(filename.c_str(), std::ios::out | std::ios::trunc);
        output = &filestream;
    }

    *output << b.to_string() << std::endl;

    if (filestream.is_open()) {
        filestream.close();
    }

    return 0;
}

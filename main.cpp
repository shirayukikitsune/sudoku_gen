#include <iostream>
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
            ("difficulty,d", po::value<int>()->default_value(3), "set generated difficulty [1 (very easy) to 5 (very hard)]")
            ("sequence,s", po::value<int>()->default_value(1), "set sequence generator [1 (random), 2 (incremental)]");
    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help")) {
        std::cout << desc << "\n";
        return 1;
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
            std::cout << "Invalid difficulty value " << vm["difficulty"].as<int>() << "\n";
            return 2;
        }
    }

    if (vm.count("sequence")) {
        switch (vm["sequence"].as<int>()) {
        case 1:
            seq = new sequence::random;
            break;
        case 2:
            seq = new sequence::incremental;
            break;
        default:
            std::cout << "Invalid sequence value " << vm["sequence"].as<int>() << "\n";
            return 3;
        }
    }

    std::cout << "Using " << seq->name() << " sequence generator\n";

    g.generate(&b);
    b.print();

    std::cout << std::endl;

    s.solve(&b);
    b.print();

    std::cout << std::endl;

    d.dig(&b, seq, dif);
    b.print();

    std::cout << std::endl;

    return 0;
}

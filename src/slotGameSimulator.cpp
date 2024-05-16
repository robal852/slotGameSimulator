#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "GameSimulator.hpp"
#include "WinningLinesChecker.hpp"
#include "RandomGenerator.hpp"
#include "Timer.hpp"
#include "FruitType.hpp"
#include "FruitTypeHelper.hpp"
#include <set>

void processSymbolsArgument(const std::string &symbols_str) {
    std::vector<FruitType> symbols;
    std::stringstream ss(symbols_str);
    std::string token;
    while (std::getline(ss, token, ',')) {
        try {
            int num = std::stoi(token);
            if (num >= 0 && num <= 7) {
                symbols.push_back(static_cast<FruitType>(num));
            } else {
                std::cerr << "Value out of range [0, 7]." << std::endl;
                exit(1);
            }
        }
        catch (...) {
            std::cerr << "Invalid value." << std::endl;
            exit(1);
        }
    }

    std::vector<FruitType> symbolsIndexedByColumns = FruitTypeHelper::changeIndexingByRowsIntoByColumns(symbols);

    WinningLinesChecker checker = WinningLinesChecker(symbolsIndexedByColumns);
    std::cout << checker.calculateWinnings() << std::endl;
    exit(0);
}


int main(int argc, char *argv[]) {
    if (argc == 3) {
        std::string arg(argv[1]);
        if (arg == "-symbols") {
            processSymbolsArgument(argv[2]);
        } else {
            std::cerr << "Unknown argument: " << arg << std::endl;
        }
    } else if (argc != 7) {
        std::cerr << "Invalid number of arguments" << std::endl;
        std::cerr
                << "Proper usage: ./slotGameSimulator -gamesCount <number_of_games> -startCredit <initial_credit> -creditOutFile <output_file> \n";
        return 1;
    }

    uint64_t gamesCount = 0;
    uint64_t startCredit = 0;
    std::string creditOutFile;

    for (int i = 1; i < argc; i += 2) {
        std::string arg(argv[i]);
        if (arg == "-gamesCount") {
            try {
                gamesCount = std::stoi(argv[i + 1]);
            }
            catch (const std::invalid_argument &e) {
                std::cerr << "Invalid value for gamesCount: " << argv[i + 1] << std::endl;
                return 1;
            }
        } else if (arg == "-startCredit") {
            try {
                startCredit = std::stoi(argv[i + 1]);
            }
            catch (const std::invalid_argument &e) {
                std::cerr << "Invalid value for startCredit: " << argv[i + 1] << std::endl;
                return 1;
            }
        } else if (arg == "-creditOutFile") {
            creditOutFile = argv[i + 1];
            std::ifstream fileExists(creditOutFile);
            if (fileExists.good()) {
                std::cout << "File " << creditOutFile << " already exists." << std::endl;
            } else {
                std::ofstream createFile(creditOutFile);
                if (createFile.is_open()) {
                    std::cout << "File " << creditOutFile << " created successfully." << std::endl;
                    createFile.close();
                } else {
                    std::cerr << "Error creating file " << creditOutFile << std::endl;
                    return 1;
                }
            }
        } else {
            std::cerr << "Unknown argument: " << arg << std::endl;
            return 1;
        }
    }

//if the program has been run correctly now it is time to prepare the simulation

    //Hardcoded fruits on drum rollers like in real life machine
    //You can find the expansion of the abbreviations in the file FruitTypeHelper.hpp
    //From the requirements there can be at most 5 drawn scatters so there should be a distance of at least 3 between scatterers
    std::string code = R"(
S P P O L O W C S O C P S O O C 7 W L G C P P O L O W C C O C P C O O C 7 W L G
C S G C P G O L 7 7 O 7 W G L L S P O W C C G C P G O L 7 7 O 7 W G L L G P O W
W C S O O C L G G S P 7 S 7 L L L 7 L O W C C O O P L G G C P 7 C P L L L 7 L O
G W L L 7 C O G L G C W C C L S 7 O C P G W L L 7 C O G L G C W C C L C 7 O C P
G P C 7 O L C S L 7 L P P P W G O G C W G P C 7 O L C C L 7 L P P P W G O G C W )";

    std::vector<std::vector<FruitType>> rollersSetup = FruitTypeHelper::decodeFruits(code);

    if (FruitTypeHelper::isRollersSetupValid(rollersSetup)) {
        RandomGenerator randomGenerator{};
        GameSimulator simulator(randomGenerator, gamesCount, startCredit, creditOutFile, rollersSetup);

#if 0
        // Function used to determine the initial setting of the marks on the drum rollers
        rollersSetup = simulator.findProperRollersSetup();
#endif
        {
            Timer timer{}; // to measure the simulation time
            simulator.runSimulation();
        }
    }
    return 0;
}


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
		O 7 L O O C C W W P 7 7 7 P S 7 C L S P
		W 7 S L W G C P W 7 L W P C W O L G O C
		G W S P O L S O G W S L O W L C C P C S
		C G L O 7 C G O 7 G P P L C P S O L P S
		G P G C O C C C C O L P W S O L O O P P)";

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


#include "Drum.hpp"
#include "Definitions.hpp"
#include "FruitTypeHelper.hpp"


Drum::Drum(RandomGenerator randomGenerator) : randomGenerator(randomGenerator) {
    rollers.resize(NUM_ROLLERS, std::vector<FruitType>(ROLLER_SIZE));
    generateRandomContent();
}

Drum::Drum(RandomGenerator randomGenerator, const std::vector<std::vector<FruitType>> rollersSetting) : randomGenerator(
        randomGenerator) {
    if (rollersSetting.size() != NUM_ROLLERS) {
        std::cout << "Warninng drumSettings.size() != NUM_ROLLERS \n";
    }

    for (size_t i = 0; i < rollersSetting.size(); ++i) {
        if (rollersSetting[i].size() != ROLLER_SIZE) {
            std::cout << "rollersSetting[" << i << "].size() != ROLLER_SIZE \n";
        }
    }
    rollers = rollersSetting;
}


void Drum::generateRandomContent() {
    for (auto &roller: rollers) {
        for (auto &fruit: roller) {
            fruit = static_cast<FruitType>(randomGenerator.getRandomInt(static_cast<int>(FruitType::Scatter),
                                                                        static_cast<int>(FruitType::Seven)));
        }
    }
}


/*
 Example:
 5 rows, 20 cols
P 7 L O O C C W W P 7 7 7 P S 7 C L S P
W 7 S L W G C P W 7 L W P C W O L G O C
G W S P O L S O G W S L O W L C C P C S
C G L O 7 C G O 7 G P P L C P S O L P S
G P G C O C C C C O L P W S O L O O P P
*/

void Drum::setValue(int row, int col, FruitType value) {
    if (row < 0 || row >= NUM_ROLLERS || col < 0 || col >= ROLLER_SIZE) {
        std::cerr << "Invalid row or column index." << std::endl;
        return;
    }

    if (value == FruitType::Scatter) {
        // Calculate the indices for neighboring columns
        const int leftCol1 = (col - 2 + ROLLER_SIZE) % ROLLER_SIZE;
        const int leftCol2 = (col - 1 + ROLLER_SIZE) % ROLLER_SIZE;
        const int rightCol1 = (col + 2) % ROLLER_SIZE;
        const int rightCol2 = (col + 1) % ROLLER_SIZE;

        // Check if Scatter is too close to other Scatters
        if (rollers[row][leftCol1] == FruitType::Scatter ||
            rollers[row][leftCol2] == FruitType::Scatter ||
            rollers[row][rightCol1] == FruitType::Scatter ||
            rollers[row][rightCol2] == FruitType::Scatter) {
            std::cerr << "Drum::setValue Error: Scatter too close" << std::endl;
            return;
        }
    }

    rollers[row][col] = value;
}


void Drum::displayContent() const {
    for (const auto &roller: rollers) {
        for (const auto &fruit: roller) {
            switch (fruit) {
                case FruitType::Scatter:
                    std::cout << "S ";
                    break;
                case FruitType::Cherry:
                    std::cout << "C ";
                    break;
                case FruitType::Lemon:
                    std::cout << "L ";
                    break;
                case FruitType::Orange:
                    std::cout << "O ";
                    break;
                case FruitType::Plum:
                    std::cout << "P ";
                    break;
                case FruitType::Grape:
                    std::cout << "G ";
                    break;
                case FruitType::Watermelon:
                    std::cout << "W ";
                    break;
                case FruitType::Seven:
                    std::cout << "7 ";
                    break;
            }
        }
        std::cout << std::endl;
    }
}

std::vector<FruitType> Drum::retrieveValuesFromRollers() {
    std::vector<FruitType> result;
    result.reserve(NUM_ROLLERS * 3);

    for (size_t i = 0; i < NUM_ROLLERS; ++i) {
        int index = randomGenerator.getRandomInt(0, ROLLER_SIZE - 1);
        FruitType beforeIndex = rollers[i][(index - 1 + ROLLER_SIZE) % ROLLER_SIZE];
        FruitType atIndex = rollers[i][index];
        FruitType afterIndex = rollers[i][(index + 1) % ROLLER_SIZE];

        result.push_back(beforeIndex);
        result.push_back(atIndex);
        result.push_back(afterIndex);
    }
    return result;
}

void Drum::spinRollers() {
    retrievedValues = retrieveValuesFromRollers();
}

void Drum::showRetrievedValues() const {
    for (auto it: retrievedValues) {
        std::cout << it << " ";
    }
    std::cout << std::endl;
}

std::vector<FruitType> Drum::getRetrievedValues() const {
    return retrievedValues;
}

std::vector<std::vector<FruitType>> Drum::getRollers() const {
    return rollers;
}


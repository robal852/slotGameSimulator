#include "gtest/gtest.h"
#include "../src/Drum.hpp"
#include "../src/FruitTypeHelper.hpp"
#include "../src/RandomGenerator.hpp"


TEST(DrumTest, setValueTest) {
    std::string code = R"(
		O 7 L O O C C W W P 7 7 7 P S 7 C L S P
		W 7 S L W G C P W 7 L W P C W O L G O C
		G W S P O L S O G W S L O W L C C P C S
		C G L O 7 C G O 7 G P P L C P S O L P S
		G P G C O C C C C O L P W S O L O O P P
    )";//You can find the expansion of the abbreviations in the file FruitTypeHelper.hpp

    const std::vector<std::vector<FruitType>> rollersSetup = FruitTypeHelper::decodeFruits(code);
    RandomGenerator randomGenerator = RandomGenerator();
    Drum drum(randomGenerator, rollersSetup);


    // Verify if values are correctly set based on the provided code
    std::vector<std::vector<FruitType>> rollers = drum.getRollers();
    for (size_t i = 0; i < rollers.size(); ++i) {
        for (size_t j = 0; j < rollers[i].size(); ++j) {
            FruitType expectedFruit = rollersSetup[i][j];
            FruitType actualFruit = rollers[i][j];
            EXPECT_EQ(expectedFruit, actualFruit) << "Mismatch at position (" << i << ", " << j << ")";
        }
    }

//---------------------------------------------------------------------------------------------------------------------
    drum.setValue(0, 0, FruitType::Plum);
    rollers = drum.getRollers();


    std::string code2 = R"(
		P 7 L O O C C W W P 7 7 7 P S 7 C L S P
		W 7 S L W G C P W 7 L W P C W O L G O C
		G W S P O L S O G W S L O W L C C P C S
		C G L O 7 C G O 7 G P P L C P S O L P S
		G P G C O C C C C O L P W S O L O O P P
    )";

    const std::vector<std::vector<FruitType>> rollersSetup2 = FruitTypeHelper::decodeFruits(code2);

    for (size_t i = 0; i < rollers.size(); ++i) {
        for (size_t j = 0; j < rollers[i].size(); ++j) {
            FruitType expectedFruit = rollersSetup2[i][j];
            FruitType actualFruit = rollers[i][j];
            EXPECT_EQ(expectedFruit, actualFruit) << "Mismatch at position (" << i << ", " << j << ")";
        }
    }
//---------------------------------------------------------------------------------------------------------------------
//    std::cout<<"before\n";
//    drum.displayContent();
    drum.setValue(0, 19, FruitType::Scatter);//Drum::setValue Error: Scatter too close
//    std::cout<<"after\n";
//    drum.displayContent();
    rollers = drum.getRollers();


    for (size_t i = 0; i < rollers.size(); ++i) {
        for (size_t j = 0; j < rollers[i].size(); ++j) {
            FruitType expectedFruit = rollersSetup2[i][j];
            FruitType actualFruit = rollers[i][j];
            EXPECT_EQ(expectedFruit, actualFruit) << "Mismatch at position (" << i << ", " << j << ")";
        }
    }
//---------------------------------------------------------------------------------------------------------------------

    drum.setValue(2, 3, FruitType::Scatter);//Drum::setValue Error: Scatter too close
    rollers = drum.getRollers();


    const std::vector<std::vector<FruitType>> rollersSetup4 = FruitTypeHelper::decodeFruits(code2);

    for (size_t i = 0; i < rollers.size(); ++i) {
        for (size_t j = 0; j < rollers[i].size(); ++j) {
            FruitType expectedFruit = rollersSetup4[i][j];
            FruitType actualFruit = rollers[i][j];
            EXPECT_EQ(expectedFruit, actualFruit) << "Mismatch at position (" << i << ", " << j << ")";
        }
    }
//---------------------------------------------------------------------------------------------------------------------
}

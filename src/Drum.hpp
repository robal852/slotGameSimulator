#pragma once

#include <iostream>
#include <vector>
#include <random>
#include "FruitType.hpp"
#include "RandomGenerator.hpp"

class Drum {
public:
	Drum(RandomGenerator randomGenerator); //Construct drum with random values in rollers

	Drum(RandomGenerator randomGenerator, const std::vector<std::vector<FruitType>> rollersSetting); //Construct drum with given rollers setting

	void setValue(int row, int col, FruitType value);

	void displayContent() const;

	void spinRollers();

	void showRetrievedValues() const;

	std::vector<FruitType> getRetrievedValues() const;

	std::vector<std::vector<FruitType>> getRollers() const;


private:
	void generateRandomContent();

	std::vector<FruitType> retrieveValuesFromRollers();

	RandomGenerator randomGenerator;
	std::vector<std::vector<FruitType>> rollers;
	std::vector<FruitType> retrievedValues;

};

/*

retrievedValues as a vector of 15 numbers formed by consecutive triples from each roll as shown below:


-----------------------
| 0 | 3 | 6 |  9 | 12 |
-----------------------
| 1 | 4 | 7 | 10 | 13 |
-----------------------
| 2 | 5 | 8 | 11 | 14 |
-----------------------


*/
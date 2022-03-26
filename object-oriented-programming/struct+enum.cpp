#include<iostream>

using namespace std;


struct part
{
	int modelNumber_;
	int partNumber_;
	float cost_;
};

struct Distance
{
	int meters_;
	int santimeters_;
};

struct Room
{
	Distance length_;
	Distance width_;
};


int main()
{
	part part_1;
	part_1.modelNumber_ = 938725;
	part_1.partNumber_ = 233;
	part_1.cost_ = 14.94;

	Room sleeping; 
	sleeping = { {3, 54}, {4, 87} };

	// обращение к полям структурной переменной `sleeping`;
	sleeping.length_.meters_ = 2;

	enum Suits { clubs, diamonds, hearts, spades  = 10, groves}; // groves = 11
	Suits suit_1 = clubs;
	Suits suit_2 = suit_1;
	cout << suit_2 << '\n';

	return 0;
}


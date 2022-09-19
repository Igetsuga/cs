/*****************************************************************//**
 * \file   Computer.h
 * \brief  Заголовочный файл класса `Computer`. Содержит объявление всех 
 * методов соответсвтующего класса.
 * 
 * \author averu
 * \version 1.0.0
 * \date   September 2022
 *********************************************************************/
#pragma once
#include <iostream>
#include <fstream>
#include <algorithm>

/**
 * \brief Основной класс, таблица 1.2 Вариант 23.
 */
class Computer {
public:

	Computer (std::string model,
			  double price,
			  int numCores,
			  int ram,
			  double diaganal);

	Computer (const Computer &other);

	Computer& operator= (const Computer &other);

	~Computer();



	// GetValue

	std::string GetModel() const noexcept;

	double GetPrice() const noexcept;

	int GetNumCores() const noexcept;

	int GetRam() const noexcept;

	double GetDiagonal() const noexcept;



	bool operator== (const Computer &other) const noexcept;
	bool operator!= (const Computer &other) const noexcept;
	bool operator> (const Computer &other) const noexcept;
	bool operator< (const Computer &other) const noexcept;
	bool operator>= (const Computer &other) const noexcept;
	bool operator<= (const Computer &other) const noexcept;



	friend std::ostream &operator<< (std::ostream &output, const Computer &computer);



private:
	std::string _model;
	double      _price;
	int         _numCores;
	int         _ram;
	double      _diagonal;
};


/*****************************************************************//**
 * \file   Computer.cpp
 * \brief  Файл	определения класса `Computer`.
 *
 * Вспомогательный класс для практической работы по ООП-2-1.
 * Объявление класса смотри в файле `Computer.h`.
 *
 * \author Sirazetdinov Rustem 
 * \version 1.0.0
 * \date   September 2022
 *********************************************************************/
#include "Computer.h"

/**
* Конструктор по умолчанию.
*
* \param brand
* \param price
* \param numCores
* \param ram
* \param diaganal
*/
Computer::Computer (std::string model,
					double price,
					int numCores,
					int ram,
					double diaganal) {
	_model = model;
	_price = price;
	_numCores = numCores;
	_ram = ram;
	_diagonal = diaganal;
}

/**
* Конструктор копий.
*
* \warning Определен компилятором.
* \param other
*/
Computer::Computer (const Computer &other) = default;

/**
* Перегрузка оператора `operator=`.
*
* \warning Определен компилятором.
*
* \param other
* \return Новый объект класса, поля которого равны полям входящего объекта.
*/
Computer &Computer::operator= (const Computer & other) = default;

/**
 * Деструктор.
 * 
 * \warning Определен компилятором.
 * 
 */
Computer::~Computer() = default;



// GetValue	

std::string Computer::GetModel() const noexcept { return _model; }

double Computer::GetPrice() const noexcept { return _price; }

int Computer::GetNumCores() const noexcept { return _numCores; }

int Computer::GetRam() const noexcept { return _ram; }

double Computer::GetDiagonal() const noexcept { return _diagonal; }

/**
* Перегрузка оператора `operator==`.
*
*
* \param other
* \return `true`, если все поля экземплятров класса совпадают, в противном случае - `false`.
*/
bool Computer::operator== (const Computer & other) const noexcept {
	if ( _model == other._model &&
		_price == other._price &&
		_numCores == other._numCores &&
		_ram == other._ram &&
		_diagonal == other._diagonal ) {
		return true;
	}


	return false;
}

/**
* Перегрузка оператора `operator!=`.
*
*
* \param other
* \return `true`, если хотя бы одно поле одного экземпляра класса отлично от этого же поля
*  другого экземпляра класса, в противном случае - `false`.
*/
bool Computer::operator!= (const Computer & other) const noexcept {
	return !(*this == other);
}

/**
* Перегрузка оператора `operator>`.
*
* Сравнивает объекты класса `Computer` в соответствии с приоритетом полей класса.
*
* Цепочка приоритета: _model > _price > _diaganal > _numCores > _ram
*
* \param other
* \return `true`, если поле объекта `*this` имеет больший приоритет, если приоритеты одного
* одних атрибутов равны, сравнение спускается по цепочке приоритетов, иначе `false`.
*/
bool Computer::operator> (const Computer & other) const noexcept {

	std::string modelLowerCase = _model;
	std::for_each(modelLowerCase.begin(), modelLowerCase.end(),
				  [](unsigned char c) { return std::tolower(c); }); 


	std::string otherModelLowerCase = other._model;
	std::for_each(otherModelLowerCase.begin(), otherModelLowerCase.end(),
				  [](unsigned char c) { return std::tolower(c); });


	if ( modelLowerCase > otherModelLowerCase ) {
		return true;
	}
	else if ( modelLowerCase == otherModelLowerCase ) {
		if ( _price > other._price ) {
			return true;
		}
		else if ( _price == other._price ) {
			if ( _diagonal > other._diagonal ) {
				return true;
			}
			else if ( _diagonal == other._diagonal ) {
				if ( _numCores > other._numCores ) {
					return true;
				}
				else if ( _ram > other._ram ) {
					return true;
				}
			}
		}
	}


	return false;
}

/**
* Перегрузка оператора `operator<`.
*
*
* \param other
* \return Противоположное значение оператора `operator>`.
*/
bool Computer::operator< (const Computer & other) const noexcept {
	return (!(*this > other) && !(*this != other));
}

/**
 * Перегрузка оператора `operator>=`.
 *
 * \param other
 * \return `true` если экземпляры имеют одинаковые значения атрубутов
 * или первый имеет более высокий приоритет, иначе `false`.
 */
bool Computer::operator>= (const Computer & other) const noexcept {
	return (*this > other || *this == other);
}
/**
 * Перегрузка оператора `operator<=`.
 *
 * \param other
 * \return `true` если экземпляры имеют одинаковые значения атрубутов
 * или первый имеет более низкий приоритет, иначе `false`.
 */
bool Computer::operator<= (const Computer & other) const noexcept {
	return (!(*this > other) || *this == other);
}

/**
* Перегрузка оператора `operator<<`.
*
* \param output
* \param computer
*
* \return Ссылку на стандартный поток вывода.
*/
std::ostream &operator<< (std::ostream & output, const Computer & computer) {
	if ( typeid(output).name() != typeid(std::ofstream).name() ) {
		output << "{ " << computer.GetModel() << "; " << computer.GetPrice() << "; "
			<< computer.GetDiagonal() << "; " << computer.GetNumCores() << "; " << computer.GetRam() << " }";
	}
	else {
		output << '\n' << computer.GetModel() << " " << computer.GetPrice() << " "
			<< computer.GetDiagonal() << " " << computer.GetNumCores() << " " << computer.GetRam() << '\n';
	}


	return output;
}


/*****************************************************************//**
 * \file   Computer.cpp
 * \brief  Файл	определения класса `Computer`.
 * 
 * Вспомогательный класс для практической работы по ООП-2-1.
 * Опеределение класса смотри в файле `Computer.h`.
 * 
 * \author averu
 * \version 1.0.0
 * \date   September 2022
 *********************************************************************/
#include "Computer.h"

/**
* Конструктор по умолчанию класса `Computer`.
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
* Перегрузка оператора `=`.
*
* \warning Определен компилятором.
*
* \param other
* \return Новый объект класса, поля которого равны полям входящего объекта.
*/
Computer &Computer::operator= (const Computer &other) = default;

Computer::~Computer() = default;



// GetValue	

std::string Computer::GetModel() const noexcept { return _model; }

double Computer::GetPrice() const noexcept { return _price; }

int Computer::GetNumCores() const noexcept { return _numCores; }

int Computer::GetRam() const noexcept { return _ram; }

double Computer::GetDiagonal() const noexcept { return _diagonal; }

/**
* Перегрузка оператора `==`.
*
*
* \param other
* \return Возвращает `true`, если поля экземплятров класса совпадают, в противном случае - `false`.
*/
bool Computer::operator== (const Computer &other) const noexcept {
	if ( _model == other._model &&
		_price == other._price &&
		_numCores == other._numCores&&
		_ram == other._ram &&
		_diagonal== other._diagonal ) {
		return true;
	}


	return false;
}

bool Computer::operator!= (const Computer &other) const noexcept {
	return !(*this == other);
}

/**
* Перегрузка оператора >.
*
* Сравнивает объекты класса `Computer` в соответствии с приоритетом полей класса.
*
* Цепочка приоритета: _model -> _price -> _diaganal -> _numCores -> _ram
*
* \param other
* \return `true`, если поле объекта `*this` имеет больший приоритет, если приоритеты одного
* одних атрибутов равны, сравнение спускается по цепочке приоритетов, иначе `false`.
*/
bool Computer::operator> (const Computer &other) const noexcept {
	
	std::string brandLowerCase = _model;
	//std::transform(brandLowerCase.begin(), brandLowerCase.end(), brandLowerCase.begin(),
	// 			   [](unsigned char c) { return std::tolower(c); }); //< преобразование поля *this._model в нижний регистр
	std::for_each(brandLowerCase.begin(), brandLowerCase.end(),
				  [](unsigned char c) { return std::tolower(c); }); //< преобразование поля *this._model в нижний регистр

	std::string otherBrandLowerCase = other._model;
	//std::transform(otherBrandLowerCase.begin(), otherBrandLowerCase.end(), otherBrandLowerCase.begin(),
	//			   [](unsigned char c) { return std::tolower(c); }); //< преобразование поля other._model в нижний регистр
	std::for_each(otherBrandLowerCase.begin(), otherBrandLowerCase.end(),
				  [](unsigned char c) { return std::tolower(c); });
	
	if ( brandLowerCase > otherBrandLowerCase ) {
		return true;
	}
	else if ( brandLowerCase == otherBrandLowerCase ) {
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
* Перегрузка оператора <.
*
*
* \param other
* \return Противоположное значение оператора >.
*/
bool Computer::operator< (const Computer &other) const noexcept {
	return ( !(*this > other) && !(*this != other) );
}

/**
 * Перегрузка оператора >=.
 * 
 * \param other
 * \return `true` если экземпляры имеют одинаковые значения атрубутов
 * или первый имеет более высокий приоритет иначе `false`.
 */
bool Computer::operator>= (const Computer &other) const noexcept {
	return (*this > other || *this == other);
}
/**
 * Перегрузка оператора <=.
 *
 * \param other
 * \return `true` если экземпляры имеют одинаковые значения атрубутов
 * или первый имеет более низкий приоритет иначе `false`.
 */
bool Computer::operator<= (const Computer &other) const noexcept {
	return (!(*this > other) || *this == other);
}

/**
* Перегрузка оператора <<.
*
* \param output
* \param computer
*
* \return output
*/
std::ostream &operator<< (std::ostream &output, const Computer &computer) {
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


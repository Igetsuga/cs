#pragma once
#define nline '\n'
#include <iostream>
#include <fstream>
#include <algorithm>

/**
 * \brief Класс для p.2.
 *
 * Класс был создан по таблице 1.2.
 */
class Bike {
public:

	/**
	 * Конструктор по умолчанию.
	 *
	 *
	 * \param brand
	 * \param bikeType
	 * \param breaksType
	 * \param wheelCount
	 * \param wheelDiameter
	 * \param isAbsorber
	 * \param isAdult
	 */
	Bike (std::string brand = "unknown", std::string bikeType = "unknown",
		  std::string breaksType = "unknown", int wheelCount = 2,
		  float wheelDiameter = 26, bool isAbsorber = 0,
		  bool isAdult = 1) {
		_brand = brand;
		_bikeType = bikeType;
		_breaksType = breaksType;
		_wheelCount = wheelCount;
		_wheelDiameter = wheelDiameter;
		_isAbsorber = isAbsorber;
		_isAdult = isAdult;
	}


	/**
	 * Конструктор копий.
	 *
	 * \warning Опеределен компилятором.
	 *
	 * \param other
	 */
	Bike (const Bike &other) = default;

	/**
	 * Перегрузка оператора `=`.
	 *
	 * \warning Определен компилятором.
	 *
	 * \param other
	 * \return Новый объект класса, поля которого равны полям входящего объекта.
	 */
	Bike &operator= (const Bike &other) = default;

	/**
	 * Деструктор.
	 *
	 * \warning Деструктор определен компилятором и не является виртуальным.
	 *
	 */
	~Bike() = default;



	// GetValue

	std::string GetBrand() const noexcept { return _brand; }

	int GetWheelCount() const noexcept { return _wheelCount; }

	float GetWheelDiameter() const noexcept { return _wheelDiameter; }

	std::string GetBikeType() const noexcept { return _bikeType; }

	std::string GetBreaksType() const noexcept { return _breaksType; }

	bool GetIsAbsorber() const noexcept { return _isAbsorber; }

	bool GetIsAdult() const noexcept { return _isAdult; }



	/**
	 * Перегрузка оператора `==`.
	 *
	 *
	 * \param other
	 * \return Возвращает `true`, если поля экземплятров класса совпадают, в противном случае - `false`.
	 */
	bool operator== (const Bike &other) const noexcept {
		if ( _brand == other._brand &&
			_bikeType == other._bikeType &&
			_breaksType == other._breaksType &&
			_wheelCount == other._wheelCount &&
			_wheelDiameter == other._wheelDiameter &&
			_isAbsorber == other._isAbsorber &&
			_isAdult == other._isAdult ) {
			return true;
		}


		return false;
	}

	/**
	 * Перегрузка оператора >.
	 *
	 * Сравнивает объекты класса `Bike` в соответствии с приоритетом полей класса.
	 *
	 * Цепочка приоритета: _wheelDiameter -> _wheelCount -> _brand(lexi-graph) -> ...
	 *
	 * \param other
	 * \return `true`, если поле объекта `*this` имеет больший приоритет, если приоритеты равны,
	 * сравнение спускается по цепочки приоритетов, иначе `false`.
	 * \warning Реализация с ошибкой.
	 */
	bool operator> (const Bike &other) const noexcept {
		if ( _wheelDiameter > other._wheelDiameter ) {
			return true;
		}
		else if ( _wheelDiameter == other._wheelDiameter ) {
			if ( _wheelCount > other._wheelCount ) {
				return true;
			}
			else if ( _wheelCount == other._wheelCount ) {

				std::string brandLowerCase = _brand;
				std::transform(brandLowerCase.begin(), brandLowerCase.end(), brandLowerCase.begin(),
							   [](unsigned char c) { return std::tolower(c); }); //< преобразование поля *this._brand в нижний регистр

				std::string otherBrandLowerCase = other._brand;
				std::transform(otherBrandLowerCase.begin(), otherBrandLowerCase.end(), otherBrandLowerCase.begin(),
							   [](unsigned char c) { return std::tolower(c); }); //< преобразование поля other._brand в нижний регистр

				// other way
				/*std::string brandLowerCase = _brand;
				std::for_each(brandLowerCase.begin(), brandLowerCase.end(),
							  [](unsigned char c) { return std::tolower(c); });

				std::string otherBrandLowerCase = other._brand;
				std::for_each(otherBrandLowerCase.begin(), otherBrandLowerCase.end(),
							  [](unsigned char c) { return std::tolower(c); });*/

				if ( brandLowerCase > otherBrandLowerCase ) {
					return true;
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
	bool operator< (const Bike &other) const noexcept {
		return (!(*this > other) && !(*this == other));
	}

	bool operator>= (const Bike &other) const noexcept {
		return (*this > other || *this == other);
	}

	bool operator<= (const Bike &other) const noexcept {
		return (!(*this > other) || *this == other);
	}


	/**
	 * Перегрузка оператора <<.
	 *
	 * \param output
	 * \param bike
	 *
	 * \return output
	 */
	friend std::ostream &operator<< (std::ostream &output, const Bike &bike);



private:
	std::string _brand;
	std::string _bikeType;
	std::string _breaksType;
	int    _wheelCount;
	float  _wheelDiameter; // inch 
	bool   _isAbsorber;
	bool   _isAdult;
};

/**
 * Перегрузка оператора<<.
 *
 * \param output
 * \param bike
 *
 * \return output
 */
std::ostream &operator<< (std::ostream &output, const Bike &bike) {
	if ( typeid(output).name() != typeid(std::ofstream).name() ) {
		output << "{ " << bike.GetWheelDiameter() << "; " << bike.GetWheelCount() << "; "
			<< bike.GetBrand() << "; " << bike.GetBikeType() << "; " << bike.GetBreaksType() << "; "
			<< bike.GetIsAbsorber() << "; " << bike.GetIsAdult() << " }";
	}
	else {
		output << nline << bike.GetWheelDiameter() << " " << bike.GetWheelCount() << " "
			<< bike.GetBrand() << " " << bike.GetBikeType() << " " << bike.GetBreaksType() << " "
			<< bike.GetIsAbsorber() << " " << bike.GetIsAdult() << nline;
	}


	return output;
}


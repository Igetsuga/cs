/*******************************************************************
 * @file 
 * \brief  Практическая работа 1
 * 
 * \author Sirazetdinov Rustem
 * \date   August 2022
 *********************************************************************/

#define nline '\n'
#include <iostream>
#include <fstream>


#include <list>
#include <iterator>
#include <algorithm>


/**
 * \brief Класс для p.2.
 * 
 * Класс был создан по таблице 1.2 из методического пособия по ООП/2. 
 */
class Bike 
{
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
				
				std::string otherBrandLowerCasae = other._brand;
				std::transform(otherBrandLowerCasae.begin(), otherBrandLowerCasae.end(), otherBrandLowerCasae.begin(),
							   [](unsigned char c) { return std::tolower(c); }); //< преобразование поля other._brand в нижний регистр

				// other way
				/*std::string brandLowerCase = _brand;
				std::for_each(brandLowerCase.begin(), brandLowerCase.end(),
							  [](unsigned char c) { return std::tolower(c); });

				std::string otherBrandLowerCasae = other._brand;
				std::for_each(otherBrandLowerCasae.begin(), otherBrandLowerCasae.end(),
							  [](unsigned char c) { return std::tolower(c); });*/
				
				if ( brandLowerCase > otherBrandLowerCasae ) {
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
	 * \return Противоположное значение оператора>
	 */
	bool operator< (const Bike &other) const noexcept {
		return !(*this > other);
	}

	bool operator>= (const Bike &other) const noexcept {
		return (*this > other || *this == other);
	}

	bool operator<= (const Bike &other) const noexcept {
		return ( !(*this > other) || *this == other );
	}


	/**
	 * Перегрузка оператора<<.
	 * 
	 * \param output
	 * \param bike
	 * 
	 * \return output
	 */
	friend std::ostream& operator<< (std::ostream &output, const Bike &bike);
	


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
std::ostream& operator<< (std::ostream &output, const Bike &bike) {
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



/**
 * Помещает объект в контейнер std::list.
 * 
 * Объект помещается в контейнер std::list при этом контейнер остается отсортированным.
 * 
 * \param list
 * \param object
 */
template<class Type> void push_ (std::list<Type> &list, const Type &object) {
	
	auto it_pos = list.begin();
	// std::list<Type>::iterator it_pos = list.begin();

	while ( it_pos != list.end() ) {
		// >= лучше чем >, т.к. при > вставка сильно замедляется, 
		// если все объекты в списке равны между собой
		if ( *it_pos >= object ) { break; }
		it_pos++;
	}

	list.insert(it_pos, object);
}

/**
* \
 * Спецификация шаблона функции push_.
 * 
 * Данная функция является спецификацией шаблона функции. Она предназначена для работы с экземплярами класса `Bike`,
 * поскольку требуется расположить экземпляры этого класса в контейнере с сортировкой по убыванию.
 *  
 * \param bikeList
 * \param bike
 */
void push_ (std::list<Bike> &bikeList, const Bike &bike) {
	auto it_pos = bikeList.begin();
	// std::list<Type>::iterator it_pos = list.begin();

	while ( it_pos != bikeList.end() ) {
		// >= лучше чем >, т.к. при > вставка сильно замедляется, 
		// если все объекты в списке равны между собой
		if ( *it_pos <= bike ) { break; }
		it_pos++;
	}

	bikeList.insert(it_pos, bike);
}



/**
 * Удаление элемента из контейнера std::list.
 * 
 * Функция удаляет элемент из контейнера и возвращает элемент, который имеет наибольший приоритет,
 * поскольку контейнер отсортирован, наибольший приоритет имеет объект, стоящий самым первым. 
 * Если после удаления элемента из контейнера, контейнер оказывается пустым, то возвращается 
 * последний удаленный объект.
 * 
 * \param list
 * \param pos
 * \return Объект с наибольшим приоритетом.
 * \warning Объект типа `Type` обязательно должен иметь конструктор по умолчанию, иначе UB!
 */
template<class Type> Type pop_ (std::list<Type> &list, const int &pos = 0) {
	
	// инициализация по умолчанию +-
	Type object_r_temp;

	if ( pos == 0 ) {
		object_r_temp = list.front();
		list.pop_front(); 
	}
	else if ( pos == list.size() ) {
		object_r_temp = list.back();
		list.pop_back();
	}
	else {
		auto it_pos = std::next(list.begin(), pos);
		// or / auto it_pos = list.begin(); std::advance(it_pos, pos); 
	    // or / std::list<Type>::iterator it_pos = std::next(list.begin(), pos);
		object_r_temp = *it_pos;
		list.erase(it_pos);
	}


	if ( !list.empty() ) {
		return list.back(); // != return *list.end() == nullptr;
	}
	else {
		return object_r_temp;
	}
}


/**
 * Фильтрация объектов контейнера по функции-ключу.
 * 
 * \param list
 * \param *func_key
 * \return Новый контейнер, элементы которого удовлетворяют функции-ключу.
 */
template<class Type> std::list<Type> filter (const std::list<Type> &list,
											 int (*func_key)(const Type &)) 
{
	std::list<Type> ListResult;

	// for (std::list<Type>::iterator it_pos = list.begin(); it_pos != list.end(); it_pos++) {...}
	for ( auto object : list ) {
		if ( func_key(object) ) { ListResult.push_back(object); }
	}


	return ListResult;
}

/**
 * Вывод содержимого контейнера.
 * 
 * Отправляет каждый элемент контейнера в поток вывода std::ostream.
 * 
 * \param list
 */
template<class Type> void print (const std::list<Type> &list) {	
	std::cout << "{";
	// for (std::list<Type>::iterator it_pos = list.begin(); it_pos != list.end(); it_pos++) {...}
	for ( auto object : list ) {
		std::cout << " " << object;
	}
	std::cout << "}; " << nline;
}

/**
 * Определение факторила четного числа.
 * 
 * Функция опеределяет является ли заданное число факториалом четного число, 
 * и находит это число, если это так.
 * 
 * \param value_
 * \return 0, если входное число не является факториалом четного числа, иначе само число,
 *  факториалом которого является входное число.
 */
int IsFactorialOfEven (const int &value_) {
	int value = value_; int div = 1;
	
	while ( value > 1 ) {
		div++;

		if ( value % div == 0 ) {
			value = value / div; 
		} 
		else { break; }
	}

	
	if ( value == 1 && div % 2 == 0 ) { return div; }
	return 0;
}



int main()
{
	// int value = 2;
	// while ( value != -1) {
	// 	std::cin >> value;
	// 	std::cout << IsFactorialOfEven(value) << nline;
	// }



	// -------------- p.1 --------------
	// Cоздаем лист с элементами типа `int`
	std::list<int> myList = {215, 507, 668, 680, 1004, 1207, 1550, 2854,
		2972, 3091, 3209, 3706, 4078, 4482, 4925, 5458, 5892, 6476, 6896,
		7076, 7268, 7373, 8168, 8443, 9406};
	
	// Проверка функции `print` для объектов типа std::list<Type>
	print(myList);
	

	// Добавим в лист некоторое количество элементов. Проверим, останется ли
	// он отсортированным
	push_(myList, 2);           // = 2!
	push_(myList, 24);          // = 4!
	push_(myList, 720);         // = 6!
	push_(myList, 40320);       // = 8!
	push_(myList, 3628800);     // = 10!
	push_(myList, 479001600);   // = 12!
	push_(myList, 362880);      // = 9!
	push_(myList, 120);         // = 5!
	push_(myList, 1);           // = 1!

	if ( std::is_sorted(myList.begin(), myList.end()) ) { std::cout << "SORTED" << nline; }
	else { std::cout << "UNSORTED" << nline; }
	
	print(myList);

	// Удалим из листа несколько значений
	auto hValue_temp = pop_(myList, 1); std::cout << nline << hValue_temp << " ";
	hValue_temp = pop_(myList, 9); std::cout << nline << hValue_temp << " ";
	hValue_temp = pop_(myList, myList.size() - 1); std::cout << nline << hValue_temp << " ";
	std::cout << nline << nline;

	if ( std::is_sorted(myList.begin(), myList.end()) ) { std::cout << "SORTED" << nline; }
	else { std::cout << "UNSORTED" << nline; }

	print(myList);
	
	
	// Выделим из нашего листа новый, элементы которого представляют собой
	// факториалы четных чисел.
	// int (*func_key)(const int &) = nullptr; func_key = &IsFactorialOfEven;
	int (*func_key)(const int &) = IsFactorialOfEven;

	std::list<int> newList = filter(myList, func_key);
	print(newList);

	myList.clear();


	// -------------- p.2 --------------
	std::list<Bike> bikeList;

	Bike bikeSimple("simple", "mountain", "mechamnical", 2, 24, false, false);
	Bike bikeSimpleUPG("Simple", "mountain", "disc", 2, 24, false, false);
	// std::cout << nline << bikeSimple << nline << bikeSimpleUPG << nline;
	// bikeSimple > bikeSimpleUPG ? std::cout << nline << "1" : std::cout << nline << "2";

	Bike bikeUltra("ULTRA", "road", "hydDisc", 2, 29, true, true);
	Bike bikeMedium("Medium", "urban", "disc", 2, 27, true, true);
	Bike bikeHigh("High", "mountain", "disc", 2, 27.5, true, true);

	push_(bikeList, bikeSimple); 
	push_(bikeList, bikeSimpleUPG);
	push_(bikeList, bikeUltra);
	push_(bikeList, bikeHigh);
	push_(bikeList, bikeMedium);

	print(bikeList);
	
	std::cout << pop_(bikeList, 2);


	return 0;
}
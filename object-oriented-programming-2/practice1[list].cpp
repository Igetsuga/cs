#define nline '\n'
#include <iostream>
#include <fstream>


//  
#include <list>
#include <iterator>
#include <algorithm>



class Bike {
public:
	// default constructor
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

	// copy constructor
	Bike (const Bike &other) = default;

	// operator=
	Bike &operator= (const Bike &other) = default;

	// default destructor
	~Bike() = default;


	// Get
	std::string GetBrand() const noexcept { return _brand; }

	int GetWheelCount() const noexcept { return _wheelCount; }

	float GetWheelDiameter() const noexcept { return _wheelDiameter; }

	std::string GetBikeType() const noexcept { return _bikeType; }

	std::string GetBreaksType() const noexcept { return _breaksType; }

	bool GetIsAbsorber() const noexcept { return _isAbsorber; }

	bool GetIsAdult() const noexcept { return _isAdult; }




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
							   [](unsigned char c) { return std::tolower(c); });
				
				std::string otherBrandLowerCasae = other._brand;
				std::transform(otherBrandLowerCasae.begin(), otherBrandLowerCasae.end(), otherBrandLowerCasae.begin(),
							   [](unsigned char c) { return std::tolower(c); });

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

	bool operator< (const Bike &other) const noexcept {
		return !(*this > other);
	}

	bool operator>= (const Bike &other) const noexcept {
		return (*this > other || *this == other);
	}

	bool operator<= (const Bike &other) const noexcept {
		return ( !(*this > other) || *this == other );
	}


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



// TODO написать документацию
template<class Type> void push_ (std::list<Type> &list_, const Type &object) {
	
	auto it_pos= list_.begin();
	// std::list<Type>::iterator it_pos = list_.begin();

	while ( it_pos != list_.end() ) {
		// >= лучше чем >, т.к. при > вставка сильно замедляется, 
		// если все объекты в списке равны между собой
		if ( *it_pos >= object ) { break; }
		it_pos++;
	}

	list_.insert(it_pos, object);
}

void push_ (std::list<Bike> &bikeList, const Bike &bike) {
	auto it_pos = bikeList.begin();
	// std::list<Type>::iterator it_pos = list_.begin();

	while ( it_pos != bikeList.end() ) {
		// >= лучше чем >, т.к. при > вставка сильно замедляется, 
		// если все объекты в списке равны между собой
		if ( *it_pos <= bike ) { break; }
		it_pos++;
	}

	bikeList.insert(it_pos, bike);
}


// TODO написать документацию
// TODO отдельная быстрая реализация удаления с начала и с конца 
template<class Type> Type pop_ (std::list<Type> &list_, const int &pos = 0) {
	
	// инициализация по умолчанию +-
	Type object_r_temp;

	if ( pos == 0 ) {
		object_r_temp = list_.front();
		list_.pop_front(); 
	}
	else if ( pos == list_.size() ) {
		object_r_temp = list_.back();
		list_.pop_back();
	}
	else {
		auto it_pos = std::next(list_.begin(), pos);
		// or / auto it_pos = list_.begin(); std::advance(it_pos, pos); 
	    // or / std::list<Type>::iterator it_pos = std::next(list_.begin(), pos);
		object_r_temp = *it_pos;
		list_.erase(it_pos);
	}


	if ( !list_.empty() ) {
		return list_.back(); // != return *list_.end() == nullptr;
	}
	else {
		return object_r_temp;
	}
}


// TODO написать документацию
template<class Type> std::list<Type> filter (const std::list<Type> &list_,
											 int (*func_key)(const Type &)) {
	std::list<Type> ListResult;

	// for (std::list<Type>::iterator it_pos = list_.begin(); it_pos != list_.end(); it_pos++) {...}
	for ( auto object : list_ ) {
		if ( func_key(object) ) { ListResult.push_back(object); }
	}


	return ListResult;
}

// TODO написать документацию
template<class Type> void print (const std::list<Type> &list_) {	
	std::cout << "{";
	// for (std::list<Type>::iterator it_pos = list_.begin(); it_pos != list_.end(); it_pos++) {...}
	for ( auto object : list_ ) {
		std::cout << " " << object;
	}
	std::cout << "}; " << nline;
}

// TODO написать документацию
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
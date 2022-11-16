﻿#include <map>

#include <utility>
#include <string>
#include <iostream>
#include <vector>





namespace ds_lib {

	// ---------------------------------------------------------------------------------------------
	// ---------------------------------------------------------------------------------------------


template <typename Type1, typename Type2> class ipair {
public:

	virtual Type1 first () const noexcept = 0;
	virtual Type2 second () const noexcept = 0;

};

// ---------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------


template<typename Type1, typename Type2> class pair : ipair<Type1, Type2> {
public:

	pair (const Type1 &value1, const Type2 &value2) {
		_value1 = value1;
		_value2 = value2;
	}

	pair (const pair &pair_other) {
		_value1 = pair_other._value1;
		_value2 = pair_other._value2;
	}



	virtual ~pair() = default;



	Type1 first ()  const noexcept override final { return _value1; }
	Type2 second () const noexcept override final { return _value2; }



	bool operator == (const pair &pair_other) const noexcept {
		return (_value1 == pair_other._value1 && _value2 == pair_other._value2 ? true : false);
	}

	bool operator > (const pair &pair_other) const noexcept {
		if ( _value1 > pair_other._value1 ) {
			return true;
		}
		else if ( _value1 == pair_other._value1 ) {
			return (_value2 > pair_other._value2 ? true : false);
		}


		return false;
	}

	bool operator < (const pair &pair_other) const noexcept {
		return !(*this > pair_other);
	}

	bool operator >= (const pair &pair_other) const noexcept {
		return (this > pair_other || this == pair_other);
	}

	bool operator <= (const pair &pair_other) const noexcept {
		return (this < pair_other || this == pair_other);
	}



protected:
	Type1 _value1;
	Type2 _value2;
};

template<typename Type1, typename Type2>
std::ostream &operator<< (std::ostream &output, const pair<Type1, Type2> &pair) {
	// output << '\n' << "first: " << pair.first() << '\n' << "second: " << pair.second() << '\n';
	output << '\n' << "{first, second} : {" << pair.first() << ", " << pair.second() << "}; " << '\n';


	return output;
}


template<typename Type1, typename Type2>
ds_lib::pair<Type1, Type2> &make_pair (const Type1 &value1, const Type2 &value2) noexcept {
	return ds_lib::pair<Type1,Type2>(value1, value2);
}

template<typename Type1, typename Type2>
std::pair<Type1, Type2> &make_std_pair (const Type1 &value1, const Type2 &value2) noexcept {
	return std::make_pair(value1, value2);
}

// ---------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------


class bike_key : public ds_lib::pair<std::string, int> {
public:

	bike_key (const std::string &brand, int diameter) : pair (brand, diameter) {};

	virtual ~bike_key() = default;

};


// ---------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------


class bike_value : public ds_lib::pair<std::string, bool> {
public:

	bike_value (const std::string &type, bool is_absorb) : pair (type, is_absorb) {};

	virtual ~bike_value() = default;
};


// ---------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------


}


// ---------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------------
// --------------------------------------------task2--------------------------------------------
// ---------------------------------------------------------------------------------------------
// Почему срабатывает деструктор, почему так не работает
//ds_lib::bike_value &find_value (ds_lib::bike_key &key, std::map<ds_lib::bike_key, ds_lib::bike_value> &map) noexcept {
ds_lib::bike_value find_value (ds_lib::bike_key &key, std::map<ds_lib::bike_key, ds_lib::bike_value> &map) noexcept {
	ds_lib::bike_value answer("NONE", "0");
	
	for ( const auto &element : map ) {
		if ( element.first == key ) {
			answer = element.second;
			break;
		}
	}


	return answer;
}

const ds_lib::bike_key find_key (ds_lib::bike_value &value, std::map<ds_lib::bike_key, ds_lib::bike_value> &map) noexcept {
	ds_lib::bike_key answer("NONE", -1);
	for ( const auto &element : map ) {
		if ( element.second == value ) {
			answer = element.first;
			break;
		}
	}


	return answer;
}

const std::string foo (std::vector<std::string> vector) {
	std::string answer;
	for ( const auto &element : vector ) {
		if ( element == "key" ) {
			answer = element;
			break;
		}
	}


	return answer;
}


// ---------------------------------------------------------------------------------------------
// --------------------------------------------task3--------------------------------------------
// ---------------------------------------------------------------------------------------------
template<typename Type1, typename Type2> void print_iter (std::map<Type1, Type2> &map) {
	auto itt = map.begin();

	while ( itt != map.end() ) {
		std::cout << '\n' << (*itt).second;
		itt++;
	}
}


// ---------------------------------------------------------------------------------------------
// --------------------------------------------task4--------------------------------------------
// ---------------------------------------------------------------------------------------------

bool func_key (const ds_lib::bike_value &value, const int &threshold = 0) {
	return (value.second() > threshold);
}

using func = bool(*)(const ds_lib::bike_value&, const int&);
func func_task4 = &func_key;

//tempalate<typename Type1, typename Type2> 
std::map<ds_lib::bike_key, ds_lib::bike_value> &filter (std::map<ds_lib::bike_key, ds_lib::bike_value> map,
												  bool(*func_key)(const ds_lib::bike_value&, const int&)) {
	std::map<ds_lib::bike_key, ds_lib::bike_value> map_result;
	
	for ( auto &element : map ) {
		if ( func_key(element.second, 0) == true ) {
			//std::cout << typeid(element).name();
			map_result.insert(element);
		}
	}


	return map_result;
}

// ---------------------------------------------------------------------------------------------
// --------------------------------------------task5--------------------------------------------
// ---------------------------------------------------------------------------------------------

//std::map<ds_lib::bike_key, ds_lib::bike_value> &insert(std::map<ds_lib::bike_key, ds_lib::bike_value> map,
//													   std::pair<ds_lib::bike_key, ds_lib::bike_value> pait) {

//}

// ---------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------

using namespace ds_lib;
int main() {

// ---------------------------------------------------------------------------------------------
// --------------------------------------------task1--------------------------------------------
// ---------------------------------------------------------------------------------------------
	std::vector<ds_lib::bike_key> vector_key;
	std::vector<ds_lib::bike_value> vector_value;
	std::string value = "value";
	std::string key = "key";

	std::map<bike_key, bike_value> bike_map;

	for ( int i = 0; i < 13; i++ ) {
		vector_key.push_back(bike_key(key + std::to_string(i), std::rand()));
		vector_value.push_back(bike_value(value + std::to_string(i), std::rand()));
 
		bike_map.insert({vector_key[i], vector_value[i]});
	}
	// Проверка правильного постороения структуры std::map
	//for ( const auto kv : bike_map ) {
	//	std::cout << kv.first << kv.second;
	//}

	// Поиск по ключу
	auto find_value_key1 = find_value(vector_key[1], bike_map);
	std::cout << "----" << find_value_key1 << "----" << vector_value[1];
	std::cout << "______";
	// Поиск по значению
	auto find_key_value1 = find_key(vector_value[1], bike_map);
	std::cout << find_key_value1;

	//std::cout << k1 << k2;

	// std::cout<< map[k1];

	//std::vector<std::string> vector{"gal;d", "g;fgs", "ert", "etewrt", "key", "adgs", "gterw"};
	//std::cout << foo(vector);

    // Вывод через итераторы
	print_iter(bike_map);


	auto map_result = filter(bike_map, func_task4);
	print_iter(map_result);







	return 0;
}
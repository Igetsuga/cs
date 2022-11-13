#include <map>

#include <utility>
#include <string>
#include <iostream>
#include <vector>

namespace lib {

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

	pair(const Type1 &value1, const Type2 &value2) {
		_value1 = value1;
		_value2 = value2;
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
lib::pair<Type1, Type2> &make_pair (const Type1 &value1, const Type2 &value2) noexcept {
	return lib::pair<Type1,Type2>(value1, value2);
}

template<typename Type1, typename Type2>
std::pair<Type1, Type2> &make_std_pair (const Type1 &value1, const Type2 &value2) noexcept {
	return std::make_pair(value1, value2);
}

// ---------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------


class bike_key : public lib::pair<std::string, int> {
public:

	bike_key (const std::string &brand, int diameter) : pair (brand, diameter) {};

	virtual ~bike_key() = default;

};


// ---------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------


class bike_value : public lib::pair<std::string, bool> {
public:

	bike_value (const std::string &type, bool is_absorb) : pair (type, is_absorb) {};

	virtual ~bike_value() = default;
};


// ---------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------


}


// ---------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------


lib::bike_value &find_value (lib::bike_key &key, std::map<lib::bike_key, lib::bike_value> &map) noexcept {
	/*for ( auto element : map ) {
		if ( element.first == key ) {
			return element.second;
		}
	}*/
    lib::bike_value answer("NONE", "")
	for ( auto element : map ) {
		if ( element.first == key ) {
			= 
			return element.second;
		}
	}

	//return nullptr;
}

//const lib::bike_key &find_key (lib::bike_value &value, std::map<lib::bike_key, lib::bike_value> &map) noexcept {
//	for ( auto element : map ) {
//		if ( element.second == value ) {
//			return element.first;
//		}
//	}
//}

// ---------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------

using namespace lib;
int main() {

	std::vector<lib::bike_key> vector_key;
	std::vector<lib::bike_value> vector_value;
	std::string value = "value";
	std::string key = "key";

	std::map<bike_key, bike_value> bike_map;

	for ( int i = 0; i < 13; i++ ) {
		vector_key.push_back(bike_key(key + std::to_string(i), std::rand()));
		vector_value.push_back(bike_value(value + std::to_string(i), std::rand()));

		bike_map.insert({vector_key[i], vector_value[i]});
	}
	// Проверка правильного постороения структуры std::map
	for ( const auto kv : bike_map ) {
		std::cout << kv.first << kv.second;
	}


	auto find_value_key11 = find_value(vector_key[1], bike_map);
	std::cout << "----" << find_value_key11 << "----" << vector_value[10];


	//std::cout << k1 << k2;

	// std::cout<< map[k1];


	return 0;
}
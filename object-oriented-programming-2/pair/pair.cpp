#include <map>

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



		virtual Type1 first ()  const noexcept override final { return _value1; }
		virtual Type2 second () const noexcept override final { return _value2; }



		virtual bool operator == (const pair &pair_other) const noexcept  {
			return (_value1 == pair_other._value1 && _value2 == pair_other._value2 ? true : false);
		}

		virtual bool operator > (const pair &pair_other) const noexcept {
			if ( _value1 > pair_other._value1 ) {
				return true;
			}
			else if ( _value1 == pair_other._value1 ) {
				return (_value2 > pair_other._value2 ? true : false);
			}


			return false;
		}

		bool operator < (const pair &pair_other) const noexcept  {
			return !(*this > pair_other);
		}

		bool operator >= (const pair &pair_other) const noexcept  {
			return (this > pair_other || this == pair_other);
		}

		bool operator <= (const pair &pair_other) const noexcept  {
			return (this < pair_other || this == pair_other);
		}



	protected:
		Type1 _value1;
		Type2 _value2;
	};

	template<typename Type1, typename Type2>
	std::ostream &operator<< (std::ostream &output, const pair<Type1, Type2> &pair) {
		// output << '\n' << "first: " << pair.first() << '\n' << "second: " << pair.second() << '\n';
		// output << '\n' << "{first, second} : {" << pair.first() << ", " << pair.second() << "}; " << '\n';
		output << "(" << pair.first() << ", " << pair.second() << ")";

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


	class bike_key final : public ds_lib::pair<std::string, int> {
	public:

		bike_key (const std::string &brand, int diameter) : pair (brand, diameter) {};


		bool operator > (const pair &pair_other) const noexcept override {
			if ( _value2 > pair_other.second() ) {
				return true;
			}


			return false;
		}


		virtual ~bike_key() = default;

	};


// ---------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------


	class bike_value final : public ds_lib::pair<std::string, bool> {
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
ds_lib::bike_value find_value (const std::map<ds_lib::bike_key, ds_lib::bike_value> &map,
							   const ds_lib::bike_key &key) noexcept {
	ds_lib::bike_value answer("NONE", 0);
	
	for ( const auto &element : map ) {
		if ( element.first == key ) {
			answer = element.second;
			break;
		}
	}


	return answer;
}

const ds_lib::bike_key find_key (const std::map<ds_lib::bike_key, ds_lib::bike_value> &map,
								 const ds_lib::bike_value &value) noexcept {
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

template<typename Type1, typename Type2> void print_iter (const std::map<Type1, Type2> &map) {
	auto itt = map.begin();

	std::cout << "{" << '\n';
	while ( itt != map.end() ) {
		std::cout << (*itt).first << " --- " << (*itt).second << '\n';
		itt++;
	}
	std::cout << "};" << '\n';

}

template<typename Iterator_type>
void print_iter (Iterator_type begin, Iterator_type end) {
	
	std::cout << "{" << '\n';
	
	while ( begin != end ) {
		std::cout << (*begin).first << " --- " << (*begin).second << '\n';
		begin++;
	}
	std::cout << "};" << '\n';
}


// ---------------------------------------------------------------------------------------------
// --------------------------------------------task4--------------------------------------------
// ---------------------------------------------------------------------------------------------

bool func_key (const ds_lib::bike_value &value, const int &threshold = 0) {
	return (value.second() > threshold);
}

using func = bool(*)(const ds_lib::bike_value&, const int&);
func func_task4 = &func_key;

// TODO: doesn't work with &filter, idk
template<typename Type1, typename Type2> 
std::map<Type1, Type2> filter (const std::map<Type1, Type2> &map,
								bool(*func_key)(const ds_lib::bike_value&, const int &),
								const int &threshold) {
	std::map<Type1, Type2> map_result;
	
	for ( const auto &element : map ) {
		if ( func_key(element.second, threshold) == true ) {
			//std::cout << typeid(element).name();
			map_result.insert(element);
		}
	}

	// TODO: the code below doesn't work, idk what the problem
	/*auto iter = map.begin();
	while ( iter != map.end() ) {
		if (func_key( (*iter).second, threshold ) == true ) {
			map_result.insert(*iter);
		}
	}*/

	return map_result;
}

// ---------------------------------------------------------------------------------------------
// --------------------------------------------task5--------------------------------------------
// ---------------------------------------------------------------------------------------------

class Exception : public std::exception
{
public:

	Exception()
	{
		message_ = nullptr;
	}


	Exception(const std::string &message)
	{

		message_ = new std::string(message);
		// message_ = new char[strlen(message) + 1];   // strlen(С-string) <=> string::message.size();	
		// strcpy_s(message_, strlen(message) + 1, message);   // method from C, idk, better to use methods with `string`
	}

	// constructor_copy
	Exception(const Exception &exception)  
	{
		message_ = new std::string(*exception.message_);
		// message_ = new char[strlen(exception.message_) + 1];
		// strcpy_s(message_, strlen(exception.message_) + 1, exception.message_);
	}

	// destructor
	virtual ~Exception()
	{
		delete[] message_; message_ = nullptr;
	}

	virtual void what()
	{
		std::cout  << '\n' << "{Exception}: " << message_ << "; " << std::exception::what();
	}
	
	protected:
	std::string* message_; // error message
};








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
	std::string value = "v";
	std::string key = "k";

	std::map<bike_key, bike_value> bike_map;

	for ( int i = 0; i < 13; i++ ) {
		vector_key.push_back(bike_key(key + std::to_string(i), std::rand()));
		vector_value.push_back(bike_value(value + std::to_string(i), std::rand() % 2));
 
		bike_map.insert({vector_key[i], vector_value[i]});
	}
	// Проверка правильного постороения(правилность сортировки по ключу) структуры std::map
	std::cout << "{" << '\n';
	for ( const auto element : bike_map ) {
		std::cout << element.first << " --- " << element.second << '\n';
	}
	std::cout << "};" << '\n';

// ---------------------------------------------------------------------------------------------
// --------------------------------------------task2--------------------------------------------
// ---------------------------------------------------------------------------------------------

	// Поиск по ключу
	auto find_value_key1 = find_value(bike_map, vector_key[1]);
	auto find_value_key10 = find_value(bike_map, vector_key[10]);
	std::cout << "RESULT VALUE: " << find_value_key1 << " --> TRUE VALUE: " << vector_value[1] << '\n';
	std::cout << "RESULT VALUE: " << find_value_key10 << " --> TRUE VALUE: " << vector_value[10] << '\n';
	
	// Поиск по значению
	auto find_key_value1 = find_key(bike_map, vector_value[1]);
	auto find_key_value11 = find_key(bike_map, vector_value[11]);
	std::cout << "RESULT KEY: " << find_key_value1 << " --> TRUE KEY: " << vector_key[1] << '\n';
	std::cout << "RESULT KEY: " << find_key_value11 << " --> TRUE KEY: " << vector_key[11] << '\n';

	//std::cout << k1 << k2;

	// std::cout<< map[k1];

	//std::vector<std::string> vector{"gal;d", "g;fgs", "ert", "etewrt", "key", "adgs", "gterw"};
	//std::cout << foo(vector);

// ---------------------------------------------------------------------------------------------
// --------------------------------------------task3--------------------------------------------
// ---------------------------------------------------------------------------------------------

    // Вывод через итераторы
	print_iter(bike_map);

// ---------------------------------------------------------------------------------------------
// --------------------------------------------task4--------------------------------------------
// ---------------------------------------------------------------------------------------------

	std::cout << '\n' << "----------------------------------" << '\n';

	//auto iter = bike_map.begin();
	std::map<ds_lib::bike_key, ds_lib::bike_value> map_result;
	//std::map<ds_lib::bike_key, ds_lib::bike_value> map_train;
	//map_train.insert({vector_key[0], vector_value[0]});
	//map_train.insert({vector_key[1], vector_value[1]});
	

	map_result = filter(bike_map, func_task4, 0);
	print_iter( map_result.begin(), map_result.end() );

// ---------------------------------------------------------------------------------------------
// --------------------------------------------task5--------------------------------------------
// ---------------------------------------------------------------------------------------------





	return 0;
}
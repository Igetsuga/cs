#include <iostream>
// Сиразетдинов Рустем КМБО-01-21 Вариант- 24

#include <ostream>
using namespace std;
using std::cin;
using std::cout;
// using std::vector;
using std::string;
//
// using vi = vector<int>;
// using vvi = vector<vi>;
//
// using ll = long long;
//
// const ll mod = ll(1e9 + 7);

class Exception
{
protected:
	string message_; // error message
public:

	// default constructor
	Exception()
	{
		message_ = "ERROR";
	}

	// constructor_1
	Exception(const string& message)
	{
		message_ = message;
	}

	// constructor_copy
	Exception(const Exception& error)
	{
		message_ = error.message_;
	}

	// destructor
	~Exception() {}

	virtual void print()
	{
		cout << "Exception: " << message_ << '\n';
	}
};

class OutOfBounds : public Exception
{
private:
	string message_;
public:
	OutOfBounds(string message = "String index out of bounds") : Exception(message) {}
	~OutOfBounds() {}
};


class StringBase
{
protected:
	char* string_;    // array of chars
	int length_;
	int capacity_;
public:

	// default constructor
	StringBase(int capacity = 128)
	{
		string_ = new char[capacity];
		// char message[128] = "From default constructor";
		// string_ = message;

		capacity_ = capacity;
		length_ = 0;

		cout << '\n' << "(" << typeid(*this).name() << ") object has been created" << '\n';
	}

	// constructor const char*
	StringBase(const char* chars)
	{
		length_ = 0;
		while (chars[length_] != '\0')
		{
			length_++;
		}

		capacity_ = (length_ <= 128) ? 128 : length_;
		
		string_ = new char[capacity_ + 1];
		for (int itt = 0; itt < length_; itt++)
		{
			string_[itt] = chars[itt];
		}
		string_[length_] = '\0';
	}

	// destructor
	~StringBase()
	{
		capacity_, length_ = 0;

		if (string_ != nullptr)
		{
			delete[] string_;
			string_ = nullptr;
		}

		cout << '\n' << "(" << typeid(*this).name() << ") object has been deleted" << '\n';
	}

	// constructor_copy
	StringBase(const StringBase& string) 
	{
		string_ = new char[string.capacity_];
		
		capacity_ = string.capacity_;

		length_ = string.length_;

		for (int itt = 0; itt < length_; itt++)
		{
			string_[itt] = string.string_[itt];
		}
		string_[length_] = '\0';
	}

	int GetLenght() { return length_; }
	int GetCapacity() { return capacity_; }

	char& operator[](int index)
	{
		if (index > 0 && index < length_) { return string_[index]; }
		else { throw OutOfBounds(); }
	}

	StringBase& operator=(const StringBase& string)
	{
		if (capacity_ < string.capacity_)
		{
			delete[] string_; string_ = nullptr;
			string_ = new char[string.capacity_];
		}

		capacity_ = string.capacity_;
		length_ = string.length_;

		for (int itt = 0; itt < length_; itt++)
		{
			string_[itt] = string.string_[itt];
		}


		return (*this);
	}

	StringBase& operator=(const string& string_existing)
	{
		if (capacity_ < string_existing.size())
		{
			delete[] string_; string_ = nullptr;
			string_ = new char[string_existing.size()];
		}

		capacity_, length_ = string_existing.size();
		 

		for (int itt = 0; itt < length_; itt++)
		{
			string_[itt] = string_existing[itt];
		}


		return (*this);
	}

	StringBase& operator=(const char* array_char)
	{
		string array_char_copy = array_char;


		return (*this) = array_char_copy;
	}
	

	virtual void print()
	{
		cout << '\n' << "object (" << typeid(*this).name() << ") = \"";
		
		for (int itt = 0; itt < length_; itt++)
		{
			cout << string_[itt];
		}
		cout << "\"" << '\n';
	}

	friend ostream& operator<<(ostream& os, const StringBase& str);


};

class StringBaseSub : public StringBase
{
public:
	// default constructor
	StringBaseSub(int capacity = 128) : StringBase(capacity)
	{
		string_ = new char[capacity];

		capacity_ = capacity;
		length_ = 0;

		cout << '\n' << "(" << typeid(*this).name() << ") object has been created" << '\n';
	}

	// constructor const char*
	StringBaseSub(const char* chars) : StringBase(chars)
	{
		length_ = 0;
		while (chars[length_] != '\0')
		{
			length_++;
		}

		capacity_ = (length_ <= 128) ? 128 : length_;

		string_ = new char[capacity_ + 1];
		for (int itt = 0; itt < length_; itt++)
		{
			string_[itt] = chars[itt];
		}
		string_[length_] = '\0';
	}

	// destructor
	~StringBaseSub()
	{
		capacity_, length_ = 0;

		if (string_ != nullptr)
		{
			delete[] string_;
			string_ = nullptr;
		}

		cout << '\n' << "(" << typeid(*this).name() << ") object has been deleted" << '\n';
	}

	// constructor_copy
	StringBaseSub(const StringBaseSub &string)
	{
		string_ = new char[string.capacity_];

		capacity_ = string.capacity_;

		length_ = string.length_;

		for (int itt = 0; itt < length_; itt++)
		{
			string_[itt] = string.string_[itt];
		}
		string_[length_] = '\0';
	}

	// StringBaseSub(const StringBaseSub& string) : StringBase(string) {}

	int GetLenght() { return length_; }
	int GetCapacity() { return capacity_; }

	char& operator[](int index)
	{
		if (index > 0 && index < length_) { return string_[index]; }
		else { throw OutOfBounds(); }
	}

	StringBaseSub& operator=(const StringBaseSub& string)
	{
		if (capacity_ < string.capacity_)
		{
			delete[] string_; string_ = nullptr;
			string_ = new char[string.capacity_];
		}

		capacity_ = string.capacity_;
		length_ = string.length_;

		for (int itt = 0; itt < length_; itt++)
		{
			string_[itt] = string.string_[itt];
		}


		return (*this);
	}

	StringBaseSub& operator=(const string& string_existing)
	{
		if (capacity_ < string_existing.size())
		{
			delete[] string_; string_ = nullptr;
			string_ = new char[string_existing.size()];
		}

		capacity_, length_ = string_existing.size();


		for (int itt = 0; itt < length_; itt++)
		{
			string_[itt] = string_existing[itt];
		}


		return (*this);
	}

	StringBaseSub& operator=(const char* array_char)
	{
		string array_char_copy = array_char;


		return (*this) = array_char_copy;
	}

	int tolower(char c)
	{
		int c_int = int(c);
		
		if ( (c_int >= 65 && c_int <= 90) || (c_int >= 97 && c_int <= 122) ) // if ( isalpha(c) )
		{
			return ((c_int >= 97) ? (c_int - 32) : c_int);
		}
		
		return c_int;
	}

	int foo_1(char c)
	{
		int value = int(StringBaseSub::tolower(c));

		int result = 0;

		for (int itt = 0; itt < length_; itt++)
		{
			result += 1 * ( int(StringBaseSub::tolower(string_[itt])) > value && int(StringBaseSub::tolower(string_[itt])) < 123 );
		}


		return result;
	}

	int foo_2(char c)
	{
		int value = int(std::tolower(c));

		int result = 0;

		for (int itt = 0; itt < length_; itt++)
		{
			result += 1 * (int(std::tolower(string_[itt])) > value && int(std::tolower(string_[itt])) < 123);
		}


		return result;
	}

	virtual void print()
	{
		cout << '\n' << "object (" << typeid(*this).name() << ") = \"";

		for (int itt = 0; itt < length_; itt++)
		{
			cout << string_[itt];
		}
		cout << "\"" << '\n';
	}


};

//ostream& operator<<(ostream& os, const StringBase& str)
//{
//	for (int itt = 0; itt < str.GetLength(); itt++)
//	{
//		os << str[itt];
//	}
//
//		
//	return os;
//}

int main()
{
	// Тестирование "aBcDefGhijKLmN"

	StringBase str_m; str_m = "abcdefghijklmn"; 

	StringBase* ptr; ptr = &str_m;

	ptr->print();
	
	cout << '\n' << "///////////////////////////////////////////////"
		<< "//////////////////" << '\n';

	StringBase str_1 = "gneiounve"; str_1.print();

	cout << '\n' << "///////////////////////////////////////////////"
		<< "//////////////////" << '\n';

	string c1 = "gh3on"; string c2 = "fn3ignv"; 

	*ptr = c1 = c2; ptr->print(); 
	cout << '\n' << "capacity_ is : " << ptr->GetCapacity() 
		<< " and length_ is:" << ptr->GetCapacity() << '\n';

	cout << '\n' << "///////////////////////////////////////////////"
		<< "//////////////////" << '\n' << '\n';

	// Проверим на объекте производного класса метод foo 
	// на строке "aBcDefGhijKLmN". 
	// (Метод foo(char c) возвращает количество символов,
	// которые в алфавитном порядке больше заданного параметра `c`
	// при этом регистр не важен. Если параметр `c` = B, то метод 
	// должен вернуть 12 (это символы c,d,e,f,g,h,i,j,k,l,m, n),
	///если араметр `c` = j, то метод должен вернуть 4
	// (k,l,m,n)

	StringBaseSub str = "aBcDefGhijKLmN";

	string test = "Bjqwertyuiopasdfghklzxcvnm";

	for (int itt = 0; itt < test.size(); itt++)
	{
		cout << "Case #" << itt << " current value is " << test[itt] << " : answer = " << str.foo_1(test[itt]) << " == " << str.foo_2(test[itt]) << '\n';
	}

	cout << '\n' << "///////////////////////////////////////////////"
		<< "//////////////////" << '\n';



	return 0;
}
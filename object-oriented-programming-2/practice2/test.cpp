#include <vector>
#include <map>
#include <set>
#include <string>
#include <iostream>
#define nline '\n'

class Student {
	public:
		Student(std::string surname){
			_surname = surname;
		}
		~Student() = default;
	protected:
		std::string _surname;
};


int main() {
	std::map<std::string, int> journal;
	journal.insert(std::pair<std::string, int>("ivanov", 5));
	
	std::cout << journal["ivanov"] << nline;
	std::cout << journal.at("ivanov") << nline;
	std::cout << typeid(journal["ivanov"]).name() << nline;
	std::cout << typeid(journal.at("ivanov")).name() << nline;
	std::cout << journal["iv"] << nline;
	std::cout << journal.at("iv") << nline;

	journal["petrov"] = 3;
	std::cout << journal["petrov"] << nline;
	std::map<std::string, int>::iterator itt = journal.find("ivanov");

	std::vector<int> vector;
	std::set<int> set;
	for(int i = 0; i < 100; i++) {
		vector.push_back(rand());	
		set.insert(vector[i]);
	}
	for (auto element : vector) {
		std::cout << element << " : ";
	}
	std::cout << nline;



}

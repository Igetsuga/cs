/*****************************************************************//**
 * \file   practice1.cpp
 * \brief  Практическая работа 1.
 * 
 * \author Sirazetdinov Rustem
 * \version 
 * \date   September 2022
 *********************************************************************/

#define nline '\n'
#include <iostream>
#include <fstream>


#include <list>
#include <iterator>
#include <algorithm>

#include "Computer.h"




/**
 * Помещает объект в контейнер std::list, оставляя его отсортированным.
 * 
 * \param list
 * \param object
 */
template<class Type> void push (std::list<Type> &list, const Type &object) {
	
	// auto it_pos = list.begin();
	std::list<Type>::template iterator it_pos = list.begin();
	
	while ( it_pos != list.end() ) {
		// >= лучше чем >, т.к. при > вставка сильно замедляется, 
		// если все объекты в списке равны между собой
		if ( *it_pos >= object ) { break; }
		it_pos++;
	}

	list.insert(it_pos, object);
}


/**
 * Удаление элемента из контейнера std::list.
 * 
 * Функция удаляет элемент из контейнера и возвращает элемент, который имеет наибольший приоритет,
 * поскольку контейнер отсортирован, наибольший приоритет имеет объект, стоящий самым последним. 
 * Если после удаления элемента из контейнера, контейнер оказывается пустым, то возвращается 
 * последний удаленный объект.
 * 
 * \param list
 * \param pos
 * \return Объект с наибольшим приоритетом.
 */
template<class Type> Type pop (std::list<Type> &list, const int &pos = list.size() - 1 ) {
	
	if ( pos > list.size() || pos < 0 ) { 
		throw std::out_of_range("pop ( std::list<Type> &list, const int &pos = ... ) Index out of range");
	}

	Type object_remove = list.back();

	if ( pos == 0 ) {
		list.pop_front(); 
	}
	else if ( pos == list.size() - 1 ) {
		list.pop_back();
	}
	else {
		std::list<Type>::template iterator it_pos = std::next(list.begin(), pos);
		// or / auto it_pos = std::next(list.begin(), pos);
		// or / std::list<Type>::iterator it_pos = list.begin(); std::advance(it_pos, pos); 
		list.erase(it_pos);
	}


	return object_remove;
}


/**
 * Фильтрация объектов контейнера по функции-ключу.
 * 
 * \param list
 * \param *func_key
 * \return Новый контейнер, элементы которого удовлетворяют функции-ключу.
 */
// как передавать произвольный контейнер? 
// ответ: передача итератора начала и конца		
// или template<class Type1, class Type2> ...
template<class Type> std::list<Type>& filter (const std::list<Type> &list,
											 bool (*func_key)(const Type, const Type), double param) {
	std::list<Type> ListResult;

	for ( Type object : list ) {
		if ( func_key(param, object) ) { push(ListResult, object); }
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
	std::cout << nline << "{";
	for ( Type object : list ) {
		std::cout << " " << object;
	}
	std::cout << " }; " << nline;
}


bool EvaluateFractionalPart (const double p, const double value) {
	int value_ceil = int(value);
	double diff = value - value_ceil;
	
	
	return (diff - p < 0);
}



int main()
{
	
	// -------------- p.1 --------------
	// Cоздаем лист с элементами типа `int`
	std::list<double> doubleList;
	for ( int i = 0; i < 20; i++ ) {
		push(doubleList, (double)rand());
		//doubleList.push_back( (double)rand() );
	}
	
	// Проверка функции `print` для объектов типа std::list<Type>
	print(doubleList);

	// Проверка того, что функция `push` добавляет элементы в контейнер, оставляя его отсортированным
	if ( std::is_sorted(doubleList.begin(), doubleList.end()) ) { std::cout << "SORTED" << nline; }
	else { std::cout << "UNSORTED" << nline; }
	
	print(doubleList);

	// Удалим из листа несколько значений
	auto hValue_temp = pop(doubleList, 1); std::cout << nline << hValue_temp << " ";
	print(doubleList);

	hValue_temp = pop(doubleList, 9); std::cout << nline << hValue_temp << " ";
	print(doubleList);

	hValue_temp = pop(doubleList, doubleList.size() - 1); std::cout << nline << hValue_temp << " ";
	std::cout << nline << nline;
	print(doubleList);

	
	
	// Выделим из нашего листа новый, элементы которого представляют собой
	// числа типа `double` с дробной частью не превышающей числа `p`.
	bool (*func_key)(const double, const double) = &EvaluateFractionalPart;
	//int (*func_key)(const int &) = IsFactorialOfEven;

	double param = 0.4567;
	//std::for_each(doubleList.begin(), doubleList.end(), [](double n) {n /= 100; });
	for ( auto x : doubleList ) {
		x = x / 100.0;
	}
	// std::for_each(doubleList.begin(), doubleList.end(), [](double n) {std::cout << n << " "; });
	print(doubleList);
	//std::list<double> listFiltered = filter(doubleList, func_key, param);
	
	//std::cout << nline << "listFiltered is: " << nline;
	//print(listFiltered);

	doubleList.clear();
	//listFiltered.clear();



	//// -------------- p.2 --------------
	//std::list<Computer> bikeList;

	//Computer bikeSimple();
	//Computer bikeSimpleUPG();
	//// std::cout << nline << bikeSimple << nline << bikeSimpleUPG << nline;
	//// bikeSimple > bikeSimpleUPG ? std::cout << nline << "1" : std::cout << nline << "2";

	//Computer bikeUltra();
	//Computer bikeMedium();
	//Computer bikeHigh();

	//push(bikeList, bikeSimple); 
	//push(bikeList, bikeSimpleUPG);
	//push(bikeList, bikeUltra);
	//push(bikeList, bikeHigh);
	//push(bikeList, bikeMedium);

	//print(bikeList);
	//
	//std::cout << pop(bikeList, 2);


	return 0;
}

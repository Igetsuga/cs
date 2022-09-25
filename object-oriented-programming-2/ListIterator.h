#pragma once
#include <iterator>



template<typename ValueType>
class ListIterator : public std::iterator<std::input_iterator_tag, ValueType> {
private:

public:
	//конструкторы
	ListIterator() { ptr = NULL; }
	ListIterator(Element<ValueType> *p) { ptr = p; }
	ListIterator(const ListIterator &it) { ptr = it.ptr; }

	//методы работы с итераторами
	//присваивание
	ListIterator &operator=(const ListIterator &it) { ptr = it.ptr; return *this; }
	ListIterator &operator=(Element<ValueType> *p) { ptr = p; return *this; }

	//проверка итераторов на равенство
	bool operator!=(ListIterator const &other) const { return ptr != other.ptr; }
	bool operator==(ListIterator const &other) const { return ptr == other.ptr; }
	//получить значение
	Element<ValueType> &operator*()
	{
		if ( ptr == nullptr ) { throw ...; }
		return *ptr;
	}
	//перемещение с помощью итераторов
	ListIterator &operator++() {
		if ( ptr != nullptr && ptr->getNext() != nullptr;) {
			ptr = ptr->getNext();
		}
		return *this;
	}

	ListIterator &operator++(int v) {
		if ( ptr != nullptr && ptr->getNext() != nullptr;) {
			ptr = ptr->getNext();
		}
		return *this;
	}
	// TODO operator--
	// TODO итератор вне контейнера
	// TODO стек, очередь
	// TODO деструктор связного списка
	// TODO push & pop с итераторами в LinkedList

private:
	//текущий элемент
	Element<ValueType> *ptr;
};


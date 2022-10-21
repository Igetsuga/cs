/*****************************************************************//**
 * \file   Node.cpp
 * \brief  Файл определения класса `Node`.
 *
 * Вспомогательный класс для контейнеров. Выступает в роли
 * элемента контейнера. Класс реализован через указатели.
 * Объявление класса смотри в файле `Node.h`.
 *
 * \author  Sirazetdinov Rustem
 * \version
 * \date    September 2022
 *********************************************************************/
#include "Node.h"

/**
 * Конструктор класса.
 *
 * \param data
 * \param sucessor
 * \param predecessor
 */
template<class Type> Node<Type>::Node(const Type &data,
									  Node<Type> *sucessor,
									  Node<Type> *predecessor) {
	_sucessor = sucessor;
	_predecessor = predecessor;
	_data = data;
}


/**
 * Деструктор класса.
 *
 * \waring Деструктор определен компилятором.
 */
template<class Type> Node<Type>::~Node () = default;


/**
 * Предоставляет возможность получить доступ к полю `_sucessor`.
 *
 * \return Указатель на следующий узел.
 */
template<class Type> Node<Type> *Node<Type>::getSucessor() const noexcept {
	return _sucessor;
}


/**
 * Предоставляет возможность получить доступ к полю `_predecessor`.
 *
 * \return Указатель на предыдущий узел.
 */
template<class Type> Node<Type> *Node<Type>::getPredecessor() const noexcept {
	return _predecessor;
}


/**
 * Предоставляет возможность получить доступ к полю `_data`.
 *
 * \return Копию информации, которые содержит текущий узел.
 */
template<class Type> const Type &Node<Type>::getData() const noexcept {
	return _data;
}


/**
 * Предоставляет возможность установить новое значение для поля `_sucessor`.
 *
 * \param sucessor
 */
template<class Type> void Node<Type>::setSucessor (const Node<Type> *sucessor) noexcept {
	_sucessor = sucessor;
}


/**
 * Предоставляет возможность установить новое значение для поля `_predecessor`.
 *
 * \param predecessor
 */
template<class Type> void Node<Type>::setPredecessor (const Node<Type> *predecessor) noexcept {
	_predecessor = predecessor;
}


/**
 * Предоставляет возможность установить новое значения для поля `_data`.
 *
 * \param data
 */
template<class Type> void Node<Type>::setData (const Type & data) noexcept {
	_data = data;
}


/**
 * Проверка равенства объектов(deep).
 *
 *
 * \param node
 * \return
 */
template<class Type> bool Node<Type>::deepEqual (const Node<Type> &node) const noexcept {
	if ( _data == node._data &&
		_sucessor == node._sucessor &&
		_predecessor == node._predecessor ) {
		return true;
	}


	return false;
}


/**
 * \breif Перегрузка оператора `operator=`(shallow).
 *
 * \param node
 */
template<class Type> Node<Type> &Node<Type>::operator= (const Node<Type> &node) {
	_sucessor = node._sucessor;
	_predecessor = node._predecessor;
	_data = node._data;
}


/**
 * \brief Перегрузка оператора `operator==`.
 *
 * Проверка равенства объектов(shallow).
 *
 * \param node
 */
template<class Type> bool Node<Type>::operator== (const Node<Type> &node) const noexcept {
	if ( _data == node._data &&
		_sucessor._data == node._sucessor._data &&
		_predecessor._data == node._predecessor._data ) {
		return true;
	}


	return false;
}


/**
 * \brief Перегрузка оператора `operator`=`.
 *
 * Проверка неравенства объектов(shallow).
 *
 * \param node
 */
template<class Type> bool Node<Type>::operator!= (const Node<Type> &node) const noexcept {
	return !(*this == node);
}


/**
 * Перегрузка оператора `operator<<`.
 *
 * \param output
 * \param node
 * \return Ссылку на стандартный поток вывода.
 */
template<class Type> std::ostream &operator<< (std::ostream & output,
											   const Node<Type> &node) {
	output << node._data;


	return output;
}
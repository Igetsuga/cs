/*****************************************************************//**
 * \file   Node.cpp
 * \brief  ���� ����������� ������ `Node`.
 *
 * ��������������� ����� ��� �����������. ��������� � ����
 * �������� ����������. ����� ���������� ����� ���������.
 * ���������� ������ ������ � ����� `Node.h`.
 *
 * \author  Sirazetdinov Rustem
 * \version
 * \date    September 2022
 *********************************************************************/
#include "Node.h"

/**
 * ����������� ������.
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
 * ���������� ������.
 *
 * \waring ���������� ��������� ������������.
 */
template<class Type> Node<Type>::~Node () = default;


/**
 * ������������� ����������� �������� ������ � ���� `_sucessor`.
 *
 * \return ��������� �� ��������� ����.
 */
template<class Type> Node<Type> *Node<Type>::getSucessor() const noexcept {
	return _sucessor;
}


/**
 * ������������� ����������� �������� ������ � ���� `_predecessor`.
 *
 * \return ��������� �� ���������� ����.
 */
template<class Type> Node<Type> *Node<Type>::getPredecessor() const noexcept {
	return _predecessor;
}


/**
 * ������������� ����������� �������� ������ � ���� `_data`.
 *
 * \return ����� ����������, ������� �������� ������� ����.
 */
template<class Type> const Type &Node<Type>::getData() const noexcept {
	return _data;
}


/**
 * ������������� ����������� ���������� ����� �������� ��� ���� `_sucessor`.
 *
 * \param sucessor
 */
template<class Type> void Node<Type>::setSucessor (const Node<Type> *sucessor) noexcept {
	_sucessor = sucessor;
}


/**
 * ������������� ����������� ���������� ����� �������� ��� ���� `_predecessor`.
 *
 * \param predecessor
 */
template<class Type> void Node<Type>::setPredecessor (const Node<Type> *predecessor) noexcept {
	_predecessor = predecessor;
}


/**
 * ������������� ����������� ���������� ����� �������� ��� ���� `_data`.
 *
 * \param data
 */
template<class Type> void Node<Type>::setData (const Type & data) noexcept {
	_data = data;
}


/**
 * �������� ��������� ��������(deep).
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
 * \breif ���������� ��������� `operator=`(shallow).
 *
 * \param node
 */
template<class Type> Node<Type> &Node<Type>::operator= (const Node<Type> &node) {
	_sucessor = node._sucessor;
	_predecessor = node._predecessor;
	_data = node._data;
}


/**
 * \brief ���������� ��������� `operator==`.
 *
 * �������� ��������� ��������(shallow).
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
 * \brief ���������� ��������� `operator`=`.
 *
 * �������� ����������� ��������(shallow).
 *
 * \param node
 */
template<class Type> bool Node<Type>::operator!= (const Node<Type> &node) const noexcept {
	return !(*this == node);
}


/**
 * ���������� ��������� `operator<<`.
 *
 * \param output
 * \param node
 * \return ������ �� ����������� ����� ������.
 */
template<class Type> std::ostream &operator<< (std::ostream & output,
											   const Node<Type> &node) {
	output << node._data;


	return output;
}
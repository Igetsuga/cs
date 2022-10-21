/*****************************************************************//**
 * \file   Node.h
 * \brief  ������������ ���� ���������� ������ `Node`.
 *
 * ��������������� ����� ��� �����������. ��������� � ����
 * �������� ����������. ����� ���������� ����� ���������.
 * ������������ ������ ������ � ����� `Node.cpp`.
 *
 * \author  Sirazetdinov Rustem
 * \version
 * \date    September 2022
 *********************************************************************/
#pragma once
#include <iostream>
#define nline '\n'

/**
* /brief ����� ������������ ����� ������, ������� ��������� ��� �������� �������� ������.
*
* ����� ���������� ����� ������� ���������.
*/
template<class Type> class Node {
public:

	Node (const Type &data,
		  Node<Type> *sucessor = nullptr,
		  Node<Type> *predecessor = nullptr);

	~Node ();



	Node<Type> *getSucessor() const noexcept;
	Node<Type> *getPredecessor() const noexcept;
	const Type &getData() const noexcept;



	void setSucessor (const Node<Type> *sucessor) noexcept;
	void setPredecessor (const Node<Type> *predecessor) noexcept;
	void setData (const Type &data) noexcept;


	bool deepEqual (const Node<Type> &node) const noexcept;

	Node<Type> &operator= (const Node<Type> &node);

	bool operator== (const Node<Type> &node) const noexcept;

	bool operator!= (const Node<Type> &node) const noexcept;

	template<class Type> friend std::ostream &operator<< (std::ostream &output,
														  const Node<Type> &node);
private:
	Node<Type> *_sucessor;
	Node<Type> *_predecessor;
	Type        _data;
};

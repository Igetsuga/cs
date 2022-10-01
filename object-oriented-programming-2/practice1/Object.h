/*****************************************************************//**
 * \file   Object.h
 * \brief  ������������ ���� ����������� ������ `Object`.
 *
 * ��������������� ����� ��� �����������. ��������� � ����
 * �������� ����������. ����� ���������� ����� ����� ���������. 
 * ������������ ������ ������ � ����� `Object.cpp`.
 * 
 * \author averu
 * \version
 * \date   September 2022
 *********************************************************************/
#pragma once
#include <iostream>
#include <memory>

template<class Type> using uptr = std::unique_ptr<Type>;
template<class Type> using sptr = std::shared_ptr<Type>;
template<class Type> using wptr = std::weak_ptr<Type>;

/**
* /brief ����� ���������� ����� ����� ���������.
*
* ����� ������������ ����� ������, ������� ��������� ��� �������� �������� ������.
*/
template<class Type> class Object {
public:

	Object (const Type &data, wptr<Object<Type>> sucessor = nullptr, wptr<Object<Type>> predecessor = nullptr);

	~Object();



	uptr<Object<Type>> GetSucessor() const noexcept;
	uptr<Object<Type>> GetPredecessor() const noexcept;
	Type GetData() const noexcept;



	void SetSucessor (wptr<Object<Type>> otherSucessor) noexcept;
	void SetPredecessor (wptr<Object<Type>> otherPredecessor) noexcept;
	void SetData (Type &otherData) noexcept;



	template<class T> friend std::ostream &operator<< (std::ostream &output, Object<T> &object);

private:
	sptr<Object> _sucessor;
	sptr<Object> _predecessor;
	Type  _data;
};


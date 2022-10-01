/*****************************************************************//**
 * \file   Object.cpp
 * \brief  ���� ������������ ������ `Object`.
 * 
 * ��������������� ����� ��� �����������. ��������� � ����
 * �������� ����������. ����� ���������� ����� ����� ���������. 
 * ������������ ������ ������ � ����� `Object.h`.
 * 
 * \author averu
 * \version
 * \date   September 2022
 *********************************************************************/
#include "Object.h"



/**
 * ����������� ������ `Object<Type>`.
 *
 * \param data
 * \param sucessor
 * \param predecessor
 */
template<class Type> Object<Type>::Object(const Type &data,
									  wptr<Object<Type>> sucessor,
									  wptr<Object<Type>> predecessor) {

	_sucessor = sucessor;
	_predecessor = predecessor;
	_data = data;
}

/**
 * ���������� ������ `Object<Type>`.
 *
 * /waring ���������� ��������� ������������.
 */
template<class Type> Object<Type>::~Object() = default;



/**
 * ������������� ����������� �������� ������ � ���� `_sucessor`.
 *
 * \return ��������� �� ��������� ����.
 */
template<class Type> uptr<Object<Type>> Object<Type>::GetSucessor() const noexcept { return _sucessor; }

/**
 * ������������� ����������� �������� ������ � ���� `_predecessor`.
 *
 * \return ��������� �� ���������� ����.
 */
template<class Type> uptr<Object<Type>> Object<Type>::GetPredecessor() const noexcept { return _predecessor; }

/**
 * ������������� ����������� �������� ������ � ���� `_data`.
 *
 * \return ����� ������, ������� �������� ������� ����.
 */
template<class Type> Type Object<Type>::GetData() const noexcept { return _data; }



/**
 * ������������� ����������� ���������� ����� �������� ��� ���� `_sucessor`.
 *
 * \param otherSucessor
 */
template<class Type> void Object<Type>::SetSucessor(wptr<Object<Type>> otherSucessor) noexcept {
	_sucessor = otherSucessor;
}

/**
 * ������������� ����������� ���������� ����� �������� ��� ���� `_predecessor`.
 *
 * \param otherPredecessor
 */
template<class Type> void Object<Type>::SetPredecessor(wptr<Object<Type>> otherPredecessor) noexcept {
	_predecessor = otherPredecessor;
}

/**
 * * ������������� ����������� ���������� ����� �������� ��� ���� `_data`.
 *
 * \param otherData
 */
template<class Type> void Object<Type>::SetData(Type & otherData) noexcept {
	_data = otherData;
}



/**
 * ���������� ��������� `operator<<`.
 *
 * \param output
 * \param object
 */
template<class T> std::ostream &operator<< (std::ostream & output, const Object<T> &object) {
	output << object._data;


	return output;
}

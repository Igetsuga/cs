#pragma once

#include "BinaryTreeIterated.h"


template<class Type> class AVLTree : public BinaryTreeIterated<Type> {
public:
	
	AVLTree<Type>() : BinaryTreeIterated<Type>();

	virtual ~AVLTree<Type>();

	virtual Node<Type> *push (Node<Type> *node) override;

	//������������ ������� ���������� ����. �������� ����������, �� �������� ���� ���� - ���������� � ����� ��� ������ ���������
	virtual Node<Type> *push_R (const Node<Type> *node, const Node<Type> *Current) override;

	//������� ��� ���������� �����. ������ ����� ���� � ����� ������� � �������� ������ ������� ���������� � ������
	virtual Node<Type> *push (const Type &data) override;

	//�������� ����
	virtual void pop (const Node<Type> *node) override;

protected:
	//����������� �������� ����� ���� �����������
	const int bfactor (const Node<Type> *p) const noexcept;

	//��� ���������� ����� � ��� ��� ���������� � �������, �.�. �� ����, ���� � ������ ��� �������
	//����� ���������� ���� ������������ ��� ������ (���������� �� �����) � ����������� ������ � �����, ��� ���
	//�������� ����� ����������
	void fixHeight (const Node<Type> *node) noexcept;

	
	const Node<Type> *RotateRight(Node<Type> *node) noexcept;

	const Node<Type> *RotateLeft(Node<Type> *q) noexcept;

	//������������ ��������� ���� p - ����� ������ ��������� � ����������� �� ���������� �������
	const Node<Type> *Balance(Node<Type> *p) noexcept;
};
#pragma once

#include "BinaryTreeIterated.h"


template<class Type> class AVLTree : public BinaryTreeIterated<Type> {
public:
	
	AVLTree<Type>() : BinaryTreeIterated<Type>();

	virtual ~AVLTree<Type>();

	virtual Node<Type> *push (Node<Type> *node) override;

	//рекуррентная функция добавления узла. Устроена аналогично, но вызывает сама себя - добавление в левое или правое поддерево
	virtual Node<Type> *push_R (const Node<Type> *node, const Node<Type> *Current) override;

	//функция для добавления числа. Делаем новый узел с этими данными и вызываем нужную функцию добавления в дерево
	virtual Node<Type> *push (const Type &data) override;

	//удаление узла
	virtual void pop (const Node<Type> *node) override;

protected:
	//определение разности высот двух поддеревьев
	const int bfactor (const Node<Type> *p) const noexcept;

	//при добавлении узлов в них нет информации о балансе, т.к. не ясно, куда в дереве они попадут
	//после добавления узла рассчитываем его высоту (расстояние до корня) и редактируем высоты в узлах, где это
	//значение могло поменяться
	void fixHeight (const Node<Type> *node) noexcept;

	
	const Node<Type> *RotateRight(Node<Type> *node) noexcept;

	const Node<Type> *RotateLeft(Node<Type> *q) noexcept;

	//балансировка поддерева узла p - вызов нужных поворотов в зависимости от показателя баланса
	const Node<Type> *Balance(Node<Type> *p) noexcept;
};
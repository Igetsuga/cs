#pragma once
#include <iostream>
#include <memory>

template<class Type> using uptr = std::unique_ptr<Type>;
template<class Type> using sptr = std::shared_ptr<Type>;
template<class Type> using wptr = std::weak_ptr<Type>;

/**
 * Класс представляет собой обочку, которая покрывает все элементы связного списка.
 */
template<class Type> class Node {
public:

	Node (const Type &data, wptr<Node<Type>> sucessor = nullptr, wptr<Node<Type>> predecessor = nullptr);

	~Node();



	uptr<Node<Type>> GetSucessor() const noexcept; 
	uptr<Node<Type>> GetPredecessor() const noexcept;
	Type GetData() const noexcept;



	void SetSucessor (wptr<Node<Type>> otherSucessor) noexcept;
	void SetPredecessor (wptr<Node<Type>> otherPredecessor) noexcept;
	void SetData (Type &otherData) noexcept;



	template<class T> friend std::ostream &operator<< (std::ostream &output, Node<T> &node);

private:
	sptr<Node> _sucessor;
	sptr<Node> _predecessor;
	Type  _data;
};


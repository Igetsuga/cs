#include "Node.h"



/**
 * Конструктор класса `Node<Type>`.
 * 
 * \param data
 * \param sucessor
 * \param predecessor
 */
template<class Type> Node<Type>::Node(const Type &data,
									  wptr<Node<Type>> sucessor,
									  wptr<Node<Type>> predecessor) {
	
	_sucessor = suceessor;
	_predecessor = predecessor;
	_data = data;
}

/**
 * Деструктор класса `Node<Type>`.
 * 
 * /waring Деструктор определен компилятором.
 */
template<class Type> Node<Type>::~Node() = default;



/**
 * Предоставляет возможность получить доступ к полю `_sucessor`.
 * 
 * \return Указатель на следующий узел.
 */
template<class Type> uptr<Node<Type>> Node<Type>::GetSucessor() const noexcept { return _sucessor; }

/**
 * Предоставляет возможность получить доступ к полю `_predecessor`.
 * 
 * \return Указатель на предыдущий узел.
 */
template<class Type> uptr<Node<Type>> Node<Type>::GetPredecessor() const noexcept { return _predecessor; }

/**
 * Предоставляет возможность получить доступ к полю `_data`.
 * 
 * \return Копию данных, которые содержит текущий узел.
 */
template<class Type> Type Node<Type>::GetData() const noexcept { return _data; }



/**
 * Предоставляет возможность установить новое значение для поля `_sucessor`.
 * 
 * \param other
 */
template<class Type> void Node<Type>::SetSucessor(wptr<Node<Type>> otherSucessor) noexcept {
	_sucessor = otherSucessor;
}

/**
 * * Предоставляет возможность установить новое значение для поля `_predecessor`.
 * 
 * \param other
 */
template<class Type> void Node<Type>::SetPredecessor(wptr<Node<Type>> otherPredecessor) noexcept {
	_predecessor = otherPredecessor;
}

/**
 * * Предоставляет возможность установить новое значение для поля `_data`.
 * 
 * \param data
 */
template<class Type> void Node<Type>::SetData(Type &otherData) noexcept {
	_data = otherData;
}



/**
 * Перегрузка оператора `operator<<`.
 * 
 * \param output
 * \param node
 */
template<class T> std::ostream &operator<< (std::ostream &output, const Node<T> &node) {
	output << node._data;

	
	return output;
}

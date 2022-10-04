/*****************************************************************//**
 * \file   Object.cpp
 * \brief  Файл определения класса `Object`.
 *
 * Вспомогательный класс для контейнеров. Выступает в роли
 * элемента контейнера. Класс реализован через умные указатели.
 * Объявление класса смотри в файле `Object.h`.
 *
 * \author  Sirazetdinov Rustem
 * \warning Класс не реализован. НЕ ИСПОЛЬЗОВАТЬ КЛАСС!
 * \date    September 2022
 *********************************************************************/
#include "Object.h"



/**
 * Конструктор класса.
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
 * Деструктор класса.
 *
 * \waring Деструктор определен компилятором.
 */
template<class Type> Object<Type>::~Object() = default;



/**
 * Предоставляет возможность получить доступ к полю `_sucessor`.
 *
 * \return Указатель на следующий узел.
 */
template<class Type> uptr<Object<Type>> Object<Type>::GetSucessor() const noexcept { return _sucessor; }

/**
 * Предоставляет возможность получить доступ к полю `_predecessor`.
 *
 * \return Указатель на предыдущий узел.
 */
template<class Type> uptr<Object<Type>> Object<Type>::GetPredecessor() const noexcept { return _predecessor; }

/**
 * Предоставляет возможность получить доступ к полю `_data`.
 *
 * \return Копию информации, которую содержит текущий узел.
 */
template<class Type> Type Object<Type>::GetData() const noexcept { return _data; }



/**
 * Предоставляет возможность установить новое значение для поля `_sucessor`.
 *
 * \param otherSucessor
 */
template<class Type> void Object<Type>::SetSucessor(wptr<Object<Type>> otherSucessor) noexcept {
	_sucessor = otherSucessor;
}

/**
 * Предоставляет возможность установить новое значение для поля `_predecessor`.
 *
 * \param otherPredecessor
 */
template<class Type> void Object<Type>::SetPredecessor(wptr<Object<Type>> otherPredecessor) noexcept {
	_predecessor = otherPredecessor;
}

/**
 * * Предоставляет возможность установить новое значение для поля `_data`.
 *
 * \param otherData
 */
template<class Type> void Object<Type>::SetData(Type & otherData) noexcept {
	_data = otherData;
}



/**
 * Перегрузка оператора `operator<<`.
 *
 * \param output
 * \param object
 * 
 * \return Ссылку на поток стандартного вывода.
 */
template<class T> std::ostream &operator<< (std::ostream & output, const Object<T> &object) {
	output << object._data;


	return output;
}

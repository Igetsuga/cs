#define nline '\n'
#include <iostream>
#include <limits>

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////

class Vector {
public:

    // full constructor
    Vector (double x = 0, double y = 0, double z = 0) noexcept { // x{_x} : y{_y} : z{_z}
        _x = x; _y = y; _z = z;
    }
    
    // destructor
    ~Vector() = default;
     
    // type interpretator
    template <class Type> Vector (const Type &value) noexcept {
        _x = value; _y = 0; _z = 0;
    }
 


    Vector operator+= (const Vector &other) noexcept {
        _x += other._x;
        _y += other._y;
        _z += other._z;


        return *this;
    }

    Vector operator+ (const Vector &other) const noexcept {
        Vector result(*this);

        return result += other;
    }

	Vector operator+= (const int &value) noexcept {
		_x += value;


		return *this;
	}

	Vector operator+ (const int &value) const noexcept {
		Vector result(*this);

		return result += value;
	}

 

    void Print() const {
        std::cout << nline << "{" << _x << ", " << _y << ", " << _z << "}" << nline;
    }


    
    friend Vector operator+ (const int &value, const Vector &other) noexcept;
    friend Vector operator+= (const int &value, Vector &other) noexcept;
    

protected:
    double _x = 0;
    double _y = 0;
    double _z = 0;

};


Vector operator+ (const int &value, const Vector &other) noexcept {
	Vector temp(other);


	return (temp + value);
}

Vector operator+= (const int &value, Vector &other) noexcept {
	Vector temp(value);

	return (other += temp);
}

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////



class Exception : public std::exception {
protected:
	//сообщение об ошибке
	char *str;
public:
	Exception(const char *s)
	{
		str = new char[strlen(s) + 1];
		strcpy_s(str, strlen(s) + 1, s);
	}
	Exception(char *s)
	{
		str = new char[strlen(s) + 1];
		strcpy_s(str, strlen(s) + 1, s);
	}
	Exception()
	{
		str = NULL;
	}
	Exception(const Exception &e)
	{
		str = new char[strlen(e.str) + 1];
		strcpy_s(str, strlen(e.str) + 1, e.str);
	}
	~Exception()
	{
		delete [] str;
	}

	//функцию вывода можно будет переопределить в производных классах, когда будет ясна конкретика
	virtual void print()
	{
		std::cout << "Exception: " << str << "; " << what();
	}
};

template<class T> class Element {
protected:
	Element *next;
	T info;
public:
	Element(T data)
	{
		next = NULL;
		info = data;
	}

	Element(T data, Element *Next)
	{
		next = Next;
		info = data;
	}

	template<class T1>
	friend std::ostream &operator<<(std::ostream &s, Element<T1> &el);

	Element *getNext() { return next; }
	void setNext(Element *value) { next = value; }

	T getData() { return info; }
	void setData(T value) { info = value; }
};

template<class T1> std::ostream &operator<<(std::ostream &s, Element<T1> &el)
{
	s << el.info;
	return s;
}

template<class T> class ForwardList {
protected:
	Element<T> *head_;
public:

	ForwardList() { head_ = nullptr; }

	virtual Element<T> *pop() = 0;
	virtual Element<T> *push(T value) = 0;

	T &operator[](int index) = 0;

	template<class T1> friend std::ostream &operator<< (std::ostream &s, ForwardList<T1> &el);

	virtual ~ForwardList() {};
};


template<class Type> class LinkedList : public ForwardList<Type> {


	// typedef ForwardList<Type>::head_ ForwardList<Type>::head_;

	// default constructor.
	LinkedList()
	{
		ForwardList<Type>::head_ = nullptr;
		size_ = 0;
	}

	// destructor.
	~LinkedList()
	{
		size_ = 0;
		forceObjectDelete(ForwardList<Type>::head_);
	}

	// for destructor. 
	void forceObjectDelete (Element<Type> *element)
	{
		if ( element == nullptr ) { return; }

		Element<Type> *nextObjectDelete = element->getNext();
		delete element;

		forceObjectDelete(nextObjectDelete);
	}

	// shallow copy
	LinkedList (const LinkedList<Type> &other)
	{
		if ( other.size_ != 0 ) {
			ForwardList<Type>::head_ = new Element<Type> (other.ForwardList<Type>::head_->getData()); // c. (*head_).data_ = (*other.head).data_;
														// c. (*head_).sucessor_ = nullptr;
														// c. (*head_).predecessor_ = nullptr;
			Element<Type> *this_ptr_current = ForwardList<Type>::head_;
			Element<Type> *other_ptr_current = other.ForwardList<Type>::head_;

			while ( other_ptr_current != other.GetSize_() ) {
				// c. (*this_ptr_current).data_ = (*other_ptr_current).data_; 
				// c. (*this_ptr_current).sucessor_ = nullptr;

				Element<Type> *this_ptr_new_sucessor = new Element<Type>((other_ptr_current->getNext())->getData(), this_ptr_current);

				this_ptr_current->setNext(this_ptr_new_sucessor);
				// (this_ptr_current->GetSucessor())->SetPredecessor( this_ptr_current );

				this_ptr_current = this_ptr_current->getNext();
				other_ptr_current = other_ptr_current->getNext();
			}

		}
		else {
			ForwardList<Type>::head_ = nullptr;
		}

		size_ = other.size_;
	}


	Element<Type> *push (const Type &data) noexcept override final
	{

		if ( size_ == 0 ) {
			ForwardList<Type>::head_ = new Element<Type> (data, ForwardList<Type>::head_);
			size_++;
		}
		else {
			Element<Type> *elementCurrent = ForwardList<Type>::head_;

			while ( elementCurrent->GetData() < elementCurrent->getNext()->getData() ) {
				elementCurrent = elementCurrent->getNext();
			}

			Element<Type> *elementInsert = new Element<Type> (data, elementCurrent->getNext());

			elementCurrent->setNext(elementInsert);
			size_++;

			return elementInsert;
		}
	}

	Element<Type> *pop() noexcept override final
	{
		if ( size_ == 0 ) {
			return;
		}
		else {
			Element<Type> *elementCurrent = ForwardList<Type>::head_;

			for ( int position = 1; position < size_ - 1; position++ ) {
				elementCurrent = elementCurrent->getNext();
			}


			Element<Type> *removeElement = elementCurrent->getNext();
			Element<Type> *new_sucessor_ = removeElement->getNext();

			Element<Type> *removeCopy = removeElement;
			delete removeElement;

			elementCurrent->setNext() = new_sucessor_;
			size_--;


			return removeCopy;
		}
	}


	LinkedList<Type> slice (const int start = 1, const int finish = size_) const {

		if (start > size_ || finish > size_ || start < 1 || finish < 1) { throw std::out_of_range("LinkedList<Type>::slice: pos < 0"); }
		if ( size_ == 0 ) { throw Exception("The size of your vector is equal 0, slice cant be received"); }
		
		
		size_t pos = 1; LinkedList<Type> result;
		// if ( start == finish ) { return result; }
		
		Element<Type> *currentElement = ForwardList<Type>::head_;
		

		while ( pos <= size_ ) {
			
			if ( pos >= start && pos <= finish ) { result.push( currentElement->getData() ); }
			else if ( pos > finish ) { /*return result;*/ break; }

			currentElement = currentElement->getNext();
			pos++;
		}


		return result;
	}






	Type find (const Element<Type>* element) const noexcept {
		
		Type value = element->info();

		int itt_right = size_;
		int itt_left = 1;
		int itt_middle = 0;

		if ( this->[itt_left] == value ) { return itt_left; }
		if ( this->[itt_right] == value ) { return itt_right; }

		while ( itt_left <= itt_right ) {

			itt_middle = itt_left + ( (itt_right - itt_left) / 2 );

			if ( this->[itt_middle] == value ) { return itt_middle; }
			else if ( this->[itt_middle] > value ) { itt_right = itt_middle - 1; }
			else { itt_left = itt_middle + 1; }
		}


		return itt_middle;

		Element<Type> *elementCurrent = ForwardList<Type>::head_;
		
		for ( int position = 1; position <= size_; position++ ) {
			if ( elementCurrent == element ) { return position; }\
			else { elementCurrent = elementCurrent->getNext(); }
		}


		return 0;
	}


	Element<Type>* GetPredecessor (const Element<Type> *element) const noexcept {
		Element<Type> *elementCurrent = ForwardList<Type>::head_;

		if ( element == nullptr || size_ <= 1 ) { return nullptr; }

		while ( elementCurrent->getNext() != element ) {
			elementCurrent = elementCurrent->getNext();
		}


		return elementCurrent;
	}


	Element<Type>* GetHead() const noexcept { return ForwardList<Type>::head_; }

	Type &operator[] (const int &pos) const {

		if ( pos <= 0 ) { throw std::out_of_range("LinkedList<Type>::operator[]: pos < 0"); }
		else if ( pos > size_ ) { throw std::out_of_range("LinkedList<Type>::operator[]: pos > size"); }

		Element<Type> *elementCurrent = ForwardList<Type>::head_;

		for ( size_t itt = 1; itt != pos; itt++ ) {
			elementCurrent = elementCurrent->getNext();
		}


		return elementCurrent->getData();
	}


	const size_t &GetSize() const noexcept { return size_; }

	template <class Type> friend std::ostream& operator<< (std::ostream &output, const LinkedList<Type> &list);

	//void PrintReverse() const noexcept {

	//	std::cout << nline;

	//	for ( size_t itt = size_; itt > 0; itt-- ) {
	//		std::cout << this->[itt] << " ";
	//	}

	//	std::cout << nline;
	//}


protected:
	size_t size_;

};

template <class Type> std::ostream &operator<< (std::ostream &output, const LinkedList<Type> &list) {

	if ( size_ == 0 ) { /*throw Exception("...");*/ return output; }
	int pos = 1; 

	Element<Type> *currentElement = list.GetHead();
	
	output << nline;
	if ( typeid(output).name() == typeid(std::ofstream).name() ) {
		
		while ( pos <= size_ ) {
			output << currentElement->getData() << " ";
			
			currentElement = currentElement->getNext();
			
			pos++;
		}
	}
	else {
		output << "{";

		while ( pos <= size_ ) {
			output << currentElement->getData() << ", ";
			
			currentElement = currentElement->getNext();
			
			pos++;
		}

		output << "}";
	}
	output << nline;

		
	return output;
}



int main()
{
    Vector vector_1(1, 2, 4); Vector vector_2(4, 2, 1); Vector vector_3(1, 1, 1);
    vector_1.Print(); vector_2.Print(); vector_3.Print();


    Vector vector_result = vector_1 + vector_2 + vector_3;
    vector_result.Print();

    vector_result = vector_result + 64 + 1; vector_result.Print();

    vector_result = -5 + vector_result; vector_result.Print();

    /////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////

	// LinkedList<int> list();
	// list.push(12);

    return 0;
}











































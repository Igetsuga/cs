#include <iomanip>
#include <iostream>
#include <fstream>
// #include "LinkedList.cpp"

///////////////////////////////////////////////////////////////////////////////
// class Human. 
class Human
{
public:
    // default constructor
    Human(std::string name = "unknown", std::string surname = "unknown")
    {
        name_ = name;
        surname_ = surname;
    }

    // copy constructor.
    Human(const Human& other) = default;

    // operator= .
    Human& operator= (const Human& other) = default;

    // destructor.
    virtual ~Human() = default; // { std::cout << "Object \"Human\" was deleted" << '\n'; } // = default;



    // Get & Set.
    std::string GetName() { return name_; }
    std::string GetSurname() { return surname_; }
    void SetName(std::string name) { name_ = name; }
    void SetSurname(std::string surname) { surname_ = surname; }



protected:
    std::string name_;
    std::string surname_;
};



// class Worker.
class Worker : public Human
{
public:
    // default constructor
    Worker(std::string job = "unknown") { job_ = job; }

    // copy constructor.
    Worker(const Worker& other) = default;

    // operator= .
    Worker& operator= (const Worker& other) = default;

    // destructor.
    virtual ~Worker() = default; // { std::cout << "Object \"Worker\" was deleted" << '\n'; }// = default;



    // Get & Set.
    std::string GetJob() { return job_; }
    void SetJob(std::string job) { job_ = job; }



protected:
    std::string job_;
};



class Programmer : public Worker
{
public:
    // default constructor.
    Programmer(
        const         int& level      = 0,
        const std::string& lang       = "unknown",
        const std::string& name       = "unknown",
        const std::string& surname    = "unknown",
        const std::string& email      = "unknown",
        const std::string& telegramID = "unknown",
        const std::string& skypeID    = "unknown",
        const std::string& job        = "unknown")

    {
             Programmer::level_ = level;
              Programmer::lang_ = lang;
                   Human::name_ = name;
                Human::surname_ = surname;
             Programmer::email_ = email;
        Programmer::telegramID_ = telegramID;
           Programmer::skypeID_ = skypeID;
                   Worker::job_ = job;
    }

    // copy constructor.
    Programmer(const Programmer& other)
    {
        // this->Human = other.Human
        this->Human::name_ = other.Human::name_;
        this->Human::surname_ = other.Human::surname_;

        this->Worker::job_ = other.Worker::job_;

        this->Programmer::level_ = other.Programmer::level_;
        this->Programmer::lang_ = other.Programmer::lang_;
        this->Programmer::email_ = other.Programmer::email_;
        this->Programmer::telegramID_ = other.Programmer::telegramID_;
        this->Programmer::skypeID_ = other.Programmer::skypeID_;
    }

    // destructor
    virtual ~Programmer() = default; // { std::cout << "Object \"Pragrammer\" was deleted" << '\n'; }

    void GetInfo() const
    {
        std::cout << '\n' << "---------------------START--------------------" << '\n';

        std::cout << "   name: " << (*this).Human::name_ << '\n'
            << "surname: " << (*this).Human::surname_ << '\n'
            << "------------------Information:----------------" << '\n';

        std::cout << "     level: " << (*this).Programmer::level_ << '\n'
            << "      lang: " << (*this).Programmer::lang_ << '\n'
            << "     email: " << (*this).Programmer::email_ << '\n'
            << "telegramID: " << (*this).Programmer::telegramID_ << '\n'
            << "   skypeID: " << (*this).Programmer::skypeID_ << '\n'
            << "       job: " << (*this).Worker::job_ << '\n'
            << "----------------------END---------------------" << '\n';
    }

    friend std::ostream& operator<< (std::ostream& output, const Programmer& programmer);
    friend std::istream& operator>> (std::istream& output, Programmer& programmer);

protected:
    int            level_;
    std::string    lang_;
    std::string    email_;
    std::string    telegramID_;
    std::string    skypeID_;
};
std::ostream& operator<< (std::ostream& output, const Programmer& programmer)
{
    if ( typeid(output).name() == typeid(std::ofstream).name() )
    {
       
    }
    else
    {
        output << programmer.name_;
    }
    


    return output;
}
std::istream& operator>> (std::istream& input, Programmer& programmer)
{
    if ( typeid(input).name() == typeid(std::ofstream).name() )
    {

    }
    else
    {
        input >> programmer.level_;
        input >> programmer.lang_;
        input >> programmer.email_;
        input >> programmer.telegramID_;
        input >> programmer.skypeID_;
    }


    return input;
}
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////
// class LinkedList.
template<class Type> class LinkedList
{
public:

    virtual class Object
    {
    public:
        // default constructor.
        Object(const Type& data, LinkedList<Type>::Object* sucessor = nullptr, LinkedList<Type>::Object* predecessor = nullptr)
        {
               sucessor_ = sucessor;
            predecessor_ = predecessor;
                   data_ = data;
        }

        // destructor.
        ~Object() = default;



        Type removeNext()
        {
            Object* removeObject = sucessor_; Type data = removeObject->data_;
            Object* new_sucessor_ = removeObject->sucessor_;

            delete removeObject;

            sucessor_ = new_sucessor_;
            new_sucessor_->predecessor_ = this;

            return data;
        }

        void insertNext() {};

        // protected:
        LinkedList<Type>::Object* sucessor_;
        LinkedList<Type>::Object* predecessor_;
                            Type  data_;
    };



    // default constructor.
    LinkedList()
    {
        head_ = tail_ = nullptr;
        size_ = 0;
    }

    // copy constructor.
    LinkedList(const LinkedList& other)
    {
        if (other.size_ != 0)
        {
            head_ = new Object(other.head_->data_); // c. (*head_).data_ = (*other.head).data_;
                                                    // c. (*head_).sucessor_ = nullptr;
                                                    // c. (*head_).predecessor_ = nullptr;
            Object* this_ptr_current = head_;
            Object* other_ptr_current = other.head_;

            while (other_ptr_current != nullptr)
            {
                // c. (*this_ptr_current).data_ = (*other_ptr_current).data_; 
                // c. (*this_ptr_current).sucessor_ = nullptr;
                this_ptr_current->sucessor_ = new Object(other_ptr_current->sucessor_->data_);
                (this_ptr_current->sucessor_)->predecessor_ = this_ptr_current;

                this_ptr_current = this_ptr_current->sucessor_;
                other_ptr_current = other_ptr_current->sucessor_;
            }
        }
        else
        {
            head_ = tail_ = nullptr;
        }

        size_ = other.size_;
    }

    LinkedList& operator= (const LinkedList& other) // coping, not rename other.
                                                    // this->sucessor_ != other->sucessor_.
                                                    // this->data_ = other->data_.
    {
        this->clear();

        size_ = other.size_;
        head_ = nullptr;

        if (size_ != 0)
        {

            Object* ptr_other_iterator = other.head_;
            Object* ptr_this = new Object(other.head_->data_);
            head_ = ptr_this; // after: head_->sucessor_ = ptr_this->sucessor_ (=nullptr);  
                              //        head_->data_ = ptr_this->data_ (=other.head_->data_);
            Object* ptr_other_data_copy = nullptr;

            ptr_other_iterator = ptr_other_iterator->sucessor_;
            while (ptr_other_iterator != nullptr)
            {
                ptr_other_data_copy = new Object(ptr_other_iterator->data_);
                ptr_this->sucessor_ = ptr_other_data_copy;
                ptr_this = ptr_other_data_copy; // КАК ЭТО ПРОИСХОДИТ, ЕСЛИ У МЕНЯ НЕ ПЕРЕГРУЖЕН ОПЕРАТОР= ДЛЯ объектов Object
                ptr_other_iterator = ptr_other_iterator->sucessor_;
            }

        }


        return *this;
    }

    // destructor.
    virtual ~LinkedList()
    {
        size_ = 0;
        forceObjectDelete(head_);
    }

    // for destructor. 
    virtual void forceObjectDelete(Object* object) final
    {
        if (object == nullptr) { return; }

        LinkedList<Type>::Object* nextObjectDelete = object->sucessor_;
        delete object;

        forceObjectDelete(nextObjectDelete);
    }

    virtual void clear() final
    {
        while (head_ != nullptr) // <=> (head_ != tail_)
        {
            this->removeFront();
        }
        size_ = 0;
    }



    virtual void insert(const int& pos, const Type& data)
    {
        if (pos <= 0) { throw std::out_of_range("LinkedList<Type>::insert: pos < 0"); }
        else if (pos > size_ + 1 && (pos != 1 && size_ != 0)) { throw std::out_of_range("LinkedList<Type>::insert: pos > size"); }

        if (pos == 1)
        {
            this->pushFront(data);
        }
        else if (pos == size_ + 1)
        {
            this->pushBack(data);
        }
        else
        {
            Object* objectCurrent = head_;

            for (int position = 1; position < pos - 1; position++)
            {
                objectCurrent = objectCurrent->sucessor_;
            }

            Object* objectInsert = new Object(data, objectCurrent->sucessor_, objectCurrent);
            
            objectCurrent->sucessor_ = objectInsert;
            (objectInsert->sucessor_)->predecessor_ = objectInsert;

            size_++;
        }
    }

    virtual void pushFront(const Type& data) final
    {
        head_ = new Object(data, head_);

        if (size_ == 0)
        {
            tail_ = head_;
        }
        else 
        {
            (head_->sucessor_)->predecessor_ = head_;
        }

        size_++;
    }

    virtual void pushBack(const Type& data) final
    {
        if (size_ == 0)
        {
            head_ = tail_ = new Object(data, nullptr, nullptr); // <==> head_ = new Object(data, nullptr, nullptr);
        }
        else
        {
            tail_ = new Object(data, nullptr, tail_);
            (tail_->predecessor_)->sucessor_ = tail_;
        }
        size_++;
    }



    virtual Type remove(const int& pos)
    {
        if (pos <= 0) { throw std::out_of_range("LinkedList<Type>::remove: pos < 0"); }
        else if (pos > size_) { throw std::out_of_range("LinkedList<Type>::remove: pos > size"); }

        if (pos == 1)
        {
            return this->removeFront();
        }
        else
        {
            Object* objectCurrent = head_;

            for (int position = 1; position < pos - 1; position++)
            {
                objectCurrent->sucessor_;
            }

            size_--;


            return objectCurrent->removeNext();
        }
    }

    virtual Type removeFront() final
    {

        Type data = head_->data_;

        if ( size_ == 1 )
        {
            delete head_; head_ = tail_ = nullptr;
        }
        else
        {
            Object* next_after_head = head_->sucessor_;
            delete head_; head_ = next_after_head;
            head_->predecessor_ = nullptr;
        }
        size_--;


        return data;
    }

    virtual Type removeBack() final
    {
        size_--;

        Object* before_tail_= tail_->predecessor_; Type data = tail_->data_;

        delete tail_;

        tail_ = before_tail_; tail_->sucessor_ = nullptr;


        return data;
    }




    size_t size() const { return size_; }

    virtual LinkedList<Type>::Object* GetObject(const int& pos) const
    {
        if (pos <= 0 || pos > size_) { throw std::out_of_range("LinkedList<Type>::*GetObject: index out of range"); }
        else {
            // size_t position = static_cast<size_t>(pos);

            Object* ptr_current = this->head_;
            for (int pos_current = 1; pos_current < pos; pos_current++)
            {
                ptr_current = ptr_current->sucessor_;
            }


            return ptr_current;
        }

    }

    virtual const Type& operator[] (const int& pos) const final { return GetObject(pos)->data_; }

    virtual LinkedList<Type> filter(bool (*fn)(Type))
    {
        LinkedList<Type> resultList;

        int size = static_cast<int>(size_);
        for (int i = 1; i <= size; i++)
        {
            if (fn((*this)[i])) // if (fn (this->GetObject(pos)->data_) )
            {
                resultList.pushBack((*this)[i]);
            }
        }


        return resultList;
    }



    template<class Type> friend std::ostream& operator<< (std::ostream& output, const LinkedList<Type>& list);

    // template<class Type> friend std::istream& operator>> (std::istream& input, Object object);


protected:
    
    Object* head_;
    Object* tail_;
    size_t  size_;
};
template<class Type> std::ostream& operator<< (std::ostream& output, const LinkedList<Type>& list)
{
    if (typeid(output).name() != typeid(std::ofstream).name())
    {
        output << '\n' << "{ ";
        for ( int object_number = 1; object_number <= list.size_; object_number++ )
        {
            output << list[object_number] << " ";
        }
        output << "}" << '\n';
    }
    else
    {
 
    }


    return output;
}




///////////////////////////////////////////////////////////////////////////////
// class Stack.
template<class Type> class Stack : public LinkedList<Type>
{
public:

    // constructor.
    Stack<Type>() : LinkedList<Type>() {};

    // destructor.
    virtual ~Stack<Type>() = default;



    void insert(const Type& data) { LinkedList<Type>::pushBack(data); }

    Type remove() { return LinkedList<Type>::removeFront(); }

    
};


///////////////////////////////////////////////////////////////////////////////
// class DLS.

template<class Type> class DLS : public LinkedList<Type>
{
    typedef LinkedList<Type>::Object llObject;
public:
    
    // constructor.
    DLS<Type>() : LinkedList<Type>() {};

    // destructor.
    virtual ~DLS<Type>() = default;



    void insert(const int& pos, const Type& data) override
    {
        if ( pos <= 0 ) { throw std::out_of_range("LinkedList<Type>::insert: pos < 0"); }
        else if ( pos > LinkedList<Type>::size_ + 1 && (pos != 1 && LinkedList<Type>::size_ != 0) ) 
        { throw std::out_of_range("LinkedList<Type>::insert: pos > size"); }

        if ( pos == 1 )
        {
            this->LinkedList<Type>::pushFront(data);
        }
        else if ( pos == LinkedList<Type>::size_ + 1 )
        {
            this->LinkedList<Type>::pushBack(data);
        }
        else if (pos < LinkedList<Type>::size_ / 2)
        {
            auto* objectCurrent = LinkedList<Type>::head_;

            for ( int position = 1; position < pos - 1; position++ )
            {
                objectCurrent = objectCurrent->sucessor_;
            }

            llObject* objectInsert = new llObject(data, objectCurrent->sucessor_, objectCurrent);

            objectCurrent->sucessor_ = objectInsert;
            (objectInsert->sucessor_)->predecessor_ = objectInsert;

            LinkedList<Type>::size_++;
        }
    }

    //virtual Type remove()
    //{
    //    std::cout<< "gjitk yfpeq";
    //}
};


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
int main()
{
    // Задание 6.0: Проверка общей работоспособности системы.
    ////////////////////////////////////////////////////////////////////////////
    Programmer Rustem1(1, "c++", "Rustem1", "Sirazetdinov",
        "avesirazetdinov@gmail.com", "I_getsuga");
    Programmer Rustem2(1, "c++", "Rustem2", "Sirazetdinov",
        "avesirazetdinov@gmail.com", "I_getsuga");
    Programmer Rustem3(1, "c++", "Rustem3", "Sirazetdinov",
        "avesirazetdinov@gmail.com", "I_getsuga");
    Programmer Rustem4(1, "c++", "Rustem4", "Sirazetdinov",
        "avesirazetdinov@gmail.com", "I_getsuga");
    Programmer Rustem5(1, "c++", "Rustem5", "Sirazetdinov",
        "avesirazetdinov@gmail.com", "I_getsuga");
    Programmer Rustem6(1, "c++", "Rustem6", "Sirazetdinov",
        "avesirazetdinov@gmail.com", "I_getsuga");
    Programmer Rustem7(1, "c++", "Rustem7", "Sirazetdinov",
        "avesirazetdinov@gmail.com", "I_getsuga");
    Programmer Rustem8(1, "c++", "Rustem8", "Sirazetdinov",
        "avesirazetdinov@gmail.com", "I_getsuga");
    Programmer Rustem9(1, "c++", "Rustem9", "Sirazetdinov",
        "avesirazetdinov@gmail.com", "I_getsuga");
    Programmer Rustem10(1, "c++", "Rustem10", "Sirazetdinov",
        "avesirazetdinov@gmail.com", "I_getsuga");
    Programmer Rustem11(1, "c++", "Rustem11", "Sirazetdinov",
        "avesirazetdinov@gmail.com", "I_getsuga");
    Programmer Rustem12(1, "c++", "Rustem12", "Sirazetdinov",
        "avesirazetdinov@gmail.com", "I_getsuga");
    ///////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////
    LinkedList<Programmer> list;

    list.pushBack(Rustem1); std::cout << list;
    list.pushFront(Rustem2); std::cout << list;
    list.insert(2, Rustem3); std::cout << list;
    auto something1 = list.removeBack(); std::cout << list << something1;
    auto something2 = list.removeFront(); std::cout << list << something2;

    list.pushBack(Rustem4); list.pushBack(Rustem5); list.pushBack(Rustem6);
    list.pushBack(Rustem7); list.pushBack(Rustem8); std::cout << list;

    auto something3 = list.remove(2); std::cout << list << something3 << '\n';

    std::cout << list[2];
    // std::cin >> list[2];

    list.clear(); std::cout << list;


    ///////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////
    Stack<Programmer> stack;

    stack.insert(Rustem1); std::cout << stack;
    stack.insert(Rustem2); std::cout << stack;
    stack.insert(Rustem3); std::cout << stack;
    stack.insert(Rustem4); std::cout << stack;



    auto something4 = stack.remove(); std::cout << stack << something4;

    stack.remove(); std::cout << stack;

    ///////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////

    // std::cin >> Rustem12; Rustem12.GetInfo();

    ///////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////
    DLS<Programmer> dls;
    dls.insert(1, Rustem1); std::cout << dls;















    return 0;
}
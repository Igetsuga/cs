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


///////////////////////////////////////////////////////////////////////////////
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


///////////////////////////////////////////////////////////////////////////////
// class Programmer
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
    void SetInfo(const Programmer& other)
    {
             Programmer::level_ = other.level_;
              Programmer::lang_ = other.lang_;
                   Human::name_ = other.name_;
                Human::surname_ = other.surname_;
             Programmer::email_ = other.email_;
        Programmer::telegramID_ = other.telegramID_;
           Programmer::skypeID_ = other.skypeID_;
                   Worker::job_ = other.job_;
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
        // constructor.
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

        // 
        LinkedList<Type>::Object* GetSucessor() { return sucessor_; }
        void SetSucessor (LinkedList<Type>::Object* other) { sucessor_ = other; }

        LinkedList<Type>::Object* GetPredecessor() { return predecessor_; }
        void SetPredecessor (LinkedList<Type>::Object* other) { predecessor_ = other; }

        const Type& GetData() const { return data_; }
        void SetData (Type& data) { data_ = data; }


    protected:
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
    LinkedList (const LinkedList& other)
    {
        if (other.size_ != 0)
        {
            head_ = new Object(other.head_->GetData()); // c. (*head_).data_ = (*other.head).data_;
                                                        // c. (*head_).sucessor_ = nullptr;
                                                        // c. (*head_).predecessor_ = nullptr;
            Object* this_ptr_current = head_;
            Object* other_ptr_current = other.head_;

            while (other_ptr_current != nullptr)
            {
                // c. (*this_ptr_current).data_ = (*other_ptr_current).data_; 
                // c. (*this_ptr_current).sucessor_ = nullptr;
                this_ptr_current->SetSucessor( new Object((other_ptr_current->GetSucessor())->GetData()) );
                (this_ptr_current->GetSucessor())->SetPredecessor( this_ptr_current );

                this_ptr_current = this_ptr_current->GetSucessor();
                other_ptr_current = other_ptr_current->GetSucessor();
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
    virtual void forceObjectDelete (Object* object) final
    {
        if (object == nullptr) { return; }

        LinkedList<Type>::Object* nextObjectDelete = object->GetSucessor();
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



    virtual void insert (const int& pos, const Type& data)
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
                objectCurrent = objectCurrent->GetSucessor();
            }

            Object* objectInsert = new Object(data, objectCurrent->GetSucessor(), objectCurrent);
            
            objectCurrent->SetSucessor(objectInsert);
            (objectInsert->GetSucessor())->SetPredecessor(objectInsert);

            size_++;
        }
    }

    virtual void pushFront (const Type& data) final
    {
        head_ = new Object(data, head_);

        if (size_ == 0)
        {
            tail_ = head_;
        }
        else 
        {
            ( head_->GetSucessor() )->SetPredecessor(head_);
        }

        size_++;
    }

    virtual void pushBack (const Type& data) final
    {
        if (size_ == 0)
        {
            head_ = tail_ = new Object(data, nullptr, nullptr); // <==> head_ = new Object(data, nullptr, nullptr);
        }
        else
        {
            tail_ = new Object(data, nullptr, tail_);
            ( tail_->GetPredecessor() )->SetSucessor(tail_);
        }
        size_++;
    }



    virtual Type remove (const int& pos)
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
                objectCurrent->GetSucessor();
            }

            size_--;


            return objectCurrent->removeNext();
        }
    }

    virtual Type removeFront() final
    {

        Type data = head_->GetData();

        if ( size_ == 1 )
        {
            delete head_; head_ = tail_ = nullptr;
        }
        else
        {
            Object* next_after_head = head_->GetSucessor();
            delete head_; head_ = next_after_head;
            head_->SetPredecessor(nullptr);
        }
        size_--;


        return data;
    }

    virtual Type removeBack() final
    {
        size_--;

        Object* before_tail_= tail_->GetPredecessor(); Type data = tail_->GetData();

        delete tail_;

        tail_ = before_tail_; tail_->SetSucessor(nullptr);


        return data;
    }




    size_t size() const { return size_; }

    virtual LinkedList<Type>::Object* GetObject (const int& pos) const
    {
        if (pos <= 0 || pos > size_) { throw std::out_of_range("LinkedList<Type>::*GetObject: index out of range"); }
        else {
            // size_t position = static_cast<size_t>(pos);

            Object* ptr_current = this->head_;
            for (int pos_current = 1; pos_current < pos; pos_current++)
            {
                ptr_current = ptr_current->GetSucessor();
            }


            return ptr_current;
        }

    }

    virtual const Type& operator[] (const int& pos) const { return GetObject(pos)->Object::GetData(); }

    virtual LinkedList<Type> i_filter (bool (*fn)(Type))
    {
        LinkedList<Type> listResult;
        // int size = static_cast<int>(size_);

        for (Object* objectCurrent = head_; objectCurrent != nullptr;
            objectCurrent = objectCurrent->GetSucessor() )
        {
            if ( fn(objectCurrent->GetData()) ) // if ( fn(this->GetObject(pos)->data_) )
            {
                listResult.pushBack(objectCurrent->GetData());
            }
        }


        return listResult;
    }

    virtual LinkedList<Type> r_filter (bool (*fn)(Type), LinkedList<Type> listResult, Object* objectCurrent = head_)
    {   
        if ( objectCurrent == nullptr) { return listResult; }
        else if ( fn(objectCurrent->GetData()) ) // if ( fn(this->GetObject(pos)->data_) )
        {
            listResult.pushBack(objectCurrent->GetData());
        }


        return r_filter(fn, listResult, objectCurrent->GetSucessor());
    }

    virtual Type i_find (bool (*fn)(Type))
    {
        Object* objectCurrent = head_;
        while ( true )
        {
            if ( objectCurrent == nullptr )
            {
                Type unknown; // implies of defualt_constructor existing


                return unknown;
            }
            else if ( fn(objectCurrent->GetData()) ) { return objectCurrent->GetData(); }

            objectCurrent = objectCurrent->GetSucessor();
        }
    }
    
    virtual Type r_find (bool (*fn)(Type), Object* objectCurrent = head_)
    {
        if ( objectCurrent == nullptr )
        {
            Type unknown; // implies of defualt_constructor existing


            return unknown;
        }
        else if ( fn(objectCurrent->GetData()) ) { return objectCurrent->GetData(); }

        
        return r_find (fn, objectCurrent->GetSucessor());
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



    virtual void insert(const int& pos, const Type& data) override
    {
        if ( pos <= 0 ) { throw std::out_of_range("LinkedList<Type>::insert: pos < 0"); }
        else if ( pos > LinkedList<Type>::size_ + 1 && (pos != 1 && LinkedList<Type>::size_ != 0) ) 
        { throw std::out_of_range("LinkedList<Type>::insert: pos > size"); }

        llObject* objectCurrent = nullptr;

        if ( pos == 1 )
        {
            this->LinkedList<Type>::pushFront(data);
            return;
        }
        else if ( pos == LinkedList<Type>::size_ + 1 )
        {
            this->LinkedList<Type>::pushBack(data);
            return;
        }
        else if (pos <= LinkedList<Type>::size_ / 2)
        {
            objectCurrent = LinkedList<Type>::head_;

            for ( int position = 1; position < pos - 1; position++ )
            {
                objectCurrent = objectCurrent->GetSucessor();
            }
        }
        else
        {
            objectCurrent = LinkedList<Type>::tail_;

            for ( int position = LinkedList<Type>::size_; position > pos - 1; position-- )
            {
                objectCurrent = objectCurrent->GetPredecessor();
            }
        }
        llObject* objectInsert = new llObject(data, objectCurrent->GetSucessor(), objectCurrent);

        objectCurrent->SetSucessor(objectInsert);
        (objectInsert->GetSucessor())->SetPredecessor(objectInsert);

        LinkedList<Type>::size_++;
    }

    virtual Type remove(const int& pos) override
    {
        if ( pos <= 0 ) { throw std::out_of_range("LinkedList<Type>::remove: pos < 0"); }
        else if ( pos > LinkedList<Type>::size_ ) { throw std::out_of_range("LinkedList<Type>::remove: pos > size"); }

        llObject* objectCurrent = nullptr;

        if ( pos == 1 )
        {
            return this->removeFront();
        }
        else if ( pos == LinkedList<Type>::size_ )
        {
            return this->removeBack();
        }
        else if ( pos <= LinkedList<Type>::size_ / 2 )
        {
            objectCurrent = LinkedList<Type>::head_;

            for ( int position = 1; position < pos - 1; position++ )
            {
                objectCurrent = objectCurrent->GetSucessor();
            }
        }
        else
        {
            objectCurrent = LinkedList<Type>::tail_;

            for ( int position = LinkedList<Type>::size_; position > pos - 1; position-- )
            {
                objectCurrent = objectCurrent->GetPredecessor();
            }
        }
        LinkedList<Type>::size_--;


        return objectCurrent->removeNext();
    }

    virtual void print() final
    {
        llObject* objectCurrent = LinkedList<Type>::head_;

        std::cout << '\n' << "print: { ";
        while ( objectCurrent != nullptr )
        {
            std::cout << objectCurrent->GetData() << " ";
            objectCurrent = objectCurrent->GetSucessor();
        }
        std::cout << "}" << '\n';

    }

    virtual void print_reverse() final
    {
        llObject* objectCurrent = LinkedList<Type>::tail_;

        std::cout << '\n' << "print_reverse: { ";
        while ( objectCurrent != nullptr )
        {
            std::cout << objectCurrent->GetData() << " ";
            objectCurrent = objectCurrent->GetPredecessor();
        }
        std::cout << "}" << '\n';
    }

};

///////////////////////////////////////////////////////////////////////////////
// class MC.
template<class Type> class Queue : protected DLS<Type>
{
    typedef LinkedList<Type>::Object llObject;
public:
    
    // constructor.
    Queue<Type>() : DLS<Type>() {};

    // destructor.
    virtual ~Queue<Type>() = default;

    // clear all objects
    virtual void clearQueue()
    {
        while ( LinkedList<Type>::head_ != nullptr ) // <=> (head_ != tail_)
        {
            this->dequeue();
        }
        LinkedList<Type>::size_ = 0;
    }

    virtual llObject* GetObject (const int& pos) const
    {
        if ( pos <= 0 || pos > LinkedList<Type>::size_ ) { throw std::out_of_range("Queue<Type>::*GetObject: index out of range"); }
        else {
            // size_t position = static_cast<size_t>(pos);

            llObject* ptr_current = this->LinkedList<Type>::head_;
            for ( int pos_current = 1; pos_current < pos; pos_current++ )
            {
                ptr_current = ptr_current->GetSucessor();
            }


            return ptr_current;
        }
    }

    virtual const Type& operator[] (const int& pos) const { return GetObject(pos)->GetData(); }



    virtual void enqueue (const Type& data)
    {
        LinkedList<Type>::head_ = new llObject(data, LinkedList<Type>::head_);

        if ( LinkedList<Type>::size_ == 0 )
        {
            LinkedList<Type>::tail_ = LinkedList<Type>::head_;
        }
        else
        {
            (LinkedList<Type>::head_->GetSucessor())->SetPredecessor(LinkedList<Type>::head_);
        }

        LinkedList<Type>::size_++;
    }

    virtual Type dequeue()
    {
        Type data = LinkedList<Type>::head_->GetData();

        if ( LinkedList<Type>::size_ == 1 )
        {
            delete LinkedList<Type>::head_; LinkedList<Type>::head_ = LinkedList<Type>::tail_ = nullptr;
        }
        else
        {
            llObject* next_after_head = LinkedList<Type>::head_->GetSucessor();
            delete LinkedList<Type>::head_; LinkedList<Type>::head_ = next_after_head;
            LinkedList<Type>::head_->SetPredecessor(nullptr);
        }
        LinkedList<Type>::size_--;


        return data;
    }

     /*virtual const Type& operator[] (const int& pos) const  { return GetObject(pos)->GetData(); }*/

    virtual void load(std::string fileName)
    {
        std::ifstream file_input; file_input.open(fileName);
        if ( file_input.is_open() )
        {
            int size = 0; file_input >> size;
            Type value_from_file;

            if ( size == LinkedList<Type>::size_ )
            {
                for ( int object_number = 1; object_number <= size; object_number++ )
                {
                   file_input >> value_from_file;
                   GetObject(object_number)->SetData(value_from_file);
                }
            }
            else
            {
                this->clearQueue();

                for ( int object_number = 1; object_number <= size; object_number++ )
                {
                    file_input >> value_from_file;
                    this->enqueue(value_from_file);
                }
            }
            LinkedList<Type>::size_ = size;
            file_input.close();
        }
    }
    
    virtual void save(std::string fileName)
    {
        std::ofstream file_output(fileName);
        if ( file_output.is_open() )
        {
            file_output << LinkedList<Type>::size_ << "\n";
            
            for ( int object_number = 1; object_number <= LinkedList<Type>::size_; object_number++ )
            {
                // file_output << *this[object_number].GetInfo() << '\n';
                // file_output << GetObject(object_number)->GetData() << " ";
                file_output << (*this)[object_number] << '\n';
            }
            file_output << '\n';

            file_output.close();
        }
    }
    
    template<typename Type> friend std::ostream& operator<< (std::ostream& output, const Queue<Type>& other);
};
template<typename Type> std::ostream& operator<< (std::ostream& output, const Queue<Type>& other)
{
    if ( typeid(output).name() != typeid(std::ofstream).name() )
    {
        /*output << '\n' << "{ ";
        for ( int object_number = 1; object_number <= other.LinkedList<Type>::size_; object_number++ )
        {
            output << manupulator_custom << other[object_number] << " ";
        }
        output << "}" << '\n';*/

        output << '\n' << "{ ";
        for ( int object_number = 1; object_number <= other.LinkedList<Type>::size_; object_number++ )
        {
            output << other[object_number] << " ";
        }
        output << "}" << '\n';
    }
    else
    {
        output << '\n';
        for ( int object_number = 1; object_number <= other.LinkedList<Type>::size_; object_number++ )
        {
            output << other[object_number] << " ";
        }
        output << '\n';
    }


    return output;
}


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

std::ostream& manupulator_custom (std::ostream& output)
{
    output.unsetf(std::ios::dec); output.setf(std::ios::oct);
    
    output.setf(std::ios::left);
    output.width(80);
    

    return output;
}

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
    std::cout << "///////////////////////////////////////////////////////////////////////////";
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
    std::cout << "///////////////////////////////////////////////////////////////////////////";
    ///////////////////////////////////////////////////////////////////////////
    DLS<Programmer> dls;
    dls.insert(1, Rustem1); std::cout << dls;
    dls.insert(2, Rustem2); std::cout << dls;
    dls.insert(3, Rustem3); std::cout << dls;
    dls.insert(4, Rustem4); std::cout << dls;

    dls.insert(2, Rustem5); std::cout << dls;
    dls.insert(4, Rustem6); std::cout << dls;
    std::cout << "indexation " <<  dls[5];
    dls.print();
    dls.print_reverse();


    auto objectRemove1 = dls.remove(2); std::cout << dls << objectRemove1 << '\n';
    auto objectRemove2 = dls.remove(4); std::cout << dls << objectRemove2 << '\n';
    dls.print();
    dls.print_reverse();


    Programmer Rustem13;
    Rustem13.GetInfo();

    ///////////////////////////////////////////////////////////////////////////
    std::cout << "///////////////////////////////////////////////////////////////////////////";
    ///////////////////////////////////////////////////////////////////////////

    Queue<Programmer> queue;
    
    queue.enqueue(Rustem1); std::cout << queue; 
    queue.enqueue(Rustem2); std::cout << queue;
    queue.enqueue(Rustem3); std::cout << queue;
    queue.enqueue(Rustem4); std::cout << queue;
    
    // std::cout << queue[2];

    queue.dequeue(); std::cout << queue;
    queue.dequeue(); std::cout << queue;

    queue.clearQueue(); std::cout << queue;



    return 0;
}
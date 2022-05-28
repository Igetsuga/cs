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
    Human(const Human &other) = default;

    // operator= .
    Human& operator= (const Human &other) = default;

    // destructor.
    virtual ~Human() { std::cout << "Object \"Human\" was deleted" << '\n'; } // = default;



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
    Worker(const Worker &other) = default;

    // operator= .
    Worker& operator= (const Worker &other) = default;

    // destructor.
    virtual ~Worker() { std::cout << "Object \"Worker\" was deleted" << '\n'; }// = default;



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
    Programmer (const int &level = 0,
        const std::string &lang       = "unknown",
        const std::string &name       = "unknown",
        const std::string &surname    = "unknown",
        const std::string &email      = "unknown",
        const std::string &telegramID = "unknown",
        const std::string &skypeID    = "unknown",
        const std::string &job        = "unknown")

    {
        Programmer::level_      = level;
        Programmer::lang_       = lang;
        Human::name_            = name;
        Human::surname_         = surname;
        Programmer::email_      = email;
        Programmer::telegramID_ = telegramID;
        Programmer::skypeID_    = skypeID;
        Worker::job_            = job;
    }

    // copy constructor.
    Programmer(const Programmer &other)
    {
        // this->Human = other.Human
        this->Human::name_ = other.Human::name_;
        this->Human::surname_ = other.Human::surname_;

        this->Worker::job_ = other.Worker::job_;

        this->Programmer::level_      = other.Programmer::level_;
        this->Programmer::lang_       = other.Programmer::lang_;
        this->Programmer::email_      = other.Programmer::email_;
        this->Programmer::telegramID_ = other.Programmer::telegramID_;
        this->Programmer::skypeID_    = other.Programmer::skypeID_;
    }

    // destructor
    ~Programmer() { std::cout << "Object \"Pragrammer\" was deleted" << '\n'; }
 
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

    friend std::ostream& operator<< (std::ostream &output, const Programmer &other);

protected:
    int            level_;
    std::string    lang_;
    std::string    email_;
    std::string    telegramID_;
    std::string    skypeID_;
};
std::ostream& operator<< (std::ostream &output, const Programmer &other)
{
    output << other.name_;
    
    
    return output;
}





///////////////////////////////////////////////////////////////////////////////
// LinkedList.
template<class Type> class LinkedList
{
public:

    virtual struct Object
    {
        // default constructor.
        Object(const Type& data, Object* sucessor = nullptr)
        {
            sucessor_ = sucessor;
            data_ = data;
        }

        // destructor.
        ~Object() = default;

        void removeNext()
        {
            Object* removeObject = sucessor_;
            sucessor_ = removeObject->sucessor_;
            delete removeObject;
        }

        void insertNext()
        {

        }

        Object* sucessor_;
        Type    data_;
    };

    // default constructor.
    LinkedList()
    {
        head_ = nullptr;
        size_ = 0;
    }

    // copy constructor.
    LinkedList (const LinkedList &other)
    {
        if (other.size_ != 0)
        {
            head_ = new Object(other.head_->data_); // (*head_).data_ = (*other.head).data_;
                                                    // (*head_).sucessor_ = nullptr;
            Object *ptr_current_this = head_;
            Object *ptr_current_other = other.head_;

            while (ptr_current_other != nullptr)
            {
                // (*ptr_current_this).data_ = (*ptr_current_other).data_; 
                // (*ptr_current_this).sucessor_ = nullptr;
                ptr_current_this->sucessor_ = new Object(ptr_current_other->sucessor_->data_);

                ptr_current_this = ptr_current_this->sucessor_; // ptr_current_this = nullptr;
                ptr_current_other = ptr_current_other->sucessor_;
            }
        }
        else 
        {
            head_ = nullptr;
        }

        size_ = other.size_;
    }

    // LinkedList::list1 = LinkedList::list2 ==> list1.
    // HELP
    LinkedList& operator= (const LinkedList &other) // coping, not rename other.
                                                    // this->sucessor_ != other->sucessor_.
                                                    // this->data_ = other->data_.
    {
        this->clear();

        size_ = other.size_;
        head_ = nullptr;

        if (size_ != 0)
        {
            Object *ptr_other_iterator = other.head_;
            Object *ptr_this = new Object(other.head_->data_);
            head_ = ptr_this; // after: head_->sucessor_ = ptr_this->sucessor_ (=nullptr);  
                              //        head_->data_ = ptr_this->data_ (=other.head_->data_);
            Object *ptr_other_data_copy = nullptr;

            ptr_other_iterator = ptr_other_iterator->sucessor_;
            while (ptr_other_iterator != nullptr)
            {
                ptr_other_data_copy = new Object(ptr_other_iterator->data_);
                ptr_this->sucessor_ = ptr_other_data_copy;
                ptr_this = ptr_other_data_copy; // КАК ЭТО ПРОИСХОДИТ, ЕСЛИ У МЕНЯ НЕ ПЕРЕГРУЖЕН ОПЕРАТОР= ДЛЯ объектов Object
                ptr_other_iterator = ptr_other_iterator->sucessor_;
            }

            
        }
    } 

    // destructor.
    ~LinkedList()
    {
        size_ = 0;
        forceObjectDelete(head_);
    }

    void forceObjectDelete (Object *object)
    {
        if (object == nullptr) { return; }
        
        Object *nextObjectDelete = object->sucessor_;
        delete object;

        forceObjectDelete(nextObjectDelete);
    }
    
    size_t size() const 
    {
        return size_;
    }

    void clear() 
    {
        while (head_ != nullptr)
        {
            this->removeFront();
        }
        size_ = 0;
    }

    void removeFront()
    {
        if (size_ == 1)
        {
            delete head_; head_ = nullptr;
            size_ = 0;
        }
        else
        {
            Object *removeFront_next = head_->sucessor_;
            delete head_; head_ = removeFront_next;
            size_--;
        }
    }

    void removeBack()
    {
        Object *currentObject = head_;
        
        int currentPosition = 1;
        while (currentPosition < size_ - 1)
        {
            currentObject = currentObject->sucessor_;
            currentPosition++;
        }

        // now: currentObject = penultimateObject
        currentObject->removeNext();
        // delete (currentObject->sucessor_);
        // currentObject->sucessor = nullptr;
        size_--;

    }

    LinkedList<Type>::Object* GetObject (const int &pos) const 
    {
        if (pos < 0 || pos > size_) { throw std::out_of_range("LinkedList<Type>::*GetObject: index out of range"); }
        else {
            // size_t position = static_cast<size_t>(pos);

            Object *ptr_current = this->head_;
            for (int pos_current = 1; pos_current < pos; pos_current++)
            {
                ptr_current = ptr_current->sucessor_;
            }

            
            return ptr_current;
        }
        
    }
    
    void pushBack (const Type &data)
    {
        if (size_ == 0)
        {
            head_ = new Object(data, head_); // <==> head_ = new Object(data, nullptr);
            size_++;
        }
        else
        {
            insert(size_, data);
        }
    }

    void pushFront (const Type &data)
    {
        head_ = new Object(data, head_);
        size_++;
    }

    void insert (const int &pos, const Type &data)
    {
        if (pos <= 0) { throw std::out_of_range("LinkedList<Type>::insert: pos < 0"); }
        else if (pos > size_ && (pos != 1 && size_ != 0)) { throw std::out_of_range("LinkedList<Type>::insert: pos > size"); }

        if (pos == 1)
        {
            this->pushFront(data);
        }
        else
        {
            Object* currentObject = head_;

            for (int position = 1; position < pos - 1; position++)
            {
                currentObject->sucessor_;
            }

            currentObject->sucessor_ = new Object(data, currentObject->sucessor_);
            size_++;
        }
    }

    void remove (const int &pos)
    {
        if (pos <= 0) { throw std::out_of_range("LinkedList<Type>::remove: pos < 0"); }
        else if (pos > size_) { throw std::out_of_range("LinkedList<Type>::remove: pos > size"); }

        if (pos == 1) 
        {
            this->removeFront();
        }
        else 
        {
            Object* currentObject = head_;

            for (int position = 1; position < pos - 1; position++)
            {
                currentObject->sucessor_;
            }

            currentObject->removeNext();
            size_--;
        }
    }
    
    LinkedList<Type> filter ( bool (*fn)(Type) )
    {
        LinkedList<Type> resultList;
        for (int i = 1; i <= size_; i++)
        {
            if ( fn( (*this)[i] ) ) // if (fn (this->GetObject(pos)->data_) )
            {
                resultList.pushBack( (*this)[i] );
            }
        }


        return resultList;
    }

    template<class Type> friend std::ostream& operator<< (std::ostream &output, const LinkedList<Type> &list);
    
    const Type& operator[] (const int &pos) const
    {
            return GetObject(pos)->data_;
    }

protected:
    Object *head_;
    size_t  size_;
};

template<class Type> std::ostream& operator<< (std::ostream &output, const LinkedList<Type> &list)
{
    if (typeid(output).name() != typeid(std::ofstream).name())
    {
        output << '\n' << "{ ";
        for (int object_number = 1; object_number <= list.size_; object_number++)
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
    ///////////////////////////////////////////////////////////////////////////

    LinkedList<Programmer> list;

    list.pushBack(Rustem1); std::cout << list;
    list.pushFront(Rustem2); std::cout << list;
    list.insert(2, Rustem3); std::cout << list;
    list.removeBack(); std::cout << list;
    list.removeFront(); std::cout << list;

    list.pushBack(Rustem4); list.pushBack(Rustem5); list.pushBack(Rustem6);
    list.pushBack(Rustem7); list.pushBack(Rustem8); std::cout << list;

    list.remove(2); std::cout << list;

    list.clear(); std::cout << list;
    































    return 0;
}
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
 


    friend std::ostream& operator<< (std::ostream &output, const Programmer &other);

    void SetLevel(int level) { level_ = level; }
protected:
    int            level_;
    std::string    lang_;
    std::string    email_;
    std::string    telegramID_;
    std::string    skypeID_;
};
std::ostream& operator<< (std::ostream &output, const Programmer &other)
{
    output << '\n' << "---------------------START--------------------" << '\n';

    output << "   name: " << other.Human::name_ << '\n'
           << "surname: " << other.Human::surname_ << '\n'
                   <<"------------------Information:----------------" << '\n';

    output << "     level: " << other.Programmer::level_ << '\n'
           << "      lang: " << other.Programmer::lang_ << '\n'
           << "     email: " << other.Programmer::email_ << '\n'
           << "telegramID: " << other.Programmer::telegramID_ << '\n'
           << "   skypeID: " << other.Programmer::skypeID_ << '\n'
           << "       job: " << other.Worker::job_ << '\n'
                   << "----------------------END---------------------" << '\n';


    return output;
}





///////////////////////////////////////////////////////////////////////////////
// LinkedList.
template<class Type> class LinkedList
{
    class Object
    {
    public:
        // default constructor.
        Object (const Type &data, Object *sucessor = nullptr)
        {
            sucessor_ = sucessor;
            data_ = data;
        }

        // destructor.
        ~Object() = default;

        void deleteNext()
        {
            Object *removeObject = sucessor_;
            sucessor_ = removeObject->sucessor_;
            delete removeObject;
        }

        void insertNext()
        {

        }

    protected:
        Object *sucessor_;
        Type    data_;
    };
public:
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
        forceObjectdelete(head_);
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
        currentObject->deleteNext();
        // delete (currentObject->sucessor_);
        // currentObject->sucessor = nullptr;
        size_--;

    }

    LinkedList<Type>::Object *GetObject (const int &pos) const 
    {
        if (pos < 0 || pos >= size_) { std::cout << "index out of range"; }
        else {
            size_t position = static_cast<size_t>(pos);

            Object *ptr_current = this->head_;
            for (int pos_current = 0; pos_current < position; pos_current++)
            {
                ptr_current = ptr_current->sucessor_;
            }

            
            return ptr_current;
        }
        
    }








    const Type& operator[] (const int &pos) const
    {
            return GetObject(pos)->data_;
    }

protected:
    Object *head_;
    size_t  size_;
};




int main()
{
    // Задание 6.0: Проверка общей работоспособности системы.
    //////////////////////////////////////////////////////////////////////////////
    Programmer Rustem1(1, "c++", "Rustem", "Sirazetdinov",
        "avesirazetdinov@gmail.com", "I_getsuga");

    Programmer Rustem2 = Rustem1;

    std::cout << Rustem1 << Rustem2;
    //delete ptr2;
}
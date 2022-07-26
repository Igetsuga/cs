#include <iomanip>
#include <iostream>
#include <fstream>
#include  "LinkedList.h"

///////////////////////////////////////////////////////////////////////////////
// class Human. 

// default constructor
Human::Human(std::string name = "unknown", std::string surname = "unknown")
{
    name_ = name;
    surname_ = surname;
}

// copy constructor.
Human::Human(const Human& other) = default;

// operator= .
Human& Human::operator= (const Human& other) = default;

// destructor.
Human::~Human() { std::cout << "Object \"Human\" was deleted" << '\n'; } // = default;



// Get & Set.
std::string Human::GetName() { return name_; }
std::string Human::GetSurname() { return surname_; }
void Human::SetName(std::string name) { name_ = name; }
void Human::SetSurname(std::string surname) { surname_ = surname; }
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// class Worker.
// default constructor
Worker::Worker(std::string job = "unknown") { job_ = job; }

// copy constructor.
Worker::Worker(const Worker& other) = default;

// operator= .
Worker& Worker::operator= (const Worker& other) = default;

// destructor.
Worker::~Worker() { std::cout << "Object \"Worker\" was deleted" << '\n'; }// = default;



// Get & Set.
std::string Worker::GetJob() { return job_; }
void Worker::SetJob(std::string job) { job_ = job; }
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////




///////////////////////////////////////////////////////////////////////////////
// default constructor.
Programmer::Programmer(const int& level = 0,
    const std::string& lang = "unknown",
    const std::string& name = "unknown",
    const std::string& surname = "unknown",
    const std::string& email = "unknown",
    const std::string& telegramID = "unknown",
    const std::string& skypeID = "unknown",
    const std::string& job = "unknown")

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
Programmer::Programmer(const Programmer& other)
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
Programmer::~Programmer() { std::cout << "Object \"Pragrammer\" was deleted" << '\n'; }


void Programmer::SetLevel(int level) { level_ = level; }

std::ostream& operator<< (std::ostream& output, const Programmer& other)
{
    output << '\n' << "---------------------START--------------------" << '\n';

    output << "   name: " << other.Human::name_ << '\n'
        << "surname: " << other.Human::surname_ << '\n'
        << "------------------Information:----------------" << '\n';

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
///////////////////////////////////////////////////////////////////////////////






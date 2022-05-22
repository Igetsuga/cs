#pragma once
#include <iomanip>
#include <iostream>
#include <fstream>



///////////////////////////////////////////////////////////////////////////////
// class Human. 
class Human
{
public:
    // default constructor
    Human(std::string name = "unknown", std::string surname = "unknown");
    

    // copy constructor.
    Human (const Human& other);

    // operator= .
    Human& operator= (const Human& other);

    // destructor.
    virtual ~Human();



    // Get & Set.
    std::string GetName();
    std::string GetSurname();
    void SetName(std::string name);
    void SetSurname(std::string surname);



protected:
    std::string name_;
    std::string surname_;
};



// class Worker.
class Worker : public Human
{
public:
    // default constructor
    Worker(std::string job = "unknown");

    // copy constructor.
    Worker(const Worker& other);

    // operator= .
    Worker& operator= (const Worker& other);

    // destructor.
    virtual ~Worker();



    // Get & Set.
    std::string GetJob();
    void SetJob(std::string job);



protected:
    std::string job_;
};



class Programmer : public Worker
{
public:
    // default constructor.
    Programmer(const int& level = 0,
        const std::string& lang = "unknown",
        const std::string& name = "unknown",
        const std::string& surname = "unknown",
        const std::string& email = "unknown",
        const std::string& telegramID = "unknown",
        const std::string& skypeID = "unknown",
        const std::string& job = "unknown");

    // copy constructor.
    Programmer(const Programmer& other);
    

    // destructor
    ~Programmer();



    friend std::ostream& operator<< (std::ostream& output, const Programmer& other);

    void SetLevel(int level);
protected:
    int            level_;
    std::string    lang_;
    std::string    email_;
    std::string    telegramID_;
    std::string    skypeID_;
};






///////////////////////////////////////////////////////////////////////////////
// LinkedList.
//template<class Type> class LinkedList
//{
//
//protected:
//    Object<Type> *head_;
//    size_t size_;
//};




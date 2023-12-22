#ifndef CAT_H
#define CAT_H
#include <iostream>
#include <string>
class Cat
{
public:
    Cat(std::string name, int age);

    // 可变引用
    std::string &name()
    {
        return this->m_name;
    }
    // 不可变引用
    const std::string &name() const
    {
        return this->m_name;
    }
    int &age()
    {
        return this->m_age;
    }
    const int &age() const
    {
        return this->m_age;
    }
    // print
    void print_object() const;

private:
    std::string m_name;
    int m_age;
};

#endif

#include <iostream>

namespace tema1
{
    class Person
    {
        public:
        std::string name; // fields should be private!

        private:
        int age;
        int salary = 0;
        int taxes = 300;

        public:
        // multiple constructors to initialize different attributes
        Person()
        {

        }

        Person(std::string n, int a)
        {
            name = n;
            age = a;
        }

        Person(std::string n, int a, int s) // overloading
        {
            name = n;
            age = a;
            salary = calculateSalary(s);
        }

        void setAge(int newAge)
        {
            age = newAge;
        }

        void display() // made public should be used by everyone 
        {
            std::cout << "Name: " << name << "\nAge: " << age << "\nSalary: " << salary << std::endl;
        }

        private:
        int calculateSalary(int salary) // does internal calculations should not be used by everyone
        {
            return salary - taxes;
        }

    };
} // namespace tema1

using namespace tema1;

int main()
{
    Person p0;
    std::cout << "This is my name: " << p0.name << std::endl; // won't print anything for name since it was not initialized!

    Person p1("Alice", 30, 1200);
    Person p2("Mike", 25); // still okey since we have a constructor

    p1.name = "Bob"; // users of the class should not be able to change the attributer directly, it breaks encapsulation
    //p1.age = 10; // gives error
    p1.setAge(20); // the correct way to do it

    p1.display();
    p2.display();
    return 0;
}
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
        double* height;

        public:
        // multiple constructors to initialize different attributes
        Person()
        {
            height = (double *) malloc(sizeof(double));
        }

        Person(std::string n, int a)
        {
            name = n;
            age = a;
            height = (double *) malloc(sizeof(double));
        }

        Person(std::string n, int a, int s) // overloading
        {
            name = n;
            age = a;
            salary = calculateSalary(s);
            height = (double *) malloc(sizeof(double));
        }

        Person(std::string n, int a, int s, double h)
        {
            name = n;
            age = a;
            salary = calculateSalary(s);
            height = (double *) malloc(sizeof(double)); //allocating space on the heap
            *height = h;
        }

        //custom destructor
        ~Person()
        {
            //stack is cleaned automatically, heap is cleaned manually
            std::cout << "Destructor running, destroying: " << name << std::endl;
            free(height); //the space that was manually allocated need to be freed, no memory leaks
            // also file handles or network connections can be closed in the destructor
        }

        //custom copy constructor
        Person(const Person& otherPerson)
        {
            height = (double*)malloc(sizeof(double)); //allocates another addres for the new object - deep copy
            *height = *(otherPerson.height);
        }

        void setAge(int newAge)
        {
            age = newAge;
        }

        int getAge()
        {
            return age;
        }

        void setHeight(double newHeight)
        {
            *height = newHeight;
        }

        double getHeight()
        {
            return *height;
        }

        void display() // made public should be used by everyone 
        {
            std::cout << "Name: " << name << "\nAge: " << age << "\nSalary: " << salary << std::endl;
        }

        void fullInfo()
        {
            std::cout << "Name: " << name << "\nAge: " << age << "\nSalary: " << salary << "\nHeight:" << *height << std::endl;
        }

        private:
        int calculateSalary(int salary) // does internal calculations should not be used by everyone
        {
            return salary - taxes;
        }

    };
} // namespace tema1

using namespace tema1;

void testDestructor()
{
    Person p("John", 23);
} // destructor called here, after the program terminates

int main()
{
    Person p0;
    std::cout << "This is my name: " << p0.name << std::endl; // won't print anything for name since it was not initialized!

    Person p1("Alice", 30, 1200);
    Person p2("Mike", 25); // still okey since we have a constructor

    p1.name = "Bob"; // users of the class should not be able to change the attributer directly, it breaks encapsulation
    //p1.age = 10; // gives error
    p1.setAge(20); // the correct way to do it

    testDestructor();

    p1.display();
    p2.display();

    Person* p3 = new Person("Johnny", 45);
    delete p3; //the destructor is called explicitly
    

    //Exemplification of copy constructor
    std::cout << "-------------------Copy constructor---------------" << std::endl;
    Person p4("Betty", 34, 2300, 173.2);
    //Person p5("Emma", 34, 2600, 178.2);

    //p5 = p4; // this is an asignement, won't call the copy constructor

    Person p5 = p4; //in this way you call the copy-constructor (p4 is the otherPerson)

    p4.fullInfo();
    p5.fullInfo();

    //here both p4 and p5 store the same memory address for the allocated attribure here is an example

    p4.setAge(44); // in this case the age will be chnaged only for P4
    std::cout << "P4 age: " << p4.getAge() << std::endl;
    std::cout << "P5 age: " << p5.getAge() << std::endl;

    p4.setHeight(170.8); // but in this case the height will be changed for both P4 and P5, shallow copy
    std::cout << "P4 height: " << p4.getHeight() << std::endl;
    std::cout << "P5 height: " << p5.getHeight() << std::endl;

    exit(1);// another problem arises if we didn't have this exit() both destructors would've called free on the same address 

    return 0;
}
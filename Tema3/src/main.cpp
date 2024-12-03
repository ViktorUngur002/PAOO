#include <iostream>

namespace tema3 {

    class Engine
    {
        private:
            std::string manufacturer;
            std::string type;
            double weight;
            int powerOutput;

        public:
            Engine(std::string m, std::string t, double w, int po):
            manufacturer(m),
            type(t),
            weight(w),
            powerOutput(po)
            {}

            friend std::ostream& operator<<(std::ostream& os, const Engine& engine) {
                os << "\nManufacturer: " << engine.manufacturer << ", Type: " << engine.type << ", Weight: " << engine.weight << ", Power output: " << engine.powerOutput;
                return os;
            }
    };

    class Plane
    {
        private:
            std::string model;
            double wingspan;
            double maxSpeed;
            Engine *engine;

        public:
            Plane(std::string m, double w, double ms, Engine* e):
            model(m),
            wingspan(w),
            maxSpeed(ms),
            engine(e)
            {}

            // this way of implementing the assign operator can cause problems in some environments,  
            // when it is called for self-assignement
            // if this and p are the same object, delete destroy engine for both p and current object
            /*
            Plane& operator=(const Plane& p)
            {
                delete engine;
                engine = new Engine(*p.engine);

                return *this; //convention that applies to every assing operators, they return a reference to left-hand object
            }*/

            // the fixed version of the above is
            /*Plane& operator=(const Plane& p)
            {
                Engine *engineOrig = engine; // remember original
                engine = new Engine(*p.engine); // point engine to a copy of p's engine
                delete engineOrig; // delete original

                return *this;
            }*/


            //copy and swap technique

            void swap(Plane& p)
            {
                using std::swap;
    
                swap(model, p.model);
                swap(wingspan, p.wingspan);
                swap(maxSpeed, p.maxSpeed);
                swap(engine, p.engine);
            }

            Plane& operator=(const Plane& p)
            {
                Plane temp(p);
                swap(temp);

                return *this;
            }

            friend std::ostream& operator<<(std::ostream& os, const Plane& plane) {
                os << "Model: " << plane.model << ", Wingspan: " << plane.wingspan << ", Max Speed: " << plane.maxSpeed << ", Engine: " << *(plane.engine);
                return os;
            }
    
    };

    // here we will discuss the problem that appears when modifying default copy functions,
    // and how you need to constantly modify them when adding new attributes
    class Employee
    {
        private:
            std::string name;
        
        public:
            Employee(std::string n):name(n)
            {}

            Employee(const Employee& e)
            {
                name = e.name;
            }

            Employee& operator=(const Employee& e)
            {
                name = e.name;
                return *this;
            }

            void print()
            {
                std::cout << name << std::endl;
            }
    };

    class HeadEmployee: public Employee
    {
        private:
            int specialCardNumber;

        public:
            HeadEmployee(std::string n, int scn):
            Employee(n),
            specialCardNumber(scn)
            {}

            // when we are rewriting copying functions we should make sure that:
            //  1. we copy all local data members
            //  2. invoke the appropriate copy functions from base classes 
        HeadEmployee(const HeadEmployee& e) : 
            Employee(e), 
            specialCardNumber(e.specialCardNumber) 
            {}

        // Correct assignment operator for HeadEmployee
        HeadEmployee& operator=(const HeadEmployee& e) {
            Employee::operator=(e); // Call the base class assignment operator
            specialCardNumber = e.specialCardNumber;
            return *this;
        }

        void print()
        {
            Employee::print();
            std::cout << specialCardNumber << std::endl;
        }
    };

}

using namespace tema3;

int main()
{
    Engine *e = new Engine("Boeing", "propeller", 50, 900);
    Plane p("Boeing 1", 10, 300, e);

    //Plane p2 = p;
    p = p;

    //std::cout << p2 << std::endl;
    std::cout << p << std::endl;
    
    //Last item

    HeadEmployee h1("Mike", 1234);
    HeadEmployee h2(h1);

    h1.print();
    h2.print();

    return 0;
}
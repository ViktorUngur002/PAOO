#include <iostream>
#include <tr1/memory>

namespace tema4 
{
    class Dog
    {
        private:
            std::string name;
            int food;
        
        public:
            Dog(std::string n, int f):
            name(n),
            food(f)
            {}

            void print()
            {
                std::cout << name << std::endl;
            }

            int getFood()
            {
                return food;
            }
    };

    Dog* createDog()
    {
        Dog* d = new Dog("Fluffy", 5);
        return d;
    }
}

using namespace tema4;

// as we discussed before these dynamically allocated objects need to be destroyed via delete
// but in this case if the if condition is met a return will happen and we would have memory leaks
// also there could be other cases in which delete would not be reached so this design is wrong 
void f1()
{
    Dog* createdDog = createDog();

    if(createdDog->getFood() < 10)
    {
        return;
    }

    delete createdDog;
}

// to make sure the object will be deleted we need to put it inside an object whise destructor will automatically
// release the resource
// a depracted version to solve this was auto_ptr, which had the problem that no two pointers of this type
// could point to same object
// the better version is reference-counting smart pointer
// this pointer keeps track of how many objects point to a particular resource and automatically deletes the resource
// when nobody is pointing to it any longer
void f2()
{
    std::tr1::shared_ptr<Dog> createdDog(createDog());

    //both creadtedDog and createdDog2 point to the object
    std::tr1::shared_ptr<Dog> createdDog2(createdDog);

    createdDog->print();
    createdDog2->print();

    if(createdDog->getFood() < 10)
    {
        //now even dought we return here the allocated createdDog will be destroyed
        return;
    }    
}

int main()
{
    f1();
    f2();
    return 0;
}
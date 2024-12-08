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
    
    class Mutex
    {

    };

    // class when inherited blocks copying for child class
    class Uncopyable {
        protected:
            Uncopyable() {} 
            ~Uncopyable() {}
        private:
            Uncopyable(const Uncopyable&);
            Uncopyable& operator=(const Uncopyable&);
    };

    // lock managing class
    // we could block the copying by inheriting Uncopyable
    // to perform hold on a resource as in the shared_ptr, we need to modify its initialization
    // since we don't want to delete our resource but to unlock(logic from destructor in Lock)
    // we could specify a deleter for shared_ptr
    // this is also handy for lets say when you need to close connections when calling the destructor
    class Lock/*: private Uncopyable*/
    {
        private:
            //Mutex* mutexPtr;
            std::tr1::shared_ptr<Mutex> mutexPtr;

            void lock(Mutex* pm)
            {
                std::cout << "Locking the mutex." << std::endl;
            }
            static void unlock(Mutex* pm)
            {
                //unlock logic
            }

        public:
            // as we can see this constructor puts a lock on the mutex object
            explicit Lock(Mutex* pm):mutexPtr(pm, unlock) // now here unlock function is sent as the deleter logic
            {
                lock(mutexPtr.get());
            }

            // and the destructor takes the lock from that object
            /*
            ~Lock()
            {
                unlock(mutexPtr);
            }*/
            // we no longer need the destructor when using shared_ptr
    };
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
        // now even dought we return here the allocated createdDog will be destroyed
        return;
    }    
}

Mutex m;
void f3()
{
    Lock mutexLock1(&m);

    // now we have the question what should happen when a copy is performed?
    Lock mutexLock2(mutexLock1);

    // we could perform two actions here
    // either we prohibit copying for objects that this makes sense
    // or we hold on to a resource until the last object using it has been destroyed - by using shared_ptr
}

int main()
{
    f1();
    f2();
    return 0;
}
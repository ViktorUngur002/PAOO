#include <iostream>

namespace page
{
    class Page
    {
        public:
            Page()
            {
                std::cout << "Page is initialized" << std::endl;
            }

            void getContent()
            {
                std::cout << "Page content!" << std::endl;
            }
    };

    //non-local static object
    //static Page globalPage;

    Page& getPage()
    {
        static Page instance; // define and initialize a local static object
        return instance; // return an instance to it
    }
}

namespace tema2 
{
    //using page::globalPage;
    using page::getPage;

    class Book
    {
        public:
            // the initialization order will always respect declaration order
            std::string title;
            std::string author;
            int numPages;
            double rating;
            std::string category;
        
        Book()
        {

        }

        // we need to initialize all the attributes in the constructor, but
        // in this way the values are being assigned not initialized
        // initialization happens before contructor body 
        /*
        Book(std::string t, std::string a, int numP, double r, std::string c)
        {
            title = t;
            author = a;
            numPages = numP; // the affirmation above is not true for numPages and rating since they are built-in types
            rating = r;
            category = c;
        }*/

        //using the member initialization list
        Book(std::string t, std::string a, int numP, double r, std::string c)
        :title(t),
         author(a),
         numPages(numP),
         rating(r),
         category(c)
        {
        }

        // if we use it like this we could get the desired output if the globalPage is initialized first
        // and Book class instance second, but that is something we could not tell
        /*
        Book(std::string t):title(t)
        {
            globalPage.getContent();
        }*/

        // in order to asure the globalPAge will be initialized first we need to:
        Book (std::string t):title(t)
        {
            getPage().getContent();
        }
    };

    class Silent
    {
        //here I will provide the constructors C++ silently writes and calls
        public:
            // these (without cout) are called if let the class empty, usage in main
            Silent()
            {
                std::cout << "The default contstructor" << std::endl;
            }
            ~Silent()
            {
                std::cout << "The destructor" << std::endl;
            }
            Silent(const Silent& s)
            {
                std::cout << "The copy contstructor" << std::endl;
            }
            Silent& operator = (const Silent& s)
            {
                std::cout << "The copy assignment operator" << std::endl;
                return *this;
            }
    };

    // by inheriting this class we move the error to compile time
    class Uncopyable {
        protected:
            Uncopyable() {} 
            ~Uncopyable() {}
        private:
            Uncopyable(const Uncopyable&);
            Uncopyable& operator=(const Uncopyable&);
    };

    // we want to declare a class of unique 1 of 1 watches, these should not have copy constructor or operator
    // defined, but because they are defined by default we need to set them as private 
    class UniqueWatch: private Uncopyable
    {
        public:
            UniqueWatch()
            {
                std::cout << "A unique watch was created!" << std::endl;
            }

            //member function
            void copyWatchMember(const UniqueWatch& otherWatch)
            {
                *this = otherWatch;
            }

            //friend function
            friend void copyWatchFriend(UniqueWatch& dest, const UniqueWatch& src)
            {
                dest = src;
            }
        
        //when done this way, and we try to perform copy in a member or a friend function we will get a link error
        
        /*private:
            UniqueWatch(const UniqueWatch&); 
            UniqueWatch& operator=(const UniqueWatch&);
        */
    };

}

using namespace tema2;

int main()
{
    Book b1;
    //since we are not initializing the values, what are they going to contain its unknown
    std::cout << "The book title is: " << b1.title << std::endl;
    std::cout << "The book authot is: " << b1.author << std::endl;
    std::cout << "The book category is: " << b1.category << std::endl;
    std::cout << "The book number of pages is: " << b1.numPages << std::endl;
    std::cout << "The book rating is: " << b1.rating << std::endl;

    Book b2("Book 1", "Author 1", 500, 8.9, "Drama");
    
    std::cout << "The book title is: " << b2.title << std::endl;
    std::cout << "The book authot is: " << b2.author << std::endl;
    std::cout << "The book category is: " << b2.category << std::endl;
    std::cout << "The book number of pages is: " << b2.numPages << std::endl;
    std::cout << "The book rating is: " << b2.rating << std::endl;

    std::cout << "--------------------------------------------------------" << std::endl;
    
    Book b3("Title 2");

    std::cout << "-------------------------Examples of silently called function---------------------" << std::endl;

    // neither of them are explicitly called by me
    Silent s1;

    Silent s2(s1);
    s2 = s1;

    std::cout << "-------------------------Examples of disallowing silent dunctions---------------------" << std::endl;

    UniqueWatch w1;
    UniqueWatch w2;

    copyWatchFriend(w1, w2);
    w1.copyWatchMember(w2);

    return 0;
}
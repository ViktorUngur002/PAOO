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

    return 0;
}
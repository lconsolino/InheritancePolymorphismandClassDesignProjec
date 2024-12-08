#include <sstream>
#include <iomanip>
#include "product.h"
#include "book.h"
#include "util.h"
using namespace std;

Book::Book (const std::string name, double price, int qty, std::string ISBN, std::string author): Product( "book", name, price, qty)
{
    isbn_=ISBN;
    author_=author;
};

Book::~Book(){

}

std::string Book::getISBN() const{
    return isbn_;

}
std::string Book::getAuthor() const{
    return author_;
}

/**
* Returns the appropriate keywords that this product should be associated with
 */
std::set<std::string> Book::keywords()const{ 
    std::set<std::string> keywordsBook;
    std::set<std::string> authorWords= parseStringToWords(getAuthor());
    for(std::set <std::string>:: iterator it =authorWords.begin(); it !=authorWords.end(); ++it){
        keywordsBook.insert(*it);
    }
    std::set<std::string> nameWords= parseStringToWords(getName());
    for(std::set <std::string>:: iterator it =nameWords.begin(); it !=nameWords.end(); ++it){
        keywordsBook.insert(*it);
    }
    keywordsBook.insert(getISBN());
    return keywordsBook;
}

/**
* Returns a string to display the product info for hits of the search
*/
std::string Book::displayString() const{ 
    string display;
    display = getName() + "\n" + "Author: "+author_ + " ISBN: " +isbn_+ "\n" + to_string(price_).substr(0,5) + " " + to_string(qty_) + " left.";
    return display; 
}   

void Book::dump(std::ostream& os) const { 
    os << category_ << "\n" << name_ << "\n" << fixed<< setprecision(2)<< price_ << "\n" << qty_ << "\n" << isbn_ <<"\n" << author_ <<endl;
}


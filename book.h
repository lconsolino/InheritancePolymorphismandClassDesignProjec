// #ifndef BOOK_H
// #define BOOK_H
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>

class Book: public Product{
public:
    Book(const std::string name, double price, int qty, std::string ISBN, std::string author);
    ~Book(); 
    /**
     * Returns the appropriate keywords that this product should be associated with
     */
    std::set<std::string> keywords() const override;

    /**
     * Returns a string to display the product info for hits of the search
     */
    std::string displayString()const override;

    std::string getISBN() const;
    std::string getAuthor() const;
    void dump(std::ostream& os) const override;

private:
    std::string isbn_;
    std::string author_; 
};
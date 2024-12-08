// #ifndef PRODUCT_H
// #define PRODUCT_H
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>

class Movie: public Product{
public:
    Movie(const std::string name, double price, int qty, std::string genre, std::string rating);
    ~Movie(); 
    /**
     * Returns the appropriate keywords that this product should be associated with
     */
    virtual std::set<std::string> keywords() const override;

    /**
     * Returns a string to display the product info for hits of the search
     */
    virtual std::string displayString()const override;
    virtual void dump(std::ostream& os) const override;

    std::string getGenre() const;
    std::string getRating() const;

private:
    std::string genre_;
    std::string rating_; 
};
    #include <iomanip>
    #include "product.h"
    #include "clothing.h"
    #include "util.h"
    using namespace std;
    
    Clothing::Clothing (const std::string name, double price, int qty, std::string brand, std::string size): Product( "clothing", name, price, qty)
    {
        brand_=brand;
        size_=size;
    }

    Clothing::~Clothing(){

    }
    /**
     * Returns the appropriate keywords that this product should be associated with
     */
    std::set<std::string> Clothing::keywords() const{
        std::set<std::string> keywordsClothing;
        std::set<std::string> brandWords= parseStringToWords(getBrand());
        for(std::set <std::string>:: iterator it =brandWords.begin(); it !=brandWords.end(); ++it){
            keywordsClothing.insert(*it);
        }
        std::set<std::string> nameWords= parseStringToWords(getName());
        for(std::set <std::string>:: iterator it =nameWords.begin(); it !=nameWords.end(); ++it){
            keywordsClothing.insert(*it);
        }
        return keywordsClothing;
    }

    /**
     * Returns a string to display the product info for hits of the search
     */
    std::string Clothing::displayString() const{
        return  getName() + "\n" + "Size: " + size_ + " Brand: "+brand_ + "\n" + to_string(price_).substr(0,5)+" "+ to_string(qty_)+" left.";
        }
        
    void Clothing::dump(std::ostream& os) const { 
        os << category_ << "\n" << name_ << "\n" << fixed <<setprecision(2) << price_ << "\n" << qty_ << "\n" << size_ <<"\n" << brand_ <<endl;
    }

    std::string Clothing::getSize() const{
        return size_;

    }
    std::string Clothing::getBrand() const{
        return brand_;
    }
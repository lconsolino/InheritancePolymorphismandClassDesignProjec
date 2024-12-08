    #include <iomanip>
    #include "product.h"
    #include "movie.h"
    #include "util.h"
    using namespace std;
    //: Product( "movie", name, price, qty)
    
    Movie::Movie (const std::string name, double price, int qty, std::string genre, std::string rating):Product("movie", name, price, qty)
    {
        genre_=genre;
        rating_=(rating);
    }
    Movie::~Movie(){
        
    }
    /**
     * Returns the appropriate keywords that this product should be associated with
     */
    std::set<std::string> Movie::keywords()const {
        std::set<std::string> keywordsMovie;
        std::set<std::string> nameWords= parseStringToWords(getName());
        for(std::set <std::string>:: iterator it =nameWords.begin(); it !=nameWords.end(); ++it){
            keywordsMovie.insert(*it);
        }
        for(std::set <std::string>:: iterator it =keywordsMovie.begin(); it !=keywordsMovie.end(); ++it){
            std::cout<<*it<<endl;
        }
        std::set<std::string> genreWords= parseStringToWords(getGenre());
        //keywordsMovie.insert(getGenre());
        for(std::set <std::string>:: iterator it =genreWords.begin(); it !=genreWords.end(); ++it){
            keywordsMovie.insert(*it);
        }
        return keywordsMovie;
    }

    /**
     * Returns a string to display the product info for hits of the search
     */
    std::string Movie::displayString() const{
        string display= getName() + "\n" + "Genre: " + genre_ + " Rating: " + rating_ + "\n" + to_string(price_).substr(0,5) + " " + to_string(qty_) + " left.";
        return display;
    }

    std::string Movie::getGenre() const{
        return genre_;

    }
    std::string Movie::getRating() const{
        return rating_;
    }
    void Movie::dump(std::ostream& os) const { 
        os << category_ << "\n" << name_ << "\n" << fixed<< setprecision(2)<< price_ << "\n" << qty_ << "\n" << genre_ <<"\n" << rating_ <<endl;
    }
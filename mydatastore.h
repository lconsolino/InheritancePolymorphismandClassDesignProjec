#include <string>
#include <set>
#include <vector>
#include "product.h"
#include "user.h"
#include "datastore.h"
#include "db_parser.h"
#include "util.h"
#include <map>
#include <queue>

class myDataStore : public DataStore{
public:
    myDataStore();
    ~myDataStore();
        /*
         * Adds a product to the data store
         */
    void addProduct(Product* p);

        /**
         * Adds a user to the data store
         */
    void addUser(User* u);
    void keywordsSetInit(Product* p);

        /**
         * Performs a search of products whose keywords match the given "terms"
         *  type 0 = AND search (intersection of results for each term) while
         *  type 1 = OR search (union of results for each term)
         */
    std::vector<Product*> search(std::vector<std::string>& terms, int type);

        /**
         * Reproduce the database file from the current Products and User values
         */
    void dump(std::ostream& ofile);

    /*takes item from spec. index of hits and adds to map of user to cart queue*/
    void addToCart(std::string uname,Product* item);

    /*takes username and prints all of items in mapped cart queue */
    void viewCart(std::string uname);

    /*takes username and 'buys' all products from cart queue while updating appropriate members*/
    void buyCart(std::string uname);

protected:
    std::map<std::string, std::set<Product*>> keywordsToProd_;
    //map of keywords key values to one product that relate to that keyword 
    std::set<Product*> productSet_;
    //a set of all products
    std::map<std::string, std::vector<Product*>> userToCart_;
    // a map of user to user cart [vector]
    std::set<User*> userSet_;
    //a set of all users
    std::set<std::string> userNames_;
    //a set of all users names
    std::map<std::string, User*> nameToUser_;
    //map of names to users
};
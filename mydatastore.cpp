#include <string>
#include <set>
#include <vector>
#include <sstream>
#include <iomanip>
#include "product.h"
#include "user.h"
#include "datastore.h"
#include "mydatastore.h"
#include "db_parser.h"
#include "util.h"
#include "product.h"
#include <map>
#include <queue>

using namespace std;
/*
         * Adds a product to the data store
         */
        myDataStore::myDataStore(){

        };
        myDataStore::~myDataStore(){
            for( std::set <Product*>:: iterator it = productSet_.begin(); it!= productSet_.end();++it){
                delete *it;
            }
            for( std::set <User*>:: iterator it = userSet_.begin(); it!= userSet_.end();++it){
                delete *it;
            }

        }
        
        void myDataStore::addProduct(Product* p) {
            //add to set of products
            productSet_.insert(p);
            keywordsToProd_[p->getName()];
            //map of keywords key values to one product that relate to that keyword 
            userToCart_[p->getName()];
            keywordsSetInit(p);
            return;
        }
        void myDataStore::keywordsSetInit(Product* p){
            std::set<std::string> keywordsSet= p->keywords();
            for(set<std::string> :: iterator it= keywordsSet.begin(); it != (keywordsSet.end()); ++it){
                if(((*it).size())>0){
                    keywordsToProd_[*it].insert(p);
                }
            }
        }

        /**
         * Adds a user to the data store
         */
        void myDataStore::addUser(User* u) {
            userToCart_[u->getName()];
            //initialize user cart as empty
            userSet_.insert(u);
            //adds user to set of all users
            userNames_.insert(u->getName());
            //add username to set of names
            nameToUser_[u->getName()]=u;
            return;
        }

        /**
         * Performs a search of products whose keywords match the given "terms"
         *  type 0 = AND search (intersection of results for each term) while
         *  type 1 = OR search (union of results for each term)
         */
        std::vector<Product*> myDataStore::search(std::vector<std::string>& terms, int type) {
            //if search is of type OR
            if(terms.size()==0){
                std::vector<Product *> result(0,0);
            }
            std::set <Product*> prodWithTerms=keywordsToProd_[terms[0]];
            //initializes set of products to contain return 
            for(long unsigned int i=0;i<terms.size();i++){
                if(type){
                  prodWithTerms= setUnion(keywordsToProd_[terms[i]],prodWithTerms);
                }
                //adds both sets together to prod with terms for each iteration and stores back in prodWithTerms
                else{
                  prodWithTerms=setIntersection(keywordsToProd_[terms[i]],prodWithTerms);
                  //adds duplicates between sets to prod with terms for each iteration and stores back in prodWithTerms
                }
            }
            std::vector<Product *> result(prodWithTerms.begin(), prodWithTerms.end());
            return result;
            }

        /**
         * Reproduce the database file from the current Products and User values
         */
        void myDataStore::dump(std::ostream& ofile) {
            ofile<< "<products>"<<endl;
            for( std::set <Product*>:: iterator it = productSet_.begin(); it!= productSet_.end();++it){
                (*it)->dump(ofile);
            }
            ofile<< "</products>"<<endl;
            ofile<< "<users>"<<endl;
            for( std::set <User*>:: iterator it = userSet_.begin(); it!= userSet_.end();++it){
                (*it)->dump(ofile);
            }
            ofile<< "</users>"<<endl;
            
        }

        void myDataStore::addToCart(string uname,Product* item){
            if(userNames_.find(uname)==userNames_.end()){ 
                //check for invalid username
                cout<<"Invalid username"<<endl;
                return;
            }
            userToCart_[uname].push_back(item);
            //push item [new product] to back of user Cart queue 
        }

        void myDataStore::viewCart(string uname){
            if(userNames_.find(uname)==userNames_.end()){ 
                //check for invalid username
                cout<<"Invalid username"<<endl;
                return;
            }
            vector <Product*> temp =userToCart_[uname];
            //make a copy of cart list
            for(long unsigned int i=0; i<temp.size(); i++){  
                cout << "Item "<< i+1<<endl;
                //repeat until end of cart
                cout<<temp[i]->displayString()<<endl;
                //print front product displayString
            } 
        }

        void myDataStore::buyCart(string uname){
            if(userNames_.find(uname)==userNames_.end()){ 
                //check for invalid username
                cout<<"Invalid username"<<endl;
                return;
            }
            vector <Product*> cartItems=userToCart_[uname];
            for(long unsigned int i=0; i<cartItems.size();i++){
                //for each element in cart from front to back
                if((cartItems[i]->getQty())>=1 && 
                ((nameToUser_[uname]->getBalance()) >=(cartItems[i]->getPrice()))){
                    //if in stock and user has enough credit to purchase
                    cartItems[i]->subtractQty(1);
                    //update product qty
                    nameToUser_[uname]->deductAmount(cartItems[i]->getPrice());
                    //update user credit
                }
            }
        }
#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
    //if product name, book author or clothing brand, keyword is a string >1 char 
    //if word has punctuation it should split at each puntuation 
std::set<std::string> parseStringToWords(string rawWords) 
{
    set <string> setOfWords; //stores valid words
    string storage; //stores curr letter from rawwords 
    for(int i =0; i<rawWords.length();i++ ){
        if((ispunct(rawWords[i]) || rawWords[i]==' ') && storage.length()>1){ 
            //if is punctuation or space and storage len makes letters in storage a valid word
            setOfWords.insert(convToLower(trim(storage)));
            //add lowercase storage to set
            storage="";
            //reset storage to empty
        }
        else if(rawWords[i]!=' ' && !ispunct(rawWords[i])){
            //if letter is not punctuation or space 
            storage.push_back(tolower(rawWords[i]));
            //add lowercase curr letter to storage string 
        }
        else{
            //if punctuation of space and storage len makes letters in storage an invalid word
            storage="";
            //make storage empty
        }
    }
    if(storage.length()>1 || storage==""){
        //if storage len greater than one or empty at end of rawWords add to set
        setOfWords.insert(trim(storage));
    }   
    return setOfWords;
}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}

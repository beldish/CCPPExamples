#include <iostream>
#include <string>
#include <vector>
#include <map>
#include<list>

class Printer {
private:
    std::string _name;
    int _page_count;
public:
    Printer(std::string name, int page_count) {
        _name = name;
        _page_count = page_count;
    };
    void PrintText(std::string text) {
        int pages_needed = text.length();

        if ( pages_needed > _page_count ) {
            throw std::runtime_error("Not enough pages!");
        } 
        _page_count -= pages_needed;

        std::cout << _name << ": " << text << "   pages left " << _page_count << std::endl;
    };  
};

int main(int argc, char *argv[]) {
    std::map<std::string,int> mymap = {{"ABBB",0},{"b",1},{"c",2}};
    std::vector<std::string>  myvec = {"a","b","c","d","e","f","g","h"};
    std::list<std::string>    mylist = {"a","b","c","d","e","f","g","h"};

    // for(auto el : mymap) {
    //     std::cout << el.first << " " << el.second << std::endl;
    // }   
    // for(auto el : myvec) {
    //     std::cout << el << std::endl;
    // } 
    // for(auto el : mylist) {
    //     std::cout << el << std::endl;
    // }

    try {
        Printer printer("My Printer ", 10);
        printer.PrintText("12345");
        printer.PrintText("123");
        printer.PrintText("1234");
    }
    catch (std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    }

    std::cout << "Hello, World!" << std::endl;
    return 0;
}   // end of function

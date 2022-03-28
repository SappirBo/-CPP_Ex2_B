#include <iostream>
#include "Notebook.hpp"
#include <climits>
#include "Direction.hpp"
#include <vector>
#include <map>


// Declering the constent magic numbers.
constexpr int ONE_DIG = 10;
constexpr int TWO_DIG  = 100;
constexpr int THREE_DIG  =1000;
constexpr int MAX_LINE  =100; 
constexpr int MAX_CHAR  =126;
constexpr int MIN_CHAR  =32; 


using namespace std;

namespace ariel{
    // Notebook Constructor
    Notebook::Notebook(){}
    // Notebook DeConstructor
    Notebook::~Notebook(){}

    void Notebook::write(int page, int row, int column, Direction  d,string txt){
        // Checking for bad inputs -> Throw exeption. 
        for(size_t i=0; i<txt.length(); i++){
            if(txt[i] < MIN_CHAR || txt[i] > MAX_CHAR){throw invalid_argument("Caught Exception: Bad Input!.");}
            if(txt[i] == '~'){throw invalid_argument("Caught Exception: char must be != '~'.");}
            if(txt[i] == '\n'){throw invalid_argument("Caught Exception: char must be != '\n'.");}        
        }
        if(page<0 || row<0 || column<0 || column >= MAX_LINE){
            throw invalid_argument("Caught Exception: Page /Row /Column must be grater or equal to 0. (column also >= 100)");
        }
        if((size_t)column+txt.length() > MAX_LINE && d == Direction::Horizontal){
            throw invalid_argument("Caught Exception: Text Length is too big (for Horizontal writing).");
        }
        // In case the page is not exit! 
        if(book.count(page) == 0){
            if(d == Direction::Horizontal){
                book[page][row] = EmptyLine;
                size_t x = 0;
                for(size_t i=(size_t) column; i<(size_t) column+txt.length(); i++){
                    book[page][row][i] = txt[x++];
                }
            }
            else{
                size_t x = 0;
                for(size_t i=(size_t) row; i<(size_t) row+txt.length(); i++){
                    this->book[page][i] = EmptyLine;
                    book[page][i][(size_t)column] = txt[x++];
                }
            }
        }
        // Else -> 
        else{
            if(d == Direction::Horizontal){
                if(book[page].count(row)==0){
                        book[page][row] = EmptyLine; 
                }
                // Checking if there is text writen in this place
                for(size_t i=(size_t) column; i<(size_t) column+txt.length(); i++){
                    if(book[page][(size_t)row][i] != '_'){throw invalid_argument("Caught Exception: This Place allready taken).");}
                }
                // The action is Valid -> writing text.
                size_t x = 0;
                for(size_t i=(size_t) column; i<(size_t)column+txt.length(); i++){
                    book[page][(size_t)row][i] = txt[x++];
                }
            }
            else{
                // Checking if there is text writen in this place
                for(size_t i=(size_t) row; i<(size_t) row+txt.length(); i++){
                    if(book[page].count(i) == 1){
                        if(book[(size_t)page][i][(size_t)column] != '_'){
                            throw invalid_argument("Caught Exception: This Place allready taken).");
                        }
                    }
                }
                // The action is Valid -> writing text.
                size_t x = 0;
                for(size_t i=(size_t) row; i<(size_t) row+txt.length(); i++){
                    if(book[page].count(i) == 0){
                        book[page][i] = EmptyLine; 
                    }
                    book[page][i][(size_t)column] = txt[x++];
                }
            }
        }   
    }
    
    string Notebook::read(int page, int row, int column,Direction d,int length){
        // Checking for bad inputs -> Throw exeption. 
        if(page<0 || row<0 || column<0 || column>=MAX_LINE){
            throw invalid_argument("Caught Exception: Page /Row /Column must be grater or equal to 0.");
        }
        if((size_t)column+(size_t)length > MAX_LINE && d == Direction::Horizontal){
            throw invalid_argument("Caught Exception.");
        }
        if(length <0){
            throw invalid_argument("Caught Exception");
        }
        // 
        string str;
        if(book.count(page) == 0){
            string str;
            for(unsigned int i=0; i<length; i++){
                str += '_';
            }
            return str;
        }
        if(d == Direction::Horizontal){
            if(book[page].count((size_t)row) == 0){
                for(int i=0; i<length; i++){
                    str += '_';
                }
            }
            else{
                for(size_t i= (size_t) column; i<column+length; i++){
                    str += book[page][(size_t)row][i];
                }
            }
        }
        else{
            for(size_t i=(size_t)row; i<length+row ; i++){
                if(book[page].count(i)== 1){
                    str += book[page][i][(size_t)column];
                } 
                else{
                    str += '_';
                }      
            }
        }
        return str;
    }
    
    void Notebook::erase(int page, int row, int column,Direction d,int length){
        if(page<0 || row<0 || column<0 || column >= MAX_LINE){
            throw invalid_argument("Caught Exception: Page /Row /Column must be grater or equal to 0.");
        }
        if(length < 0){
            throw invalid_argument("Caught Exception");
        }
        if((size_t)column+(size_t)length > MAX_LINE && d == Direction::Horizontal){
            throw invalid_argument("Caught Exception: Text Length is too big (for Horizontal writing).");
        }
        if(book.count(page) == 0){
            if(d == Direction::Horizontal){
                book[page][row] = EmptyLine;
                for(int i=column; i<(size_t)column+(size_t)length; i++){
                    book[page][row][(size_t)i] = '~';
                }
            }
            else{
                for(int i=row; i<(size_t)row+(size_t)length; i++){
                    book[page][i] = EmptyLine;
                    book[page][(size_t)i][(size_t)column] = '~';
                }
            }
        }
        else{
            if(d == Direction::Horizontal){
                if(book[page].count(row) == 0){
                        book[page][row] = EmptyLine; 
                }
                for(int i=column; i<(column+length); i++){
                    book[page][(size_t)row][(size_t)i] = '~';
                }
            }
            else{ 
                for(int i=row; i<(size_t)row +(size_t)length; i++){
                    if(book[page].count(i) == 0){
                        book[page][i] = EmptyLine; 
                    }
                    book[page][(size_t)i][(size_t)column] = '~';
                }
            }
        }   
    }
    
    void Notebook::show(int page){
        if(page < 0){
            throw invalid_argument("Caught Exception: Wrong page number (negative number).");
        }
        if(book.count(page) == 0){
            cout << "";
        }
        for(const auto &ptr: book[page]){
            auto row = ptr.first;
            string str = ptr.second;
            string dig1 = ":   ";
            string dig2 = ":  ";
            string dig3 = ": ";
            if(row < ONE_DIG){
                cout << row << dig1 << str << endl;
            }
            else if(row < TWO_DIG){
                cout << row << dig2 << str << endl;
            }
            else if(row < THREE_DIG){
                cout << row << dig3 << str << endl;
            }
            
        }
        
    }

}

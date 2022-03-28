#include <iostream>
#include <climits>
#include "Direction.hpp"
#include <vector>
#include <map>

#define EmptyLine "____________________________________________________________________________________________________"

using namespace std;


namespace ariel
{
    class Notebook{
        private:
        map<int,map<int,string>>  book;

        public:
        Notebook();
        ~Notebook();
        void write(int page, int row, int column, Direction,std::string txt);
        string read(int page, int row, int column,Direction,int length);
        void erase(int page, int row, int column,Direction,int length);
        void show(int page);


    };
}


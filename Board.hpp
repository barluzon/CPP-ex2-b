#pragma once
#include <vector>
#include <string>
#include "Direction.hpp"
using namespace std;

namespace ariel
{
    class Board {
        vector<string> board;
        unsigned int horiStart = INT32_MAX;
        unsigned int vertStart = INT32_MAX;
        int horiEnd = -1;
        int vertEnd = -1;
        void boardSizeUpdate(unsigned int horizontal, unsigned int vertical,Direction dir, unsigned int len);

    public:
        void post(unsigned int horizontal, unsigned int vertical, Direction dir, const string &message);
        string read(unsigned int horizontal, unsigned int vertical, Direction dir, unsigned int len);
        void show();
    };


}

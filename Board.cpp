#include <string>
#include <vector>
#include <iterator>
#include <iostream>
#include "Board.hpp"
#include "Direction.hpp"
using namespace std;
using ariel::Direction;

void ariel::Board::boardSizeUpdate(unsigned int horizontal, unsigned int vertical, Direction dir, unsigned int length){

    int horiLength = 0;
    int vertLength = 0;
    if(dir == Direction::Horizontal){
        horiLength = (int)horizontal+1;
        vertLength = (int)(vertical+length);
    }
    else if(dir == Direction::Vertical){
        vertLength = (int)vertical+1;
        horiLength = (int)(horizontal+length);
    }
    // if board is empty
    if(horiStart == INT32_MAX && horiEnd == -1 && vertStart == INT32_MAX && vertEnd == -1){
        horiStart = horizontal;
        horiEnd = horiLength;
        vertStart = vertical;
        vertEnd = vertLength;
        board.insert(board.begin(),(unsigned int)horiEnd-horiStart,"_");
    }
    // if board is small and we want to make it bigger from end position
    if (horiLength > horiEnd){
        board.insert(board.end(),  ((unsigned int)horiLength - (unsigned int)horiEnd), "_");
        horiEnd = horiLength;
    }
    // if board is small and we want to make it bigger from start position
    if(horizontal<horiStart){
        board.insert(board.begin(), horiStart - horizontal, "_");
        horiStart=horizontal;
    }
    //same vertically
    if (vertical < vertStart){
        vertStart = vertical;
    }
    if (vertLength > vertEnd){
        vertEnd = vertLength;
    }
    //write '_' vertically
    for (auto pointer = board.begin(); pointer < board.end(); pointer++){
        (*pointer).resize((unsigned int)vertEnd-vertStart,'_');
    }
}

void ariel::Board::post(unsigned int horizontal, unsigned int vertical, Direction dir, const string &message){
    //check by direction
    switch (dir){
        case Direction::Horizontal:
            boardSizeUpdate(horizontal,vertical,dir,message.length());
            board.at(horizontal-horiStart).replace(vertical-vertStart,message.length(),message);
            break;

        case Direction::Vertical:
            boardSizeUpdate(horizontal,vertical,dir,message.length());
            for (unsigned int i = 0; i <message.length() ; i++){
                board.at(horizontal-horiStart+i).at(vertical-vertStart)=message[i];
            }
            break;

        default:
            throw out_of_range("please enter: Horizontal or Vertical");
    }
}

string ariel::Board::read(unsigned int horizontal, unsigned int vertical, Direction dir, unsigned int length){
    //check by direction
    vector<string> retMessage(1,"_");
    switch (dir){
        case Direction::Horizontal:
            retMessage.at(0).resize(length,'_');
            //if not in the board
            if(horizontal +1 > horiEnd || horizontal<horiStart){
                return retMessage.at(0);
            }
            for (unsigned int i=0; i < length; ++i){
                //try and catch for out of bound exception
                try{
                    retMessage.at(0).at(i) = board.at(horizontal-horiStart).at(vertical-vertStart+i);
                }
                catch (const std::exception& exc){
                }
            }
            return retMessage.at(0);

        case Direction::Vertical:
            retMessage.at(0).resize(length,'_');
            //if not in the board
            if(vertical+1>(int)vertEnd || vertical<vertStart){
                return retMessage.at(0);
            }
            for (unsigned int i=0; i < length && horizontal+i<horiEnd; i++){
                try{
                    retMessage.at(0).at(i) = board.at(horizontal-horiStart + i).at(vertical-vertStart);
                }
                catch (const std::exception& exc){
                }
            }
            return retMessage.at(0);

        default: 
            throw out_of_range("please enter: Horizontal or Vertical");
    }
}

void ariel::Board::show(){
      for (auto&runner:board){
           cout << string(runner) << endl;
      }
}
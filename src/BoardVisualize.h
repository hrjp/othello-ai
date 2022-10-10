#pragma once
#include <Siv3D.hpp>
#include "Board.h"

class BoardVisualize{
public:
    BoardVisualize(int x, int y, int size);
    void setup(int x, int y, int size);
    void draw(const Board & board);
private:
    int x_;
    int y_;
    int size_;
};

void BoardVisualize::setup(int x, int y, int size){
    x_=x;
    y_=y;
    size_=size;
}

 BoardVisualize::BoardVisualize(int x, int y, int size){
    setup(x,y,size);
 }

void BoardVisualize::draw(const Board & board){
    Rect{ x_, y_, size_ }.draw(Palette::Blue);
}
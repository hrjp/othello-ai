#pragma once
#include<iostream>

namespace OthelloAI{

class Point{
public:
    int x_;
    int y_;
    Point(int x, int y){
        x_=x;
        y_=y;
    }
    Point(){Point(0,0);}
};

class Color{
public:
    //color
    static const int8_t white=1;
    static const int8_t black=-1;
    static const int8_t free=0;

    uint8_t color_;
    Color(uint8_t color){color_=color;}
    Color(){color_=free;}
};

class Disk{
public:
    Point point_;
    Color color_;

    Disk(int x, int y, int8_t color):
        point_(x,y),
        color_(color){}
    Disk(Point point, Color color){
        point_=point;
        color_.color_=color.color_;
    }
    Disk(){Disk(0,0,0);}
};

}// namespace OthelloAI
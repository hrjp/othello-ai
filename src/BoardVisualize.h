#pragma once
#define NO_S3D_USING
#include <Siv3D.hpp>
#include "Board.h"

namespace OthelloAI{

class BoardVisualize{
public:
    BoardVisualize(int x, int y, int size);
    void setup(int x, int y, int size);
    void draw(const Board & board);
    const std::optional<Point> getMouseSquare();
private:
    int x_;
    int y_;
    int size_;
    double square_ratio_=0.95;
    double disk_ratio_=0.9;
    const int board_size_=8;
    std::vector<std::vector<s3d::Circle> > disks_;
};

void BoardVisualize::setup(int x, int y, int size){
    x_=x;
    y_=y;
    size_=size/board_size_;
    for(int x=0;x<board_size_;x++){
        for(int y=0;y<board_size_;y++){
            disks_[x][y].set( x_+int(0.5*size_)+x*size_, y_+int(0.5*size_)+y*size_, int(0.5*size_*square_ratio_));
        }
    }
}

 BoardVisualize::BoardVisualize(int x, int y, int size)
    :disks_(board_size_, std::vector<s3d::Circle>(board_size_)){
    setup(x,y,size);
 }

void BoardVisualize::draw(const Board & board){
    s3d::Rect{x_,y_,size_*board_size_}.draw(s3d::Palette::Black);
    for(int x=0;x<board.getBoard().size();x++){
        for(int y=0;y<board.getBoard().size();y++){
            s3d::Rect{ x_+int((1-square_ratio_)*0.5*size_)+x*size_, y_+int((1-square_ratio_)*0.5*size_)+y*size_, int(size_*square_ratio_)}.draw(s3d::Palette::Green);
            auto disk_color=s3d::Palette::Green;
            if(board.getBoard()[x][y]==OthelloAI::Color::black){
                disk_color=s3d::Palette::Black;
            }
            if(board.getBoard()[x][y]==OthelloAI::Color::white){
                disk_color=s3d::Palette::White;
            }
            disks_[x][y].draw(disk_color);
        }
    }
}

const std::optional<Point> BoardVisualize::getMouseSquare(){
    for(int x=0;x<board_size_;x++){
        for(int y=0;y<board_size_;y++){
            if(disks_[x][y].leftClicked()){
                std::optional<Point> point=Point(x,y);
                return point;
            }
        }
    }
    return std::nullopt;
}
}// namespace OthelloAI
#pragma once

#include "Board.h"

namespace OthelloAI{
class BoardUtils{
public:
    const bool isPlace(const Board & board, const Disk & disk);
    const bool isPlaces(const Board & board, const Color & color);
    const bool isPlaces(const Board & board, const Color & color, std::vector<Disk> & enable_places);
    const bool place(Board & board, const Disk & disk);
    const int count(const Board & board, const Color & color);
    const bool isFinish(const Board & board);
private:
    const int board_size_=8;
    const std::vector<std::vector<int> > disk_dir={{1,0},{1,1},{0,1},{-1,1},{-1,0},{-1,-1},{0,-1},{1,-1}};
    const bool is_area(int x,int y=0);
};

const bool BoardUtils::is_area(int x,int y){
    return (0<=x && x<board_size_ && 0<=y && y<board_size_);
}

const bool BoardUtils::isPlace(const Board & board, const Disk & disk){
    if(board.getColor(disk.point_) != Color::free){
        return false;
    }
    
    for(const auto dir : disk_dir){
        const auto x=disk.point_.x_+dir[0];
        const auto y=disk.point_.y_+dir[1];
        if(is_area(x,y) && (disk.color_*(-1)==board.getBoard()[x][y])){
            int step=1;
            while (is_area(x+dir[0]*step,y+dir[1]*step)){
                if(disk.color_==board.getBoard()[x+dir[0]*step][y+dir[1]*step]){
                    return true;
                }
                ++step;
            }
                
        }
    }
    return false;
}

const bool BoardUtils::place(Board & board, const Disk & disk){
    if(board.getColor(disk.point_) != Color::free){
        return false;
    }
    bool isPlace=false;
    for(const auto dir : disk_dir){
        const auto x=disk.point_.x_+dir[0];
        const auto y=disk.point_.y_+dir[1];
        if(is_area(x,y) && (disk.color_*(-1)==board.getBoard()[x][y])){
            int step=1;
            while (is_area(x+dir[0]*step,y+dir[1]*step)){
                if(disk.color_==board.getBoard()[x+dir[0]*step][y+dir[1]*step]){
                    while(step!=0){
                        --step;
                        board.setDisk(x+dir[0]*step,y+dir[1]*step,disk.color_);     
                    }
                    board.setDisk(disk);
                    isPlace=true;
                    break;
                }
                ++step;
            }
                
        }
    }
    return isPlace;
}

const bool BoardUtils::isPlaces(const Board & board, const Color & color){
    for(int x=0; x<board_size_; ++x){
        for(int y=0; y<board_size_; ++y){
            Disk disk(x,y,color);
            if(isPlace(board,disk)){
                return true;
            }
        }
    }
    return false;
}

const bool BoardUtils::isPlaces(const Board & board, const Color & color, std::vector<Disk> & enable_places){
    enable_places.clear();
    for(int x=0; x<board_size_; ++x){
        for(int y=0; y<board_size_; ++y){
            Disk disk(x,y,color);
            if(isPlace(board,disk)){
                enable_places.emplace_back(disk);
            }
        }
    }
    return enable_places.size()>0;
}

const int BoardUtils::count(const Board & board, const Color & color){
    int disk_cou=0;
    for(const auto & col : board.getBoard()){
        for(const auto & disk : col){
            if(disk == color){
                ++disk_cou;
            }
        }
    }
    return disk_cou;
}

const bool BoardUtils::isFinish(const Board & board){
    const int black_cou=count(board,OthelloAI::Color::black);
    const int white_cou=count(board,OthelloAI::Color::white);
    if(black_cou==0 or white_cou==0 or (black_cou+white_cou)==64){
        return true;
    }
    return false;
}

}// namespace OthelloAI
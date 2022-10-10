#pragma once
#include<vector>
#include "Disk.h"
namespace OthelloAI{

class Board{
    public:
    Board(int size):board_(size, std::vector<int8_t>(size, 0)){};
    Board(){Board(8);}

    void setDisk(Disk disk){board_[disk.point_.x_][disk.point_.y_]=disk.color_.color_;}
    const Disk getDisk(Point point){Disk(point.x_,point.y_,board_[point.x_][point.y_]);}

    void setBoard(std::vector<std::vector<int8_t> > board){board_=board;}
    const std::vector<std::vector<int8_t> > & getBoard();

    private:
     std::vector<std::vector<int8_t> > board_;

};

}// namespace OthelloAI
#pragma once

namespace OthelloAI{
class BoardUtils{
public:
    const bool is_place(Board & board, const Disk & disk);
    //const Board is_places(Board & board, const Disk & disk);
    const bool place(Board & board, const Disk & disk);
private:
    const int board_size_=8;
    const std::vector<int> dir_x={1,1,0,-1,-1,-1,0,1};
    const std::vector<int> dir_y={0,1,1,1,0,-1,-1,-1};
    const std::vector<std::vector<int> > disk_dir={{1,0},{1,1},{0,1},{-1,1},{-1,0},{-1,-1},{0,-1},{1,-1}};
    const bool is_area(int x,int y=0);
};

const bool BoardUtils::is_area(int x,int y){
    return (0<=x && x<board_size_ && 0<=y && y<board_size_);
}

const bool BoardUtils::is_place(Board & board, const Disk & disk){
    if(board.getColor(disk.point_) != Color::free){
        s3d::Print<<U"not free area";
        return false;
    }
    
    for(const auto dir : disk_dir){
        const auto x=disk.point_.x_+dir[0];
        const auto y=disk.point_.y_+dir[1];
        s3d::Print<<U"search point: "<<x<<U", "<<y;
        if(is_area(x,y) && (disk.color_*(-1)==board.getBoard()[x][y])){
            s3d::Print<<U"white point: "<<x<<U", "<<y;
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
        s3d::Print<<U"not free area";
        return false;
    }
    bool is_place=false;
    for(const auto dir : disk_dir){
        const auto x=disk.point_.x_+dir[0];
        const auto y=disk.point_.y_+dir[1];
        s3d::Print<<U"search point: "<<x<<U", "<<y;
        if(is_area(x,y) && (disk.color_*(-1)==board.getBoard()[x][y])){
            s3d::Print<<U"white point: "<<x<<U", "<<y;
            int step=1;
            while (is_area(x+dir[0]*step,y+dir[1]*step)){
                if(disk.color_==board.getBoard()[x+dir[0]*step][y+dir[1]*step]){
                    while(step!=0){
                        --step;
                        board.setDisk(x+dir[0]*step,y+dir[1]*step,disk.color_);     
                    }
                    board.setDisk(disk);
                    is_place=true;
                    break;
                }
                ++step;
            }
                
        }
    }
    return is_place;
}

}// namespace OthelloAI
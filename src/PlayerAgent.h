#pragma once
#define NO_S3D_USING
#include <Siv3D.hpp>
#include "Board.h"
#include "BoardUtils.h"
#include "BoardVisualize.h"

namespace OthelloAI{

class PlayerAgent{
public:
    PlayerAgent(Color mycolor);
    PlayerAgent(){}
    std::optional<Disk> getPlace(const BoardVisualize & board_viz, const Board & board);
    const Color & getColor() const{return mycolor_;}

private:
    Color mycolor_=Color::black;
    BoardUtils utils_;
};

PlayerAgent::PlayerAgent(Color mycolor){
    mycolor_=mycolor;
}

std::optional<Disk> PlayerAgent::getPlace(const BoardVisualize & board_viz, const Board & board){
    const auto point=board_viz.getMouseSquare(); 
    if(point){
        const auto disk=OthelloAI::Disk(point.value(),mycolor_);
        if(utils_.isPlace(board,disk)){
            std::optional<Disk> disk_opt(disk);
            return disk_opt;
        }
    }
    return std::nullopt;
}

}
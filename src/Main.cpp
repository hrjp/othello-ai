#define NO_S3D_USING
#include <Siv3D.hpp>
#include "OthelloAI.h"

void Main(){
    s3d::Window::SetStyle(s3d::WindowStyle::Sizable);
    s3d::Scene::SetBackground(s3d::Palette::Black);
    
    OthelloAI::BoardVisualize board_viz(50,50,50);
    OthelloAI::Board board;
    OthelloAI::BoardUtils board_utils;
    board.setDefaultDisk();
    board.setDisk(OthelloAI::Disk(6,3,OthelloAI::Color::white));
    std::vector<OthelloAI::Disk> enable_places;
    OthelloAI::Color now_color(OthelloAI::Color::black);

    const double board_offset=0.05;

    board_utils.isPlaces(board,now_color,enable_places);

    while (s3d::System::Update()){
       
        auto point=board_viz.getMouseSquare();
        if(point){
            auto disk=OthelloAI::Disk(point.value(),now_color);
            if(board_utils.place(board,disk)){
                now_color.reverse();
            }
            if(!board_utils.isPlaces(board,now_color,enable_places)){
                now_color.reverse();
            }
            if(board_utils.isFinish(board)){
                break;
            }
        }

        board_viz.resize();
        board_viz.draw(board);
        board_viz.drawEnablePlaces(enable_places);
    }
    while (s3d::System::Update()){
        board_viz.resize();
        board_viz.draw(board);

    }

}

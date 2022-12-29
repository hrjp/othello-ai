#define NO_S3D_USING
#include <Siv3D.hpp>
#include "OthelloAI.h"

void Main(){
    s3d::Window::SetStyle(s3d::WindowStyle::Sizable);
    s3d::Scene::SetBackground(s3d::Palette::Skyblue);
    
    OthelloAI::BoardVisualize board_viz(50,50,50);
    OthelloAI::Board board;
    OthelloAI::BoardUtils board_utils;
    board.setDefaultDisk();
    std::vector<OthelloAI::Disk> enable_places;
    OthelloAI::Color now_color(OthelloAI::Color::black);

    const double board_offset=0.05;
    int scene_num=0;
    board_utils.isPlaces(board,now_color,enable_places);
    while (s3d::System::Update()){
        //match
        if(scene_num==0){
            const auto point=board_viz.getMouseSquare();
            if(point){
                auto disk=OthelloAI::Disk(point.value(),now_color);
                if(board_utils.place(board,disk)){
                    now_color.reverse();
                }
                if(!board_utils.isPlaces(board,now_color,enable_places)){
                    now_color.reverse();
                    board_utils.isPlaces(board,now_color,enable_places);
                }
                if(board_utils.isFinish(board)){
                    ++scene_num;
                }
            }
            board_viz.resize();
            board_viz.draw(board);
            board_viz.drawEnablePlaces(enable_places);
            board_viz.drawInfo(board,now_color);
        }
        //result
        else if(scene_num==1){
            board_viz.resize();
            board_viz.draw(board);
            board_viz.drawInfo(board,now_color);
            board_viz.drawResult(board);
        }
    }
}

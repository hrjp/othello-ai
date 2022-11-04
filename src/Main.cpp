#define NO_S3D_USING
#include <Siv3D.hpp>
#include "OthelloAI.h"

void Main(){
    s3d::Window::SetStyle(s3d::WindowStyle::Sizable);
    s3d::Scene::SetBackground(OthelloAI::Color::black);
    
    OthelloAI::BoardVisualize board_viz(50,50,50);
    OthelloAI::Board board;
    OthelloAI::BoardUtils board_utils;
    board.setDefaultDisk();

    const double board_offset=0.05;

    while (s3d::System::Update()){
        //window size
        auto x=s3d::Scene::Size().x*0.5-s3d::Scene::Size().y*(0.5-board_offset);
        auto y=s3d::Scene::Size().y*board_offset;
        auto size=s3d::Scene::Size().y*(1.0-2.0*board_offset);
        board_viz.setup(x,y,size);

        auto point=board_viz.getMouseSquare();
        static OthelloAI::Color now_color(OthelloAI::Color::black);
        if(point){
            auto disk=OthelloAI::Disk(point.value(),now_color);
            if(board_utils.place(board,disk)){
                now_color.reverse();
            }
            if(!board_utils.is_places(board,now_color)){
                now_color.reverse();
            }
            if(now_color==OthelloAI::Color::black){
                s3d::Scene::SetBackground(s3d::Palette::Black);
            }
            else{
                s3d::Scene::SetBackground(s3d::Palette::White);
            }
        }
        board_viz.draw(board);
    }

}

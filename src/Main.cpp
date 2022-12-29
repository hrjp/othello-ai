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
    
    OthelloAI::Color now_color(OthelloAI::Color::black);
    OthelloAI::Player player1(now_color);
    OthelloAI::Player player2(!now_color);

    int scene_num=0;
    std::vector<OthelloAI::Disk> enable_places=board_utils.getEnablePlaces(board,now_color);

    while (s3d::System::Update()){
        //match
        if(scene_num==0){
            
            bool place_flag=false;
            if(player1.getColor()==now_color){
                if(const auto disk=player1.getPlace(board_viz,board); disk){
                    board_utils.place(board,disk.value());
                    place_flag=true;
                }
            }
            else if(player2.getColor()==now_color){
                if(const auto disk=player2.getPlace(board_viz,board); disk){
                    board_utils.place(board,disk.value());
                    place_flag=true;
                }
            }

            if(place_flag){
                if(board_utils.isFinish(board)){
                    ++scene_num;
                }
                else{
                    now_color.reverse();
                    if(!board_utils.isPlaces(board,now_color,enable_places)){
                        now_color.reverse();
                        enable_places=board_utils.getEnablePlaces(board,now_color);
                    }
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

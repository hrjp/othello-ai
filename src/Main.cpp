#define NO_S3D_USING
# include <Siv3D.hpp>

#include "OthelloAI.h"

void Main(){
    // Set background color to sky blue
    s3d::Scene::SetBackground(s3d::ColorF{ 0.8, 0.9, 1.0 });

    OthelloAI::BoardVisualize board_viz(50,50,50);
    OthelloAI::Board board;
    board.setDefaultDisk();
    while (s3d::System::Update()){
        auto point=board_viz.getMouseSquare();
        if(point){
            board.setDisk(point.value(),OthelloAI::Color::black);
        }
        board_viz.draw(board);
    }
}

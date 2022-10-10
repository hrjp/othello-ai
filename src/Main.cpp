# include <Siv3D.hpp>

#include "Board.h"
#include "BoardVisualize.h"

void Main()
{
    // Set background color to sky blue
    Scene::SetBackground(ColorF{ 0.8, 0.9, 1.0 });

    
    // Print a text
    Print << U"Push [A] key";

    while (System::Update())
    {   
        Circle{ 400, 300, 20 }.draw();
    }
}

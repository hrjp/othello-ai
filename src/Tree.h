#pragma once
#include "Board.h"
#include <memory>
#include <vector>

namespace OthelloAI{

class Tree{
public:
    Board board_;
    int count_=0;
    double score_=0.0;
    std::vector<std::shared_ptr<Tree> > children_;
}

}// namespace OthelloAI
#pragma once
#include <string>
#include <vector>
#include "TicTacToeBoard.h"

using namespace std;

class TicTacToeTree
{
public:
    void buildFullTree();
    void breadthFirstSearchForOutcome(string boardSring, TicTacToeBoard::BOARD_STATE requestedState);
    void depthFirstSearchForOutcome(string boardSring, TicTacToeBoard::BOARD_STATE requestedState);
private:
    struct Node
    {
        TicTacToeBoard* board;
        vector < Node* > children;
        Node* parent;
    };
    
    void buildFullTreeHelper(Node* children_node);
};

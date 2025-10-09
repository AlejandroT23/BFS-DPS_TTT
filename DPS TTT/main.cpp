#include <iostream>
#include "TicTacToeBoard.h"
#include "TicTacToeTree.h"

using namespace std;

int main()
{
    TicTacToeTree tree;
    tree.buildFullTree();
    
    string boardStr = "X--O-----";
    tree.breadthFirstSearchForOutcome(boardStr, TicTacToeBoard::BOARD_STATE::X_WIN);
    tree.depthFirstSearchForOutcome(boardStr, TicTacToeBoard::BOARD_STATE::X_WIN);
    
    return 0;
}

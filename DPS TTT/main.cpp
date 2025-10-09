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
    
    tree.breadthFirstSearchForOutcome(boardStr, TicTacToeBoard::BOARD_STATE::O_WIN);
    tree.depthFirstSearchForOutcome(boardStr, TicTacToeBoard::BOARD_STATE::O_WIN);
    
    tree.depthFirstSearchForOutcome(boardStr, TicTacToeBoard::BOARD_STATE::DRAW);
    
    string boardStr2 = "X--OX--O-";
    tree.breadthFirstSearchForOutcome(boardStr2, TicTacToeBoard::BOARD_STATE::X_WIN);
    tree.depthFirstSearchForOutcome(boardStr2, TicTacToeBoard::BOARD_STATE::X_WIN);
    
    tree.breadthFirstSearchForOutcome(boardStr2, TicTacToeBoard::BOARD_STATE::O_WIN);
    tree.depthFirstSearchForOutcome(boardStr2, TicTacToeBoard::BOARD_STATE::O_WIN);
    
    tree.depthFirstSearchForOutcome(boardStr2, TicTacToeBoard::BOARD_STATE::DRAW);
    
    string boardStr3 = "X--OX--O----O--X";
    tree.breadthFirstSearchForOutcome(boardStr3, TicTacToeBoard::BOARD_STATE::X_WIN);
    tree.depthFirstSearchForOutcome(boardStr3, TicTacToeBoard::BOARD_STATE::X_WIN);
    
    tree.breadthFirstSearchForOutcome(boardStr3, TicTacToeBoard::BOARD_STATE::O_WIN);
    tree.depthFirstSearchForOutcome(boardStr3, TicTacToeBoard::BOARD_STATE::O_WIN);
    
    tree.depthFirstSearchForOutcome(boardStr3, TicTacToeBoard::BOARD_STATE::DRAW);
    
    
    return 0;
}

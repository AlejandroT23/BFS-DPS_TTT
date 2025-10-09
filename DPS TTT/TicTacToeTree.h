#pragma once
#include <string>
#include <vector>
#include <deque>
#include "TicTacToeBoard.h"


using namespace std;

class TicTacToeTree
{
public:
    TicTacToeTree();
    void buildFullTree();
    void breadthFirstSearchForOutcome(string boardSring, TicTacToeBoard::BOARD_STATE requestedState);
    void depthFirstSearchForOutcome(string boardSring, TicTacToeBoard::BOARD_STATE requestedState);
private:
    struct Node
    {
        TicTacToeBoard* board;
        vector < Node* > children;
        Node* parent;
        
        ~Node() {
            delete board;
            for (Node* child : children) {
                delete child;
            }
        }
    };
    
    // Stores Dimension size, used throughout the TicTacToeTree.cpp file
    int boardDim;
    
    // Private Functions --Full Tree--
    void buildFullTreeHelper(Node* node, TicTacToeBoard::PLAYER_TURN p_turn, int& xWins, int& oWins, int& draws, int& total_g, int& total_b);
    
    // Private Functions --Search Functions--
    void searchHelper(string board, TicTacToeBoard::BOARD_STATE requestedState, string searchType);
    string getTypeGame(TicTacToeBoard::BOARD_STATE state);
    void getWinPath(Node* currentNode, deque < Node* >& nodes);
    void printWinPath(deque < Node* >& path, int boards, string searchType, string winType);
    
    // Private Functions --Universal Helpers--
    void createChild(Node* &currentNode, TicTacToeBoard::PLAYER_TURN p_turn, int& totalBoards);
    void deleteNodes(Node* node);

};

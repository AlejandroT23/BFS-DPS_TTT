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
    
    void printStats();
    
    void setXWins(int num);
    void setOWins(int num);
    void setDraws(int num);
    void setTotal(int num);
    
    int getXWins();
    int getOWins();
    int getDraws();
    int getTotal();
    
    int totalGames;
    int xWins;
    int oWins;
    int draws;
    
    void buildFullTreeHelper(Node* children_node);
    void getEmptySpaces(vector < int >& empty, string str);
};

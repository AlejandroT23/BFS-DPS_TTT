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
    
    // Getters and Setters for stat numbers
    void setXWins(long long num);
    void setOWins(long long num);
    void setDraws(long long num);
    void setTotalGames(long long num);
    void setTotalBoards(long long num);
    
    long long getXWins();
    long long getOWins();
    long long getDraws();
    long long getTotalGames();
    long long getTotalBoards();
    
    // Declaration for stat numbers
    // Pass these by reference
    long long xWins;
    long long oWins;
    long long draws;
    long long totalGames;
    long long totalBoards;
    int boardDim;
    
    // Private Functions --Full Tree--
    void buildFullTreeHelper(Node* node, TicTacToeBoard::PLAYER_TURN p_turn);
    void deleteNodes(Node* node);
    void printStats();
    
    // Private Functions --Search Functions--
    void searchHelper(string board, TicTacToeBoard::BOARD_STATE requestedState, string searchType);
    void getWinPath(Node* currentNode, deque < Node* >& nodes);
    void printWinPath(deque < Node* >& path, long long boardNum);
    
    //--
    void createChild(Node* &currentNode, TicTacToeBoard::PLAYER_TURN p_turn);
   

};

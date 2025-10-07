#include "TicTacToeTree.h"
#include "TicTacToeBoard.h"
#include <iostream>
#include <cmath>

using namespace std;

void TicTacToeTree::buildFullTree() {
    Node* firstNode = new Node;
    firstNode->parent = NULL;
    
    firstNode->board = new TicTacToeBoard();
    
    
// ask if the TTT board will always be 3x3, but try to find a way to NOT hard code it
// set the turn
    
    for (int i = 1; i < 10; i++) {
        Node* childNode = new Node;
        childNode->parent = firstNode;
        
        childNode->board = new TicTacToeBoard();
        
        int currentCol = i % 3;
        
        if (i % 3 == 0) {
            int currentRow = (i % 3) - 1;
        } else {
            int currentRow = i % 3;
        }
        
//        childNode->board->setSquare(currentRow, currentCol, 'X'); REPLACE X with proper syntax
        
        firstNode->children.push_back(childNode);
    }
    
    for (int j = 0; j < firstNode->children.size(); j++) {
        buildFullTreeHelper(firstNode->children[j]);
    }
}
//--
void TicTacToeTree::buildFullTreeHelper(Node* node) {
    string currentBoardStr = node->board->getBoardString();
    
    TicTacToeBoard::BOARD_STATE currState = node->board->getBoardState();
    
    if (currState != TicTacToeBoard::INCOMPLETE_GAME) {
        
    } else {
        vector < int > emptySpaces;
        TicTacToeBoard::PLAYER_TURN currTurn = node->board->getPlayerTurn();
        
        for (int i = 0; i < emptySpaces.size(); i++) {
            Node* childNode = new Node;
            childNode->parent = node;
            
            childNode->board = new TicTacToeBoard();
            
            int currentPos = emptySpaces[i];
            int currentCol = currentPos % 3;
            
            int currentRow;
            
            if (i % 3 == 0) {
                currentRow = (currentPos % 3) - 1;
            } else {
                currentRow = currentPos % 3;
            }
            
            TicTacToeBoard::SQUARE_OCCUPANT currSquare = childNode->board->getSquare(currentRow, currentCol);
            childNode->board->setSquare(currentRow, currentCol, currSquare);
            
            node->children.push_back(childNode);
        }
        
        for (int j = 0; j < node->children.size(); j++) {
            buildFullTreeHelper(node->children[j]);
        }
    }
}
//--
void TicTacToeTree::getEmptySpaces(vector < int >& empty, string str) {
    for (int i = 0; i < str.length(); i++) {
        if (str.at(i) == '=') {
            empty.push_back(i);
        }
    }
}
//--
void TicTacToeTree::setXWins(int num) {
    xWins = num;
}
//-
void TicTacToeTree::setOWins(int num) {
    oWins = num;
}
//--
void TicTacToeTree::setDraws(int num) {
    draws = num;
}
//--
void TicTacToeTree::setTotalGames(int num) {
    totalGames = num;
}
//--
void TicTacToeTree::setTotalBoards(int num) {
    totalBoards = num;
}
//--
int TicTacToeTree::getXWins() {
    return xWins;
}
//--
int TicTacToeTree::getOWins() {
    return oWins;
}
//--
int TicTacToeTree::getDraws() {
    return draws;
}
//--
int TicTacToeTree::getTotalGames() {
    return totalGames;
}
//--
int TicTacToeTree::getTotalBoards() {
    return totalBoards;
}
//--
void TicTacToeTree::printStats() {
    cout << "Total Games: " << totalGames << endl;
    cout << "X wins: " << xWins << endl;
    cout << "Y wins: " << oWins << endl;
    cout << "Draws: " << draws << endl;
    cout << endl;
    cout << "Total Boards created: " << totalBoards << endl;
}

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
    
    // get game state
    TicTacToeBoard::BOARD_STATE currState = node->board->getBoardState();
    
    if (currState != TicTacToeBoard::INCOMPLETE_GAME) {
        
    } else {
        vector < int > emptySpaces;
        
        
        
        // get playerState
        
        
        
        for (int i = 0; i < emptySpaces.size(); i++) {
            Node* childNode = new Node;
            childNode->parent = node;
            
            childNode->board = new TicTacToeBoard();
            
            int currentPos = emptySpaces[i];
            int currentCol = currentPos % 3;
            
            if (i % 3 == 0) {
                int currentRow = (currentPos % 3) - 1;
            } else {
                int currentRow = currentPos % 3;
            }
            
    //        childNode->board->setSquare(currentRow, currentCol, 'X'); REPLACE X with proper syntax
            
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
void TicTacToeTree::printStats() {
    cout << "Total Games: " << "d" << endl;
    cout << "X wins: " << "d" << endl;
}

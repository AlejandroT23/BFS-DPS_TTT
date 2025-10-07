#include "TicTacToeTree.h"
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
        
    }
}

//--

void TicTacToeTree::buildFullTreeHelper(Node* child_node) {
    
}

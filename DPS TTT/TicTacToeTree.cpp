#include "TicTacToeTree.h"
#include "TicTacToeBoard.h"
#include <iostream>
#include <cmath>

using namespace std;

void TicTacToeTree::buildFullTree() {
    Node* root = new Node;
    root->parent = NULL;
    root->board = new TicTacToeBoard();
    
    boardDim = root->board->getBoardDimension();
    TicTacToeBoard::PLAYER_TURN currentTurn = root->board->getPlayerTurn();
    
    // since this is start, we might be able to get away with hard coding X
    for (int row = 0; row < boardDim; row++){
        for (int col = 0; col < boardDim; col++) {
            TicTacToeBoard::SQUARE_OCCUPANT currentSpace = root->board->getSquare(row, col);
            
            if (currentSpace == TicTacToeBoard::EMPTY) {
                Node* child = new Node;
                child->parent = root;
                child->board = new TicTacToeBoard();
                
                if (currentTurn == TicTacToeBoard::X_TURN) {
                    child->board->setSquare(row, col, TicTacToeBoard::X);
                } else {
                    child->board->setSquare(row, col, TicTacToeBoard::O);
                }
                
                root->children.push_back(child);
                
            }
        }
    }
    
    for (int k = 0; k < root->children.size(); k++) {
        buildFullTreeHelper(root->children[k]);
    }
    
    //figure this out before running code
    printStats();
    deleteNodes(root);

    
}
//--
void TicTacToeTree::newBuildFullTreeHelper(Node* currentNode, TicTacToeBoard::PLAYER_TURN p_turn) {
    
    TicTacToeBoard::BOARD_STATE currBoard = currentNode->board->getBoardState();
    
    // Look at more efficient way to make the "if" part of this logic gate if given the chance
    if (currBoard != TicTacToeBoard::INCOMPLETE_GAME) {
        if (currBoard == TicTacToeBoard::X_WIN) {
            setXWins(xWins++);
        } else if (currBoard == TicTacToeBoard::O_WIN) {
            setOWins(oWins++);
        } else if (currBoard == TicTacToeBoard::DRAW) {
            setDraws(draws++);
        }
    } else {
        for (int row = 0; row < boardDim; row++) {
            for (int col = 0; col < boardDim; col++) {
                TicTacToeBoard::SQUARE_OCCUPANT currSpace = currentNode->board->getSquare(row, col);
                
                if (currSpace == TicTacToeBoard::EMPTY) {
                    Node* child = new Node;
                    child->parent = currentNode;
                    child->board = new TicTacToeBoard();
                    
                    if (p_turn == TicTacToeBoard::X_TURN) {
                        child->board->setSquare(row, col, TicTacToeBoard::X);
                    } else {
                        child->board->setSquare(row, col, TicTacToeBoard::O);
                    }
                    
                    currentNode->children.push_back(child);
                }
            }
        }
        
        for (int k = 0; k < currentNode->children.size(); k++) {
            newBuildFullTreeHelper(currentNode->children[k], currentNode->children[k]->board->getPlayerTurn());
        }
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
//--
void TicTacToeTree::deleteNodes(Node* node) {
    
}

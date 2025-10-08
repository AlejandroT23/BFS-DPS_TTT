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
    
    buildFullTreeHelper(root, currentTurn);
    
    //figure this out before running code
    printStats();
    deleteNodes(root);
}
//--
void TicTacToeTree::buildFullTreeHelper(Node* currentNode, TicTacToeBoard::PLAYER_TURN p_turn) {
    
    setTotalBoards(totalBoards++);
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
        setTotalGames(totalGames++);
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
            buildFullTreeHelper(currentNode->children[k], currentNode->children[k]->board->getPlayerTurn());
        }
    }
}
//---------------------------------------------------
// SETTER FUNCTIONS FOR ALL OF THE STATS THAT WE NEED
//---------------------------------------------------
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
//---------------------------------------------------
// GETTER FUNCTIONS FOR ALL OF THE STATS THAT WE NEED
//---------------------------------------------------
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
//-----------------------
// PRINTS OUT THE RESULTS
//-----------------------
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

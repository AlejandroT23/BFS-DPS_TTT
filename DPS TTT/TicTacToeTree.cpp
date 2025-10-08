#include "TicTacToeTree.h"
#include "TicTacToeBoard.h"
#include <iostream>
#include <cmath>

using namespace std;

void TicTacToeTree::buildFullTree() {
    cout << "The function reaches buildFullTree()" << endl;
    Node* root = new Node;
    root->parent = NULL;
    root->board = new TicTacToeBoard();
    
    boardDim = root->board->getBoardDimension();
    TicTacToeBoard::PLAYER_TURN currentTurn = root->board->getPlayerTurn();
    
    buildFullTreeHelper(root, currentTurn);
    
    //figure this out before running code
    printStats();
    deleteNodes(root);
    cout << "It reaches here" << endl;
}
//--
void TicTacToeTree::buildFullTreeHelper(Node* currentNode, TicTacToeBoard::PLAYER_TURN p_turn) {
//    cout << "The function reaches buildFullTreeHelper()" << endl;
    totalBoards++;
    setTotalBoards(totalBoards);
    TicTacToeBoard::BOARD_STATE currBoard = currentNode->board->getBoardState();
    
    // Possible to for setter functions to automatically increment if that is only what I can them to do?
    // Look at more efficient way to make the "if" part of this logic gate if given the chance
    if (currBoard != TicTacToeBoard::INCOMPLETE_GAME) {
//        cout << "Finished a game" << endl;
        if (currBoard == TicTacToeBoard::X_WIN) {
            xWins++;
            setXWins(xWins);
        } else if (currBoard == TicTacToeBoard::O_WIN) {
            oWins++;
            setOWins(oWins);
        } else if (currBoard == TicTacToeBoard::DRAW) {
            draws++;
            setDraws(draws);
        }
        totalGames++;
        setTotalGames(totalGames);
    } else {
        for (int row = 0; row < boardDim; row++) {
            for (int col = 0; col < boardDim; col++) {
                TicTacToeBoard::SQUARE_OCCUPANT currSpace = currentNode->board->getSquare(row, col);
                
                if (currSpace == TicTacToeBoard::EMPTY) {
                    Node* child = new Node;
                    child->parent = currentNode;
                    child->board = new TicTacToeBoard(currentNode->board->getBoardString());
                    
                    if (p_turn == TicTacToeBoard::X_TURN) {
                        child->board->setSquare(row, col, TicTacToeBoard::X);
                    } else {
                        child->board->setSquare(row, col, TicTacToeBoard::O);
                    }
                    
                    currentNode->children.push_back(child);
                }
            }
        }
        
        for (size_t k = 0; k < currentNode->children.size(); k++) {
            buildFullTreeHelper(currentNode->children[k], currentNode->children[k]->board->getPlayerTurn());
        }
    }
}
//---------------------------------------------------
// SETTER FUNCTIONS FOR ALL OF THE STATS THAT WE NEED
//---------------------------------------------------
void TicTacToeTree::setXWins(long long num) {
    xWins = num;
}
//-
void TicTacToeTree::setOWins(long long num) {
    oWins = num;
}
//--
void TicTacToeTree::setDraws(long long num) {
    draws = num;
}
//--
void TicTacToeTree::setTotalGames(long long num) {
    totalGames = num;
}
//--
void TicTacToeTree::setTotalBoards(long long num) {
    totalBoards = num;
}
//---------------------------------------------------
// GETTER FUNCTIONS FOR ALL OF THE STATS THAT WE NEED
//---------------------------------------------------
long long TicTacToeTree::getXWins() {
    return xWins;
}
//--
long long TicTacToeTree::getOWins() {
    return oWins;
}
//--
long long TicTacToeTree::getDraws() {
    return draws;
}
//--
long long TicTacToeTree::getTotalGames() {
    return totalGames;
}
//--
long long TicTacToeTree::getTotalBoards() {
    return totalBoards;
}
//-----------------------
// PRINTS OUT THE RESULTS
//-----------------------
void TicTacToeTree::printStats() {
    cout << "Total Games: " << totalGames << endl;
    cout << "X wins: " << xWins << endl;
    cout << "O wins: " << oWins << endl;
    cout << "Draws: " << draws << endl;
    cout << endl;
    cout << "Total Boards created: " << totalBoards << endl;
}
//--
void TicTacToeTree::deleteNodes(Node* node) {
//    cout << "Deleting node at: " << node << endl;
    
    if (node->children.empty()) {
        delete node;
    } else {
        while (!node->children.empty()) {
//            cout << "Deleting child at: " << node << endl;
            deleteNodes(node->children.back());
            node->children.pop_back();
        }
        delete node;
//        cout << "Node deleted: " << node << endl;
    }
}

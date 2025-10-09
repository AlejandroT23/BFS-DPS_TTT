#include "TicTacToeTree.h"
#include "TicTacToeBoard.h"
#include <iostream>
#include <cmath>

using namespace std;

TicTacToeTree::TicTacToeTree() {
    totalBoards = 0;
    totalGames = 0;
    xWins = 0;
    oWins = 0;
    draws = 0;
}
//--
void TicTacToeTree::buildFullTree() {
    // Creates initial root node, and initializes its values
    Node* root = new Node;
    root->parent = NULL;
    root->board = new TicTacToeBoard();
    
    // Sets up the board dimensions and first player's turn
    boardDim = root->board->getBoardDimension();
    TicTacToeBoard::PLAYER_TURN currentTurn = root->board->getPlayerTurn();
    
    // Call helper function to create the branch of boards
    buildFullTreeHelper(root, currentTurn);
    
    // Prints the stats of the game and deletes the nodes
    printStats();
    deleteNodes(root);
}
//--
//-- PASS STATS BY REFERENCE
void TicTacToeTree::buildFullTreeHelper(Node* currentNode, TicTacToeBoard::PLAYER_TURN p_turn) {
    // Everytime this function is called, we increase the board count since we are iterating through the children vector
    totalBoards++;
    setTotalBoards(totalBoards);
    
    // We check the board state before we proceed
    TicTacToeBoard::BOARD_STATE currBoard = currentNode->board->getBoardState();
    
    // If the state is finished, we increase stat based on final game state
    if (currBoard != TicTacToeBoard::INCOMPLETE_GAME) {
        // cout << "Finished a game" << endl;
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
        // Increase the total amount of games
        totalGames++;
        setTotalGames(totalGames);
    } else {
        // Set up the row and column of the square
        for (int row = 0; row < boardDim; row++) {
            for (int col = 0; col < boardDim; col++) {
                // Check if the square is occupied
                TicTacToeBoard::SQUARE_OCCUPANT currSpace = currentNode->board->getSquare(row, col);
                
                // If the square is empty, then we create a child node
                if (currSpace == TicTacToeBoard::EMPTY) {
                    Node* child = new Node;
                    child->parent = currentNode;
                    child->board = new TicTacToeBoard(currentNode->board->getBoardString());
                    
                    // Place X/O depending on player turn
                    if (p_turn == TicTacToeBoard::X_TURN) {
                        child->board->setSquare(row, col, TicTacToeBoard::X);
                    } else {
                        child->board->setSquare(row, col, TicTacToeBoard::O);
                    }
                    
                    currentNode->children.push_back(child);
                }
            }
        }
        
        // Recursion through the children vector to create all the boards
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
//---------------------------------------------
// DELETE THE NODES ONCE YOU FINISH THE PROGRAM
//---------------------------------------------
void TicTacToeTree::deleteNodes(Node* node) {
    if (node->children.empty()) {
        delete node;
    } else {
        while (!node->children.empty()) {
            deleteNodes(node->children.back());
            node->children.pop_back();
        }
        delete node;
    }
}

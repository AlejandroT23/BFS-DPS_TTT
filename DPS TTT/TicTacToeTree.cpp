#include "TicTacToeTree.h"
#include "TicTacToeBoard.h"
#include <deque>
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
//--
void TicTacToeTree::breadthFirstSearchForOutcome(string board, TicTacToeBoard::BOARD_STATE requestedState) {
//    Node* root = new Node;
//    root->parent = NULL;
//    root->board = new TicTacToeBoard(board);
//    TicTacToeBoard::PLAYER_TURN p_turn;
//    boardDim = root->board->getBoardDimension();
//    
//    deque < Node* > queue;
//    queue.push_back(root);
//    
//    totalBoards = 1;
//    
//    while (!queue.empty()) {
//        Node* current = queue.front();
//        queue.pop_front();
//        p_turn = current->board->getPlayerTurn();
//        
//        if (current->board->getBoardState() == requestedState) {
//            deque < Node* > winPath;
//            getWinPath(current, winPath);
//            printWinPath(winPath, totalBoards);
//            break;
//        } else {
//            for (int row = 0; row < boardDim; row++){
//                for (int col = 0; col < boardDim; col++) {
//                    TicTacToeBoard::SQUARE_OCCUPANT currSquare = current->board->getSquare(row, col);
//                    
//                    if(currSquare == TicTacToeBoard::EMPTY) {
//                        Node* child = new Node;
//                        child->parent = current;
//                        child->board = new TicTacToeBoard(current->board->getBoardString());
//                        
//                        if (p_turn == TicTacToeBoard::X_TURN) {
//                            child->board->setSquare(row, col, TicTacToeBoard::X);
//                        } else {
//                            child->board->setSquare(row, col, TicTacToeBoard::O);
//                        }
//                        
//                        // Figure out if vector needed?
//                        current->children.push_back(child);
//                        queue.push_back(child);
//                        totalBoards++;
//                    }
//                }
//            }
//            
////            queue.pop_front();
//        }
//    }
//    
//    deleteNodes(root);
    searchHelper(board, requestedState, "BFS");
}
void TicTacToeTree::depthFirstSearchForOutcome(string board, TicTacToeBoard::BOARD_STATE requestedState) {
//    Node* root = new Node;
//    root->parent = NULL;
//    root->board = new TicTacToeBoard(board);
//    TicTacToeBoard::PLAYER_TURN p_turn;
//    boardDim = root->board->getBoardDimension();
//    
//    deque < Node* > queue;
//    queue.push_back(root);
//    
//    totalBoards = 1;
//    
//    while (!queue.empty()) {
//        Node* current = queue.back();
//        queue.pop_back();
//        p_turn = current->board->getPlayerTurn();
//        
//        if (current->board->getBoardState() == requestedState) {
//            deque < Node* > winPath;
//            getWinPath(current, winPath);
//            printWinPath(winPath, totalBoards);
//            break;
//        } else {
//            createChild(current, p_turn);
//            
//            for (Node* n : current->children) {
//                queue.push_back(n);
//            }
//        }
//    }
//    
//    deleteNodes(root);
    searchHelper(board, requestedState, "DFS");
}
//--
void TicTacToeTree::searchHelper(string board, TicTacToeBoard::BOARD_STATE requestedState, string searchType) {
    Node* root = new Node;
    root->parent = NULL;
    root->board = new TicTacToeBoard(board);
    TicTacToeBoard::PLAYER_TURN p_turn;
    boardDim = root->board->getBoardDimension();
    
    deque < Node* > queue;
    queue.push_back(root);
    
    totalBoards = 1;
    
    while (!queue.empty()) {
        
        Node* current;
        
        // if BPS, we grab from front, otherwise we grab from back
        if (searchType == "BFS") {
            current = queue.front();
            queue.pop_front();
        } else {
            current = queue.back();
            queue.pop_back();
        }
        
        p_turn = current->board->getPlayerTurn();
        
        if (current->board->getBoardState() == requestedState) {
            deque < Node* > winPath;
            getWinPath(current, winPath);
            printWinPath(winPath, totalBoards);
            break;
        } else {
            createChild(current, p_turn);
            
            for (Node* n : current->children) {
                queue.push_back(n);
            }
        }
    }
    
    deleteNodes(root);
}
//--
void TicTacToeTree::createChild(Node* &current, TicTacToeBoard::PLAYER_TURN p_turn) {
    for (int row = 0; row < boardDim; row++){
        for (int col = 0; col < boardDim; col++) {
            TicTacToeBoard::SQUARE_OCCUPANT currSquare = current->board->getSquare(row, col);
            
            if(currSquare == TicTacToeBoard::EMPTY) {
                Node* child = new Node;
                child->parent = current;
                child->board = new TicTacToeBoard(current->board->getBoardString());
                
                if (p_turn == TicTacToeBoard::X_TURN) {
                    child->board->setSquare(row, col, TicTacToeBoard::X);
                } else {
                    child->board->setSquare(row, col, TicTacToeBoard::O);
                }
                
                current->children.push_back(child);
                totalBoards++;
            }
        }
    }
}
//--
void TicTacToeTree::getWinPath(Node* currentNode, deque < Node* >& nodes) {
    if (currentNode->parent != NULL) {
        nodes.push_front(currentNode);
        getWinPath(currentNode->parent, nodes);
    } else {
        nodes.push_front(currentNode);
    }
}
//--
void TicTacToeTree::printWinPath(deque < Node* >& path, long long boardNum) {
    // MAKE THIS UNIVERSAL
    cout << "BFS X Win:" << endl;
    int counter = 0;
    
    for (Node* node : path) {
        counter++;
        cout << counter << "." << endl;
        node->board->printBoard();
        cout << endl;
    }
    
    cout << "There were " << boardNum << " boards created." << endl;
    cout << endl;
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
    cout << endl;
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

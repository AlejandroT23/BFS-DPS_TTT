#include "TicTacToeTree.h"
#include "TicTacToeBoard.h"
#include <deque>
#include <iostream>
#include <cmath>

using namespace std;

TicTacToeTree::TicTacToeTree() {
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
    
    int x_wins = 0;
    int o_wins = 0;
    int draw = 0;
    int total_game = 0;
    int total_board = 1;
    
    // Call helper function to create the branch of boards
    buildFullTreeHelper(root, currentTurn, x_wins, o_wins, draw, total_game, total_board);
    
    cout << "Total Games: " << total_game << endl;
    cout << "X wins: " << x_wins << endl;
    cout << "O wins: " << o_wins << endl;
    cout << "Draws: " << draw << endl;
    cout << endl;
    cout << "Total Boards created: " << total_board << endl;
    cout << endl;
    
    deleteNodes(root);
}
//--
//-- PASS STATS BY REFERENCE
void TicTacToeTree::buildFullTreeHelper(Node* currentNode, TicTacToeBoard::PLAYER_TURN p_turn, int& xWins, int& oWins, int& draws, int& totalGames, int& totalBoards) {
    // Everytime this function is called, we increase the board count since we are iterating through the children vector
    
    // We check the board state before we proceed
    TicTacToeBoard::BOARD_STATE currBoard = currentNode->board->getBoardState();
    
    // If the state is finished, we increase stat based on final game state
    if (currBoard != TicTacToeBoard::INCOMPLETE_GAME) {
        if (currBoard == TicTacToeBoard::X_WIN) {
            xWins++;
        } else if (currBoard == TicTacToeBoard::O_WIN) {
            oWins++;
        } else if (currBoard == TicTacToeBoard::DRAW) {
            draws++;
        }
        
        totalGames++;
    } else {
        createChild(currentNode, p_turn, totalBoards);
        // Recursion through the children vector to create all the boards
        for (size_t k = 0; k < currentNode->children.size(); k++) {
            buildFullTreeHelper(currentNode->children[k], currentNode->children[k]->board->getPlayerTurn(), xWins, oWins, draws, totalGames, totalBoards);
        }
    }
}
//--
void TicTacToeTree::breadthFirstSearchForOutcome(string board, TicTacToeBoard::BOARD_STATE requestedState) {
    searchHelper(board, requestedState, "BFS");
}
//--
void TicTacToeTree::depthFirstSearchForOutcome(string board, TicTacToeBoard::BOARD_STATE requestedState) {
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
    
    int totalBoards = 1;
    
    while (!queue.empty()) {
        
        Node* current;
        
        // if BFS, we grab from front, otherwise we grab from back
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
            printWinPath(winPath, totalBoards, searchType);
            break;
        } else {
            createChild(current, p_turn, totalBoards);
            
            for (Node* n : current->children) {
                queue.push_back(n);
            }
        }
    }
    
    deleteNodes(root);
}
//--
void TicTacToeTree::createChild(Node* &current, TicTacToeBoard::PLAYER_TURN p_turn, int& totalBoards) {
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
void TicTacToeTree::printWinPath(deque < Node* >& path, int boards, string search) {
    cout << search << " X Win:" << endl;
    int counter = 0;
    
    for (Node* node : path) {
        counter++;
        cout << counter << "." << endl;
        node->board->printBoard();
        cout << endl;
    }
    
    cout << "There were " << boards << " boards created." << endl;
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

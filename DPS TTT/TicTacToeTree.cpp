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
    
    // Initializes of stats for full tree
    // These stats are passed thoughout this function by reference, that one they are only declared once
    int x_wins = 0;
    int o_wins = 0;
    int draw = 0;
    int total_game = 0;
    int total_board = 1;
    
    // Call helper function to recursively iterate through the binary tree
    buildFullTreeHelper(root, currentTurn, x_wins, o_wins, draw, total_game, total_board);
    
    // Once you establish every game state possible, we print out the stats
    cout << "Total Games: " << total_game << endl;
    cout << "X wins: " << x_wins << endl;
    cout << "O wins: " << o_wins << endl;
    cout << "Draws: " << draw << endl;
    cout << endl;
    cout << "Total Boards created: " << total_board << endl;
    cout << endl;
    
    // To prevent memory leak, we delete the nodes
    deleteNodes(root);
}
//--
void TicTacToeTree::buildFullTreeHelper(Node* currentNode, TicTacToeBoard::PLAYER_TURN p_turn, int& xWins, int& oWins, int& draws, int& totalGames, int& totalBoards) {
    // Everytime this function is called, we proceed to check the game state of the current nodes board to make sure the game is still incomplete
    TicTacToeBoard::BOARD_STATE currBoard = currentNode->board->getBoardState();
    
    // If the state is finished, we increase stat based on the result of the final game
    if (currBoard != TicTacToeBoard::INCOMPLETE_GAME) {
        if (currBoard == TicTacToeBoard::X_WIN) {
            xWins++;
        } else if (currBoard == TicTacToeBoard::O_WIN) {
            oWins++;
        } else if (currBoard == TicTacToeBoard::DRAW) {
            draws++;
        }
        
        // Since the game is over, we increase the amount of games by one
        totalGames++;
    } else {
        // To create the children of the current node, we pass it through a function that takes the node, whose turn it is, and the current total amount of boards
        createChild(currentNode, p_turn, totalBoards);
        
        // Once we get the amount of boards, we iterate through the children vector of the current node to create more branches
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
    // Create root node
    Node* root = new Node;
    root->parent = NULL;
    root->board = new TicTacToeBoard(board);
    
    // Establish board dimensions as well as current player rotation
    TicTacToeBoard::PLAYER_TURN p_turn;
    boardDim = root->board->getBoardDimension();
    
    // Establish the queue and insert the root
    deque < Node* > queue;
    queue.push_back(root);
    
    int totalBoards = 1;
    
    // As long as the queue is not empty, we check throughout the tree
    while (!queue.empty()) {
        
        Node* current;
        
        // If BFS, we grab from front, otherwise we grab from back
        if (searchType == "BFS") {
            current = queue.front();
            queue.pop_front();
        } else {
            current = queue.back();
            queue.pop_back();
        }
        
        // We get the player's turn based on the current node's board
        p_turn = current->board->getPlayerTurn();
        
        // As long as the current board state doesn't match what we are looking for, the loop goes on
        if (current->board->getBoardState() == requestedState) {
            deque < Node* > winPath;
            getWinPath(current, winPath);
            
            printWinPath(winPath, totalBoards, searchType, getTypeGame(requestedState));
            break;
        } else {
            // Create the children based on current node
            createChild(current, p_turn, totalBoards);
            
            // Easier way to say: for (size_t i = 0; i < current->children.size(); i++) {}
            for (Node* n : current->children) {
                queue.push_back(n);
            }
        }
    }
    
    // To prevent memory leak, we delete all nodes once we are finished
    deleteNodes(root);
}
//--
void TicTacToeTree::createChild(Node* &current, TicTacToeBoard::PLAYER_TURN p_turn, int& totalBoards) {
    // Gets the position of the square
    for (int row = 0; row < boardDim; row++){
        for (int col = 0; col < boardDim; col++) {
            // Checks what currently occupies the square
            TicTacToeBoard::SQUARE_OCCUPANT currSquare = current->board->getSquare(row, col);
            
            // As long as the square is empty, we create a child node
            if(currSquare == TicTacToeBoard::EMPTY) {
                // Child node is establish, points to the parent, and shares it board
                Node* child = new Node;
                child->parent = current;
                child->board = new TicTacToeBoard(current->board->getBoardString());
                
                // Sets symbol depending on whose turn it is
                if (p_turn == TicTacToeBoard::X_TURN) {
                    child->board->setSquare(row, col, TicTacToeBoard::X);
                } else {
                    child->board->setSquare(row, col, TicTacToeBoard::O);
                }
                
                // Pushes child node into the children vector of the current node and increases the total number of boards
                current->children.push_back(child);
                totalBoards++;
            }
        }
    }
}
//--
string TicTacToeTree::getTypeGame(TicTacToeBoard::BOARD_STATE state) {
    // Based on desired outcome, we return the letter / word for the print statement
    if (state == TicTacToeBoard::X_WIN) {
        return "X";
    } else if (state == TicTacToeBoard::O_WIN) {
        return "O";
    } else {
        return "Draw";
    }
}
    
//--
void TicTacToeTree::getWinPath(Node* currentNode, deque < Node* >& nodes) {
    if (currentNode->parent != NULL) {
        // We inverse the position of the path, ex: 30 20 10 -> 10 20 30
        nodes.push_front(currentNode);
        getWinPath(currentNode->parent, nodes);
    } else {
        // We move the root to the front of the path
        nodes.push_front(currentNode);
    }
}
//--
void TicTacToeTree::printWinPath(deque < Node* >& path, int boards, string search, string winType) {
    // Custom print out based on what type of search and win we were looking for
    cout << search << " " << winType << " Win:" << endl;
    
    // Initializes counter, and iterates through the path queue to display each turn the players made
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

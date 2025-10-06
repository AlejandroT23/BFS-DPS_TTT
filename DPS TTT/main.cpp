#include <iostream>
#include "TicTacToeBoard.h"

using namespace std;

int main()
{
    TicTacToeBoard b1;
    b1.printBoard();
    cout << endl;

    TicTacToeBoard b2("XXXOOOXXX");
    b2.printBoard();
    cout << endl;
    
    return 0;
}
// This program is a Connect-4 game. Two players switch off, placing their respective
// markers on a 6x7 board. First person to get 4 ina row (horizontal + vertical) wins.

#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <iterator>
#define ROW 6
#define COL 7

using namespace std;

void make_board(char board[ROW][COL]);
void show_board(char board[ROW][COL]);
void play();
bool is_board_full(char board[ROW][COL]);
void reinitialize_pos_array(int posArr[COL]);
bool vertical_win(char board[ROW][COL], char marker, int rowNum, int colNum);
bool horizontal_win(char board[ROW][COL], char marker);
bool diagonal_win(char board[ROW][COL], char marker);

int main(){
    play();
    return 0;
}

// Initializes the dashed board with specified ROW and COL values
void make_board(char board[ROW][COL]){
    for(int i = 0; i < ROW; i++){
        for(int j = 0; j < COL; j++){
            board[i][j] = '-';
        }
    }
}

// Prints the board, starting from the top row (ROW - 1) to the bottom row (ROW = 0)
void show_board(char board[ROW][COL]){
    cout << "*CHECKERBOARD*" << endl;
    for(int i = ROW - 1; i >= 0; i--){ //must print from top (row[5]) to bottom to utilize endl
        for(int j = 0; j < COL; j++){
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

// Play function for the CONNECT4 game. Handles turn logic
void play(){
    char board[ROW][COL];
    make_board(board);
    show_board(board);
    int inputtedCol;
    int currentPlayer = 1;
    char marker;
    int posArr[COL]; // array that keeps track of lowest available position within each column.
    reinitialize_pos_array(posArr);
    while(true){
        if(currentPlayer == 1){
            marker = 'X';
        }
        else{
            marker = 'O';
        }
        cout << "Player " << currentPlayer << "'s turn: Enter a column number: " << endl;
        cin >> inputtedCol;
        if(cin.fail()){ // ERRORS ON NON-INTEGER INPUTS
            cout << "Non-integer input: Please restart the game." << endl;
            break;
        }
        if(inputtedCol != 1 && // checking for a valid input.
           inputtedCol != 2 &&
           inputtedCol != 3 &&
           inputtedCol != 4 &&
           inputtedCol != 5 &&
           inputtedCol != 6 &&
           inputtedCol != 0){
            cout << "Please enter a valid integer between 0 and 6!" << endl;
            continue;
        }
        if(posArr[inputtedCol] == ROW){ // position array has reached the top (ROW)
            cout << "This column is filled! Please input another column. " << endl;
        }
        else{
            board[posArr[inputtedCol]][inputtedCol] = marker;
            posArr[inputtedCol]++;
            if(vertical_win(board, marker, posArr[inputtedCol] - 1, inputtedCol) ||
               horizontal_win(board, marker) ||
               diagonal_win(board, marker)){
                show_board(board);
                cout << "Player " << currentPlayer << " wins! Press 1 to restart the game, or any other number to terminate the game:" << endl;
                int restartInput = 0;
                cin >> restartInput;
                if(restartInput == 1){
                    make_board(board);
                    reinitialize_pos_array(posArr);
                }
                else{
                    break;
                }
            }
            if(is_board_full(board)){
                cout << "BOARD IS FULL!" << endl;
                // NEED TO REINITIALIZE THE BOARD AS IT WAS IN THE BEGINNING (arrays are always pass by reference)
                make_board(board);
                reinitialize_pos_array(posArr);
            }
            show_board(board);
            currentPlayer = currentPlayer % 2 + 1;
        }
    }
}

// checks if the grid is completely devoid of all dashes, thus making the board full.
bool is_board_full(char board[ROW][COL]){ //checking all positions for a dash
    for(int i = 0; i < ROW; i++){
        for(int j = 0; j < COL; j++){
            if(board[i][j] == '-'){
                return false;
            }
        }
    }
    return true;
}

// resets the position array, which keeps track of available row # for every column
void reinitialize_pos_array(int posArr[COL]){
    for(int j = 0; j < COL; j++){ // initializing position array to all zero's
        posArr[j] = 0;
    }
}

// checks for vertical 4 in a rows
bool vertical_win(char board[ROW][COL], char marker, int rowNum, int colNum){
    if(rowNum < 3){
        return false;
    }
    else{
        for(int i = 0; i < 4; i++){
            if(board[rowNum - i][colNum] != marker){
                return false;
            }
        }
        return true;
    }
}


// checks for horizontal 4 in a rows
bool horizontal_win(char board[ROW][COL], char marker){
    int count = 0;
    for(int i = 0; i < ROW; i++)
    {
        for(int j = 0; j < COL; j++)
        {
            if(board[i][j] == marker){
                count++;
            }
            else{
                count = 0;
            }
            if(count == 4){
                return true;
            }
        }
        count = 0;
    }
    return false;
}

// Check for both positive-sloped diagonals and negative-sloped diagonals
// POSSIBLE STARTING POINTS FOR THE DIAGONAL WINS
// positive: row = 0 to 2, col = 0 to 3
// negative: row = 0 to 2, col = 3 to 6
// bad runtime
bool diagonal_win(char board[ROW][COL], char marker){
    int count = 0;
    // positive slope (left to right, increasing the row & col by 1 each
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 4; j++){
            for(int k = 0; k < 4; k++){
                if(board[i + k][j + k] == marker){
                    count++;
                }
                else{
                    count = 0;
                }
                if(count == 4){
                    return true;
                }
            }
        }
    }
    //negative slope (right to left, increasing the row and decreasing columns)
    for(int i = 0; i < 3; i++){
        for(int j = 3; j < 7; j++){
            for(int k = 0; k < 4; k++){
                if(board[i + k][j - k] == marker){
                    count++;
                }
                else{
                    count = 0;
                }
                if(count == 4){
                    return true;
                }
            }
        }
    }
    return false;
}

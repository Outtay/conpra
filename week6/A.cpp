#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>


//http://www.sanfoundry.com/cpp-program-solve-n-queen-problem/
 
/* check if a queen can be placed on board[row][col]*/
bool isSafe(std::vector< std::vector <int> > &board, int row, int col)
{

    //full horizontal and vertical
    for (int i = 0; i < board.size(); i++){
        if (i != col && board[row][i])
            return false;
        if (i != row && board[i][col])
            return false;
    }
    

    //diagonal starting in top left
    /*for (int i = 0; i < board.size(); i++){
        for(int j = 0; j < board.size(); j++){
            if ((i != row && j != col) && board[i][j])
                return false;
        }
    }

    //diagonal starting in bottom left 
    for (int i = board.size()-1; i >= 0; i--){
        for (int j = 0; j < board.size(); j++){
            if ((i != row && j != col) && board[i][j])
                return false;
        }
    }*/
    int i, j;
    for (i = row, j = col; i >= 0 && j >= 0; i--, j--)
    {
        if (board[i][j])
            return false;
    }
 
    for (i = row, j = col; j >= 0 && i < board.size(); i++, j--)
    {
        if (board[i][j])
            return false;
    }
 
    return true;
}
 
/*solve N Queen problem */
bool solveNQ(std::vector< std::vector <int> > &board, int col)
{

    //first check if the given conf is even a legal conf
    for(int i = 0; i < board.size(); i++){
        for(int j = 0; j < board.size(); j++){
            if (board[i][j] == 1){
                board[i][j] = 0;
                if (!isSafe(board, i,j))
                    return false;
                board[i][j] = 1;
            }
        }
    }
    if (col >= board.size())
        return true;
    for (int i = 0; i < board.size(); i++)
    {
        if ( board[i][col] == 1 || isSafe(board, i, col) ){
            board[i][col] = 1;
            if (solveNQ(board, col + 1))
                return true;
            //board[i][col] = 0;
        }
    }
    return false;
}
 

int main (){
    
    int t;
    std::cin >> t;
    for (int i = 1; i <= t; i++) {

        int n;
        std::cin >> n;

        std::vector < std::vector <int> > board(n, std::vector<int>(n));

        for (int j = 0; j < n ; j++){
            for (int k = 0; k < n; k++){
                char c; 
                std::cin >> c;
                if (c == '.')
                    board[j][k] = 0;
                else
                    board[j][k] = 1;
            }
        }

        if (solveNQ(board, 0)){
            std::cout << "Case #" << i << ":\n";
            for (int j = 0; j < n ; j++){
                std::string s;
                for (int k = 0; k < n; k++){
                    if (board[j][k] == 0)
                        s.push_back('.');
                    else 
                        s.push_back('x');
                }
                std::cout << s << "\n";
            }
        } else {
            std::cout << "Case #" << i << ":\n" << "impossible" << "\n";
        }
        

    }
    return 0;
}

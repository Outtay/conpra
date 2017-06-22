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
    for (i = row-1, j = col-1; i >= 0 && j >= 0; i--, j--)
    {
        if (board[i][j])
            return false;
    }
 
    for (i = row+1, j = col-1; j >= 0 && i < board.size(); i++, j--)
    {
        if (board[i][j])
            return false;
    }
 
    return true;
}
 
/*solve N Queen problem */
bool solveNQ(std::vector< std::vector <int> > &board, int col){

    
    if (col >= board.size())
        return true;
    for (int i = 0; i < board.size(); i++){
        if (isSafe(board, i, col) ){
            if (board[i][col] != 2)
                board[i][col] = 1;
            
            if (solveNQ(board, col + 1))
                return true;
            
            if (board[i][col] != 2)
                board[i][col] = 0;
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
                    board[j][k] = 2; //use a 2 to denote a fixed queen
            }
        }

        bool legal = true;
        //first check if the given conf is even a legal conf
        for(int i = 0; i < board.size() && legal; i++){
            for(int j = 0; j < board.size() && legal; j++){
                if (board[i][j]){
                    board[i][j] = 0;
                    if (!isSafe(board, i,j)){
                        legal = false;
                    }
                    board[i][j] = 2;
                }
            }
        }

        /*
        bool possible;
        std::vector < std::vector <int> > tmp;
        tmp = board;
        int row = 0;
        possible = solveNQ(tmp, 0, row);
        while( !possible ){
            if (row < board.size()){
                tmp = board;
                ++row;
            } else 
                break;
            possible = solveNQ(tmp, 0, row);
        }*/

        //if (possible){
        if (legal && solveNQ(board, 0)){
            //board = tmp;
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

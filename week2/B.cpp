#include <stdio.h>
#include <iostream>
#include <vector>
#include <sstream>

int main(){
    int t;
    std::cin >> t;
    for (int i = 1; i <= t; i++) {
        double dist, posts, begin, end;
        std::cin >> dist >> posts >> begin >> end;

         dist -= end - begin - 0.00002;
         double result = dist/(posts-1);
         std::cout << result;
         
    
    }
    return 0;
}
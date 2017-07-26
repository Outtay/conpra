#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>


struct Point {
    double x, y;
};




int main (){
    
    int t;
    std::cin >> t;
    for (int i = 1; i <= t; i++) {
        
        int n; 
        std::cin >> n;

        std::vector<Point> points;
        for (int j = 1; j <= n; j++){
            double x,y;
            std::cin >> x >> y;
        }
        
        
        
        
        std::cout << "Case #" << i << ": " << "something" << "\n";

    }
    return 0;
}

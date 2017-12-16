#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>


int main (){
    
    int t;
    std::cin >> t;
    for (int i = 1; i <= t; i++) {
        
        double x, y;
        int n;

        std::cin >> x >> y >> n;
        Point meteor = {x,y};

        std::vector <Point> polygon;
        for (int j = 1; j <= n; j++){
            double x1, y1, x2, y2;
            std::cin >> x1 >> y1 >> x2 >> y2;
            Point tmp1 = {x1, y1};
            Point tmp2 = {x2, y2};
            polygon.push_back(tmp1);
            polygon.push_back(tmp2);
        }

        //int result = cn_PnPoly(meteor, polygon, polygon.size());
        bool result = PointInPolygon(meteor, polygon);
        int test = pnpoly1(meteor, polygon);
        
        if (test)
            std::cout << "Case #" << i << ": " << "jackpot" << "\n";
        else 
            std::cout << "Case #" << i << ": " << "too bad" << "\n";

    }
    return 0;
}

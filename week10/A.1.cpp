#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

inline int prev(int i, int n) { return i == 0 ? n-1 : i-1; }
inline int next(int i, int n) { return i == n-1 ? 0 : i+1; }

bool orientation( std::vector<Point> &poly) {
  int n = poly.size();
  int i = std::min_element(std::begin(poly), std::end(poly)) - std::begin(poly));
  return ccw(poly[prev(i, n)], poly[next(i, n)], poly[i]) > 0;
}

int pointVsPolygon(std::vector<Point> &poly, Point &point) {
  int n = poly.size(), windingNumber = 0;
  for (int i = 0; i < n; ++i) {
    if (point == poly[i]) return 0;
    int j = next(i, n);
    if (poly[i].y == point.y && poly[j].y == point.y) {
      if (min(poly[i].x, poly[j].x) <= point.x &&
          point.x <= max(poly[i].x, poly[j].x)) return 0;
    } else {
      bool below = poly[i].y < point.y;
      if (below != (poly[j].y < point.y)) {
        bool orientation = ccw(point, poly[j], poly[i]);
        if (orientation == 0) return 0;
        if (below == (orientation > 0)) windingNumber += below ? 1 : -1;
      }
    }
  }
  return windingNumber == 0 ? 1 : -1;
}

int main (){
    
    int t;
    std::cin >> t;
    for (int i = 1; i <= t; i++) {
        
        int x, y;
        int n;

        std::cin >> x >> y >> n;
        Point meteor = {x,y};

        std::vector <Point> polygon;
        for (int j = 1; j <= n; j++){
            int x1, y1, x2, y2;
            std::cin >> x1 >> y1 >> x2 >> y2;
            Point tmp1 = {x1, y1};
            Point tmp2 = {x2, y2};
            polygon.push_back(tmp1);
            polygon.push_back(tmp2);
        }

        //int result = cn_PnPoly(meteor, polygon, polygon.size());
        bool result = isInside(polygon, meteor);
        
        if (result)
            std::cout << "Case #" << i << ": " << "jackpot" << "\n";
        else 
            std::cout << "Case #" << i << ": " << "too bad" << "\n";

    }
    return 0;
}

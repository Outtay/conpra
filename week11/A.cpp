#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>


/*

source: https://stackoverflow.com/questions/11716268/point-in-polygon-algorithm

*/

struct Point {
    double x, y;
};


int pnpoly(int npol, float *xp, float *yp, float x, float y)
    {
      int i, j, c = 0;
      for (i = 0, j = npol-1; i < npol; j = i++) {
        if ((((yp[i] <= y) && (y < yp[j])) ||
             ((yp[j] <= y) && (y < yp[i]))) &&
            (x < (xp[j] - xp[i]) * (y - yp[i]) / (yp[j] - yp[i]) + xp[i]))
          c = !c;
      }
      return c;
    }

int pnpoly1(Point test, std::vector<Point> polygon)
{
  int i, j, c = 0;
  int nvert = polygon.size();
  for (i = 0, j = nvert-1; i < nvert; j = i++) {
    if ( ((polygon[i].y>test.y) != (polygon[j].y>test.y)) &&
	 (test.x < (polygon[j].x-polygon[i].x) * (test.y-polygon[i].y) / (polygon[j].y-polygon[i].y) + polygon[i].x) )
       c = !c;
  }
  return c;
}


bool PointInPolygon(Point point, std::vector<Point> polygon) {
  std::vector<Point> points = polygon;
  int i, j, nvert = points.size();
  bool c = false;

  for(i = 0, j = nvert - 1; i < nvert; j = i++) {
    if( ( (points[i].y > point.y ) != (points[j].y > point.y) ) &&
        (point.x < (points[j].x - points[i].x) * (point.y - points[i].y) / (points[j].y - points[i].y) + points[i].x)
      )
      c = !c;
  }

  return c;
}
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

#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stack>
#include <iomanip>


struct Point {
    int x, y;
};

// A globle point needed for  sorting points with reference
// to  the first point Used in compare function of qsort()
Point p0;
 
// A utility function to find next to top in a stack
Point nextToTop(std::stack<Point> &S)
{
    Point p = S.top();
    S.pop();
    Point res = S.top();
    S.push(p);
    return res;
}

 
// A utility function to swap two points
int swap(Point &p1, Point &p2)
{
    Point temp = p1;
    p1 = p2;
    p2 = temp;
}
 
// A utility function to return square of distance
// between p1 and p2
int distSq(Point p1, Point p2)
{
    return (p1.x - p2.x)*(p1.x - p2.x) +
          (p1.y - p2.y)*(p1.y - p2.y);
}
 
// To find orientation of ordered triplet (p, q, r).
// The function returns following values
// 0 --> p, q and r are colinear
// 1 --> Clockwise
// 2 --> Counterclockwise
int orientation(Point p, Point q, Point r)
{
    int val = (q.y - p.y) * (r.x - q.x) -
            (q.x - p.x) * (r.y - q.y);

    if (val == 0) return 0;  // colinear
    return (val > 0)? 1: 2; // clock or counterclock wise
}
 
// A function used by library function qsort() to sort an array of
// points with respect to the first point
int compare(const void *vp1, const void *vp2)
{
    Point *p1 = (Point *)vp1;
    Point *p2 = (Point *)vp2;
    
    // Find orientation
    int o = orientation(p0, *p1, *p2);
    if (o == 0)
        return (distSq(p0, *p2) >= distSq(p0, *p1))? -1 : 1;
    
    return (o == 2)? -1: 1;
}
 
// Prints convex hull of a set of n points.
std::stack<Point> convexHull(std::vector<Point> points)
{
    int n = points.size();
    // Find the bottommost point
    int ymin = points[0].y;
    int min = 0;
    for (int i = 1; i < n; i++)
    {
        int y = points[i].y;
    
        // Pick the bottom-most or chose the left
        // most point in case of tie
        if ((y < ymin) || (ymin == y &&
            points[i].x < points[min].x))
            ymin = points[i].y, min = i;
    }
    
    // Place the bottom-most point at first position
    swap(points[0], points[min]);
    
    // Sort n-1 points with respect to the first point.
    // A point p1 comes before p2 in sorted ouput if p2
    // has larger polar angle (in counterclockwise
    // direction) than p1
    p0 = points[0];
    qsort(&points[1], n-1, sizeof(Point), compare);
    
    // If two or more points make same angle with p0,
    // Remove all but the one that is farthest from p0
    // Remember that, in above sorting, our criteria was
    // to keep the farthest point at the end when more than
    // one points have same angle.
    int m = 1; // Initialize size of modified array
    for (int i=1; i<n; i++)
    {
        // Keep removing i while angle of i and i+1 is same
        // with respect to p0
        while (i < n-1 && orientation(p0, points[i],
                                        points[i+1]) == 0)
            i++;
    
    
        points[m] = points[i];
        m++;  // Update size of modified array
    }
    
    
    // Create an empty stack and push first three points
    // to it.
    std::stack<Point> S;
    S.push(points[0]);
    S.push(points[1]);
    int h = 2;
    // Process remaining n-3 points
    for (int i = 2; i < m; i++)
    {

        // Keep removing top while the angle formed by
        // points next-to-top, top, and points[i] makes
        // a non-left turn

        while (orientation(nextToTop(S), S.top(), points[i]) != 2){
            //if (S.empty()) break;
            S.pop();
        }
        S.push(points[i]);
        h++;
    }
    
    // Now stack has the output points, print contents of stack
    /*while (!S.empty())
    {
        Point p = S.top();
        //std::cout << "(" << p.x << ", " << p.y <<")" << endl;
        S.pop();
    }*/
    return S;
}


//shoelace formula
double area(std::vector<double> &X, std::vector<double> &Y) {

    double area = 0.0;
 
    int j = X.size() - 1;
    for (int i = 0; i < X.size(); i++){
        area += ( X[j] + X[i]) * (Y[j] - Y[i] );
        j = i; 
    }
 
    return abs(area);
}

std::string cutOff(std::string s){

    char last = s.back();

    while (last == '0'){
        s.pop_back();
        last = s.back();
    }

    if (last == '.'){
        s.push_back('0');
    }

    return s;

}

int main (){
    
    int t;
    std::cin >> t;
    for (int i = 1; i <= t; i++) {
        
        int n;
        std::cin >> n;

        std::vector<Point> points;
        for (int j = 1; j <= n; j++){
            int x,y;
            std::cin >> x >> y;
            Point tmp = {x,y};
            points.push_back(tmp);
        }

        std::vector<double> X;
        std::vector<double> Y;
        std::stack<Point> sta;
        sta = convexHull(points);

        while (!sta.empty()){
            Point p = sta.top();
            X.push_back((double)p.x);
            Y.push_back((double) p.y);
            sta.pop();
        }

        double res = area(X,Y);

        std::string restr = cutOff(std::to_string(res));
        
        std::cout << "Case #" << i << ": " << restr << "\n";

    }
    return 0;
}

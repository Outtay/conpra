#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
 
//source: http://www.sanfoundry.com/dynamic-programming-solutions-box-stacking-problem/
 
//this structure contains the variables for the dimensions of a box ie, length, breadth and height
struct box
{
    int l,b,h;
};
 
//comparison function used for sorting of all the boxes based on their base area
bool compare(box one, box two)
{
    return one.l*one.b < two.l*two.b;
}
 
int boxStacking(vector<box> boxes, int n)
{
    int i,j;
 
    //vector to store all the results
    vector<int> lis(3*n);
 
    //lis[i]=maximum attainable height by including box i at the bottom
 
    //initialization
    for(i=0;i<3*n;i++)
        lis[i]=boxes[i].h;
 
    //implementing linear increasing subsequence approach 
    for(i=1;i<3*n;i++)
    {
        for(j=0;j<i;j++)
        {
            //if dimensions of box j are lesser than box i
            //box j can be placed on top of box i
            if(boxes[j].l<boxes[i].l && boxes[j].b<boxes[i].b)
            {
                if(lis[j]+boxes[i].h>lis[i])
                    lis[i]=lis[j]+boxes[i].h;
            }
        }
    }
 
    int maxHeight=lis[0];
 
    //now, choose the one which gives the maximum height
    for(i=1;i<3*n;i++)
    {
        if(lis[i]>maxHeight)
            maxHeight=lis[i];
    }
 
    return maxHeight;
}
 
int main()
{
    int t; 
    std::cin >> t;

    for (int i = 1; i <= t; i++){
        int h, n;
        std::cin >> h >> n;

        std::vector <box> boxes;
        for (int j = 0; j < n; j++){
            int x,y,z;
            std::cin >> x >> y >> z;
            box tmp1 = {min(y,z), max(y,z), x};
            box tmp2 = {min(x,z), max(x,z), y};
            box tmp3 = {min(x,y), max(x,y), z};

            boxes.push_back(tmp1);
            boxes.push_back(tmp2);
            boxes.push_back(tmp3);
        }

        sort(boxes.begin(),boxes.end(),compare);
        
        int max = boxStacking(boxes, boxes.size()/3);
        if ( max >= h)
            std::cout << "Case #" << i << ": " << "yes" << "\n";
        else
            std::cout << "Case #" << i << ": " << "no" << "\n";
        
    }
  return 0;
}

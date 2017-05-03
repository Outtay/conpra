#include <stdio.h>
#include <iostream>
#include <string>

int main (){
    
    int t;
    scanf("%i", &t);
    if (t == 1) {

        int n;
        scanf("%i", &n);
        
        std::string output = "";
 
        for (i = 1; i <= n; i++){
            char s1[100000];
            scanf ("%100000s" , s1 );
            std::string s2 = s2;
            size_t index = s2.find("ent");
            s2.replace(index, std::string("ent").length(), "ierender");
            
            size_t index = s2.find("entin");
            s2.replace(index, std::string("entin").length(), "ierende");
            
            size_t index = s2.find("enten");
            s2.replace(index, std::string("enten").length(), "ierende");
            output += s2;
        }
         printf ( "Case #%d:\n%s" , n , output );

    } else {
        return 0;
    }
    
    return 0;
}

#include <stdio.h>
#include <iostream>
#include <string>

void findReplaceAll(std::string &wholeString, const char *toReplace, const char *replacement){

    size_t index = wholeString.find(toReplace);
    while (index != std::string::npos){
        wholeString.replace(index, std::string(toReplace).length(), replacement);
        index = wholeString.find(toReplace);
    }
}


int main (){
    
    int t;
    scanf("%i", &t);
    if (t == 1) {

        int n;
        scanf("%i", &n);
        
        std::string output = "";
 
        for (int i = 1; i <= n; i++){
            char s1[100001];

            scanf(" %[^\n]100000s", s1);
            std::string s2 = s1;

            findReplaceAll(s2, "entin", "ierende");
            findReplaceAll(s2, "enten", "ierende");
            findReplaceAll(s2, "ent", "ierender");
            output += s2;
            if (i != n) output += "\n";
        }
         printf ( "Case #1:\n%s\n" , output.c_str() );

    } else {
        return 0;
    }
    
    return 0;
}

#include <stdio.h>
#include <iostream>

//Source for everything: your slides
int main (){
    
    int t;
    scanf("%d", &t);
    for (int i = 1; i <= t; i++) {
        
        std::string s1;
        char s2[101];
        scanf ("%100s" , s2 );
        printf ( "Case #%d: Hello %s!\n" , i , s2 );

    }
    return 0;
}

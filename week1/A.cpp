#include <stdio.h>
#include <iostream>

//Source for everything: your slides
int main (){
    
    int t;
    scanf("%d", &t);
    for (int i = 1; i <= t; i++) {
        
        char s1[101];
        scanf ("%100s" , s1 );
        printf ( "Case #%d: Hello %s!\n" , i , s1 );

    }
    return 0;
}

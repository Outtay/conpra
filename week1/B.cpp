#include <stdio.h>
#include <iostream>

int main (){
    
    int t;
    scanf("%i", &t);
    for (int i = 1; i <= t; i++) {
        
        long c = 299792458;
        int mass;
        scanf ("%i" , &mass );
        long e = mass * c * c;
        printf ( "Case #%i: %li" , i ,e );

    }
    return 0;
}

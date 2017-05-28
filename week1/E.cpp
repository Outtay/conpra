#include <iostream>
#include <string>  
#include <cctype>
#include <vector>
#include <math.h>


int main (){
    int t;
    scanf("%i", &t);
    if (t < 1 || t > 20) return -1; //only did some checks to find out if that's the problem with my submissions
    for (int i = 1; i <= t; i++){
        char s1[1002];
        scanf ("%1001s" , s1 );
        std::string s2 = s1;
        if (s2.size() < 1 || s2.size() > 1000) return -1; 

        std::vector<std::string> numbers;
        std::vector<std::string> operators;

        for (int j = 0; j < s2.length(); j++){
            //find the numbers first 
            if (std::isdigit(s2[j])){
                //ugly but yeah, just trying to add stuff to the vector
                numbers.push_back(std::string(""));
                numbers.back().push_back(s2[j]);

                
                for(int k = 1; k < 11; k++){
                    //find numbers with mulitple digits
                    if(std::isdigit(s2[j+k])){
                        numbers.back().push_back(s2[j+k]);
                        
                    } else {
                        j += k-1;
                        break;
                    }
                }
            //find the operators and just move forward with the index, since the ops are of fixed size
            } else if (std::isalpha(s2[j])){
                
                if(s2[j] == 'p'){
                    operators.push_back(std::string("p"));
                    j += 3;
                } else if(s2[j] == 'm'){
                    operators.push_back(std::string("m"));
                    j += 4;
                } else if(s2[j] == 't'){
                    if(s2[j+1] == 'o'){
                        operators.push_back(std::string("e")); //use e for powerof, just 'cause
                        j += 11;
                    } else if(s2[j+1] == 'i'){
                        operators.push_back(std::string("t")); 
                        j += 4;
                    }
                }
            }
        }

        long result; 
        //again just to see if that's better
        for (int j = 0; j < numbers.size(); j++)
            if (std::stol(numbers[j]) > 1000000000 || std::stol(numbers[j]) < 0) return -1;

        //special case: single number in input
        if (operators.size() < 1){ 
            printf ( "Case #%i: %s\n" , i ,numbers[0].c_str() );
            return 0;
        }
         //calculate the result
        for (int j = 0; j < operators.size(); j++)
            if (operators[j] == "p"){
                if (j == 0){
                    result = std::stol(numbers[0]) + std::stol(numbers[1]);
                } else {
                    result += std::stol(numbers[j+1]);
                }
            } else if (operators[j] == "m"){
                if (j == 0){
                    result = std::stol(numbers[0]) - std::stol(numbers[1]);
                } else {
                    result -= std::stol(numbers[j+1]);
                }        
            } else if (operators[j] == "e"){
                if (j == 0){
                    result = long( pow( double(std::stol(numbers[0])) ,double(std::stol(numbers[1]))) ); // not sure if it's necessary, but it looks that way
                } else {
                    result = long( pow( double(result) ,double(std::stol(numbers[j+1]))) );
                }
            } else if (operators[j] == "t"){
                if (j == 0){
                    result = std::stol(numbers[0]) * std::stol(numbers[1]);
                } else {
                    result *= std::stol(numbers[j+1]);
                }
            }
    

        printf ( "Case #%i: %li\n" , i ,result );

    }
    return 0;
}

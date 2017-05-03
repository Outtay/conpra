#include <iostream>
#include <string>  
#include <cctype>
#include <vector>
#include <math.h>


int main (){
    int t;
    scanf("%i", &t);
    for (int i = 1; i <= t; i++){
        char s1[1001];
        scanf ("%1000s" , s1 );
        std::string s2 = s1;

        std::vector<std::string> numbers;
        std::vector<std::string> operators;
        //index = std::distance(s1.begin(), it);
        for (int j = 0; j < s2.length(); j++){
            //find the numbers first 
            if (std::isdigit(s2[j])){
                //ugly but yeah
                numbers.push_back(std::string(""));
                numbers.back().push_back(s2[j]);

                //find numbers with mulitple digits
                for(int k = 1; k < 11; k++){
                    if(std::isdigit(s2[j+k])){
                        numbers.back().push_back(s2[j+k]);
                        
                    } else {
                        j += k-1;
                        break;
                    }
                }
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
                    result = long( pow( double(std::stol(numbers[0])) ,double(std::stol(numbers[1]))) );
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
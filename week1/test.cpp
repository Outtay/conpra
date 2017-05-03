#include <iostream>
#include <string>  
#include <cctype>
#include <vector>
#include <typeinfo>

int main (){
    int t = 1;
    for (int i = 1; i <= t; i++){
        char s1[1001];
        //scanf ("%1000s" , s1 );
        std::string s2 = "5000";

        std::vector<std::string> numbers;

        //index = std::distance(s1.begin(), it);
        for (int i = 0; i < s2.length(); i++){
            //find the numbers first 
            if (std::isdigit(s2[i])){
                
                //std::string temp = string(s2[i]);
                char temp = s2[i];
                std::string test;
                //test.push_back(s2[i]);
                
                numbers.push_back(std::string(""));
                numbers.back().push_back(s2[i]);


                printf("hey");
            } else if (std::isalpha(s2[i])){
                printf("ho");
                /*switch( s2[i] ){
                    case "p" :
                        break;
                    case "m" :
                        break;
                    case "t" :
                        if (s2[i+1] == "o"){

                        } else if ( s2[i+1] == "i"){

                        }
                        break;
                    default: break;
                        
                }*/
            }
            
        }

    }
}
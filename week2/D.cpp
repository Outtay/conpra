#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm> 

int main(){
    std :: ios_base :: sync_with_stdio ( false );
    int t;
    std::cin >> t;
    for (int i = 1; i <= t; i++) {
        int s, f;
        std::cin >> s >> f;
        std::vector<int> rooms;
        for (int j = 1; j <= s; j++){
            int begin, end;
            std::cin >> begin >> end;
            if (begin == end){
                rooms.push_back(begin);
                break;
            }
            for (int k = begin; k <= end; k++){
                rooms.push_back(k);
            }
        }
        std::sort(rooms.begin(), rooms.end());
        std::cout << "Case #" << i << ":\n";
        for (int j = 1; j <= f; j++){
            int friendNr;
            std::cin >> friendNr;
            std::cout << rooms[friendNr-1] << "\n";
        }

        if (i != t){
            std::string blankLine;
            std::getline(std::cin, blankLine);
        }

        
    }
    return 0;
}
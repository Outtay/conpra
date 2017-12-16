#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

/*# We are at monster i which has rem_hp HP left and Diana has
# extra_shots shots saved up, how much gold can she get?
function rec(i, rem_hp, extra_shots)
  # Base case: all monsters have been killed.
  if (rem_hp <= 0 && i + 1 == N) return 0

  # Monster i is dead, move on to the next one.
  if (rem_hp <= 0) return rec(i + 1, H[i + 1], extra_shots)

  # Memoization.
  if is_set(memo[i][rem_hp][extra_shots])
    return memo[i][rem_hp][extra_shots]

  # The tower shoots next. Diana saves up another shot.
  ret = rec(i, rem_hp - Q, extra_shots + 1)

  # Diana shoots next, using one of the saved up shots.
  # If the shot kills the current monster, she gets its gold.
  if (extra_shots > 0)
    gold = (rem_hp <= P) ? G[i] : 0
    ret = max(ret, gold + rec(i, rem_hp - P, extra_shots - 1))

  return memo[i][rem_hp][extra_shots] = ret


# Since Diana plays first, she has one extra shot initially.
print rec(0, H[0], 1) */

int rec(int i, int rem_hp, int extra_shots, std::vector<int> &minionHealth , std::vector< std::vector < std::vector <int> > > &memo, int tatt, int latt, std::vector<int> &golds){
    if (rem_hp <= 0 && i + 1 == memo.size()) 
        return 0;

    if (rem_hp <= 0)   
        return rec(i+1, minionHealth[i+1], extra_shots + 1, minionHealth, memo, tatt, latt, golds);

    if (memo[i][rem_hp][extra_shots])
        return memo[i][rem_hp][extra_shots];

    int ret = rec (i, rem_hp - tatt, extra_shots+1, minionHealth, memo, tatt, latt , golds);
    if (extra_shots>0){
        int gold;
        if (rem_hp <= latt)
            gold = golds[i];
        else
            gold = 0;
        ret = std::max(ret, gold + rec(i, rem_hp - latt, extra_shots - 1, minionHealth, memo, tatt, latt, golds)); 
    }   

    return memo[i][rem_hp][extra_shots] = ret;
}

int main (){
    
    int t;
    std::cin >> t;
    for (int i = 1; i <= t; i++) {
        
        int n, latt, tatt;
        std::cin >> n >> latt >> tatt;

        std::vector <int> minionHealth;
        std::vector <int> minionGold;
        for (int j = 0; j < n; j++){
            int tmp;
            int tmp2;
            std::cin >> tmp >> tmp2;
            minionHealth.push_back(tmp);
            minionGold.push_back(tmp2);
        }

        std::vector< std::vector < std::vector <int> > > memo (n, std::vector<std::vector<int> > (n, std::vector<int>(n)));
        int result = rec(i, minionHealth[0], 1, minionHealth, memo, tatt, latt, minionGold);


        
        std::cout << "Case #" << i << ": " << "something" << "\n";

    }
    return 0;
}

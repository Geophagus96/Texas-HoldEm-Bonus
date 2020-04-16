#include <iostream>
#include <math.h>
#include "SevenEval.h"
using namespace std;

double Expectation_3(int X1, int X2, int X3, int X4, int X5, int X6, int simulation_times_3, int cards[52]);

double Expectation_2(int X1, int X2, int X3, int X4, int X5, int simulation_times_2, int simulation_times_3);

double Expectation_1(int X1, int X2, int simulation_times_1, int simulation_times_2, int simulation_times_3);

double Expectation_3(int X1, int X2, int X3, int X4, int X5, int X6, int simulation_times, int cards[52]){
    int temp_cards[52];
    for (int i=0; i<52; i++){
        temp_cards[i] = cards[i];
    }
    int cards_unknown[46];
    int cards_known[6] = {X1,X2,X3,X4,X5,X6};
    for (int i=0; i<6; i++){
            int n = (52-i);
            int x = cards_known[i];
            n = deleteElement(temp_cards,n,x);
    }
    for (int i=0; i<46; i++){
            cards_unknown[i] = temp_cards[i];
    }
    int win_times = 0;
    int lose_times = 0;
    int temp;
    int ridx;
    for (int j=0; j<simulation_times; j++){
        for (int i=0; i<3; i++){
                ridx = rand()%(46-i);
                temp = cards_unknown[ridx];
                cards_unknown[ridx] = cards_unknown[(46-i-1)];
                cards_unknown[(46-i-1)] = temp;
        }
        int player_rank = SevenEval::GetRank(X1, X2, X3, X4, X5, X6, cards_unknown[43]);
        int dealer_rank = SevenEval::GetRank(X3, X4, X5, X6, cards_unknown[43], cards_unknown[44], cards_unknown[45]);
        if (player_rank > dealer_rank){
            win_times += 1;
        }
        else{
            lose_times += 1;
        }
    }
    return 0;
}


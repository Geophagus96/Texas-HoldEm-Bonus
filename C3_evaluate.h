#include <iostream>
#include <math.h>
#include <array>
#include "SevenEval.h"
#include "deleteElement.h"

using namespace std;

double Expectation_1(int X1, int X2, int simulation_times_1, int simulation_times_3, int cards[52]);

array<double,2> Expectation_2(int X1, int X2, int X3, int X4, int X5, int simulation_times_3, int cards[52]);

double Expectation_3(int X1, int X2, int X3, int X4, int X5, int X6, int simulation_times_3);

double Expectation_3(int X1, int X2, int X3, int X4, int X5, int X6, int simulation_times_3, int cards[52]){
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
    for (int j=0; j<simulation_times_3; j++){
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
    double win_time = win_times;
    double lose_time = lose_times;
    double prob = win_time/(win_time+lose_time);
    return prob;
}

array<double,2> Expectation_2(int X1, int X2, int X3, int X4, int X5, int simulation_times_3, int cards[52]){
    int temp_cards_2[52];
    for (int i=0; i<52; i++){
        temp_cards_2[i] = cards[i];
    }
    int cards_2_known[5] = {X1,X2,X3,X4,X5};
    for (int i=0; i<5; i++){
        int n = (52-i);
        int x = cards_2_known[i];
        n = deleteElement(temp_cards_2,n,x);
    }
    double expectation_2 = 0;
    double prob_win_2 = 0;
    for (int i=0; i<47; i++){
        int X6 = temp_cards_2[i];
        double prob_win_3 = Expectation_3(X1,X2,X3,X4,X5,X6,simulation_times_3,cards);
        if (prob_win_3 > 0.5){
            expectation_2 += (2*prob_win_3-1);
            prob_win_2 += prob_win_3;
        }
        else{
            prob_win_2 += prob_win_3;
        }
    }
    expectation_2 = expectation_2/47;
    prob_win_2 = prob_win_2/47;
    array <double,2> decision_2;
    decision_2[0] = expectation_2;
    decision_2[1] = prob_win_2;
    return decision_2;
}

double Expectation_1(int X1, int X2, int simulation_times_1, int simulation_times_2, int cards[52]){
    int temp_cards_1[52];
    for (int i=0; i<52; i++){
        temp_cards_1[i] = cards[i];
    }
    int cards_1_known[2] = {X1,X2};
    int cards_1_unknown[50];
    for (int i=0; i<2; i++){
        int n = (52-i);
        int x = cards_1_known[i];
        n = deleteElement(temp_cards_1,n,x);
    }
    for (int i=0; i<50; i++){
        cards_1_unknown[i] = temp_cards_1[i];
    }
    double prob_win_1 = 0;
    double e1_part2 = 0;
    double e1_part3 = 0;
    int ridx;
    int temp;
    for (int i=0; i<simulation_times_1; i++){
            for (int i=0; i<3; i++){
                ridx = rand()%(50-i);
                temp = cards_1_unknown[ridx];
                cards_1_unknown[ridx] = cards_1_unknown[(50-i-1)];
                cards_1_unknown[(50-i-1)] = temp;
            }
            array <double,2> decision= Expectation_2(X1, X2, cards_1_unknown[47], cards_1_unknown[48], cards_1_unknown[49],simulation_times_2, cards);
            if (decision[1] > 0.5){
                prob_win_1 += decision[1];
                e1_part2 += (2*decision[1]-1);
                e1_part3 += decision[0];
            }
            else{
                prob_win_1 += decision[1];
                e1_part3 += decision[0];
            }
    }
    prob_win_1 = prob_win_1/simulation_times_1;
    e1_part2 = e1_part2/simulation_times_1;
    e1_part3 = e1_part3/simulation_times_1;
    double e1 = 2*(2*prob_win_1-1)+e1_part2+e1_part3;
    return e1;
}

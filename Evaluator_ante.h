#include <iostream>
#include <math.h>
#include <array>
#include "SevenEval.h"
#include "deleteElement.h"

using namespace std;

array<double,2>  Expectation_1(int X1, int X2, int simulation_times_1, int simulation_times_3, int cards[52]);
array<double,5> Expectation_1_test(int X1, int X2, int simulation_times_1, int simulation_times_3, int cards[52]);



array<double,4> Expectation_2(int X1, int X2, int X3, int X4, int X5, int simulation_times_3, int cards[52]);

array<double,2> Expectation_3(int X1, int X2, int X3, int X4, int X5, int X6, int simulation_times_3);

array<double,3> Expectation_3(int X1, int X2, int X3, int X4, int X5, int X6, int simulation_times_3, int cards[52]){
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
    int tie_times =0 ;
    int winws_times =0;
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
            if (player_rank >=5854){
                winws_times +=1;
            }
        }
        else if (player_rank < dealer_rank){
            lose_times += 1;
        }
        else{
            tie_times +=1;
        }
    }
    double win_time = win_times;
    double winws_time = winws_times;
    double lose_time = lose_times;
    double p31= win_time/(win_time+tie_times+lose_time);
    double p32 = winws_time/(win_time+tie_times+lose_time);
    double p33 = lose_time/(win_time+tie_times+lose_time);
    array <double,3> decision_3;
    decision_3[0] = p31;
    decision_3[1] = p32;
    decision_3[2] = p33;
    return decision_3;
}

array<double,4> Expectation_2(int X1, int X2, int X3, int X4, int X5, int simulation_times_3, int cards[52]){
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
    double prob_win_21 = 0;
    double prob_win_22 = 0;
    double prob_lose_23=0;
    for (int i=0; i<47; i++){
        int X6 = temp_cards_2[i];
       array <double,3> prob_win_3 = Expectation_3(X1,X2,X3,X4,X5,X6,simulation_times_3,cards);
        if (prob_win_3[0]-prob_win_3[2] > 0){
            expectation_2 += (prob_win_3[0]-prob_win_3[2]);
            prob_win_21 += prob_win_3[0];
            prob_win_22 += prob_win_3[1];
            prob_lose_23 += prob_win_3[2];
        }
        else{
            prob_win_21 += prob_win_3[0];
            prob_win_22 += prob_win_3[1];
            prob_lose_23 += prob_win_3[2];
        }
    }
    expectation_2 = expectation_2/47;
    prob_win_21 = prob_win_21/47;
    prob_win_22 = prob_win_22/47;
    prob_lose_23 = prob_lose_23/47;
    array <double,4> decision_2;
    decision_2[0] = expectation_2;
    decision_2[1] = prob_win_21;
    decision_2[2] = prob_win_22;
    decision_2[3] = prob_lose_23;
    return decision_2;
}

array<double,2>  Expectation_1(int X1, int X2, int simulation_times_1, int simulation_times_2, int cards[52]){
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
    double prob_win_11 = 0;
    double prob_win_12 = 0;
    double prob_lose_13 = 0;
    double e1_part2 = 0;
    double e1_part3 = 0;
    double e0 = 0;
    double esquare=0;
    int ridx;
    int temp;
    for (int j=0; j<simulation_times_1;j++){
            for (int i=0; i<3; i++){
                ridx = rand()%(50-i);
                temp = cards_1_unknown[ridx];
                cards_1_unknown[ridx] = cards_1_unknown[(50-i-1)];
                cards_1_unknown[(50-i-1)] = temp;
            }
            array <double,4> decision= Expectation_2(X1, X2, cards_1_unknown[47], cards_1_unknown[48], cards_1_unknown[49],simulation_times_2, cards);
            if (decision[1]-decision[3]> 0){
                prob_win_11 += decision[1];
                prob_win_12 += decision[2];
                prob_lose_13 +=decision[3];
                e1_part2 += (decision[1]-decision[3]);
                e1_part3 += decision[0];

                esquare += pow(2*(decision[1]-decision[3])+(decision[1]-decision[3])+decision[0]+(decision[2]-decision[3]),2);
            }
            else{
                prob_win_11 += decision[1];
                prob_win_12 += decision[2];
                prob_lose_13 +=decision[3];
                e1_part3 += decision[0];

                esquare += pow(2*(decision[1]-decision[3])+decision[0]+(decision[2]-decision[3]),2);
            }

    }
    prob_win_11 = prob_win_11/simulation_times_1;
    prob_win_12 = prob_win_12/simulation_times_1;
    prob_lose_13 =prob_lose_13/simulation_times_1;
    e1_part2 = e1_part2/simulation_times_1;
    e1_part3 = e1_part3/simulation_times_1;
    e0 = prob_win_12-prob_lose_13;
    double e1 = 2*(prob_win_11-prob_lose_13)+e1_part2+e1_part3+e0;
    double esquare1 =esquare/(simulation_times_1);
//    -pow(e1,2)*simulation_times_1/(simulation_times_1-1);
    array <double,2> pp;
    pp[0]=e1;
    pp[1]=esquare1;
    return pp;

}

array<double,5> Expectation_1_test(int X1, int X2, int simulation_times_1, int simulation_times_2, int cards[52]){
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
    double prob_win_11 = 0;
    double prob_win_12 = 0;
    double prob_lose_13 = 0;
    double e1_part2 = 0;
    double e1_part3 = 0;
    double e0 = 0;
    int ridx;
    int temp;
    for (int j=0; j<simulation_times_1;j++){
            for (int i=0; i<3; i++){
                ridx = rand()%(50-i);
                temp = cards_1_unknown[ridx];
                cards_1_unknown[ridx] = cards_1_unknown[(50-i-1)];
                cards_1_unknown[(50-i-1)] = temp;
            }
            array <double,4> decision= Expectation_2(X1, X2, cards_1_unknown[47], cards_1_unknown[48], cards_1_unknown[49],simulation_times_2, cards);
            if (decision[1]-decision[3]> 0){
                prob_win_11 += decision[1];
                prob_win_12 += decision[2];
                prob_lose_13 +=decision[3];
                e1_part2 += (decision[1]-decision[3]);
                e1_part3 += decision[0];
            }
            else{
                prob_win_11 += decision[1];
                prob_win_12 += decision[2];
                prob_lose_13 +=decision[3];
                e1_part3 += decision[0];
            }
    }
    prob_win_11 = prob_win_11/simulation_times_1;
    prob_win_12 = prob_win_12/simulation_times_1;
    prob_lose_13 =prob_lose_13/simulation_times_1;
    e1_part2 = e1_part2/simulation_times_1;
    e1_part3 = e1_part3/simulation_times_1;
    e0 = prob_win_12-prob_lose_13;
    double e1 = 2*(prob_win_11-prob_lose_13)+e1_part2+e1_part3+e0;
    array <double,5> pp;
    pp[0]=e0;
    pp[1]=2*(prob_win_11-prob_lose_13);
    pp[2]=e1_part2;
    pp[3]=e1_part3;
    pp[4]=e1;
    return pp;
}

#include <iostream>
#include <math.h>
#include "SevenEval.h"
using namespace std;

double Expectation_3(int X1, int X2, int X3, int X4, int X5, int X6, int simulation_times_3);

double Expectation_2(int X1, int X2, int X3, int X4, int X5, int simulation_times_2, int simulation_times_3);

double Expectation_1(int X1, int X2, int simulation_times_1, int simulation_times_2, int simulation_times_3);

double Expectation_3(int X1, int X2, int X3, int X4, int X5, int X6, int simulation_times){
   int cards[52];
   for (int i=0; i<52; i++){
     cards[i] = i;
     cout << cards[i] << endl;
   }

   return 0;
}

#include <iostream>
#include "SevenEval.h"
#include "Evaluator.h"
#include <math.h>

using namespace std;
int main(){
    int cards[52];
    for (int i=0; i<52; i++){
            cards[i] = i;
   }
   double prob = Expectation_3(49, 44, 2, 14, 29, 16, 10000,cards);
   cout << prob << endl;
   double e1 = Expectation_1(44,26,10000,10000,cards);
   cout << e1 << endl;
   return 0;
}

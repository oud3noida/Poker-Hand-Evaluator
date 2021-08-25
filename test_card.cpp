#include <iostream>
#include "evaluator/Card.h"

using namespace std;

int main() {
    for (int i = 1; i <= 13; ++i) {
        for (int s = 0; s < 4; ++s) {
            string f = Card(i, s).formatted;
            cout << f << endl;
            Card c(f);
            cout << c.number << ' ' << c.suit << endl;
        }
    }
}
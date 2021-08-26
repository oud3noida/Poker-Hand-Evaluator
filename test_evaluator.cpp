#include <iostream>
#include "evaluator/Evaluator.h"

using namespace std;

int main() {
    vector<Card> cards;

    for (int i = 0; i < 7; ++i) {
        string f;
        cin >> f;
        cards.emplace_back(f);
    }

    Evaluator ev(cards);
    int ev_rank = ev.evaluate();
    cout << ev_rank << endl;
    cout << ev.get_hand_name(ev_rank) << endl;
}
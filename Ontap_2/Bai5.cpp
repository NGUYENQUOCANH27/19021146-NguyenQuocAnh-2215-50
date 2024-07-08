#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    int scores[5];
    int sum = 0;

    for(int i = 0; i < 5; ++i) {
        cin >> scores[i];
        sum += scores[i];
    }

    double average = static_cast<double>(sum) / 5;

    cout << fixed << setprecision(2) << average << endl;

    return 0;
}
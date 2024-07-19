#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int N;
    cin >> N;

    vector<int> T(N);
    for (int i = 0; i < N; i++) {
        cin >> T[i];
    }

    sort(T.begin(), T.end());

    int totalWaitingTime = 0;
    int currentTime = 0;

    for (int i = 0; i < N; i++) {
        totalWaitingTime += currentTime;
        currentTime += T[i];
    }

    cout << totalWaitingTime << endl;

    return 0;
}

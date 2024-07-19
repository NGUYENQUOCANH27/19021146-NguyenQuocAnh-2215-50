#include <iostream>
#include <string>

using namespace std;

int main() {
    int N;
    cin >> N;
    
    for (int i = 0; i < N; ++i) {
        int I;
        cin >> I;
        string strI = to_string(I);
        int count = 0;
        
        for (char c : strI) {
            int digit = c - '0';
            if (digit != 0 && I % digit == 0) {
                ++count;
            }
        }
        
        cout << count << endl;
    }
    
    return 0;
}

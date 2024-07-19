#include <iostream>
#include <string>
using namespace std;

bool isPalindrome(int num) {
    string str = to_string(num);
    int len = str.length();
    for (int i = 0; i < len / 2; ++i) {
        if (str[i] != str[len - i - 1]) {
            return false;
        }
    }
    return true;
}

int main() {
    int T;
    cin >> T;
    
    while (T--) {
        int A, B;
        cin >> A >> B;
        
        int count = 0;
        for (int i = A; i <= B; ++i) {
            if (isPalindrome(i)) {
                ++count;
            }
        }
        
        cout << count << endl;
    }
    
    return 0;
}

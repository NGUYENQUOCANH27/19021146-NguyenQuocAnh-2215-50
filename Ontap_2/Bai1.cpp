#include <iostream>
#include <vector>

using namespace std;

vector<int> distinctNumbers(const vector<int>& input) {
    vector<int> result;
    if (input.empty()) return result;
    
    result.push_back(input[0]);
    for (size_t i = 1; i < input.size(); ++i) {
        if (input[i] != input[i - 1]) {
            result.push_back(input[i]);
        }
    }
    return result;
}

int main() {
    vector<int> input;
    int num;
    
    while (cin >> num && num >= 0) {
        input.push_back(num);
    }
    input.push_back(num); 

    vector<int> output = distinctNumbers(input);
    
    for (int n : output) {
        cout << n << " ";
    }
    cout << endl;
    
    return 0;
}

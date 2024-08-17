#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> arr(n);
    unordered_map<int, int> frequency;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        frequency[arr[i]]++;
    }
    int most_frequent_element = arr[0];
    int max_frequency = frequency[most_frequent_element];
    for (const auto& element : frequency) {
        if (element.second > max_frequency) {
            most_frequent_element = element.first;
            max_frequency = element.second;
        }
    }
    cout << most_frequent_element << endl;
    return 0;
}
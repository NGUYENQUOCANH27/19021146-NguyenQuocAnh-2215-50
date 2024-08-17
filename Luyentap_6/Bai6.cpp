#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void generateWords(int n, int k, string currentWord, vector<string>& result) {
    if (currentWord.length() == k) {
        result.push_back(currentWord);
        return;
    }
    char startChar = (currentWord.empty()) ? 'a' : currentWord.back() + 1;

    for (char ch = startChar; ch < 'a' + n; ch++) {
        generateWords(n, k, currentWord + ch, result);
    }
}
int main() {
    int N, K;
    cin >> N >> K;
    vector<string> result;
    generateWords(N, K, "", result);
    sort(result.begin(), result.end());
    for (const string& word : result) {
        cout << word << endl;
    }
    return 0;
}

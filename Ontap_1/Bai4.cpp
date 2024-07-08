#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

string number_to_words(int num);

string helper(int num);

vector<string> below_20 = {"", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};

vector<string> tens = {"", "ten", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};

vector<string> thousands = {"", "thousand", "million"};

int main() {
    int num;
    cin >> num;

    if (num == 0) {
        cout << "zero" << endl;
    } else if (num < 0) {
        cout << "negative " << number_to_words(-num) << endl;
    } else {
        cout << number_to_words(num) << endl;
    }

    return 0;
}

string number_to_words(int num) {
    if (num == 0) return "zero";

    string result = "";
    int i = 0;

    while (num > 0) {
        if (num % 1000 != 0) {
            result = helper(num % 1000) + thousands[i] + (result.empty() ? "" : " " + result);
        }
        num /= 1000;
        ++i;
    }

    return result;
}

string helper(int num) {
    if (num == 0) {
        return "";
    } else if (num < 20) {
        return below_20[num] + " ";
    } else if (num < 100) {
        if (num % 10 == 0) {
            return tens[num / 10] + " ";
        } else {
            return tens[num / 10] + "-" + below_20[num % 10] + " ";
        }
    } else {
        return below_20[num / 100] + " hundred " + (num % 100 ? helper(num % 100) : "");
    }
}

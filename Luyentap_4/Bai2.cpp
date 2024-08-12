#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

class BigInt {
    string value;

public:
    BigInt() : value("0") {}

    BigInt(const char* num) : value(num) {
        value = value.substr(value.find_first_not_of('0'));
        if (value.empty()) value = "0";
    }

    BigInt(const BigInt& b) : value(b.value) {}

    friend ostream& operator<<(ostream& os, const BigInt& b) {
        os << b.value;
        return os;
    }

    friend BigInt operator+(const BigInt& a, const BigInt& b) {
        string result;
        int carry = 0;
        int sum = 0;

        int len1 = a.value.length();
        int len2 = b.value.length();
        int maxLen = max(len1, len2);

        string str1 = a.value;
        string str2 = b.value;
        reverse(str1.begin(), str1.end());
        reverse(str2.begin(), str2.end());

        for (int i = 0; i < maxLen; i++) {
            int digit1 = i < len1 ? str1[i] - '0' : 0;
            int digit2 = i < len2 ? str2[i] - '0' : 0;

            sum = digit1 + digit2 + carry;
            carry = sum / 10;
            result += (sum % 10) + '0';
        }

        if (carry > 0) {
            result += carry + '0';
        }

        reverse(result.begin(), result.end());
        return BigInt(result.c_str());
    }
};

#include <iostream>
#include <string>
#include <numeric>

using namespace std;

string gcdOfStrings(string str1, string str2);

int main() {
    string str1 = "ABC";
    string str2 = "ABCABC";

    cout << gcdOfStrings(str1, str2) << endl;

    return 0;
}

string gcdOfStrings(string str1, string str2) {
    if (str1 + str2 != str2 + str1) return "";
    return str1.substr(0, std::gcd(size(str1), size(str2)));
}

/**
 * @file sparse.cpp
 *
 * @brief Defines the non-inline functions of .
 */

#include <iostream>
#include <string>
using namespace std;

void NToBinaryString (int N, string &str)
{
    if (N == 0) {
        str.push_back('0');
        return;
    }
    while (N != 0) {
        str.push_back ('0' + N%2);
        N >>= 1;
    }
}

int BinaryStringToN (string &str)
{
    int n = 0;
    int m = 1;
    for (string::iterator it = str.begin(); it != str.end(); it++) {
        if (*it != '0') n += m;
        m <<= 1;
    }
    return n;
}

int solution (int N)
{
    string str;
    char prev;
    NToBinaryString (N+1, str);
    int m = string::npos;
    int i;

    // Find sequence of atleast 2 1's in the highest order
    for (i = 1; i < str.size(); i++) {
        if ((str[i] == '1') && (str[i-1] == '1')) {
            m = i;
        }
    }

    if (m == string::npos) return N+1;

    // Find first sequence of atleast 2 0's after the highest 1's
    for (i = m+1; i < str.size(); i++) {
        if (str[i] == '0' && str[i-1] == '0') break;
    }

    for (int j = 0; j < i-1; j++) str[j] = '0';
    if (i == str.size()) {
        str[i-1] = '0';
        str.push_back('1');
    } else {
        str[i-1] = '1';
    }
    return BinaryStringToN (str);
}

int main ()
{
    int n, c;
    cin >> n;
    while (n) {
        cin >> c;
        cout << solution(c) << endl;
        n--;
    }
    return 0;
}

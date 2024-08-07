#include <iostream>
#include <vector>

using namespace std;

struct bigint {

    static const long long BASE = 1e9;
    static const long long SIZE = 10;

    long long digits[SIZE];

    bigint() {
        for (int i = 0; i < SIZE; i++) {
            digits[i] = 0;
        }
    }

    bigint(long long x) {
        for (int i = 0; i < SIZE; i++) {
            digits[i] = 0;
        }

        int next = 0;
        while (x) {
            digits[next++] = x % BASE;
            x /= BASE;
        }
    }

    bigint(const bigint& other) {
        for (int i = 0; i < SIZE; i++) {
            digits[i] = other.digits[i];
        }
    }

    bigint& operator=(const bigint& other) {
        for (int i = 0; i < SIZE; i++) {
            digits[i] = other.digits[i];
        }

        return *this;
    }

    void operator+=(const bigint& other) {
        for (int i = 0; i < SIZE; i++) {
            digits[i] += other.digits[i];
        }

        for (int i = 0; i < SIZE - 1; i++) {
            if (digits[i] >= BASE) {
                digits[i] -= BASE;
                digits[i + 1]++;
            }
        }
    }

    bigint operator+(const bigint& other) {
        bigint n(*this);
        n += other;
        return n;
    }

    bigint& operator++() {
        *this += 1;
        return *this;
    }

    void operator-=(const bigint& other) {
        for (int i = 0; i < SIZE; i++) {
            digits[i] -= other.digits[i];
        }

        for (int i = 0; i < SIZE - 1; i++) {
            if (digits[i] < 0) {
                digits[i] += BASE;
                digits[i + 1]--;
            }
        }
    }

    bigint operator-(const bigint& other) {
        bigint n(*this);
        n -= other;
        return n;
    }

    bigint& operator--() {
        *this -= 1;
        return *this;
    }

    void operator*=(const bigint& other) {
        *this = *this * other;
    }

    bigint operator*(const bigint& other) {
        bigint result;

        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE - i; j++) {
                result.digits[i + j] += digits[i] * other.digits[j];
            }
        }

        for (int i = 0; i < SIZE - 1; i++) {
            result.digits[i + 1] += result.digits[i] / BASE;
            result.digits[i] %= BASE;
        }

        return result;
    }

    void operator/=(long long x) {
        for (int i = SIZE - 1; i >= 0; i--) {
            if (i) {
                digits[i - 1] += (digits[i] % x) * BASE;
            }

            digits[i] /= x;
        }
    }

    bigint operator/(long long x) {
        bigint n(*this);
        n /= x;
        return n;
    }
};

ostream& operator<<(ostream& out, const bigint& num) {
    string result;

    char buffer[10];

    for (int i = bigint::SIZE - 1; i >= 0; i--) {
        sprintf(buffer, "%09d", num.digits[i]);
        result += buffer;
    }

    int first_idx = result.find_first_not_of('0');
    if (first_idx == string::npos) {
        out << "0";
    } else {
        out << result.substr(first_idx);
    }

    return out;
}

int main()
{
    int n;
    cin >> n;
    if(n == 1) {
        cout << 2;
        return 0; }

    vector<bigint> dp(n+1);
    dp[0] = 1;
    dp[1] = 2;
    dp[2] = 3;

    for (int i = 3; i <= n; ++i)
        dp[i] = dp[i-1] + dp[i-2];
    cout.precision(65);
    cout << dp[n];
    return 0;
}

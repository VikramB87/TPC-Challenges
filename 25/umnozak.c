#include <stdio.h>
#include <math.h>

#define MAX_DIGITS 18

typedef long long Long64;

Long64 a, b;
int digits[MAX_DIGITS+1];
int dmax;

int GetDigits (Long64 num)
{
    int n = MAX_DIGITS;
    do {
        digits[n--] = num % 10;
        num /= 10;
    } while (num > 0);
    return n;
}

Long64 GetNumber ()
{
    int d = MAX_DIGITS;
    Long64 num = 0;
    Long64 m = 1;

    while (d > dmax) {
        num += (m*digits[d]);
        d--;
        m *= 10;
    }
    return num;
}

Long64 Init (Long64 num)
{
    int d;

    for (d = MAX_DIGITS; d > dmax; d--) {
        if (digits[d] == 0) digits[d] = 1;
    }
    return GetNumber ();
}

Long64 Increment (Long64 num)
{
        int d = MAX_DIGITS;

    while (d > dmax) {
        if (digits[d] != 9) {
            ++digits[d];
            break;
        }

        digits[d] = 1;
        d--;
    }
    if (d == MAX_DIGITS) return num+1;

    if (d == dmax) digits[dmax--] = 1;
    return GetNumber ();
}

int CountSelfProduct (Long64 a, Long64 b)
{
        Long64 n;
        int    i;
        Long64 p;
        int    count = 0;

    n = (Long64) sqrt ((double) a);

    dmax = GetDigits (n);
    n = Init (n);

    while (n <= b) {

        p = n;
        for (i = MAX_DIGITS; i > dmax; i--) {
            p *= digits[i];
            if (p > b) goto next;
        }

        if ((p >= a) && (p <= b)) {
            printf ("%d\n", n);
            count++;
        }

next:
        n = Increment (n);
    }
    return count;
}

int main ()
{
    int t;

    scanf ("%d", &t);

    while (t--) {
        scanf ("%d %d", &a, &b);

        printf ("%d\n", CountSelfProduct (a, b));
    }
}

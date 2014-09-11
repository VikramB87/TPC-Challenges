#include <stdio.h>

#define MAX_CANDY_TYPE 100
#define MAX_CANDY      500
#define MAX_CALORIE    200
#define MAX_SUM        MAX_CANDY_TYPE*MAX_CANDY*MAX_CALORIE

int k[MAX_CANDY_TYPE];
int c[MAX_CANDY_TYPE];
unsigned char s[MAX_SUM];

int main ()
{
    int n, i, j, last = 0, t, r;
    int sum = 0;
    int x;

    scanf ("%d", &n);
    for (i = 0; i < n; i++) {
        scanf ("%d %d", &k[i], &c[i]);
        sum += k[i]*c[i];
    }
    x = sum/2;

    s[0] = 1;
    for (i = 0; i < n; i++) {
        for (t = 0; t <= last; t++) {
            if (s[t]) {
                r = t;
                for (j = 1; j <= k[i]; j++) {
                    r += c[i];
                    if (r > x) break;
                    s[r] = 1;
                }
            }
        }
        last += (k[i]*c[i]);
    }

    while(!s[x]) x--;
    printf ("%ld\n", sum-2*x);

    return 0;
}

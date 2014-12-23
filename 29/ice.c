#include <stdio.h>
#include <string.h>

#define MAX_N 10000
int ci[MAX_N];


int find2 (int val, int n, int from)
{
        int i;

    for (i = from; i < n; i++) {
        if (ci[i] == val) return i;
    }
    return -1;
}

int main()
{
        int num_tests;
        int m, n, i;
        int from;

    scanf ("%d", &num_tests);
    while (num_tests--) {
        scanf ("%d", &m);
        scanf ("%d", &n);

        for (i = 0; i < n; i++) {
            scanf ("%d", &ci[i]);
        }

        for (i = 0; i < n; i++) {
            if (ci[i] < m-1) {
                from = i;
                while ((from = find2 (m-ci[i], n, from+1)) != -1) {
                    printf ("%d %d\n", i+1, from+1);
                }
            }
        }
    }

    return 0;
}


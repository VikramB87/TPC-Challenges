/**
 * @file slice.cpp
 *
 * @brief Defines the non-inline functions of .
 */

#include <stdio.h>
int gA[2560000];

int max_slice(int A[], int N)
{
    int v1, v2;
    int /*begmax, */ beg, max = 0, i, prev, beg2;
    int hasv2 = 0;

    if (N < 3) return N;

    v1   = A[0];
    i    = 1;
    beg  = 0;
    beg2 = 0;
    prev = v1;

    while (i < N) {

        if ((A[i] == v1) || (hasv2 && (A[i] == v2))) {
        } else if (!hasv2) {
            v2 = A[i];
            hasv2 = 1;
        } else {
            // End of slice
            if ((i - beg) > max) {
                max = i-beg;
                //begmax = beg;
            }
            beg = beg2;
            v1 = prev;
            v2 = A[i];
        }

        if (A[i] != prev) {
            prev = A[i];
            beg2 = i;
        }

        i++;
    }

    if ((i - beg) > max) {
        max = i-beg;
        ///begmax = beg;
    }
//    printf ("%d\n", begmax);
    return max;
}

int main()
{
    int n;
    int c;
    int i;
    int *x;

    scanf("%d", &n);
    while (n) {
        scanf("%d", &c);
        x = gA;
        for (i = 0; i < c; i++) {
            scanf("%d", gA+i);
        }
        printf ("%d\n", max_slice(gA, c));
        n--;
    }
    return 0;
}

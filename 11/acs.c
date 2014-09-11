#include <stdio.h>

#define NROW 1234
#define NCOL 5678


typedef unsigned short UShort;

UShort row[NROW+1];
UShort rrow[NROW+1];
UShort col[NCOL+1];
UShort rcol[NCOL+1];

UShort Get (UShort a[], UShort idx)
{
    return a[idx] ? a[idx] : (a[idx] = idx);
}

void Swap (UShort a[], UShort ra[], UShort idx1, UShort idx2)
{
    int t1 = Get(a, idx1);
    int t2 = Get(a, idx2);

    a[idx1] = t2;
    a[idx2] = t1;

    ra[t2] = idx1;
    ra[t1] = idx2;
}

int main ()
{
    char cmd;
    UShort  x,y;
    unsigned val;

    while (scanf ("%c", &cmd) == 1) {
        switch (cmd) {
            case 'R':
                scanf ("%hu%hu", &x, &y);
                Swap (row, rrow, x, y);
                break;

            case 'C':
                scanf ("%hu%hu", &x, &y);
                Swap (col, rcol, x, y);
                break;

            case 'Q':
                scanf ("%hu%hu", &x, &y);
                printf ("%u\n", (((unsigned)Get(row, x) - 1) * NCOL) + Get (col, y));
                break;

            case 'W':
                scanf ("%u", &val);
                printf ("%hu ", Get(rrow, ((val-1) / NCOL) + 1));
                printf ("%hu\n", Get(rcol, ((val-1) % NCOL)+1));
                break;

            default:
                break;
        }
    }
    return 0;
}






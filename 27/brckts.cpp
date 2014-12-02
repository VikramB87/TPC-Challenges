#include <cstdio>
#include <algorithm>

struct tNode {
    int min;
    int sum;
};

const unsigned MAX_LEN = 30000;
char str[MAX_LEN+1];
int   slen;
tNode segtree[65535];

#define LC(n) (((n) << 1) + 1)
#define RC(n) (((n) << 1) + 2)
#define MID(l, r) (((l) + (r)) >> 1)

void PrintSegTree (int start, int end, int idx)
{
    printf ("%d : (%d, %d)\n", idx, segtree[idx].sum, segtree[idx].min);
    if (start != end) {
        int mid = MID(start, end);
        PrintSegTree (start, mid, LC(idx));
        PrintSegTree (mid+1, end, RC(idx));
    }
}

void ConstructSegTree (int start, int end, int idx)
{
        int mid;
        int l = LC(idx);
        int r = RC(idx);

    if (start == end) {
        segtree[idx].sum = segtree[idx].min = str[start] == '(' ? 1 : -1;
        return;
    }

    mid = MID(start, end);
    ConstructSegTree (start, mid, l);
    ConstructSegTree (mid+1, end, r);

    segtree[idx].sum = segtree[l].sum + segtree[r].sum;
    segtree[idx].min = std::min (segtree[l].min, segtree[l].sum + segtree[r].min);
}

void UpdateSegTree (int start, int end, int i, int idx)
{
        int mid;
        int l = LC(idx);
        int r = RC(idx);

    if (i < start || i > end) return;

    if (start == end) {
        segtree[idx].sum = segtree[idx].min = str[start] == '(' ? 1 : -1;
        return;
    }

    mid = MID(start, end);
    UpdateSegTree (start, mid, i, l);
    UpdateSegTree (mid+1, end, i, r);

    segtree[idx].sum = segtree[l].sum + segtree[r].sum;
    segtree[idx].min = std::min (segtree[l].min, segtree[l].sum + segtree[r].min);
}

int main()
{
        int m, c, tc = 0;

    while (1) {
        scanf ("%d", &slen);
        if (slen == 0) break;
        scanf ("%s", str);
        scanf ("%d", &m);

        printf ("TEST %d\n", ++tc);
        ConstructSegTree (0, slen-1, 0);
           //PrintSegTree (0, slen-1, 0);
        while (m-- > 0) {
            scanf ("%d", &c);

            if (c > 0) {
                c--;
                str[c] = (str[c] == ')') ? '(' : ')';
                UpdateSegTree (0, slen-1, c, 0);
                //PrintSegTree (0, slen-1, 0);
            } else {
                if (segtree[0].min == 0 && segtree[0].sum == 0) printf ("YES\n");
                else printf ("NO\n");
            }
        }
    }
    return 0;
}

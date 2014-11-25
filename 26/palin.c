#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 1000001

char number[MAX_LENGTH];

void CopyReverse (int l, int r)
{
    while (l >= 0) {
        number[r] = number[l];
        l--;
        r++;
    }
}

int IncrementFrom (int mid, int len)
{
    while (mid >= 0) {
        if (number[mid] < '9') {
            ++number[mid];
            return 0;
        }
        number[mid] = '0';
        mid--;
    }
    number[len+1] = 0;
    number[len] = '1';
    while (len-- > 0) {
        number[len] = '0';
    }
    number[0] = '1';
    return 1;
}

void NextPalindrome ()
{
    int len = strlen (number);
    int mid = len/2;
    int l, r;
    int cl, cr;
    int flag = 0;

    if (len == 1) {
        if (number[0] < '9') number[0]++;
        else {
            number[0] = number [1] = '1';
            number[2] = 0;
        }
        return;
    }

    if (len % 2) {
        // Odd length
        l   = mid-1;
        r   = mid+1;
        flag = 1;
    } else {
        // Even length
        l = mid-1;
        r = mid;
    }

    cl = l, cr = r;
    while (cl >= 0) {
        if (number[cr] < number[cl]) break;
        cr++;
        cl--;
    }
    if (cl < 0) {
        if (flag) {
            flag = IncrementFrom (mid, len);
        } else {
            flag = IncrementFrom (l, len);
        }
        if (!flag) CopyReverse (l, r);
    } else {
        CopyReverse (l, r);
    }
}

int main ()
{
    int t, k;

    scanf ("%d", &t);
    while (t--) {
        scanf ("%s", number);

        NextPalindrome ();
        printf ("%s\n", number);
    }
    return 0;
}




#include <stdio.h>
#include <assert.h>
#include <malloc.h>

typedef enum {
    SINGLE,
    ENGAGED,
    MARRIED
} MaritalStatus;

typedef struct {
    MaritalStatus status;
    int           person;   // If engaged or married, to which person
} Status;

// Determines who is the most preferred partner for person p. The most preferred
// partner is the highest rated partner who is still available.
int most_preferred_girl (int **pref_array, Status *status_array, int n, int p)
{
        int i;
        int o;  // The other person

    // We won't be checking for married people - that's just wrong! :P
    assert (status_array[p].status != MARRIED);

    // Start with the most-preferred person not yet proposed to
    if (status_array[p].status == SINGLE) i = 0;
    else {
        int j;
        for (j = 0; j < n; j++) if (status_array[p].person == pref_array[p][j]) break;
        i = j+1;
    }
    assert (i < n);

    for (; i < n; i++) {
        o = pref_array[p][i];
        // If that person is available...
        if (status_array[o].status != MARRIED) return o;
    }

    // Everyone finds someone!
    assert(false);
    return 0;
}

int most_preferred_boy (int **pref_array, Status *status_array, int n, int p)
{
        int i;
        int o;  // The other person

    // We won't be checking for married people - that's just wrong! :P
    assert (status_array[p].status != MARRIED);

    for (i = 0; i < n; i++) {
        o = pref_array[p][i];
        // If that person is available...
        if (status_array[o].status != MARRIED) return o;
    }

    // Everyone finds someone!
    assert(false);
    return 0;
}

// Uses a multi-pass algorithm. In each pass, each boy 'proposes' to his most-preferred
// partner. The most-preferred partner is defines as the girl most-preferred girl who
// is not yet married. If the boy is the most-preferred for the girl (using the same definition
// of most-preferred), they are married, else the two are engaged. If another boy proposes to
// an engaged girl and the boy is the highest-preferred, the engagment is broken and the girl
// girl marries the other boy.
int* stable_marriage (int **pref_array, int n)
{
        int  b;
        int  b1;
        int  g;
        bool done = false;
        Status *status = (Status*) calloc (2*n * sizeof (Status), 1);
        int *pairs = (int*) malloc (n*sizeof(int));

    // Lets ensure everyone gets married, no matter how long it takes!
    while (!done) {
        done = true;

        // Start by pairing the boys
        for (b = 0; b < n; b++) {
            /// This one is done!
            if (status[b].status == MARRIED) continue;

            // Someone's still left
            done = false;

            // Who's the most preferred girl for this guy now?
            g = most_preferred_girl (pref_array, status, n, b);
            // And who's the most preferrd guy for that girl?
            b1 = most_preferred_boy (pref_array, status, n, g);

            // Perfect match - marry them!
            if (b == b1) {
                // Make their existing partners single
                if (status[b].status == ENGAGED) {
                    status[status[b].person].status = SINGLE;
                }
                if (status[g].status == ENGAGED) {
                    status[status[g].person].status = SINGLE;
                }

                status[b].status = MARRIED;
                status[b].person = g;
                status[g].status = MARRIED;
                status[g].person = b;
                pairs[b] = g;
            } else if (status[g].status == SINGLE){
                // The two are engaged, to be married if no one better comes along
                status[b].status = ENGAGED;
                status[b].person = g;
                status[g].status = ENGAGED;
                status[g].person = b;
            }
        }
    }

    free (status);
    return pairs;
}

void Test1 ()
{
    const int n = 2;
    int a1[] = {2,3}, a2[] = {2,3}, a3[] = {0,1}, a4[] = {0,1};
    int *pref_array[2*n] = {a1,a2,a3,a4};
    int *pairs;

    pairs = stable_marriage (pref_array, n);

    for (int i = 0; i < n; i++) printf ("%d <-> %d\n", i, pairs[i]);
    free(pairs);
}

void Test2 ()
{
    const int n = 3;
    int a1[] = {4,3,5}, a2[] = {3,5,4}, a3[] = {3,5,4}, a4[] = {0,1,2}, a5[] = {1,0,2}, a6[] = {1,2,0};
    int *pref_array[2*n] = {a1,a2,a3,a4,a5,a6};
    int *pairs;

    pairs = stable_marriage (pref_array, n);

    for (int i = 0; i < n; i++) printf ("%d <-> %d\n", i, pairs[i]);
    free(pairs);
}

void Test3 ()
{
    const int n = 4;
    int a1[] = {7,5,6,4}, a2[] = {5,4,6,7}, a3[] = {4,5,6,7}, a4[] = {4,5,6,7},
        a5[] = {0,1,2,3},a6[] = {0,1,2,3},a7[] = {0,1,2,3},a8[] = {0,1,2,3};
    int *pref_array[2*n] = {a1,a2,a3,a4,a5,a6,a7,a8};
    int *pairs;

    pairs = stable_marriage (pref_array, n);

    for (int i = 0; i < n; i++) printf ("%d <-> %d\n", i, pairs[i]);
    free(pairs);
}

int main ()
{

    printf ("Test Case 1\n");
    Test1 ();

    printf ("Test Case 2\n");
    Test2 ();

    printf ("Test Case 3\n");
    Test3 ();
    return 0;
}

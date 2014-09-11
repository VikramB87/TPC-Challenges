#include <stdio.h>
#include <assert.h>
#include <memory.h>
#include <string.h>
#include <malloc.h>

#define ARRAY_SIZE(x) (sizeof(x)/sizeof(x[0]))

#define COPY_INT_ARRAY(dest, src, num_elems) memcpy(dest, src, (num_elems)*sizeof(int))
#define MOVE_INT_ARRAY(dest, src, num_elems) memmove(dest, src, (num_elems)*sizeof(int))

void RotateTestSuite (void);
void PrintArray(int arr[], int size);

void ShiftArrayRight (int arr[], int size, int steps)
{
        bool less_than_half;
        int  n;
        int *tempbuf;

    if (steps > (size/2)) {
        less_than_half = true;
        n = steps;
    } else {
        less_than_half = false;
        n = size-steps;
    }

    tempbuf = (int*) malloc (n*sizeof (int));

    if (less_than_half) {
        COPY_INT_ARRAY (tempbuf, arr+(size-steps), n);
        MOVE_INT_ARRAY (arr+steps, arr, size-steps);
        COPY_INT_ARRAY (arr, tempbuf, n);
    } else {
        COPY_INT_ARRAY (tempbuf, arr, n);
        MOVE_INT_ARRAY (arr, arr+(size-steps), steps);
        COPY_INT_ARRAY (arr+steps, tempbuf, n);
    }

    free(tempbuf);
}

// Shifting an array of size X right by N steps = shifting the array left by X-N steps
// Hence we only handle shift right.
// Shifting left is accomplished by finding the split point and moving it the array to 
// the beginning from the split point. We use some additional memory for this. The amount
// of memory used is optimized by using lesser of the memory needed from the split point.
// Inputs:
//  arr - The array to be rotated
//  size - Size of the array
//  steps - Number of steps to rotate. A positive value indicates right rotation, negative
//          value indicates left rotation.
void RotateArray (int arr[], int size, int steps)
{
        int  n;

    if ((steps == 0) || ((steps = (steps % size)) == 0)) return;

    // Convert left shift to right shift
    if (steps < 0) {
        steps = size+steps;
    }

    ShiftArrayRight (arr, size, steps);
}

/* - - - - - - - - - - Algorithm 2 : Using no additional memory. - - - - - - - - - - */

void Swap (int *x, int *y)
{
        int t;
    t  = *x;
    *x = *y;
    *y = t;
}

void MoveArrayElemLeft (int arr[], int from, int to)
{
    while (from > to) {
        Swap (arr + (from-1), arr+from);
        from--;
    }
}

void MoveArrayElemRight (int arr[], int from, int to)
{
    while (from < to) {
        Swap (arr + from, arr+from+1);
        from++;
    }
}

void ShiftArrayRight_Swap (int arr[], int size, int steps)
{
        int from, to;

    if (steps < (size/2)) {
        from = size-steps;
        to   = 0;
        while (from < size) {
            MoveArrayElemLeft (arr, from, to);
            from++; to++;
        }

    } else {
        from = size-steps-1;
        to   = size-1;
        while (from >= 0) {
            MoveArrayElemRight (arr, from, to);
            from--; to--;
        }
    }

}

void RotateArray_Swap (int arr[], int size, int steps)
{
    if ((steps == 0) || ((steps = (steps % size)) == 0)) return;

    // Convert left shift to right shift
    if (steps < 0) {
        steps = size+steps;
    }

    ShiftArrayRight_Swap (arr, size, steps);
}

// --- Driver Routine ----
int main ()
{
        int arr[] = {1,2,3,4};

    RotateArray (arr, 4, -1);
    PrintArray (arr, 4);
    RotateArray_Swap (arr, 4, -3);
    PrintArray (arr, 4);
    RotateArray (arr, 4, 2);
    PrintArray (arr, 4);
    RotateArray_Swap (arr, 4, 2);
    PrintArray (arr, 4);

    RotateTestSuite ();

    return 0;
}

void RotateTest_1(void);
void RotateTest_2(void);
void RotateTest_3(void);

void RotateTestSuite (void)
{
    RotateTest_1();
    RotateTest_2();
    RotateTest_3();
}

// For testing
bool CompareArrays (int arr1[], int arr2[], int size)
{
        int i;
    for (i = 0; i < size; i++) if (arr1[i] != arr2[i]) return false;
    return true;
}

void PrintArray(int arr[], int size)
{
        int i;
    for (i = 0; i < size; i++) printf("%d ", arr[i]);
    printf ("\n");
}

// Test rotation which results in identity
void RotateTest_1(void)
{
    int INPUT_ARRAY[] = {1,2,3,4};
    int input[] = {1,2,3,4};
    int output[] = {1,2,3,4};

    memcpy (input, INPUT_ARRAY, sizeof(INPUT_ARRAY));
    RotateArray (input, ARRAY_SIZE(input), 0);
    assert(CompareArrays (input, output, ARRAY_SIZE(INPUT_ARRAY)));

    memcpy (input, INPUT_ARRAY, sizeof(INPUT_ARRAY));
    RotateArray (input, ARRAY_SIZE(input), ARRAY_SIZE(input));
    assert(CompareArrays (input, output, ARRAY_SIZE(INPUT_ARRAY)));

    memcpy (input, INPUT_ARRAY, sizeof(INPUT_ARRAY));
    RotateArray (input, ARRAY_SIZE(input), -ARRAY_SIZE(input));
    assert(CompareArrays (input, output, ARRAY_SIZE(INPUT_ARRAY)));

    memcpy (input, INPUT_ARRAY, sizeof(INPUT_ARRAY));
    RotateArray (input, ARRAY_SIZE(input), 2*ARRAY_SIZE(input));
    assert(CompareArrays (input, output, ARRAY_SIZE(INPUT_ARRAY)));

    memcpy (input, INPUT_ARRAY, sizeof(INPUT_ARRAY));
    RotateArray (input, ARRAY_SIZE(input), -8*ARRAY_SIZE(input));
    assert(CompareArrays (input, output, ARRAY_SIZE(INPUT_ARRAY)));

    memcpy (input, INPUT_ARRAY, sizeof(INPUT_ARRAY));
    RotateArray_Swap (input, ARRAY_SIZE(input), 0);
    assert(CompareArrays (input, output, ARRAY_SIZE(INPUT_ARRAY)));

    memcpy (input, INPUT_ARRAY, sizeof(INPUT_ARRAY));
    RotateArray_Swap (input, ARRAY_SIZE(input), ARRAY_SIZE(input));
    assert(CompareArrays (input, output, ARRAY_SIZE(INPUT_ARRAY)));

    memcpy (input, INPUT_ARRAY, sizeof(INPUT_ARRAY));
    RotateArray_Swap (input, ARRAY_SIZE(input), -ARRAY_SIZE(input));
    assert(CompareArrays (input, output, ARRAY_SIZE(INPUT_ARRAY)));

    memcpy (input, INPUT_ARRAY, sizeof(INPUT_ARRAY));
    RotateArray_Swap (input, ARRAY_SIZE(input), 2*ARRAY_SIZE(input));
    assert(CompareArrays (input, output, ARRAY_SIZE(INPUT_ARRAY)));

    memcpy (input, INPUT_ARRAY, sizeof(INPUT_ARRAY));
    RotateArray_Swap (input, ARRAY_SIZE(input), -8*ARRAY_SIZE(input));
    assert(CompareArrays (input, output, ARRAY_SIZE(INPUT_ARRAY)));
}

// Right rotations
void RotateTest_2 (void)
{
    const int ARRAY_SIZE = 9;
    int INPUT_ARRAY[ARRAY_SIZE] = {1,2,3,4,5,6,7,8,9};
    int input[ARRAY_SIZE];

    // 'Less than half'
    memcpy (input, INPUT_ARRAY, sizeof(INPUT_ARRAY));
    RotateArray (input, ARRAY_SIZE, 1);
    int output1[] = {9,1,2,3,4,5,6,7,8};
    assert (CompareArrays (input, output1, ARRAY_SIZE));

    memcpy (input, INPUT_ARRAY, sizeof(INPUT_ARRAY));
    RotateArray_Swap (input, ARRAY_SIZE, 1);
    assert (CompareArrays (input, output1, ARRAY_SIZE));

    // ----
    memcpy (input, INPUT_ARRAY, sizeof(INPUT_ARRAY));
    RotateArray (input, ARRAY_SIZE, 3);
    int output2[] = {7,8,9,1,2,3,4,5,6};
    assert (CompareArrays (input, output2, ARRAY_SIZE));

    memcpy (input, INPUT_ARRAY, sizeof(INPUT_ARRAY));
    RotateArray_Swap (input, ARRAY_SIZE, 3);
    assert (CompareArrays (input, output2, ARRAY_SIZE));

    // ----
    // 'More than half'
    memcpy (input, INPUT_ARRAY, sizeof(INPUT_ARRAY));
    RotateArray (input, ARRAY_SIZE, 5);
    int output3[] = {5,6,7,8,9,1,2,3,4};
    assert (CompareArrays (input, output3, ARRAY_SIZE));

    memcpy (input, INPUT_ARRAY, sizeof(INPUT_ARRAY));
    RotateArray_Swap (input, ARRAY_SIZE, 5);
    assert (CompareArrays (input, output3, ARRAY_SIZE));

    // ----
    memcpy (input, INPUT_ARRAY, sizeof(INPUT_ARRAY));
    RotateArray (input, ARRAY_SIZE, 8);
    int output4[] = {2,3,4,5,6,7,8,9,1};
    assert (CompareArrays (input, output4, ARRAY_SIZE));

    memcpy (input, INPUT_ARRAY, sizeof(INPUT_ARRAY));
    RotateArray_Swap (input, ARRAY_SIZE, 8);
    assert (CompareArrays (input, output4, ARRAY_SIZE));

    // ----
    memcpy (input, INPUT_ARRAY, sizeof(INPUT_ARRAY));
    RotateArray (input, ARRAY_SIZE, 10);
    assert (CompareArrays (input, output1, ARRAY_SIZE));

    memcpy (input, INPUT_ARRAY, sizeof(INPUT_ARRAY));
    RotateArray_Swap (input, ARRAY_SIZE, 10);
    assert (CompareArrays (input, output1, ARRAY_SIZE));
}

// Left rotations
void RotateTest_3 (void)
{
    const int ARRAY_SIZE = 8;
    int INPUT_ARRAY[ARRAY_SIZE] = {1,2,3,4,5,6,7,8};
    int input[ARRAY_SIZE];

    memcpy (input, INPUT_ARRAY, sizeof(INPUT_ARRAY));
    RotateArray (input, ARRAY_SIZE, -2);
    int output1[] = {3,4,5,6,7,8,1,2};
    assert (CompareArrays (input, output1, ARRAY_SIZE));

    memcpy (input, INPUT_ARRAY, sizeof(INPUT_ARRAY));
    RotateArray (input, ARRAY_SIZE, -2);
    assert (CompareArrays (input, output1, ARRAY_SIZE));

    // ----
    memcpy (input, INPUT_ARRAY, sizeof(INPUT_ARRAY));
    RotateArray_Swap (input, ARRAY_SIZE, -4);
    int output2[] = {5,6,7,8,1,2,3,4};
    assert (CompareArrays (input, output2, ARRAY_SIZE));

    memcpy (input, INPUT_ARRAY, sizeof(INPUT_ARRAY));
    RotateArray_Swap (input, ARRAY_SIZE, -4);
    assert (CompareArrays (input, output2, ARRAY_SIZE));

    // ----
    memcpy (input, INPUT_ARRAY, sizeof(INPUT_ARRAY));
    RotateArray (input, ARRAY_SIZE, -5);
    int output3[] = {6,7,8,1,2,3,4,5};
    assert (CompareArrays (input, output3, ARRAY_SIZE));

    memcpy (input, INPUT_ARRAY, sizeof(INPUT_ARRAY));
    RotateArray_Swap (input, ARRAY_SIZE, -5);
    assert (CompareArrays (input, output3, ARRAY_SIZE));

    // ---
    memcpy (input, INPUT_ARRAY, sizeof(INPUT_ARRAY));
    RotateArray (input, ARRAY_SIZE, -7);
    int output4[] = {8,1,2,3,4,5,6,7};
    assert (CompareArrays (input, output4, ARRAY_SIZE));

    memcpy (input, INPUT_ARRAY, sizeof(INPUT_ARRAY));
    RotateArray_Swap (input, ARRAY_SIZE, -7);
    assert (CompareArrays (input, output4, ARRAY_SIZE));

    // ----
    memcpy (input, INPUT_ARRAY, sizeof(INPUT_ARRAY));
    RotateArray (input, ARRAY_SIZE, -10);
    assert (CompareArrays (input, output1, ARRAY_SIZE));

    memcpy (input, INPUT_ARRAY, sizeof(INPUT_ARRAY));
    RotateArray_Swap (input, ARRAY_SIZE, -10);
    assert (CompareArrays (input, output1, ARRAY_SIZE));

    // ---
    memcpy (input, INPUT_ARRAY, sizeof(INPUT_ARRAY));
    RotateArray (input, ARRAY_SIZE, -14);
    int output5[] = {7,8,1,2,3,4,5,6};
    assert (CompareArrays (input, output5, ARRAY_SIZE));

    memcpy (input, INPUT_ARRAY, sizeof(INPUT_ARRAY));
    RotateArray_Swap (input, ARRAY_SIZE, -14);
    assert (CompareArrays (input, output5, ARRAY_SIZE));
}

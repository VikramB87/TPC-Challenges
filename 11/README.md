TPC-Challenge11
===============

Solution for "A Concrete Simulation"

You are given a matrix M of type 1234x5678. It is initially filled with integers 1...1234x5678 in row major order. Your task is to process a list of commands manipulating M. There are 4 types of commands:
"R x y" swap the x-th and y-th row of M ;
"C x y" swap the x-th and y-th column of M ;
"Q x y" write out M(x,y) ;
"W z" write out x and y where z=M(x,y).
Input

A list of valid commands. Input terminated by EOF.
Output

For each "Q x y" write out one line with the current value of M(x,y), for each "W z" write out one line with the value of x and y ( interpreted as above ) separated by a space.

Input:
R 1 2
Q 1 1
Q 2 1
W 1
W 5679
C 1 2
Q 1 1
Q 2 1
W 1
W 5679

Output:
5679
1
2 1
1 1
5680
2
2 2
1 2



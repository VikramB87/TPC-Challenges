Solution for TPC Problem 1 in Scala
Look at src/Test.scala for the solution.
Uses a simple recursive algorithm:
    Assume we have to make change for an amount 'A' with coins C1,C2 and C3.
    The solution will of two kinds: Those that include coin C1 and those that don't.
Hence we can simplify the problem. The number of ways to make change is equal to:
    - The number of ways to make change for 'A' using only C1 and C2, plus
    - The number of ways to make change for 'A' - C1 using C1,C2 and C3.
The base case is when the A is 0 and we have exactly 1 way to make the change.

TPC-Challenge10
===============

Solution for "The Black Rider" problem
Indeed, the Black Riders are in the Shire, and they are looking for the One Ring. There are N hobbits out in their fields, but when they hear the Riders approaching, or feel the fear cast by their presence, they immediately wish to run and hide in M holes located nearby.

 

Now, each hole has space for just 1 hobbit; however, once a hobbit reaches a hole, he is able to make room for one more hobbit by digging away at the earth. The time required to make enough space for a second hobbit is C units. Also, each hole CANNOT hold more than 2 hobbits, even after digging. Also note that a hobbit can begin making space for the next hobbit only after he reaches the hole.

 

You are given the time required to travel from each hobbit's current location to each hole. Find the minimum amount of time it will take before at least K of the hobbits are hiding safely.

 

Input (STDIN):

 

The first line contains T, the number of test cases.

The first line of each test case contains 4 integers - N (no of hobbits), M (no of holes), K (minimum number of hobbits to hide) and C (time taken to expand a hole).

The next N lines contain M integers each, denoting the time taken for each hobbit to each hole.

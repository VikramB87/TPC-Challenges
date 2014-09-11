Solution to the 'Longest Path in a graph' problem. A 'path' is considered to be 
We start with a depth-first traversal on any node, and repeatedly do depth-first traversal on all nodes unvisited in the previous iterations. In each traversal we track the longest path.

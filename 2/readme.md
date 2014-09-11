Solution for TPC Challenge 2. Array rotataion.
Two solutions are implemented:
1. Using at most n/2 additional memory, where n is the array size.
	This solution uses a simple array shifting logic, runs in O(s) time, where s is the number of rotation steps modulo the array size.
	Performance is independent of number of steps of rotation.
2. Using a constant amount of additional memory (4 bytes), using repeated swapping of elements.
	Algorithmic complexity: O(s*s), where is s is the number of steps of rotation modulo the array size.

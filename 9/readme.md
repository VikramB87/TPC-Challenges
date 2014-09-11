Wildcard Pattern Matching Algorithm
- Each '\*' breaks down the pattern into a sub-pattern..
- Each time a '\*' is encountered, the sub-pattern is searched in the text from the end, and if found, pattern match is done recursively on rest of the text and rest of the pattern.
- If the recursive match failed, the second last match is used and so on.

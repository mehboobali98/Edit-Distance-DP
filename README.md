# Edit Distance Dynamic Programming

## Problem Statement

In Edit Distance problem, we need to find the minimum number of edits or operations required to make two strings equal. The avaiable operations are:

- Insertion
- Deletion
- Replace

The solution to this problem is not unique. i.e. multiple optimal solutions are possible. Hence, we need to find count of all possible unique optimal solutions. For example:

𝑠 = TREE and 𝑡 = TOR, and four optimal solutions
are possible, each having cost 3.

## Approach

The algorithm to solve the problem has been implemented in three ways:

- recursive
- top-down
- bottom-up (Dynamic Programming)

## Time Complexity

The time complexity of the dynamic programming solution is: O(N^2)

# Directory Structure

📦Edit-Distance-Dynamic-Programming
┣ 📜main.cpp
┗ 📜README.md

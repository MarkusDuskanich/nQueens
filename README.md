# nQueens
solving the nQueens problem in np-time

## introduction
Brute force or even more optimised solutions like backtracking struggle to solve the problem in reasonable time as the size of the board grows, because of their exponential nature. The algoritm in this repository solves the problem in np-time, producing solutions for bords of 10000000x10000000 in less than a minute.

## basic idea of the algorithm
First, for a board of size n times n, n queens are distributed randomly but in a favourable way, in which a maximum of one queen per row and column is allowed. Now only the diagonals need to be fixed.
Secondly, a tuple of queens is formed, and they are swapped along the y axis, if this action increases the number of conflicts along the diagonal, the swap is reverted. The conflicts for each diagonal are tracked in an array.
Finally, the board is either solved after a certain number of swaps or if all possible tuples have been formed and swapping could not clear all conflicts, all queens are removed from the board and the algorithm starts from the beginning.

## np-nature of the algorithm
For a bord of size n times n, there are n nCr 2 tuples, and the calculations for the swap including the operation needed to verify if the board has been solved are constant, independent of board size. Larger boards are solved long before all tuples have been created, but there is no guarantee, which explains the nondeterministic part of the algorithm. 

Copyright Razvan-Constantin Rus 312CAa 2022-2023
## Description
This program implements some of the matrix functions featured in 
GNU Octave.

## Data Structures 
    All data structures are dynamically allocated 
1. An array of matrices in which the matrices will be saved. The program doubles the allocated memory the array of matrices 
every time it runs out.

1. Two arrays which store the size of each matrix.
    
all data structures are dynamically allocated 

## Functionality
Character to be read for each operation
1. `L` - Load a matrix scanned from STDIN, together with its number of lines 
and columns.

2. `D` - Followed by a number `i`, prints the size of the matrix on the `i`-th 
position.

3. `P` - Followed by a number `i`, prints the `i`-th matrix.

4. `C` - Followed by `i`, crops the `i`-th matrix. The new number of columns and lines is read, immediately followed by the indices of the columns and lines kept.

        Example:
            C 0
            2
            3 1
            3
            6 3 4

5. `M` - Followed by two numbers `i` and `j`, multiply the two matrices

6. `O` - sorts the matrix array by sum of the each matrix' elements.

7. `T` - Followed by `i`, transposes the `i`-th matrix. 

8. `R` - Followed by `i` and `pow`, raises the `i`-th matrix to the `pow`-th power

9. `F` - Followed by `i`, deletes the `i`-th matrix from the matrix array. All
matrices with a higher index number are then shifted by one position

10.   `S` - Matrix Product using the Strassen Algorithm. Works only
for square matrices with a size equale to a perfect square

11.   `Q` - Frees all memory used by the program and then exits the program.

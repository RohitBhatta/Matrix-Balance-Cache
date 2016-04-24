#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include "matrix.h"

// Return the balance of matrix (in matrix.h) 
// Make it run as fast as possible
// Feel free to move it to sstuff.S
int balance() {
    int count = 0;
    /*for (int r = 0; r < N; r++) {
        for (int c = r + 1; c < N; c++) {
            if (matrix[r][c] == matrix[c][r]) {
                count++;
            }
        }
    }*/

    int bound = N - (N % 32);

    //Diagonal
    for (int r = 0; r < bound; r++) {
        for (int c = r + 1; c < 32 * (r/32 + 1); c++) {
            if (matrix[r][c] == matrix[c][r]) {
                count++;
            }
        }
    }

    //Right Margin
    for (int r = 0; r < bound; r++) {
        for (int c = bound; c < N; c++) {
            if (matrix[r][c] == matrix[c][r]) {
                count++;
            }
        }
    }

    //Bottom Margin
    for (int r = bound; r < N; r++) {
        for (int c = r + 1; c < N; c++) {
            if (matrix[r][c] == matrix[c][r]) {
                count++;
            }
        }
    }

    //Other
    for (int r = 0; r < bound; r += 32) {
        for (int c = r + 32; c < bound; c += 32) {
            for (int a = r; a < r + 32; a++) {
                for (int b = c; b < c + 32; b++) {
                    if (matrix[a][b] == matrix[b][a]) {
                        count++;
                    }
                }
            }
        }
    }

    return count;
}

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX_SIZE 101
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))

#define COMPARE(x, y) ((x) < (y) ? -1 : ((x) == (y)) ? 0 : 1)

int binsearch (int list [], int searchnum, int left, int right) {
/* Search list [0] <= list [1] <= ... <= list [n-1] (ordered list) for searchnum
 * by binary search. Return its position if found. Otherwise return -1 */
    int middle;
    while (left <= right) {
        middle = (left + right) / 2;
        switch (COMPARE (list [middle], searchnum)) {
            case -1: left = middle + 1; break;
            case  0: return middle;
            case  1: right = middle - 1;
        }
    }
    return -1;
}

void sort(int[], int); /* selection sort */
int main (void) {
    int i, n;
    int list[MAX_SIZE];
    printf ("Enter the number of numbers to generate¡G");
    scanf (" %d", &n);
    if (n < 1 || n > MAX_SIZE) {
        fprintf(stderr, " Improper value of n\n");
        exit (1);
    }
    for (i = 0; i < n; i++) {
        list [i] = (n-i-1) * 10;
        printf(" %d  ",list[i]);
    }
    sort(list, n);
    printf("\n Sorted array¡G\n  ");
    for (i = 0; i < n; i++) /* print out sorted  numbers */
        printf(" %d ", list[i]);
    printf("\n");

    int find, pos;
    printf("\nInput a number you want to find: ");
    scanf("%d", &find);
    pos = binsearch(list, find, 0, n - 1);

    if (pos != -1) {
        printf("\nfind %d at %d.\n", find, pos);
    }
    else {
        printf("\n%d is not found.\n", find);
    }

    return 0;
}

void sort(int list[], int n) {
    int i, j, min, temp;
    for (i = 0; i < n - 1; i++) {
        min = i;
        for (j = i + 1; j < n; j++)
            if (list[j] < list[min])
                min = j;
        SWAP(list[i], list[min], temp);
    }
}


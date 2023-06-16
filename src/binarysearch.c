/*
 * binarysearch.c
 *
 *  Created on: 02/04/2023
 *      Author: Tiago C. Teixeira
 * Description: Implements a generic binary search in C for a generic sorted array.
 *
 * Binary Search is a searching algorithm used in a sorted array by repeatedly
 * dividing the search interval in half. The idea of binary search is to use
 * the information that the array is sorted and reduce the time complexity to
 * O(Log n).
 *
 * Binary Search Algorithm: The basic steps to perform Binary Search are:
 *
 *  1- Sort the array in ascending order.
 *  2- Set the low index to the first element of the array and the high index to the
 *     last element.
 *  3- Set the middle index to the average of the low and high indices.
 *  4- If the element at the middle index is the target element, return the middle index.
 *  5- If the target element is less than the element at the middle index, set the
 *     high index to the middle index – 1.
 *  6- If the target element is greater than the element at the middle index, set
 *     the low index to the middle index + 1.
 *  7- Repeat steps 3-6 until the element is found or it is clear that the element
 *     is not present in the array.
 *
 * Time Complexity: O(log n)
 * Auxiliary Space: O(log n)
 *
 * Advantages of Binary Search:
 *
 *   Binary search is faster than linear search, especially for large arrays.
 *   As the size of the array increases, the time it takes to perform a linear
 *   search increases linearly, while the time it takes to perform a binary
 *   search increases logarithmically.
 *   Binary search is more efficient than other searching algorithms that have
 *   a similar time complexity, such as interpolation search or exponential
 *   search.
 *   Binary search is relatively simple to implement and easy to understand,
 *   making it a good choice for many applications.
 *   Binary search can be used on both sorted arrays and sorted linked lists,
 *   making it a flexible algorithm.
 *   Binary search is well-suited for searching large datasets that are stored
 *   in external memory, such as on a hard drive or in the cloud.
 *   Binary search can be used as a building block for more complex algorithms,
 *   such as those used in computer graphics and machine learning.
 *
 * Drawbacks of Binary Search:
 *
 *   We require the array to be sorted. If the array is not sorted, we must
 *   first sort it before performing the search. This adds an additional
 *   O(n log n) time complexity for the sorting step, which can make binary
 *   search less efficient for very small arrays.
 *   Binary search requires that the array being searched be stored in
 *   contiguous memory locations. This can be a problem if the array is too
 *   large to fit in memory, or if the array is stored on external memory such
 *   as a hard drive or in the cloud.
 *   Binary search requires that the elements of the array be comparable,
 *   meaning that they must be able to be ordered. This can be a problem if
 *   the elements of the array are not naturally ordered, or if the ordering
 *   is not well-defined.
 *   Binary search can be less efficient than other algorithms, such as hash
 *   tables, for searching very large datasets that do not fit in memory.
 *
 * Applications of Binary search:
 *
 *   Searching in machine learning: Binary search can be used as a building block
 *   for more complex algorithms used in machine learning, such as algorithms for
 *   training neural networks or finding the optimal hyperparameters for a model.
 *   Commonly used in Competitive Programming.
 *
 *   Can be used for searching in computer graphics. Binary search can be used
 *   as a building block for more complex algorithms used in computer graphics,
 *   such as algorithms for ray tracing or texture mapping.*
 *   Can be used for searching a database. Binary search can be used to efficiently
 *   search a database of records, such as a customer database or a product
 *   catalog.
 *
 * When to use Binary Search:
 *
 *   When searching a large dataset as it has a time complexity of O(log n),
 *   which means that it is much faster than linear search.
 *   When the dataset is sorted.
 *   When data is stored in contiguous memory.
 *   Data does not have a complex structure or relationships.
 *
 * Summary:
 *
 *   Binary search is an efficient algorithm for finding an element within a sorted array.
 *   The time complexity of the binary search is O(log n).
 *   One of the main drawbacks of binary search is that the array must be sorted.
 *   Useful algorithm for building more complex algorithms in computer graphics
 *   and machine learning.
 *
 */

#include <stdio.h>

/* A recursive binary search function. It returns
 * location of x in given array arr[l..r] is present, otherwise -1.
 * comparefunc is a function that returns 0 if first arg equals second arg,
 * 1 if is greater than, -1 if is less than.
 *  */
int binarySearch(void* arr[], int l, int r, void* x, int (*comparefunc)(void* a, void* b))
{
    if (r >= l) {
        int mid = l + (r - l) / 2;		// (l+r)/2 can cause buffer overflow for integer type

        // If the element is present at the middle
        // itself
        if (comparefunc(arr[mid], x) == 0)
            return mid;

        // If element is smaller than mid, then
        // it can only be present in left subarray
        if (comparefunc(arr[mid], x) == 1)	// mid greater than x
            return binarySearch(arr, l, mid - 1, x, comparefunc);

        // Else the element can only be present
        // in right subarray
        return binarySearch(arr, mid + 1, r, x, comparefunc);
    }

    // We reach here when element is not
    // present in array
    return -1;
}




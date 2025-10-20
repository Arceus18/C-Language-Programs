#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Comparison function for qsort.
 * * This function is used by the C standard library's qsort to sort integers
 * in ascending order.
 * * @param a A pointer to the first element to compare.
 * @param b A pointer to the second element to compare.
 * @return An integer less than, equal to, or greater than zero if the first
 * argument is considered to be respectively less than, equal to, or
 * greater than the second.
 */
int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

/**
 * @brief Finds the length of the longest harmonious subsequence.
 * * A harmonious subsequence is a subsequence where the difference between its
 * maximum and minimum value is exactly 1. This function first sorts the array
 * and then uses a sliding window (two-pointer) approach to efficiently find
 * the longest such subsequence.
 * * @param nums A pointer to the integer array.
 * @param numsSize The number of elements in the array.
 * @return The length of the longest harmonious subsequence. Returns 0 if none is found.
 */
int findLHS(int* nums, int numsSize) {
    // A harmonious subsequence must have at least two elements.
    if (numsSize <= 1) {
        return 0;
    }

    // Step 1: Sort the array. This brings elements that could form a
    // harmonious subsequence next to each other.
    qsort(nums, numsSize, sizeof(int), compare);

    int maxLength = 0;
    int left = 0; // The left pointer of our sliding window.

    // Step 2: Iterate through the array with the right pointer.
    for (int right = 0; right < numsSize; right++) {
        // Step 3: Shrink the window from the left if the difference is too large.
        // The window [left, right] is invalid if nums[right] - nums[left] > 1.
        while (nums[right] - nums[left] > 1) {
            left++;
        }

        // Step 4: If the difference is exactly 1, we have a harmonious subsequence.
        // Check if its length is the new maximum.
        if (nums[right] - nums[left] == 1) {
            int currentLength = right - left + 1;
            if (currentLength > maxLength) {
                maxLength = currentLength;
            }
        }
    }

    return maxLength;
}

/**
 * @brief Main function to test the findLHS implementation.
 */
int main() {
    // Test Case 1: Standard example
    int nums1[] = {1, 3, 2, 2, 5, 2, 3, 7};
    int numsSize1 = sizeof(nums1) / sizeof(nums1[0]);
    int result1 = findLHS(nums1, numsSize1);
    printf("Test Case 1: Input = {1, 3, 2, 2, 5, 2, 3, 7}\n");
    printf("The length of the longest harmonious subsequence is: %d\n\n", result1); // Expected: 5

    // Test Case 2: Simple harmonious sequence
    int nums2[] = {1, 2, 3, 4};
    int numsSize2 = sizeof(nums2) / sizeof(nums2[0]);
    int result2 = findLHS(nums2, numsSize2);
    printf("Test Case 2: Input = {1, 2, 3, 4}\n");
    printf("The length of the longest harmonious subsequence is: %d\n\n", result2); // Expected: 2

    // Test Case 3: No harmonious subsequence
    int nums3[] = {1, 1, 1, 1};
    int numsSize3 = sizeof(nums3) / sizeof(nums3[0]);
    int result3 = findLHS(nums3, numsSize3);
    printf("Test Case 3: Input = {1, 1, 1, 1}\n");
    printf("The length of the longest harmonious subsequence is: %d\n\n", result3); // Expected: 0
    
    // Test Case 4: Empty array
    int nums4[] = {};
    int numsSize4 = sizeof(nums4) / sizeof(nums4[0]);
    int result4 = findLHS(nums4, numsSize4);
    printf("Test Case 4: Input = {}\n");
    printf("The length of the longest harmonious subsequence is: %d\n\n", result4); // Expected: 0

    return 0;
}

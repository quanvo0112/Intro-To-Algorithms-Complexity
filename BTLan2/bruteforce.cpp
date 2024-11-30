#include <iostream>
#include <math.h>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <cstdint>
#include <limits>

int64_t bruteForceMaxSubarray(const std::vector<int64_t>& arr) {
    if (arr.empty()) {
        return 0;
    }

    int64_t maxSum = std::numeric_limits<int64_t>::min();
    size_t n = arr.size();

    // Try all possible subarrays
    for (size_t start = 0; start < n; start++) {
        int64_t currentSum = 0;
        for (size_t end = start; end < n; end++) {
            currentSum += arr[end];
            maxSum = std::max(maxSum, currentSum);
        }
    }

    return maxSum;
}

int64_t bruteForceMaxSubarray2(const std::vector<int64_t>& arr, int64_t& count_assign, int64_t& count_compare) {
    count_assign = 0;
    count_compare = 0;

    if (arr.empty()) {
        return 0;
    }

    int64_t maxSum = std::numeric_limits<int64_t>::min();
    size_t n = arr.size();
    count_assign += 2; // maxSum and n assignments

    // Try all possible subarrays
    for (size_t start = 0; start < n; start++) {
        count_compare++; // Outer loop condition

        int64_t currentSum = 0;
        count_assign++; // currentSum initialization

        for (size_t end = start; end < n; end++) {
            count_compare++; // Inner loop condition

            currentSum += arr[end];
            count_assign++; // currentSum update

            count_compare++; // Comparison in max()
            maxSum = (currentSum > maxSum) ? currentSum : maxSum;
            count_assign++; // maxSum update
        }
    }

    return maxSum;
}
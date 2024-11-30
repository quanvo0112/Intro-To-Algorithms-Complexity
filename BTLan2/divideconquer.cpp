#include <iostream>
#include <math.h>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <cstdint>
#include <limits>

int64_t maxCrossingSum(const std::vector<int64_t>& arr, int64_t left, int64_t mid, int64_t right) {
    int64_t leftSum = std::numeric_limits<int64_t>::min();
    int64_t sum = 0;
    for (int64_t i = mid; i >= left; i--) {
        sum += arr[i];
        leftSum = std::max(leftSum, sum);
    }

    int64_t rightSum = std::numeric_limits<int64_t>::min();
    sum = 0;
    for (int64_t i = mid + 1; i <= right; i++) {
        sum += arr[i];
        rightSum = std::max(rightSum, sum);
    }

    return leftSum + rightSum;
}

int64_t divideAndConquerMaxSubarray(const std::vector<int64_t>& arr, int64_t left, int64_t right) {
    if (left == right) {
        return arr[left];
    }

    int64_t mid = (left + right) / 2;

    return std::max({
        divideAndConquerMaxSubarray(arr, left, mid),
        divideAndConquerMaxSubarray(arr, mid + 1, right),
        maxCrossingSum(arr, left, mid, right)
    });
}

int64_t maxSubarraySum(const std::vector<int64_t>& arr) {
    if (arr.empty()) return 0;
    return divideAndConquerMaxSubarray(arr, 0, arr.size() - 1);
}

int64_t maxCrossingSum2(const std::vector<int64_t>& arr, int64_t left, int64_t mid, int64_t right, 
                       int64_t& count_assign, int64_t& count_compare) {
    int64_t leftSum = std::numeric_limits<int64_t>::min();
    int64_t sum = 0;
    count_assign += 2; // leftSum and sum initialization

    for (int64_t i = mid; i >= left; i--) {
        count_compare++; // Loop condition
        sum += arr[i];
        count_assign++; // sum update
        
        count_compare++; // Comparison in max
        leftSum = (sum > leftSum) ? sum : leftSum;
        count_assign++; // leftSum update
    }

    int64_t rightSum = std::numeric_limits<int64_t>::min();
    sum = 0;
    count_assign += 2; // rightSum and sum reset

    for (int64_t i = mid + 1; i <= right; i++) {
        count_compare++; // Loop condition
        sum += arr[i];
        count_assign++; // sum update
        
        count_compare++; // Comparison in max
        rightSum = (sum > rightSum) ? sum : rightSum;
        count_assign++; // rightSum update
    }

    return leftSum + rightSum;
}

int64_t divideAndConquerMaxSubarray2(const std::vector<int64_t>& arr, int64_t left, int64_t right, 
                                   int64_t& count_assign, int64_t& count_compare) {
    count_compare++; // Base case comparison
    if (left == right) {
        return arr[left];
    }

    int64_t mid = (left + right) / 2;
    count_assign++; // mid assignment

    int64_t left_sum = divideAndConquerMaxSubarray2(arr, left, mid, count_assign, count_compare);
    int64_t right_sum = divideAndConquerMaxSubarray2(arr, mid + 1, right, count_assign, count_compare);
    int64_t cross_sum = maxCrossingSum2(arr, left, mid, right, count_assign, count_compare);
    count_assign += 3; // Three results assignments

    count_compare += 2; // Two comparisons in max of three values
    return std::max({left_sum, right_sum, cross_sum});
}

int64_t maxSubarraySum2(const std::vector<int64_t>& arr, int64_t& count_assign, int64_t& count_compare) {
    count_assign = 0;
    count_compare = 0;

    if (arr.empty()) return 0;
    count_compare++; // Empty check

    return divideAndConquerMaxSubarray2(arr, 0, arr.size() - 1, count_assign, count_compare);
}
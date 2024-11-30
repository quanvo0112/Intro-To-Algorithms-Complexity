#include <iostream>
#include <math.h>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <cstdint>

int64_t kadane(const std::vector<int64_t>& arr) {
    if (arr.empty()) {
        return 0;
    }

    int64_t maxSoFar = arr[0];
    int64_t maxEndingHere = arr[0];

    for (size_t i = 1; i < arr.size(); i++) {
        maxEndingHere = std::max(arr[i], maxEndingHere + arr[i]);
        maxSoFar = std::max(maxSoFar, maxEndingHere);
    }

    return maxSoFar;
}

int64_t kadane2(const std::vector<int64_t>& arr, int64_t& count_assign, int64_t& count_compare) {
    count_assign = 0;
    count_compare = 0;

    if (arr.empty()) {
        return 0;
    }

    int64_t maxSoFar = arr[0];
    int64_t maxEndingHere = arr[0];
    count_assign += 2; // Initial assignments

    for (size_t i = 1; i < arr.size(); i++) {
        count_compare++; // Loop condition comparison
        
        // maxEndingHere = std::max(arr[i], maxEndingHere + arr[i]);
        int64_t sum = maxEndingHere + arr[i];
        count_assign++; // sum assignment
        count_compare++; // comparison in max()
        maxEndingHere = (arr[i] > sum) ? arr[i] : sum;
        count_assign++; // maxEndingHere assignment

        // maxSoFar = std::max(maxSoFar, maxEndingHere);
        count_compare++; // comparison in max()
        maxSoFar = (maxEndingHere > maxSoFar) ? maxEndingHere : maxSoFar;
        count_assign++; // maxSoFar assignment
    }

    return maxSoFar;
}
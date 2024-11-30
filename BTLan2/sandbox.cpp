#include <iostream>
#include <math.h>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <cstdint>

// Test function to print intermediate values
void test_kadane(const std::vector<int64_t>& arr) {
    if (arr.empty()) return;

    int64_t maxSoFar = arr[0];
    int64_t maxEndingHere = arr[0];
    size_t start = 0, end = 0, temp_start = 0;
    
    std::cout << "Array: ";
    for (int64_t x : arr) std::cout << x << " ";
    std::cout << "\n\nStep by step:\n";

    for (size_t i = 1; i < arr.size(); i++) {
        // If adding current element improves sum
        if (maxEndingHere + arr[i] > arr[i]) {
            maxEndingHere = maxEndingHere + arr[i];
        } else {
            maxEndingHere = arr[i];
            temp_start = i;
        }
        
        // Update maximum sum found so far
        if (maxEndingHere > maxSoFar) {
            maxSoFar = maxEndingHere;
            start = temp_start;
            end = i;
        }
        
        std::cout << "At i=" << i << ": maxEndingHere=" << maxEndingHere 
                  << ", maxSoFar=" << maxSoFar << "\n";
    }
    
    std::cout << "\nMaximum subarray sum: " << maxSoFar << "\n";
    std::cout << "Subarray indices: [" << start << ".." << end << "]\n";
    std::cout << "Subarray elements: ";
    for (size_t i = start; i <= end; i++) 
        std::cout << arr[i] << " ";
    std::cout << "\n";
}

int main() {
    std::vector<int64_t> arr = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    test_kadane(arr);
    return 0;
}
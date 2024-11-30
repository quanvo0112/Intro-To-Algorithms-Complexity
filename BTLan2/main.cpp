#include <iostream>
#include <math.h>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
#include <cstdint>
#include <fstream>
#include <string>
#include "kadane.cpp"
#include "bruteforce.cpp"
#include "divideconquer.cpp"

std::vector<int64_t> generate_random_array(int64_t size, int64_t lower_bound, int64_t upper_bound) {
    std::vector<int64_t> arr(size);
    std::random_device rd;
    std::mt19937_64 gen(rd());  // Using 64-bit Mersenne Twister
    std::uniform_int_distribution<int64_t> dis(lower_bound, upper_bound);
    
    for (int64_t i = 0; i < size; i++) {
        arr[i] = dis(gen);
    }
    return arr;
}

// void writeToCSV(const std::vector<std::vector<std::string>>& data, const std::string& filename) {
//     std::ofstream file(filename);
    
//     // Write headers
//     file << "Size,Kadane(s),BruteForce(s),DivideConquer(s),Result,K_Assign,K_Compare,";
//     file << "B_Assign,B_Compare,D_Assign,D_Compare\n";
    
//     // Write data rows
//     for (const auto& row : data) {
//         for (size_t i = 0; i < row.size(); ++i) {
//             file << row[i];
//             if (i < row.size() - 1) file << ",";
//         }
//         file << "\n";
//     }
//     file.close();
// }

void writeToCSV(const std::vector<std::vector<std::string>>& data, const std::string& filename, bool includeOperations) {
    std::ofstream file(filename);
    
    // Write headers based on option
    if (includeOperations) {
        file << "Size,Kadane(s),BruteForce(s),DivideConquer(s),Result,K_Assign,K_Compare,";
        file << "B_Assign,B_Compare,D_Assign,D_Compare\n";
    } else {
        file << "Size,Kadane(s),BruteForce(s),DivideConquer(s),Result\n";
    }
    
    // Write data rows
    for (const auto& row : data) {
        for (size_t i = 0; i < row.size(); ++i) {
            file << row[i];
            if (i < row.size() - 1) file << ",";
        }
        file << "\n";
    }
    file.close();
}

// int main() {
//     std::vector<int64_t> sizes = {100, 200, 500, 1000, 2000, 5000};
//     std::vector<std::vector<std::string>> csv_data;
    
//     // Table header for console output
//     std::cout << std::setw(10) << "Size" 
//               << std::setw(15) << "Kadane(s)" 
//               << std::setw(20) << "BruteForce(s)"
//               << std::setw(25) << "DivideConquer(s)" 
//               << std::setw(15) << "Result" << std::endl;
//     std::cout << std::string(85, '-') << std::endl;

//     for (int64_t size : sizes) {
//         int64_t lower_bound = -10000000;
//         int64_t upper_bound = 10000000;
//         std::vector<int64_t> arr = generate_random_array(size, lower_bound, upper_bound);
        
//         // Operation counters
//         int64_t k_assign = 0, k_compare = 0;
//         int64_t b_assign = 0, b_compare = 0;
//         int64_t d_assign = 0, d_compare = 0;

//         // Kadane's Algorithm
//         auto start = std::chrono::high_resolution_clock::now();
//         int64_t result = kadane(arr, k_assign, k_compare);
//         auto end = std::chrono::high_resolution_clock::now();
//         double kadane_time = std::chrono::duration<double>(end - start).count();

//         // Brute Force
//         start = std::chrono::high_resolution_clock::now();
//         int64_t brute_result = bruteForceMaxSubarray(arr, b_assign, b_compare);
//         end = std::chrono::high_resolution_clock::now();
//         double brute_time = std::chrono::duration<double>(end - start).count();

//         // Divide and Conquer
//         start = std::chrono::high_resolution_clock::now();
//         int64_t dc_result = maxSubarraySum(arr, d_assign, d_compare);
//         end = std::chrono::high_resolution_clock::now();
//         double divide_time = std::chrono::duration<double>(end - start).count();

//         // Verify results
//         if (brute_result != result || dc_result != result) {
//             std::cerr << "Error: Results don't match!" << std::endl;
//             return 1;
//         }

//         // Store row data for CSV
//         std::vector<std::string> row;
//         row.push_back(std::to_string(size));
//         row.push_back(std::to_string(kadane_time));
//         row.push_back(std::to_string(brute_time));
//         row.push_back(std::to_string(divide_time));
//         row.push_back(std::to_string(result));
//         row.push_back(std::to_string(k_assign));
//         row.push_back(std::to_string(k_compare));
//         row.push_back(std::to_string(b_assign));
//         row.push_back(std::to_string(b_compare));
//         row.push_back(std::to_string(d_assign));
//         row.push_back(std::to_string(d_compare));
        
//         csv_data.push_back(row);

//         // Console output
//         std::cout << std::setw(10) << size 
//                   << std::setw(15) << std::fixed << std::setprecision(6) << kadane_time
//                   << std::setw(20) << brute_time
//                   << std::setw(25) << divide_time
//                   << std::setw(15) << result << std::endl;
//     }
    
//     // Write results to CSV file
//     writeToCSV(csv_data, "algorithm_comparison.csv");
    
//     return 0;
// }

void displayMenu() {
    std::cout << "\nMaximum Subarray Sum Algorithm Comparison\n";
    std::cout << "1. Measure execution time only\n";
    std::cout << "2. Measure execution time and count operations\n";
    std::cout << "Enter your choice (1-2): ";
}

int main() {
    std::vector<int64_t> sizes = {100, 200, 500, 1000, 2000, 5000};
    std::vector<std::vector<std::string>> csv_data;

    displayMenu();
    int choice = 2;
    std::cout << "\n";

    switch(choice) {
        case 1: {
            // Table header for time only
            std::cout << std::setw(10) << "Size" 
                      << std::setw(15) << "Kadane(s)" 
                      << std::setw(20) << "BruteForce(s)"
                      << std::setw(25) << "DivideConquer(s)" 
                      << std::setw(15) << "Result" << std::endl;
            std::cout << std::string(85, '-') << std::endl;

            for (int64_t size : sizes) {
                int64_t lower_bound = -10000000;
                int64_t upper_bound = 10000000;
                std::vector<int64_t> arr = generate_random_array(size, lower_bound, upper_bound);

                auto start = std::chrono::high_resolution_clock::now();
                int64_t result = kadane(arr);  // Using kadane() without counters
                auto end = std::chrono::high_resolution_clock::now();
                double kadane_time = std::chrono::duration<double>(end - start).count();

                start = std::chrono::high_resolution_clock::now();
                int64_t brute_result = bruteForceMaxSubarray(arr);
                end = std::chrono::high_resolution_clock::now();
                double brute_time = std::chrono::duration<double>(end - start).count();

                start = std::chrono::high_resolution_clock::now();
                int64_t dc_result = maxSubarraySum(arr);
                end = std::chrono::high_resolution_clock::now();
                double divide_time = std::chrono::duration<double>(end - start).count();

                std::vector<std::string> row;
                row.push_back(std::to_string(size));
                row.push_back(std::to_string(kadane_time));
                row.push_back(std::to_string(brute_time));
                row.push_back(std::to_string(divide_time));
                row.push_back(std::to_string(result));
                csv_data.push_back(row);

                std::cout << std::setw(10) << size 
                          << std::setw(15) << std::fixed << std::setprecision(6) << kadane_time
                          << std::setw(20) << brute_time
                          << std::setw(25) << divide_time
                          << std::setw(15) << result << std::endl;
            }
            writeToCSV(csv_data, "time_comparison.csv", false);
            break;
        }
        case 2: {
            // Full comparison with operation counts
            std::cout << std::setw(10) << "Size" 
                      << std::setw(15) << "Kadane(s)" 
                      << std::setw(20) << "BruteForce(s)"
                      << std::setw(25) << "DivideConquer(s)" 
                      << std::setw(15) << "Result"
                      << std::setw(15) << "K_Assign"
                      << std::setw(15) << "K_Comp"
                      << std::setw(15) << "B_Assign"
                      << std::setw(15) << "B_Comp"
                      << std::setw(15) << "D_Assign"
                      << std::setw(15) << "D_Comp" << std::endl;
            std::cout << std::string(155, '-') << std::endl;

            for (int64_t size : sizes) {
                int64_t lower_bound = 1;
                int64_t upper_bound = 100000000;
                std::vector<int64_t> arr = generate_random_array(size, lower_bound, upper_bound);
                
                int64_t k_assign = 0, k_compare = 0;
                int64_t b_assign = 0, b_compare = 0;
                int64_t d_assign = 0, d_compare = 0;

                auto start = std::chrono::high_resolution_clock::now();
                int64_t result = kadane2(arr, k_assign, k_compare);  // Using kadane2() with counters
                auto end = std::chrono::high_resolution_clock::now();
                double kadane_time = std::chrono::duration<double>(end - start).count();

                start = std::chrono::high_resolution_clock::now();
                int64_t brute_result = bruteForceMaxSubarray2(arr, b_assign, b_compare);
                end = std::chrono::high_resolution_clock::now();
                double brute_time = std::chrono::duration<double>(end - start).count();

                start = std::chrono::high_resolution_clock::now();
                int64_t dc_result = maxSubarraySum2(arr, d_assign, d_compare);
                end = std::chrono::high_resolution_clock::now();
                double divide_time = std::chrono::duration<double>(end - start).count();

                std::vector<std::string> row;
                row.push_back(std::to_string(size));
                row.push_back(std::to_string(kadane_time));
                row.push_back(std::to_string(brute_time));
                row.push_back(std::to_string(divide_time));
                row.push_back(std::to_string(result));
                row.push_back(std::to_string(k_assign));
                row.push_back(std::to_string(k_compare));
                row.push_back(std::to_string(b_assign));
                row.push_back(std::to_string(b_compare));
                row.push_back(std::to_string(d_assign));
                row.push_back(std::to_string(d_compare));
                csv_data.push_back(row);

                std::cout << std::setw(10) << size 
                          << std::setw(15) << std::fixed << std::setprecision(6) << kadane_time
                          << std::setw(20) << brute_time
                          << std::setw(25) << divide_time
                          << std::setw(15) << result
                          << std::setw(15) << k_assign
                          << std::setw(15) << k_compare
                          << std::setw(15) << b_assign
                          << std::setw(15) << b_compare
                          << std::setw(15) << d_assign
                          << std::setw(15) << d_compare << std::endl;
            }
            writeToCSV(csv_data, "full_comparison.csv", true);
            break;
        }
        default:
            std::cout << "Invalid choice!\n";
            return 1;
    }
    
    return 0;
}
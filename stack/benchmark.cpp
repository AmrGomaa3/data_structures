#include "stack.h"
#include <chrono>
#include <iostream>

const int size = 10'000'000; // 1e7
const int iterations = 10;

int main() {
    using namespace std::chrono;

    long long totalDuration = 0;
    long long phase1Total = 0, phase2Total = 0, phase3Total = 0;

    for (int iter = 0; iter < iterations; iter++) {
        Stack<int> first;
        Stack<int> second;

        // Phase 1
        //auto start1 = high_resolution_clock::now();
        for (int i = 0; i < size; i++) first.push(1);
        //auto end1 = high_resolution_clock::now();

        for (int i = 0; i < size / 2; i++) second.push(1);

        auto start1 = high_resolution_clock::now();
        second = first;
        auto end1 = high_resolution_clock::now();

        first.clear();
        second.clear();

        long long duration1 = duration_cast<milliseconds>(end1 - start1).count();
        phase1Total += duration1;

        // Phase 2
        for (int i = 0; i < size / 2; i++) first.push(1);
        //auto start2 = high_resolution_clock::now();
        for (int i = 0; i < size; i++) second.push(1);
        //auto end2 = high_resolution_clock::now();

        auto start2 = high_resolution_clock::now();
        second = first;
        auto end2 = high_resolution_clock::now();

        first.clear();
        second.clear();

        long long duration2 = duration_cast<milliseconds>(end2 - start2).count();
        phase2Total += duration2;

        // Phase 3
        //auto start3 = high_resolution_clock::now();
        for (int i = 0; i < size; i++) first.push(1);
        //auto end3 = high_resolution_clock::now();

        for (int i = 0; i < size; i++) second.push(1);

        auto start3 = high_resolution_clock::now();
        second = first;
        auto end3 = high_resolution_clock::now();

        first.clear();
        second.clear();

        long long duration3 = duration_cast<milliseconds>(end3 - start3).count();
        phase3Total += duration3;
    }

    double avgPhase1 = phase1Total / static_cast<double>(iterations);
    double avgPhase2 = phase2Total / static_cast<double>(iterations);
    double avgPhase3 = phase3Total / static_cast<double>(iterations);
    double totalAvg = (phase1Total + phase2Total + phase3Total) / static_cast<double>(iterations);

    std::cout << "Average Phase 1 time: " << avgPhase1 << " ms\n";
    std::cout << "Average Phase 2 time: " << avgPhase2 << " ms\n";
    std::cout << "Average Phase 3 time: " << avgPhase3 << " ms\n";
    std::cout << "Total average time per iteration: " << totalAvg << " ms\n";

    return 0;
}


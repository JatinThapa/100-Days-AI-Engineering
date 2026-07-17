#include <iostream>
#include <chrono>
#include <iomanip>

static inline double calculate(int iterations, double param1, double param2) {
    double result = 1.0;
    for (int i = 1; i <= iterations; ++i) {
        double fi = (double)i;
        double j1 = fi * param1 - param2;
        result -= 1.0 / j1;
        double j2 = fi * param1 + param2;
        result += 1.0 / j2;
    }
    return result;
}

int main() {
    auto start_time = std::chrono::high_resolution_clock::now();
    double result = calculate(200000000, 4.0, 1.0) * 4.0;
    auto end_time = std::chrono::high_resolution_clock::now();

    double elapsed = std::chrono::duration<double>(end_time - start_time).count();

    std::cout << std::fixed << std::setprecision(12);
    std::cout << "Result: " << result << "\n";
    std::cout << std::setprecision(6);
    std::cout << "Execution Time: " << elapsed << " seconds\n";
    return 0;
}
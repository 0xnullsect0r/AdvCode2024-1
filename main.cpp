// main.cpp
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <string>
#include <limits>   // <-- added for std::numeric_limits

int main() {
    // Open the input file (adjust path if necessary)
    std::ifstream infile("../day1input.txt");
    if (!infile) {
        std::cerr << "Failed to open input file.\n";
        return 1;
    }

    // Maps to count occurrences of each number in the first and second columns
    std::unordered_map<int, int> a;   // counts for the left column (x)
    std::unordered_map<int, int> b;   // counts for the right column (y)

    std::string line;
    while (std::getline(infile, line)) {
        // Split the line on three spaces.  We use a stringstream to read two ints.
        std::istringstream ss(line);
        int x, y;
        if (!(ss >> x))
            continue;                 // skip empty or malformed lines
        // Skip any whitespace including the triple‑space separator
        ss.ignore(std::numeric_limits<std::streamsize>::max(), ' ');
        if (!(ss >> y))
            continue;

        ++a[x];
        ++b[y];
    }

    std::vector<long long> c;  // store intermediate products

    // For every key that appears in the first map, check if it also appears
    // in the second map.  If so compute a[key] * key * b[key].
    for (const auto& kv : a) {
        int number = kv.first;
        int countA = kv.second;

        auto itB = b.find(number);
        if (itB != b.end()) {
            int countB = itB->second;
            long long product = static_cast<long long>(countA) * number * countB;
            std::cout << countA << " * " << number << " * "
                      << countB << " = " << product << '\n';
            c.push_back(product);
        }
    }

    // Sum all elements in vector c
    long long sum = 0;
    for (long long val : c) {
        sum += val;
    }

    std::cout << sum << '\n';
    return 0;
}
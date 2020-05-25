#include <iostream>
#include <vector>
#include <string>
#include "histogram.h"
#include "svg.h"
using namespace std;


vector<double> input_numbers(istream& in, const size_t count) {
    vector<double> result(count);
    for (size_t i = 0; i < count; i++) {
        in >> result[i];
    }

    return result;
}

Input
read_input(istream& in) {
    Input data;

    cerr << "Enter number count: ";
    size_t number_count;
    cin >> number_count;

    cerr << "Enter numbers: ";
    data.numbers = input_numbers(in, number_count);

    cerr << "Enter column count: ";
    cin >> data.bin_count;

    return data;
}

vector<size_t> make_histogram(const vector<double>& numbers, const size_t count) {
    vector<size_t> result(count);
    double min;
    double max;
    find_minmax(numbers, min, max);
    for (double number : numbers) {
        size_t bin = (size_t)((number - min) / (max - min) * count);
        if (bin == count) {
            bin--;
        }
        result[bin]++;
    }

    return result;
}


int main() {

    Input data = read_input(cin);
    const auto bins = make_histogram(data);
    show_histogram_svg(bins);
    return 0;
}

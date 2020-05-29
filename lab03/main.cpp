#include <iostream>
#include <vector>
using namespace std;
#include "svg.h"
#include "histogram.h"
#include <windows.h>
#include <string.h>
#include <sstream>

vector<double> input_numbers(size_t count)
{
    vector<double> result(count);
    for (size_t i = 0; i < count; i++)
    {
        cin >> result[i];
    }
    return result;
}



vector <size_t> make_histogram(const vector<double>& numbers,size_t bin_count)
{
    double min;
    double max;
    find_minmax(numbers,min,max);
    vector<size_t> bins(bin_count,0);
    for (double number : numbers)
    {
        size_t bin;
        bin = (number - min) / (max - min) * bin_count;
        if (bin == bin_count)
        {
            bin--;
        }
        bins[bin]++;
    }
    return bins;
}




void show_histogram_text(const vector<size_t> &bins)
{

    const size_t SCREEN_WIDTH = 80;
    const size_t MAX_ASTERISK = SCREEN_WIDTH - 4 - 1;

    size_t max_count = 0;
    for (size_t count : bins)
    {
        if (count > max_count)
        {
            max_count = count;
        }
    }
    const bool scaling_needed = max_count > MAX_ASTERISK;

    for (size_t bin : bins)
    {
        if (bin < 100)
        {
            cout << ' ';
        }
        if (bin < 10)
        {
            cout << ' ';
        }
        cout << bin << "|";

        size_t height = bin;
        if (scaling_needed)
        {
            const double scaling_factor = (double)MAX_ASTERISK / max_count;
            height = (size_t)(bin * scaling_factor);
        }

        for (size_t i = 0; i < height; i++)
        {
            cout << '*';
        }
        cout << '\n';
    }
}



string make_info_text()
{
    stringstream buffer;
      DWORD info = GetVersion();
     DWORD mask = 0x0000ffff;
     DWORD build;
    DWORD platform = info >> 16;
    DWORD version = info & mask;
    DWORD version_major = version & 0xff;
    DWORD version_minor = version >> 8;
    //printf("M_version10 = %lu\n",version_major);
    //printf("M_version16 = %08lx\n",version_major);
    //printf("m_version10 = %lu\n",version_minor);
    //printf("m_version16 = %08lx\n",version_minor);
    if ((info & 0x80000000) == 0)
    {
    build = platform;
    }
    else printf("minor_bit = %u",1);
     //printf("Windows v%lu.%lu (build %lu)\n",version_major,version_minor,build);
    char system_name[MAX_COMPUTERNAME_LENGTH + 1];
    DWORD Size = sizeof(system_name);
    GetComputerNameA(system_name, &Size);
   //printf("System name: %s\n", system_name);
   buffer << "Windows v" << version_major << "." << version_minor << " (build " << build << ")" << " " << "Computer name: " << system_name;
    return buffer.str();
}

int main() {
    string info = make_info_text();
    size_t number_count;
    cerr << "Enter number count: ";
    cin >> number_count;
    cerr << "Enter numbers: ";
    const auto numbers = input_numbers(number_count);
    size_t bin_count;
    cerr << "Enter column count: ";
    cin >> bin_count;
    double min, max;
    find_minmax(numbers, min, max);
    const auto bins = make_histogram(numbers, bin_count);
    show_histogram_svg(bins);
    return 0;
}

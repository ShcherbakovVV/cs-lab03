#include <iostream>
#include <conio.h>
#include <cmath>
#include <vector>

#include "histogram.h"
#include "svg.h"

using namespace std;

const size_t SCREEN_WIDTH = 80;
const size_t MAX_ASTERISK = SCREEN_WIDTH - 4 - 1;

vector<double> input_numbers( size_t& ncount )
{
    vector<double> result( ncount );
    for( size_t i = 0; i < ncount; i ++ )
    {
        cerr << "Enter array element: ";
        cin >> result[i];
    }
    return result;
}

vector<size_t> make_histogram( const vector<double>& numbers, size_t& bin_count, size_t* bin_max )
{
    double mn, mx;
    find_minmax( numbers, &mn, &mx );

    vector <size_t> bins( bin_count, 0 );

    for( double number : numbers )
    {
        size_t bin_index = (number - mn) * bin_count / ( mx - mn );
        if( bin_index == bin_count )
            bin_index --;
        bins[bin_index] ++;
    }

    *bin_max = bins[0];
    for( size_t maxbin : bins )
        if( maxbin > *bin_max )
            *bin_max = maxbin;
    return bins;
}

void show_histogram_text( const vector<size_t>& bins, size_t& bin_max )
{
    for( size_t bin : bins )
    {
        if( bin_max > MAX_ASTERISK )
        {
            size_t height = MAX_ASTERISK * ( static_cast<double>(bin) / bin_max );
            for( size_t j = 0; j < MAX_ASTERISK - height; j ++ )
                cout << " ";
            for( size_t k = 0; k < height; k ++ )
                cout << "*";
        }
        else
        {
            for( size_t l = 0; l < (bin_max - bin); l ++ )
                cout << " ";
            for( size_t m = 0; m < bin; m ++ )
                cout << "*";
        }

        cout << "|";
        if( bin < 100 )
        {
            cout << " ";
            if( bin < 10 )
                cout << " ";
        }
        cout << bin << endl;
    }
}

int main()
{
    size_t number_count;
    cerr << "Enter number count: ";
    cin >> number_count;
    const auto numbers = input_numbers( number_count );

    if( numbers.size() == 0 )
        cerr << "Massiv ne soderzhit elementov";
    else
    {
        size_t bin_count;
        cerr << "Enter bin count: ";
        cin >> bin_count;

        size_t bin_max;
        const auto bins = make_histogram( numbers, bin_count, &bin_max );

        show_histogram_svg( bins, bin_max );
    }

    getch();
    return 0;
}

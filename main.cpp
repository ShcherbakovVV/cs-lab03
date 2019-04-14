#include <iostream>
#include <conio.h>
#include <cmath>
#include <vector>

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

void find_min_max( const vector<double>& numbers, double* mn, double* mx )
{
    *mn = numbers[0];
    *mx = numbers[0];
    for( double maxmin : numbers )
    {
        if( maxmin < *mn )
            *mn = maxmin;
        if( maxmin >= *mx )
            *mx = maxmin;
    }
}

vector<size_t> make_histogram( const vector<double>& numbers, size_t& bin_count, size_t* bin_max )
{
    double mn, mx;
    find_min_max( numbers, &mn, &mx );

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

void svg_begin( double width, double height )
{
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg width='" << width << "' height='" << height << "' "
         << "viewBox='0 0 " << width << " " << height << "' "
         << "xmlns='http://www.w3.org/2000/svg'>\n";
}

void svg_end()
{
    cout << "</svg>\n";
}

void svg_text( double left, double baseline, string text )
{
    cout << "<text x='" << left << "' y='" << baseline << "'>" << text << "</text>";
}

void svg_rect( double x, double y, double width, double height, string stroke = "black", string color = "black" )
{
    cout << "<rect x='" << x << "' y='" << y << "' width='" << width << "' height='" << height << "' stroke='" << stroke << "' fill='" << color << "' />";
}

void show_histogram_svg( const vector<size_t>& bins )
{
    const auto IMAGE_WIDTH = 400;
    const auto IMAGE_HEIGHT = 300;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;
    const string stroke = "maroon";
    const string color = "#E47811";

    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);

    double top = 0;
    for (size_t bin : bins)
    {
        const double bin_width = 10 * bin;
        svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin));

        if( bin_width > (IMAGE_WIDTH - TEXT_WIDTH) )
            svg_rect(TEXT_WIDTH, top, (IMAGE_WIDTH - TEXT_WIDTH), BIN_HEIGHT, stroke, color);
        else
            svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT, stroke, color);
        top += BIN_HEIGHT;
    }

    svg_end();
}

int main()
{
    size_t number_count;
    cerr << "Enter number count: ";
    cin >> number_count;
    const auto numbers = input_numbers( number_count );

    size_t bin_count;
    cerr << "Enter bin count: ";
    cin >> bin_count;

    size_t bin_max;
    const auto bins = make_histogram( numbers, bin_count, &bin_max );

    show_histogram_svg( bins );

    getch();
    return 0;
}

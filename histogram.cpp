#include "histogram.h"

void find_minmax( const vector<double>& numbers, double* mn, double* mx )
{

    if( numbers.size() == 0 ) ;
    else
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
}

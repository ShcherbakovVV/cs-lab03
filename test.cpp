#include "histogram.h"

#include <cassert>

void test_positive()
{
    double mn = 0;
    double mx = 0;
    const vector<double> testvector = {1, 2, 3};
    find_minmax(testvector, &mn, &mx);
    assert(mn == 1);
    assert(mx == 3);
}

void test_negative()
{
    double mn = 0;
    double mx = -4;
    const vector<double> testvector = {-1, -2, -3};
    find_minmax(testvector, &mn, &mx);
    assert(mn == -3);
    assert(mx == -1);
}

void test_same()
{
    double mn = 3;
    double mx = 1;
    const vector<double> testvector = {2, 2, 2};
    find_minmax(testvector, &mn, &mx);
    assert(mn == 2);
    assert(mx == 2);
}

void test_one()
{
    double mn = 4;
    double mx = 2;
    const vector<double> testvector = {3};
    find_minmax(testvector, &mn, &mx);
    assert(mn == 3);
    assert(mx == 3);
}

void test_empty()
{
    double mn = 0;
    double mx = 0;
    const vector<double> testvector;
    find_minmax(testvector, &mn, &mx);
    assert(mn == 0);
    assert(mx == 0);
}

int main()
{
    test_positive();
    test_negative();
    test_same();
    test_one();
    test_empty();
}

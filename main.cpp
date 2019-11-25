#include "eitools.h"


int main() {
    float f_arr1[6], f_arr2[6];
    double d_arr1[6], d_arr2[6];
    eitools::DataUtils::double2floatArr(d_arr1, f_arr1, 6);
    eitools::DataUtils::float2doubleArr(f_arr1, d_arr1, 6);

    eitools::SignalFilters::ExpFilter exp_filt(1000.0, 2.0, 6);
    exp_filt.filter(d_arr1, d_arr2);

    eitools::SignalFilters::MovingAvgFilter mav_filt(6, 10);
    mav_filt.filter(d_arr1, d_arr2);
}

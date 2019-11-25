#ifndef SIGNALFILTERS_H
#define SIGNALFILTERS_H

#include <cstdlib>
#include <cstring>
#include <math.h>

namespace eitools {
namespace SignalFilters {

class ExpFilter {
private:

    const double fc;
    const double alpha;
    double *filt_buf;
    const unsigned n_dims;

public:

    /*
     * exponential filter:
     * fs       sample frequency
     * fc       cutoff frequency
     * n_dims     number of input dimensions
     * alpha is corrected by the cutoff frequency
     */
    ExpFilter(double fs, double fc, unsigned n_dims) : fc(fc), alpha(1 - fc / fs), n_dims(n_dims) {
        filt_buf = (double *) malloc(sizeof(double) * n_dims);
    }

    void filter(double *in, double *out) {
        for (int d = 0; d < n_dims; d++) {
            out[d] = alpha * filt_buf[d] + (1 - alpha) * in[d];
        }
    }

    void reset() {
        memset(filt_buf, 0, sizeof(filt_buf));
    }

    ~ExpFilter() {
        free(filt_buf);
    }

};

class MovingAvgFilter {
private:
    const unsigned n_dims;
    const unsigned n_samples;
    double** filt_buf_2D;
    unsigned ring_count = 0;
    unsigned buf_count = 0;

public:

    /* Simple moving average (SMA) filter
     * n_dims     number of input dimensions
     * n_samples  number of buffer n_samples
     */
    MovingAvgFilter(unsigned n_dims, unsigned n_samples) : n_dims(n_dims), n_samples(n_samples) {

        filt_buf_2D = new double*[n_samples]; // allocate array of double pointers for n_samples
        for (int i=0; i < n_samples; i++) {
            filt_buf_2D[i] = new double[n_dims]; // allocate double array for n_dims
        }
    }

    void filter(double *in, double *out) {
        // copy all n_dims to next sample position
        memcpy(filt_buf_2D[(ring_count++) % n_samples], in, sizeof(double) * n_dims);

        // check how many n_samples are in buffer to accelerate performance
        if (buf_count < n_samples) {
            buf_count++;
        }

        // over n_dims
        for (int d=0; d < n_dims; d++) {
            double filt_sum = 0;
            // over n_samples
            for (int s=0; s<buf_count; s++) {
                filt_sum += filt_buf_2D[s][d]; // sum up values
            }
            out[d] = filt_sum / (double)buf_count; // take average
        }
    }

    void reset() {
        for (int i=0; i < n_samples; i++) {
            memset(filt_buf_2D[i], 0, sizeof(filt_buf_2D[i]));
        }
    }

    ~MovingAvgFilter() {
        for (int i=0; i < n_samples; i++) {
            delete filt_buf_2D[i];
        }
        delete [] filt_buf_2D;
    }

};

/*
class SignalFilters
{
public:
    SignalFilters();
};
*/

} } // end namespace

#endif // SIGNALFILTERS_H

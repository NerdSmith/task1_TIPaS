#include "sin_wave.h"

x_y_lists sin_wave(int freq, int overSampleRate, int cycles, int ampl)
{
    int fs = overSampleRate * freq;
    std::vector<double> timeRange = arange<double>(0.0, cycles * 1.0 / freq, 1.0 / fs);
    std::vector<double> res(timeRange.size());
    for (int i = 0; i < timeRange.size(); i++) {
        res[i] = ampl * sin(2 * M_PI * freq * timeRange[i]);
    }
    return std::make_pair(timeRange, res);
}

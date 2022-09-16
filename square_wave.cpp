#include "square_wave.h"

x_y_lists square_wave(int freq, int overSampleRate, int cycles, int harmonics, int ampl)
{
    int fs = overSampleRate * freq;
    std::vector<double> timeRange = arange<double>(0.0, cycles * 1.0 / freq, 1.0 / fs);
    std::vector<double> res(timeRange.size());

    for (int j = 0; j < timeRange.size(); j++) {
        double currTime = timeRange[j];
        std::vector<double> to_sum(harmonics);
        for (int i = 1; i <= harmonics; i++) {
            double component = sin((2.0 * i - 1.0) * 2.0 * M_PI * freq * currTime) / (2.0 * i - 1.0);
            to_sum[i - 1] = component;
        }

        double r = ampl * 4.0 / M_PI * sum(to_sum);
        if (r < 0) {
            if (r + ampl < 0) {
                r = 0;
            } else {
                r = r + ampl;
            }
        }
        res[j] = r;
    }
    return std::make_pair(timeRange, res);
}

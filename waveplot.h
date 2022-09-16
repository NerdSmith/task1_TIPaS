#ifndef WAVEPLOT_H
#define WAVEPLOT_H

#include "fft_analysis.h"
#include "math_utils.h"
#include "qcustomplot.h"
#include "sin_wave.h"
#include "square_wave.h"
#include <QWidget>
#include <algorithm>
#include <cmath>

namespace Ui {
class WavePlot;
}

class WavePlot : public QWidget {
    Q_OBJECT

public:
    explicit WavePlot(QWidget* parent = 0);
    ~WavePlot();

private slots:
    void on_drawBtn_clicked();

    void on_squareRBtn_toggled(bool checked);

private:
    Ui::WavePlot* ui;

private:
    void setWindowSettings();
};

#endif // WAVEPLOT_H

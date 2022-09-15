#ifndef WAVEPLOT_H
#define WAVEPLOT_H

#include "qcustomplot.h"
#include <QWidget>

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

private:
    Ui::WavePlot* ui;
    //    QCustomPlot* plot;

private:
    void setWindowSettings();
};

#endif // WAVEPLOT_H

#include "waveplot.h"
#include "ui_waveplot.h"

using x_y_lists = std::pair<std::vector<double>, std::vector<double>>;

template <typename T>
std::vector<T> arange(T start, T stop, T step = 1)
{
    std::vector<T> values;
    for (T value = start; value < stop; value += step) {
        values.push_back(value);
    }
    return values;
}

void WavePlot::setWindowSettings()
{
    this->resize(1200, 700);
}

WavePlot::WavePlot(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::WavePlot)
{
    ui->setupUi(this);
    setWindowSettings();
    ui->plot->addGraph();
    ui->plot->yAxis->setLabel("y");
    ui->plot->xAxis->setRange(0, 5);
    ui->plot->yAxis->setRange(-1, 1);
    ui->plot->setInteraction(QCP::iRangeDrag, true);
    ui->plot->setInteraction(QCP::iRangeZoom, true);
    ui->plot->replot();
    repaint();
}

WavePlot::~WavePlot()
{
    delete ui;
}

x_y_lists sin_wave(int freq, int overSampleRate, int cycles)
{
    int fs = overSampleRate * freq;
    std::vector<double> timeRange = arange<double>(0.0, cycles * 1.0 / freq, 1.0 / fs);
    std::vector<double> res(timeRange.size());
    for (int i = 0; i < timeRange.size(); i++) {
        res[i] = sin(2 * M_PI * freq * timeRange[i]);
    }
    return std::make_pair(timeRange, res);
}

void WavePlot::on_drawBtn_clicked()
{
    if (ui->harmonicRBtn->isChecked()) {
        int freq;
        int overSampleRate = 50;
        int cycles = 5;

        if (ui->hz1RBtn->isChecked()) {
            freq = 1;
        } else if (ui->hz2RBtn->isChecked()) {
            freq = 2;
        } else if (ui->hz4RBtn->isChecked()) {
            freq = 4;
        } else if (ui->hz8RBtn->isChecked()) {
            freq = 8;
        }

        x_y_lists dots = sin_wave(freq, overSampleRate, cycles);
        ui->plot->graph(0)->setData(QVector<double>::fromStdVector(dots.first), QVector<double>::fromStdVector(dots.second));
        ui->plot->xAxis->setRange(*dots.first.begin(), dots.first.back());
        ui->plot->yAxis->setRange(-1, 1);
        ui->plot->replot();
    }
}

#include "waveplot.h"

#include "ui_waveplot.h"

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

    ui->harmonicsNbBox->setHidden(true);

    ui->wavePlot->addGraph();
    ui->wavePlot->xAxis->setLabel("Time");
    ui->wavePlot->yAxis->setLabel("Amplitude");
    ui->wavePlot->xAxis->setRange(0, 5);
    ui->wavePlot->yAxis->setRange(-1, 1);
    ui->wavePlot->setInteraction(QCP::iRangeDrag, true);
    ui->wavePlot->setInteraction(QCP::iRangeZoom, true);
    ui->wavePlot->replot();

    ui->spectrumPlot->addGraph();
    ui->spectrumPlot->xAxis->setLabel("Time");
    ui->spectrumPlot->yAxis->setLabel("Amplitude");
    ui->spectrumPlot->xAxis->setRange(0, 5);
    ui->spectrumPlot->yAxis->setRange(-1, 1);
    ui->spectrumPlot->setInteraction(QCP::iRangeDrag, true);
    ui->spectrumPlot->setInteraction(QCP::iRangeZoom, true);
    ui->spectrumPlot->replot();
    repaint();
}

WavePlot::~WavePlot()
{
    delete ui;
}

void WavePlot::on_drawBtn_clicked()
{

    int freq;
    int overSampleRate = ui->overSampleBoxSlider->value();
    int cycles = ui->cyclesNbSlider->value();

    if (ui->hz1RBtn->isChecked()) {
        freq = 1;
    } else if (ui->hz2RBtn->isChecked()) {
        freq = 2;
    } else if (ui->hz4RBtn->isChecked()) {
        freq = 4;
    } else if (ui->hz8RBtn->isChecked()) {
        freq = 8;
    }
    int fs = overSampleRate * freq;

    x_y_lists dots;
    if (ui->harmonicRBtn->isChecked()) {
        dots = sin_wave(freq, overSampleRate, cycles);
    } else if (ui->squareRBtn->isChecked()) {
        dots = square_wave(freq, overSampleRate, cycles, ui->harmonicsNbSlider->value());
    }

    ui->wavePlot->graph(0)->setData(
        QVector<double>::fromStdVector(dots.first),
        QVector<double>::fromStdVector(dots.second));
    ui->wavePlot->xAxis->setRange(*dots.first.begin(), dots.first.back());
    ui->wavePlot->yAxis->setRange(-1, 1);
    ui->wavePlot->replot();

    int nfft = flp2(dots.second.size());
    std::vector<double> fftRes(nfft);

    FFTAnalysis(dots.second.data(), fftRes.data(), nfft, nfft);
    std::rotate(fftRes.begin(), fftRes.begin() + (int)floor((float)fftRes.size() / 2) - 1, fftRes.end());
    std::vector<double> fftXAxis = arange(-nfft / 2.0, nfft / 2.0);
    for (int i = 0; i < fftXAxis.size(); i++) {
        fftXAxis[i] = fftXAxis[i] * (double)fs / (double)nfft;
    }
    ui->spectrumPlot->graph(0)->setData(
        QVector<double>::fromStdVector(fftXAxis),
        QVector<double>::fromStdVector(fftRes));
    ui->spectrumPlot->replot();
}

void WavePlot::on_squareRBtn_toggled(bool checked)
{
    ui->harmonicsNbBox->setVisible(checked);
}

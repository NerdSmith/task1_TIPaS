#include "waveplot.h"
#include <QApplication>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    WavePlot w;

    w.show();

    return a.exec();
}

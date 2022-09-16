#include <QApplication>

#include "waveplot.h"

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);
  WavePlot w;

  w.show();

  return a.exec();
}

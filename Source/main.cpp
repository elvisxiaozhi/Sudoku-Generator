#include "sudokugenerator.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SudokuGenerator w;
    w.show();

    return a.exec();
}

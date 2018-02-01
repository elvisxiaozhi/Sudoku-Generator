#ifndef SUDOKUGENERATOR_H
#define SUDOKUGENERATOR_H

#include <QMainWindow>

class SudokuGenerator : public QMainWindow
{
    Q_OBJECT

public:
    SudokuGenerator(QWidget *parent = 0);
    ~SudokuGenerator();
};

#endif // SUDOKUGENERATOR_H

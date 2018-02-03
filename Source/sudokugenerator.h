#ifndef SUDOKUGENERATOR_H
#define SUDOKUGENERATOR_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>

class SudokuGenerator : public QMainWindow
{
    Q_OBJECT

public:
    SudokuGenerator(QWidget *parent = 0);
    ~SudokuGenerator();

private:
    QWidget *basicLayout;
    QVBoxLayout *vLayout;
    QGridLayout *labelLayout;
    QVector<QLabel*> sudokuLbls;
    QVector<QLineEdit*> sudokuLineEdit;
    QVector<int> posVec;
    QVector<int> numsVec;

    void setBasicLayout();
    void setLabelsAndLineEdits();
    void generatePos();
    void filterPos();
    void generateNums();
    void filterNums();
};

#endif // SUDOKUGENERATOR_H

#include "sudokugenerator.h"
#include <QDebug>
#include <QValidator>

SudokuGenerator::SudokuGenerator(QWidget *parent)
    : QMainWindow(parent)
{
    setBasicLayout();
    generatePos();
    filterPos();
    generateNums();
    setLabelsAndLineEdits();
}

SudokuGenerator::~SudokuGenerator()
{

}

void SudokuGenerator::setBasicLayout()
{
    setWindowTitle("Sodoku");
    basicLayout = new QWidget(this);
    setCentralWidget(basicLayout);
    vLayout = new QVBoxLayout(basicLayout);
    basicLayout->setLayout(vLayout);
    labelLayout = new QGridLayout;
    labelLayout->setSpacing(0);
    vLayout->addLayout(labelLayout);
}

void SudokuGenerator::setLabelsAndLineEdits()
{
    QValidator *lineEditValidator = new QIntValidator(1, 9, basicLayout);

    sudokuLbls.resize(81);
    sudokuLineEdit.resize(81);
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            sudokuLbls[i * 9 + j] = new QLabel(basicLayout);
            sudokuLbls[i * 9 + j]->setMinimumSize(50, 50);
            sudokuLbls[i * 9 + j]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            sudokuLbls[i * 9 + j]->setAlignment(Qt::AlignCenter);
//            sudokuLbls[i * 9 + j]->setText(QString::number(i * 9 + j));
            labelLayout->addWidget(sudokuLbls[i * 9 + j], i, j);

            sudokuLineEdit[i * 9 + j] = new QLineEdit(basicLayout);
            sudokuLineEdit[i * 9 + j]->setMaximumSize(50, 50);
//            sudokuLineEdit[i * 9 + j]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            sudokuLineEdit[i * 9 + j]->setAlignment(Qt::AlignCenter);
            sudokuLineEdit[i * 9 + j]->setValidator(lineEditValidator);
            labelLayout->addWidget(sudokuLineEdit[i * 9 + j], i, j);


            if(std::find(posVec.begin(), posVec.end(), i * 9 + j) != posVec.end()) {
                sudokuLbls[i * 9 + j]->show();
                int distance = std::find(posVec.begin(), posVec.end(), i * 9 + j) - posVec.begin();
                sudokuLbls[i * 9 + j]->setText(QString::number(numsVec[posVec[distance]]));
                sudokuLineEdit[i * 9 + j]->hide();
            }
            else {
                sudokuLbls[i * 9 + j]->hide();
                sudokuLineEdit[i * 9 + j]->show();
            }
        }
    }
}

void SudokuGenerator::generatePos()
{
    posVec.clear();
    int range = 27 + (rand() % (45 - 27 + 1));
    for(int i = 0; i < range; i++) {
        int pos = rand() % 81;
        if(!posVec.empty()) {
            if(std::find(posVec.begin(), posVec.end(), pos) != posVec.end()) {
                i--;
            }
            else {
                posVec.push_back(pos);
            }
        }
        else {
            posVec.push_back(pos);
        }
    }
    qDebug() << "Pos:" << posVec << "size: " << posVec.size();
}

//make sure each row has at least one number and not more than 5 numbers
void SudokuGenerator::filterPos()
{
    int iterateTimes = 0;
    while(iterateTimes < 9) {
        std::sort(posVec.begin(), posVec.end());
        int i = 1;
        while(i <= 9) {
            int totalNums = 0;
            if(std::find(posVec.begin(), posVec.end(), i * 8)) {
                totalNums++;
            }
            if(totalNums > 5 || totalNums == 0) {
                generatePos();
                break;
            }
            else {
                i++;
                iterateTimes++;
            }
        }
    }
}

void SudokuGenerator::generateNums()
{
    numsVec.clear();

    numsVec.resize(81);
    for(int i = 0; i < posVec.size(); i++) {
        int num = rand() % 9 + 1;
        numsVec[posVec[i]] = num;
    }
    filterNums();
    qDebug() << "num:" << numsVec << numsVec.size();
}

void SudokuGenerator::filterNums()
{
    int tryingTimes = 0;
    while(true) {
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                QVector<int> nineNums;
                nineNums = {numsVec[10 + 27 * i + j * 3], numsVec[10 + 27 * i + j * 3 - 9], numsVec[10 + 27 * i + j * 3 + 9], numsVec[10 + 27 * i + j * 3 - 1], numsVec[10 + 27 * i + j * 3 + 1], numsVec[10 + 27 * i + j * 3 - 9 - 1], numsVec[10 + 27 * i + j * 3 - 9 + 1], numsVec[10 + 27 * i + j * 3 + 9 - 1], numsVec[10 + 27 * i + j * 3 + 9 + 1]};
                QVector<int> ninePos;
                ninePos = {10 + 27 * i + j * 3, 10 + 27 * i + j * 3 - 9, 10 + 27 * i + j * 3 + 9, 10 + 27 * i + j * 3 - 1, 10 + 27 * i + j * 3 + 1, 10 + 27 * i + j * 3 - 9 - 1, 10 + 27 * i + j * 3 - 9 + 1, 10 + 27 * i + j * 3 + 9 - 1, 10 + 27 * i + j * 3 + 9 + 1};
                for(int k = 0; k < nineNums.size(); k++) {
                    if(nineNums[k] > 0 && nineNums[k] < 10) {
                        int originalNum = nineNums[k];
                        std::replace(nineNums.begin(), nineNums.end(), nineNums[k], 10);
                        nineNums[k] = originalNum;
                    }
                }
                for(int a = 0; a < ninePos.size(); a++) {
                    numsVec[ninePos[a]] = nineNums[a];
                }
            }
        }

        for(int i = 0; i < 9; i++) {
            for(int j = 0; j < 9; j++) {
                if((i * 9 + j) / 9 == i) {
                    if(numsVec[i * 9 + j] > 0 && numsVec[i * 9 + j] < 10) {
                        int k = 1;
                        while((i * 9 + j + k) / 9 < i + 1) {
                            if(numsVec[i * 9 + j + k] == numsVec[i * 9 + j]) {
                                numsVec[i * 9 + j + k] = 10;
                            }
                            k++;
                        }
                    }
                }
            }
        }

        for(int j = 0; j < 9; j++) {
            for(int i = 0; i < 9; i++) {
                if(numsVec[i * 9 + j] > 0 && numsVec[i * 9 + j] < 10) {
                    int k = 1;
                    while(i + k < 9) {
                        if(numsVec[(i + k) * 9 + j] == numsVec[i * 9 + j]) {
                            numsVec[(i + k) * 9 + j] = 10;
                        }
                        k++;
                    }
                }
            }
        }

        int iterateTimes = 0;
        for(auto &i : numsVec) {
            if(i == 10) {
                i = rand() % 9 + 1;
            }
            else {
                iterateTimes++;
            }
        }
        if(iterateTimes == numsVec.size()) {
            break;
        }
        tryingTimes++;
        if(tryingTimes > 1000) {
            generatePos();
            filterPos();
            generateNums();
            break;
        }
    }
}

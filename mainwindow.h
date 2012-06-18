#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>

class MainWindow : public QWidget
{
    Q_OBJECT
    
public:
    MainWindow(QWidget *pwgt = 0);
private:
    //Размещение
    QVBoxLayout *pvbl;
    QVBoxLayout *pvbl2;
    QHBoxLayout* phbl;
    //Элементы
    QLabel * pLabelView;
    QLabel * pLabelAdd;
    QGroupBox *pgb;
    QRadioButton* prbItems;
    QRadioButton *prbSuppliers;
    QRadioButton *prbDeliveries;
    QRadioButton* prbWorkers;
    QTableWidget *ptw;
    QPushButton *ppbAdd;
    QToolBox *ptb;



};

#endif // MAINWINDOW_H

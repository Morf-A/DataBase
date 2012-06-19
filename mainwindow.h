#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include<QtSql>
#include "deliverydialog.h"
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
    QTableView *view;
    QSqlQueryModel *model;

    //Диалоги
    DeliveryDialog* pDevDialog;

public slots:
    void slotAddDelivery();
    void slotViewClicked();

};

#endif // MAINWINDOW_H

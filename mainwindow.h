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
   void WidgetImplementation();
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

    //Виджеты

    QWidget* wgt1; QLabel* plblwgt1;  QPushButton* pcmdwgt1;
    QWidget* wgt2; QLabel* plblwgt2;  QPushButton* pcmdwgt2;
    QWidget* wgt3; QLabel* plblwgt3;  QPushButton* pcmdwgt3;
    QWidget* wgt4; QLabel* plblwgt4;  QPushButton* pcmdwgt4;
    QWidget* wgt5; QLabel* plblwgt5;  QPushButton* pcmdwgt5;

    //Диалоги
    DeliveryDialog* pDevDialog;

public slots:
    void slotAddDelivery();
    void slotViewClicked();

};

#endif // MAINWINDOW_H

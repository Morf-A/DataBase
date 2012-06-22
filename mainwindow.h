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

    QWidget* wgt1; QLabel* plblwgt1;  QPushButton* pcmdwgt1; QSpinBox *psbxwgt11; QSpinBox *psbxwgt12;
    QWidget* wgt2; QLabel* plblwgt2;  QPushButton* pcmdwgt2; QComboBox* pcbxwgt11; QComboBox* pcbxwgt12;
    QWidget* wgt3; QLabel* plblwgt3;  QPushButton* pcmdwgt3; QRadioButton* prbwgt31;QRadioButton* prbwgt32;QRadioButton *prbwgt33;
    QWidget* wgt4; QLabel* plblwgt4;  QPushButton* pcmdwgt4; QSpinBox *psbxwgt4;
    QWidget* wgt5; QLabel* plblwgt5;  QPushButton* pcmdwgt5; QComboBox* pcbxwgt51; QComboBox* pcbxwgt52;

    //Диалоги
    DeliveryDialog* pDevDialog;

public slots:
    void slotAddDelivery();
    void slotViewClicked();
    void slotN1Clicked();
    void slotN2Clicked();
    void slotN3Clicked();
    void slotN4Clicked();
    void slotN5Clicked();


};

#endif // MAINWINDOW_H

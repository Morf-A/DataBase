#include "mainwindow.h"
#include <QtSql>
MainWindow::MainWindow(QWidget *pwgt/* =0*/): QWidget(pwgt)
{
//Внешний вид
    //RadioButtons
    pgb = new QGroupBox("View:");
    prbItems = new QRadioButton("Items");
    prbSuppliers = new QRadioButton("Suppliers");
    prbDeliveries = new QRadioButton("Deliveries");
    prbWorkers  =new QRadioButton("Workers");
    prbItems->setChecked(true);
    QHBoxLayout * phblGB = new QHBoxLayout;
    phblGB->addWidget(prbItems);
    phblGB->addWidget(prbSuppliers);
    phblGB->addWidget(prbDeliveries);
    phblGB->addWidget(prbWorkers);
    pgb->setLayout(phblGB);

    ptw = new QTableWidget(3,3);
    ppbAdd = new QPushButton("+ Add");
    ptb = new QToolBox;

    pvbl = new QVBoxLayout;
    phbl = new QHBoxLayout;
    pvbl2 = new QVBoxLayout;

    pvbl->addWidget(pgb);
    phbl->addWidget(ptw);
    pvbl2->addWidget(ppbAdd);
    pvbl2->addWidget(ptb);
    phbl->addLayout(pvbl2);
    pvbl->addLayout(phbl);

    setLayout(pvbl);


    ptb->addItem(new QLabel("111"),"Filter");

    QStringList lst;
    lst<< "First" << "Second" <<"Third";
    ptw->setHorizontalHeaderLabels(lst);
    ptw->setVerticalHeaderLabels(lst);
    QTableWidgetItem *ptwi;
    for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
        {
            ptwi = new QTableWidgetItem(QString("%1,%2").arg(i).arg(j));
            ptw->setItem(i,j,ptwi);
        }

}

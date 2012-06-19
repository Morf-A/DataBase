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
    ppbAdd = new QPushButton("+ Add...");
    connect(ppbAdd,SIGNAL(clicked()),SLOT(slotAddDelivery()));
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
    ptb->addItem(new QLabel("222"),"Filter2");
    ptb->addItem(new QLabel("333"),"Filter3");
    ptb->addItem(new QLabel("444"),"Filter4");

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


    //Соединение с БД
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("111");
    if(!db.open())
    {
        qDebug()<<"Can not open database " <<db.lastError();
        return;
    }
    else
        qDebug()<<"Open database " <<db.lastError();

}



void MainWindow::slotAddDelivery()
{
   pDevDialog = new  DeliveryDialog;

   if(pDevDialog->exec()==QDialog::Accepted)
   {
       qDebug() <<"OK";
       //qDebug()<<"Date: " << pDevDialog->GetDate() <<"\n";
      // qDebug()<<"Supplier : " << pDevDialog->GetSupplier() <<"\n";
   }
   delete pDevDialog;
}

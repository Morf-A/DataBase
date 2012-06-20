#include "mainwindow.h"
#include <QtSql>
MainWindow::MainWindow(QWidget *pwgt/* =0*/): QWidget(pwgt)
{
//Внешний вид
    //RadioButtons
    pgb = new QGroupBox("View:");
    prbItems = new QRadioButton("Items");
    connect(prbItems,SIGNAL(clicked()),SLOT(slotViewClicked()));
    prbSuppliers = new QRadioButton("Suppliers");
    connect(prbSuppliers,SIGNAL(clicked()),SLOT(slotViewClicked()));
    prbDeliveries = new QRadioButton("Deliveries");
    connect(prbDeliveries,SIGNAL(clicked()),SLOT(slotViewClicked()));
    prbWorkers  =new QRadioButton("Workers");
    connect(prbWorkers,SIGNAL(clicked()),SLOT(slotViewClicked()));
    prbItems->setChecked(true);
    QHBoxLayout * phblGB = new QHBoxLayout;
    phblGB->addWidget(prbItems);
    phblGB->addWidget(prbSuppliers);
    phblGB->addWidget(prbDeliveries);
    phblGB->addWidget(prbWorkers);
    pgb->setLayout(phblGB);

    view = new QTableView;
    model = new QSqlQueryModel;

    ppbAdd = new QPushButton("+ AddDelivery...");
    connect(ppbAdd,SIGNAL(clicked()),SLOT(slotAddDelivery()));
    ptb = new QToolBox;

    pvbl = new QVBoxLayout;
    phbl = new QHBoxLayout;
    pvbl2 = new QVBoxLayout;

    pvbl->addWidget(pgb);
    phbl->addWidget(view);
    pvbl2->addWidget(ppbAdd);
    pvbl2->addWidget(ptb);
    phbl->addLayout(pvbl2);
    pvbl->addLayout(phbl);

    setLayout(pvbl);

    ptb->addItem(new QLabel("111"),"Filter");
    ptb->addItem(new QLabel("222"),"Filter2");
    ptb->addItem(new QLabel("333"),"Filter3");
    ptb->addItem(new QLabel("444"),"Filter4");

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

    slotViewClicked();
    view->setModel(model);

}



void MainWindow::slotAddDelivery()
{
   pDevDialog = new  DeliveryDialog;

   if(pDevDialog->exec()==QDialog::Accepted)
   {
        QSqlQuery query;

   }
   delete pDevDialog;
}

void MainWindow::slotViewClicked()
{
    if(prbSuppliers->isChecked())
        model->setQuery("SELECT Name, Address, Telephone, Email FROM Suppliers");
    else if(prbItems->isChecked())
        model->setQuery("SELECT Items.Name, Items.Quantity,Workers.Name AS NameOfWorker, Suppliers.Name AS NameOfSupplier, Deliveries.Date "
                        "FROM Items , Deliveries, Suppliers, Workers "
                        "WHERE Items.id_delivery=Deliveries.id_delivery "
                        "   AND Deliveries.id_supplier=Suppliers.id_supplier "
                        "    AND Items.id_Worker=Workers.id_worker;");
    else if(prbDeliveries->isChecked())
        model->setQuery("SELECT Deliveries.Date, Suppliers.Name FROM Deliveries, Suppliers WHERE Deliveries.id_supplier=Suppliers.id_supplier");
    else
        model->setQuery("SELECT  Name, telephone, email FROM Workers");

}

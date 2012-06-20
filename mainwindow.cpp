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
        //заполняем поставку
       QSqlQuery query;
       QSqlQuery querySelect;
       query.prepare("INSERT INTO Deliveries(id_supplier, Date) VALUES (:id_supplier, :Date);");
       if(!querySelect.exec("SELECT id_supplier FROM Suppliers WHERE Name like '"+pDevDialog->GetSupliers()+"'; "))
           qDebug()<<"Unable to make SELECT";
       querySelect.last();
       int number = querySelect.value(0).toInt();
       query.bindValue("id_supplier",number);
       query.bindValue(":Date",pDevDialog->GetDate());
       if(!query.exec())
           qDebug()<<"Unable to make INSERT";

       //Заполняем товары
       QComboBox* wgtComboItem;
       QSpinBox * wgtSpinQuantity;
       QComboBox* wgtComboWorker;

       for(int i=0;i<pDevDialog->pTableItem->rowCount();i++)
       {
       wgtComboItem =  (QComboBox*)(pDevDialog->pTableItem->cellWidget(i,0));
       wgtSpinQuantity =  (QSpinBox*)(pDevDialog->pTableItem->cellWidget(i,1));
       wgtComboWorker =  (QComboBox*)(pDevDialog->pTableItem->cellWidget(i,2));

       QString strComboItem = wgtComboItem->currentText();
       QString strSpinQuantity = wgtSpinQuantity->text();
       QString strComboWorker = wgtComboWorker->currentText();

       if(strSpinQuantity=="0") continue;

           if(!querySelect.exec("SELECT id_item, Name, Quantity FROM Items WHERE Name like '"+strComboItem+"';"))
               qDebug()<<"Unable to SELECT";
           querySelect.last();
           QSqlRecord rec = querySelect.record();
           int ItemQuantity =querySelect.value(rec.indexOf("Quantity")).toInt();

           if(ItemQuantity==0)
           {

               query.prepare("UPDATE Items SET "
                             "id_delivery = :id_delivery , Quantity= :Quantity, id_Worker = :id_Worker "
                             "WHERE id_item= :id_item ;");

               query.bindValue(":id_item",querySelect.value(rec.indexOf("id_item")).toInt());

               query.bindValue(":Quantity",strSpinQuantity);

               if(!querySelect.exec("SELECT id_delivery FROM Deliveries; "))
                   qDebug()<<"Unable to make SELECT";
               querySelect.last();
               int number = querySelect.value(0).toInt();
               query.bindValue(":id_delivery",number);

               if(!querySelect.exec("SELECT id_worker FROM Workers WHERE Name like '"+strComboWorker+"' ; "))
                   qDebug()<<"Unable to make SELECT!";
               querySelect.last();
               number = querySelect.value(0).toInt();
               query.bindValue(":id_Worker",number);


               if(!query.exec()) qDebug()<<"Unable to make UPDATE";
               continue;
           }

           query.prepare("INSERT INTO Items(id_delivery, Name, Quantity, id_Worker)"
                         "VALUES (:id_delivery, :Name, :Quantity, :id_Worker);");


           if(!querySelect.exec("SELECT id_delivery FROM Deliveries; "))
               qDebug()<<"Unable to make SELECT";
           querySelect.last();
           int number = querySelect.value(0).toInt();
           query.bindValue(":id_delivery",number);
           query.bindValue(":Name",strComboItem);
           query.bindValue(":Quantity",strSpinQuantity);

           if(!querySelect.exec("SELECT id_worker FROM Workers WHERE Name like '"+strComboWorker+"' ; "))
               qDebug()<<"Unable to make SELECT!";
           querySelect.last();
           number = querySelect.value(0).toInt();
           query.bindValue(":id_Worker",number);

           if(!query.exec()) qDebug() <<"Unable to make INSERT";
       }


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
        model->setQuery("SELECT W1.Name, W1.Telephone, W1.Email, W2.Name AS NameOfSuperior "
                        " FROM Workers W1, Workers W2 "
                        " WHERE W1.id_superior = W2.id_worker;");

}

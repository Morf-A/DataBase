#include "mainwindow.h"
#include <QtSql>
MainWindow::MainWindow(QWidget *pwgt/* =0*/): QWidget(pwgt)
{
    QTextCodec *utfcodec = QTextCodec::codecForName("Windows-1251");
    QTextCodec::setCodecForTr(utfcodec);
    QTextCodec::setCodecForCStrings(utfcodec);

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

    //Внешний вид
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


    WidgetImplementation();

    ptb->addItem(wgt1,"Запрос №1");
    ptb->addItem(wgt2,"Запрос №2");
    ptb->addItem(wgt3,"Запрос №3");
    ptb->addItem(wgt4,"Запрос №4");
    ptb->addItem(wgt5,"Запрос №5");

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

void MainWindow::slotN1Clicked()
{
    model->setQuery("SELECT "
                    "CASE WHEN Items.Quantity > "+psbxwgt11->text()+" THEN 'Товаров много' ELSE "
                     "'Товаров мало' END HouMany, Items.Name , Items.Quantity, Workers.Name FROM Items, Workers "
                    "WHERE Items.id_Worker=Workers.id_worker AND Items.Quantity<>"+psbxwgt12->text()+";" );
}

void MainWindow::slotN2Clicked()
{
    QString arg;
    if(pcbxwgt12->currentText()=="убыванию")arg="DESC"; else arg="ASC";
    model->setQuery("SELECT * FROM View_1 ORDER BY "+ pcbxwgt11->currentText()+" "+arg+";");
}

void MainWindow::slotN3Clicked()
{

}

void MainWindow::slotN4Clicked()
{
    model->setQuery("SELECT SUM (Items.Quantity), Workers.Name "
                    "FROM Items INNER JOIN Workers ON Items.id_Worker=Workers.id_worker "
                    "GROUP BY Workers.Name HAVING SUM(Items.Quantity) > "+psbxwgt4->text()+";");
}

void MainWindow::slotN5Clicked()
{
    QString arg;
    if(pcbxwgt52->currentText()=="самой большой")arg="ALL"; else arg="SOME";

    model->setQuery("SELECT Name, Quantity FROM Items WHERE "
                    "Quantity >"+arg+"( SELECT Items.Quantity FROM Items WHERE Items.Name='"+pcbxwgt51->currentText()+"' );");
}

void MainWindow::WidgetImplementation()
{
    //N1
    wgt1 = new QWidget;
    plblwgt1 = new QLabel("Составной многотабличный запрос с параметром,\n"
                          "включающий соединение таблиц и CASE-выражение");
    pcmdwgt1 = new QPushButton("Запрос");
    connect(pcmdwgt1,SIGNAL(clicked()),SLOT(slotN1Clicked()));
    QGridLayout* playwgt1 = new QGridLayout;
    psbxwgt11 = new QSpinBox;
    psbxwgt12 = new QSpinBox;
    playwgt1->addWidget(plblwgt1,0,0,1,3);
    playwgt1->addWidget(new QLabel("Разделить все товары по колличеству числом: "),1,0);
    playwgt1->addWidget(psbxwgt11,1,1);
    playwgt1->addWidget(new QLabel("Исключить товары число которых: "),2,0);
    playwgt1->addWidget(psbxwgt12,2,1);
    playwgt1->addWidget(pcmdwgt1,3,0,1,3);
    wgt1->setLayout(playwgt1);

    //N2
    wgt2 = new QWidget;
    plblwgt2 = new QLabel("На основе обновляющего представления (многотабличного VIEW),\n "
                          "в котором критерий упорядоченности задает пользователь при выполнении;");
    pcmdwgt2 = new QPushButton("Запрос");
    connect(pcmdwgt2,SIGNAL(clicked()),SLOT(slotN2Clicked()));
    QStringList lst;
    lst<<"Name" <<"Supplier" <<"Date" <<"Worker" <<"PhoneOfWorker";
    pcbxwgt11 = new  QComboBox();
    pcbxwgt11->addItems(lst);
    pcbxwgt12 = new  QComboBox();
    lst.clear(); lst<<"возрастанию" <<"убыванию";
    pcbxwgt12->addItems(lst);
    QGridLayout* playwgt2 = new QGridLayout;
    playwgt2->addWidget(plblwgt2,0,0,1,3);
    playwgt2->addWidget(new QLabel("Сортировать поле "),1,0);
    playwgt2->addWidget(pcbxwgt11,1,1);
    playwgt2->addWidget(new QLabel("Сортировать по"),2,0);
    playwgt2->addWidget(pcbxwgt12,2,1);
    playwgt2->addWidget(pcmdwgt2,3,0,1,3);
    wgt2->setLayout(playwgt2);

    //N3
    wgt3 = new QWidget;
    plblwgt3 = new QLabel("Запрос, содержащий коррелированные и некоррелированные подзапросы\n "
                          "в разделах SELECT, FROM и WHERE (в каждом хотя бы по одному)");
    pcmdwgt3 = new QPushButton("Запрос");
    prbwgt31 = new QRadioButton("SELECT");
    prbwgt32 = new QRadioButton("FROM");
    prbwgt33 = new QRadioButton("WHERE");
    QGridLayout* playwgt3 = new QGridLayout;
    playwgt3->addWidget(plblwgt3,0,0);
    playwgt3->addWidget(new QLabel("Запрос 1"),1,0);
    playwgt3->addWidget(prbwgt31,1,1);
    playwgt3->addWidget(new QLabel("Запрос 2"),2,0);
    playwgt3->addWidget(prbwgt32,2,1);
    playwgt3->addWidget(new QLabel("Запрос 3"),3,0);
    playwgt3->addWidget(prbwgt33,3,1);
    playwgt3->addWidget(pcmdwgt3,4,0,1,3);
    wgt3->setLayout(playwgt3);

    //N4
    wgt4 = new QWidget;
    plblwgt4 = new QLabel("Многотабличный запрос, содержащий группировку записей,\n "
                          "агрегативные функции и параметр, используемый в разделе HAVING");
    pcmdwgt4 = new QPushButton("Запрос");
    connect(pcmdwgt4,SIGNAL(clicked()),SLOT(slotN4Clicked()));
    psbxwgt4 = new QSpinBox();
    QGridLayout* playwgt4 = new QGridLayout;
    playwgt4->addWidget(plblwgt4,0,0);
    playwgt4->addWidget(new QLabel("Работники, для которых общая сумма товаров больше "),1,0);
    playwgt4->addWidget(psbxwgt4,1,1);
    playwgt4->addWidget(pcmdwgt4,2,0,1,2);
    wgt4->setLayout(playwgt4);

    //N5
    wgt5 = new QWidget;
    plblwgt5 = new QLabel("Запрос, содержащий предикат ANY, SOME  или ALL");
    pcmdwgt5 = new QPushButton("Запрос");
    pcbxwgt52 = new QComboBox;
    lst.clear(); lst <<"самой большой" << "хотя бы одной";
    pcbxwgt52->addItems(lst);
    pcbxwgt51 = new QComboBox;
    QSqlQuery query;
    if(!query.exec("SELECT DISTINCT Name FROM Items;")) qDebug()<<"Undable to execute query";
    QSqlRecord rec = query.record();
    while(query.next()) pcbxwgt51->addItem(query.value(rec.indexOf("Name")).toString());

    connect(pcmdwgt5,SIGNAL(clicked()),SLOT(slotN5Clicked()));
    QGridLayout* playwgt5 = new QGridLayout;
    playwgt5->addWidget(plblwgt5,0,0);
    playwgt5->addWidget(new QLabel("Товары, колличество которых в поставке больше"),1,0);
    playwgt5->addWidget(pcbxwgt52,1,1);
    playwgt5->addWidget(new QLabel("из поставок товара "),2,0);
    playwgt5->addWidget(pcbxwgt51,2,1);
    playwgt5->addWidget(pcmdwgt5,3,0,1,3);
    wgt5->setLayout(playwgt5);
}


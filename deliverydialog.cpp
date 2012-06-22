#include "deliverydialog.h"

DeliveryDialog::DeliveryDialog(QWidget *parent) :
    QDialog(parent)
{
    this->resize(550,300);
    query = new QSqlQuery;
    rec = new QSqlRecord ;
    //Создание элементв управления
    pLabelS = new QLabel("Supplier:");

    pComboBoxS = new QComboBox;
     if(!query->exec("SELECT Name FROM Suppliers")) qDebug()<<"Undable to execute query";
    *rec = query->record();
    while(query->next()) pComboBoxS->addItem(query->value(rec->indexOf("Name")).toString());


    pcmdS = new QPushButton("AddSupplier...");
    connect(pcmdS,SIGNAL(clicked()),SLOT(slotAddSupplier()));

    pLabelDate = new QLabel("Date:");
    pDateEdit  = new QDateEdit(QDate::currentDate());
    pLabelItem = new QLabel("Items:");
    pTableItem = new QTableWidget(0,3);

    pcmdAddRow = new QPushButton("AddRow");
    connect(pcmdAddRow,SIGNAL(clicked()),SLOT(slotAddRow()));

    pcmdItem = new QPushButton("AddItem...");
    connect(pcmdItem,SIGNAL(clicked()),SLOT(slotAddItem()));

    pcmdWorker=new QPushButton("AddWorker...");
    connect(pcmdWorker,SIGNAL(clicked()),SLOT(slotAddWorker()));

    pcmdSubmit = new QPushButton("Submit");    
    connect(pcmdSubmit, SIGNAL(clicked()),SLOT(accept()));

    pcmdCansel = new QPushButton("Cansel");
    connect(pcmdCansel, SIGNAL(clicked()),SLOT(reject()));


    //Размещение объектв
    ptopLayout = new QGridLayout;
    ptopLayout->addWidget(pLabelS,0,0);
    ptopLayout->addWidget(pComboBoxS,0,1);
    ptopLayout->addWidget(pcmdS,0,2);
    ptopLayout->addWidget(pLabelDate,1,0);
    ptopLayout->addWidget(pDateEdit,1,1,1,2);
    ptopLayout->addWidget(pLabelItem,2,0);
    ptopLayout->addWidget(pTableItem,3,0,4,2);
    ptopLayout->addWidget(pcmdItem,2,2);
    ptopLayout->addWidget(pcmdWorker,3,2);
    ptopLayout->addWidget(pcmdAddRow,6,2);
    ptopLayout->addWidget(pcmdSubmit,7,1);
    ptopLayout->addWidget(pcmdCansel,7,2);
    setLayout(ptopLayout);

    //Таблица товаров
    pTableItem->setHorizontalHeaderLabels(QStringList()<<"Name" <<"Quantity" <<"Worker");
    slotAddRow();
    slotAddRow();


}

void DeliveryDialog::slotAddRow()
{
    QComboBox *pcbx1 = new QComboBox;

    if(!query->exec("SELECT DISTINCT Name FROM Items")) qDebug()<<"Undable to execute query";
    *rec = query->record();
    while(query->next()) pcbx1->addItem(query->value(rec->indexOf("Name")).toString());

    QComboBox *pcbx2 = new QComboBox;
    if(!query->exec("SELECT Name FROM Workers")) qDebug()<<"Undable to execute query";
    *rec = query->record();
    while(query->next()) pcbx2->addItem(query->value(rec->indexOf("Name")).toString());

    int rc = pTableItem->rowCount();
    pTableItem->setRowCount(rc+1);

    pTableItem->setCellWidget(rc,0,pcbx1);
    pTableItem->setCellWidget(rc,1,new QSpinBox);
    pTableItem->setCellWidget(rc,2,pcbx2);

}

void DeliveryDialog::slotAddSupplier()
{
    pSupDialog = new supplierdialog;
    if(pSupDialog->exec()==QDialog::Accepted)
    {
       QSqlQuery query;
       query.prepare("INSERT INTO Suppliers (Name , Address, Telephone, Email) VALUES (:Name , :Address, :Telephone, :Email);");
       query.bindValue(":Name", pSupDialog->GetName());
       query.bindValue(":Address", pSupDialog->GetAddress());
       query.bindValue(":Telephone", pSupDialog->GetTelephone());
       query.bindValue(":Email", pSupDialog->GetEmail());

       if(!query.exec())
           qDebug()<<"Unable to make insert operation";

      // pComboBoxS->addItem(pSupDialog->GetName());
    }
    delete pSupDialog;
}

void DeliveryDialog::slotAddItem()
{
    pItemDialog  = new ItemDialog;

    if(pItemDialog->exec()==QDialog::Accepted)
    {
        QSqlQuery query;
        if(!query.exec("INSERT INTO Items (id_delivery,Name,Quantity,id_Worker) VALUES (0, '" +pItemDialog->GetName()+"' , 0, 0);"))
            qDebug()<<"Unable to make insert operation";

        int rc = pTableItem->rowCount();
        pTableItem->setRowCount(0);
        for(int i=0;i<rc;i++)
            slotAddRow();
    }
    delete pItemDialog;

}

void DeliveryDialog::slotAddWorker()
{
    pWorkDialog = new WorkerDialog;

    if(pWorkDialog->exec()==QDialog::Accepted)
    {
        QSqlQuery query;
        QSqlQuery querySelect;
        query.prepare("INSERT INTO Workers (id_superior, Telephone, Email, Name) VALUES (:id_superior, :Telephone, :Email, :Name);");

        query.bindValue(":Name", pWorkDialog->GetName());
        query.bindValue(":Telephone", pWorkDialog->GetTelephone());
        query.bindValue(":Email", pWorkDialog->GetEmail());

        if(pWorkDialog->GetSuperior()=="Head")
        {
            querySelect.exec("SELECT id_worker FROM Workers;");
            querySelect.last();
            int number = querySelect.value(0).toInt();
            query.bindValue(":id_superior", number+1);
        }
        else
        {
            QString str="SELECT id_worker FROM Workers WHERE Name like '"+pWorkDialog->GetSuperior()+"' ;";
            querySelect.exec(str);
            qDebug()<<str;
            QSqlRecord rec = querySelect.record();
            querySelect.last();
            int number=querySelect.value(rec.indexOf("id_worker")).toInt();
            qDebug()<<number;
            query.bindValue(":id_superior", number);
        }

        if(!query.exec())
            qDebug()<<"Unable to make insert operation";

        int rc = pTableItem->rowCount();
        pTableItem->setRowCount(0);
        for(int i=0;i<rc;i++)
            slotAddRow();
    }
    delete pWorkDialog;
}

QString DeliveryDialog::GetSupliers() const
{
    return pComboBoxS->currentText();
}

QString DeliveryDialog::GetDate() const
{
    return pDateEdit->text();
}

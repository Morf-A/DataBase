#include "deliverydialog.h"

DeliveryDialog::DeliveryDialog(QWidget *parent) :
    QDialog(parent)
{
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
    pTableItem = new QTableWidget(0,2);

    pcmdAddRow = new QPushButton("AddRow");
    connect(pcmdAddRow,SIGNAL(clicked()),SLOT(slotAddRow()));

    pcmdItem = new QPushButton("AddItem...");
    connect(pcmdItem,SIGNAL(clicked()),SLOT(slotAddItem()));

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
    ptopLayout->addWidget(pTableItem,3,0,3,2);
    ptopLayout->addWidget(pcmdItem,3,2);
    ptopLayout->addWidget(pcmdAddRow,5,2);
    ptopLayout->addWidget(pcmdSubmit,6,1);
    ptopLayout->addWidget(pcmdCansel,6,2);
    setLayout(ptopLayout);

    //Таблица товаров
    pTableItem->setHorizontalHeaderLabels(QStringList()<<"Name" <<"Quantity");
    slotAddRow();
    slotAddRow();


}

void DeliveryDialog::slotAddRow()
{
    QComboBox *pcbx1 = new QComboBox;

    if(!query->exec("SELECT Name FROM Items")) qDebug()<<"Undable to execute query";
    *rec = query->record();
    while(query->next()) pcbx1->addItem(query->value(rec->indexOf("Name")).toString());

    int rc = pTableItem->rowCount();
    pTableItem->setRowCount(rc+1);

    pTableItem->setCellWidget(rc,0,pcbx1);
    pTableItem->setCellWidget(rc,1,new QSpinBox);
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
    }
}

void DeliveryDialog::slotAddItem()
{
    pWorkDialog  = new ItemDialog;

    if(pWorkDialog->exec()==QDialog::Accepted)
    {
       qDebug()<<pWorkDialog->GetName();
       qDebug()<<pWorkDialog->GetWorker();

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

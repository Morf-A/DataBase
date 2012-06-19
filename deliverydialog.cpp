#include "deliverydialog.h"

DeliveryDialog::DeliveryDialog(QWidget *parent) :
    QDialog(parent)
{
    //Создание элементв управления
    pLabelS = new QLabel("Supplier:");
    pComboBoxS = new QComboBox;
    pcmdS = new QPushButton("AddSupplier...");
    connect(pcmdS,SIGNAL(clicked()),SLOT(slotAddSupplier()));
    pLabelDate = new QLabel("Date:");
    pDateEdit  = new QDateEdit(QDate::currentDate());
    pLabelItem = new QLabel("Items:");
    pTableItem = new QTableWidget(2,2);
    pcmdAddRow = new QPushButton("AddRow");
    connect(pcmdAddRow,SIGNAL(clicked()),SLOT(slotAddRow()));
    pcmdItem = new QPushButton("AddItem...");
    connect(pcmdItem,SIGNAL(clicked()),SLOT(slotAddItem()));
    pcmdSubmit = new QPushButton("Submit");
    connect(pcmdSubmit, SIGNAL(clicked()),SLOT(accept()));
    pcmdCansel = new QPushButton("Cansel");
    connect(pcmdCansel, SIGNAL(clicked()),SLOT(reject()));

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
    pTableItem->setCellWidget(0,0,new QComboBox);
    pTableItem->setCellWidget(0,1,new QSpinBox);
    pTableItem->setCellWidget(1,0,new QComboBox);
    pTableItem->setCellWidget(1,1,new QSpinBox);


}

void DeliveryDialog::slotAddRow()
{
    int rc = pTableItem->rowCount();
    pTableItem->setRowCount(rc+1);
    pTableItem->setCellWidget(rc,0,new QComboBox);
    pTableItem->setCellWidget(rc,1,new QSpinBox);
}

void DeliveryDialog::slotAddSupplier()
{
    pSupDialog = new supplierdialog;

    if(pSupDialog->exec()==QDialog::Accepted)
    {
       qDebug()<<pSupDialog->GetName();
       qDebug()<<pSupDialog->GetAddress();
       qDebug()<<pSupDialog->GetTelephone();
       qDebug()<<pSupDialog->GetEmail();
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

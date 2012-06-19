#include "itemdialog.h"

ItemDialog::ItemDialog(QWidget *parent) :
    QDialog(parent)
{
    plblName = new QLabel("Name");
    plblWorker  = new QLabel("Worker");

    ptxtName = new QLineEdit;
    ptxtWorker  = new QLineEdit;

    pcmdAddWorker = new QPushButton("AddWorker...");
    connect(pcmdAddWorker,SIGNAL(clicked()),SLOT(slotAddWorker()));
    pcmdSubmit  = new QPushButton("Submit");
    connect(pcmdSubmit,SIGNAL(clicked()),SLOT(accept()));
    pcmdCancel  = new QPushButton("Cancel");
    connect(pcmdCancel,SIGNAL(clicked()),SLOT(reject()));

    ptopLayout =new QGridLayout;

    ptopLayout->addWidget(plblName,0,0); ptopLayout->addWidget(ptxtName,0,1);
    ptopLayout->addWidget(plblWorker,1,0); ptopLayout->addWidget(ptxtWorker,1,1);
    ptopLayout->addWidget(pcmdAddWorker,2,0,1,2);
    ptopLayout->addWidget(pcmdSubmit,3,0); ptopLayout->addWidget(pcmdCancel,3,1);

    setLayout(ptopLayout);

}



void ItemDialog::slotAddWorker()
{
    pWorkDialog = new WorkerDialog;

    if(pWorkDialog->exec()==QDialog::Accepted)
    {
        qDebug()<< pWorkDialog->GetName();
        qDebug()<< pWorkDialog->GetAddress();
        qDebug()<< pWorkDialog->GetSuperior();
    }
    delete pWorkDialog;
}

QString ItemDialog::GetName() const
{
    return ptxtName->text();
}
QString ItemDialog::GetWorker() const
{
    return ptxtWorker->text();
}

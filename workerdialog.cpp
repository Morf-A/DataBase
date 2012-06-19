#include "workerdialog.h"

WorkerDialog::WorkerDialog(QWidget *parent) :
    QDialog(parent)
{
    plblName = new QLabel("Name");
    plblAddress  = new QLabel("Address");
    plblSuperior  = new QLabel("Superior");

    ptxtName = new QLineEdit;
    ptxtAddress  = new QLineEdit;
    ptxtSuperior  = new QLineEdit;

    pcmdSubmit = new QPushButton("Submit");
    connect(pcmdSubmit,SIGNAL(clicked()),SLOT(accept()));
    pcmdCancel = new QPushButton("Cancel");
    connect(pcmdCancel,SIGNAL(clicked()),SLOT(reject()));
    ptopLayout = new QGridLayout;

    ptopLayout = new QGridLayout;

    ptopLayout->addWidget(plblName,0,0); ptopLayout->addWidget(ptxtName,0,1);
    ptopLayout->addWidget(plblAddress,1,0); ptopLayout->addWidget(ptxtAddress,1,1);
    ptopLayout->addWidget(plblSuperior,2,0); ptopLayout->addWidget(ptxtSuperior,2,1);
    ptopLayout->addWidget(pcmdSubmit,3,0); ptopLayout->addWidget(pcmdCancel,3,1);

    setLayout(ptopLayout);
}

QString WorkerDialog::GetName() const
{
    return ptxtName->text();
}
QString WorkerDialog::GetAddress() const
{
    return ptxtAddress->text();
}
QString WorkerDialog::GetSuperior() const
{
    return ptxtSuperior->text();
}

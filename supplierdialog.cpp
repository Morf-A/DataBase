#include "supplierdialog.h"


supplierdialog::supplierdialog(QWidget *parent) :
    QDialog(parent)
{
    //Èםעונפויס
    plblName = new QLabel("Name");
    plblAddress = new QLabel("Address");
    plblTelephone = new QLabel("Telephone");
    plblEmail = new QLabel("Email");

    ptxtName = new QLineEdit;
    ptxtAddress = new QLineEdit;
    ptxtTelephone = new QLineEdit;
    ptxtEmail = new QLineEdit;

    pcmdSubmit = new QPushButton("Submit");
    connect(pcmdSubmit,SIGNAL(clicked()),SLOT(accept()));
    pcmdCancel = new QPushButton("Cancel");
    connect(pcmdCancel,SIGNAL(clicked()),SLOT(reject()));
    ptopLayout = new QGridLayout;

    ptopLayout->addWidget(plblName,0,0); ptopLayout->addWidget(ptxtName,0,1);
    ptopLayout->addWidget(plblAddress,1,0); ptopLayout->addWidget(ptxtAddress,1,1);
    ptopLayout->addWidget(plblTelephone,2,0); ptopLayout->addWidget(ptxtTelephone,2,1);
    ptopLayout->addWidget(plblEmail,3,0); ptopLayout->addWidget(ptxtEmail,3,1);
    ptopLayout->addWidget(pcmdSubmit,4,0); ptopLayout->addWidget(pcmdCancel,4,1);

    setLayout(ptopLayout);

}

QString supplierdialog::GetName() const
{
   return ptxtName->text();
}

QString supplierdialog::GetAddress() const
{
   return ptxtAddress->text();
}

QString supplierdialog::GetTelephone() const
{
   return ptxtTelephone->text();
}

QString supplierdialog::GetEmail() const
{
   return ptxtEmail->text();
}

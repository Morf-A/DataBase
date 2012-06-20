#include "workerdialog.h"
#include <QtSQL>

WorkerDialog::WorkerDialog(QWidget *parent) :
    QDialog(parent)
{
    QSqlQuery *query = new QSqlQuery;
    QSqlRecord *rec = new QSqlRecord;
    plblName = new QLabel("Name");
    plblSuperior  = new QLabel("Superior");
    plblTelephone = new QLabel("Telephone");
    plblEmail = new QLabel("Email");

    ptxtName = new QLineEdit;
    ptxtTelephone  = new QLineEdit;
    ptxtEmail = new QLineEdit;

    pcbxSuperior  = new QComboBox;
    if(!query->exec("SELECT Name FROM Workers")) qDebug()<<"Undable to execute query";
    *rec = query->record();
    while(query->next()) pcbxSuperior->addItem(query->value(rec->indexOf("Name")).toString());
    pcbxSuperior->addItem("Head");

    pcmdSubmit = new QPushButton("Submit");
    connect(pcmdSubmit,SIGNAL(clicked()),SLOT(accept()));
    pcmdCancel = new QPushButton("Cancel");
    connect(pcmdCancel,SIGNAL(clicked()),SLOT(reject()));
    ptopLayout = new QGridLayout;

    ptopLayout = new QGridLayout;

    ptopLayout->addWidget(plblName,0,0); ptopLayout->addWidget(ptxtName,0,1);
    ptopLayout->addWidget(plblTelephone,1,0); ptopLayout->addWidget(ptxtTelephone,1,1);
    ptopLayout->addWidget(plblEmail,2,0); ptopLayout->addWidget(ptxtEmail,2,1);
    ptopLayout->addWidget(plblSuperior,3,0); ptopLayout->addWidget(pcbxSuperior,3,1);
    ptopLayout->addWidget(pcmdSubmit,4,0); ptopLayout->addWidget(pcmdCancel,4,1);

    setLayout(ptopLayout);
}

QString WorkerDialog::GetName() const
{
    return ptxtName->text();
}
QString WorkerDialog::GetTelephone() const
{
    return ptxtTelephone->text();
}

QString WorkerDialog::GetEmail() const
{
    return ptxtEmail->text();
}

QString WorkerDialog::GetSuperior() const
{
    return pcbxSuperior->currentText();
}

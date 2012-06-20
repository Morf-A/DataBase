#include "itemdialog.h"
#include <QtSQL>

ItemDialog::ItemDialog(QWidget *parent) :
    QDialog(parent)
{
    plblName = new QLabel("Name");
    ptxtName = new QLineEdit;

    pcmdSubmit  = new QPushButton("Submit");
    connect(pcmdSubmit,SIGNAL(clicked()),SLOT(accept()));
    pcmdCancel  = new QPushButton("Cancel");
    connect(pcmdCancel,SIGNAL(clicked()),SLOT(reject()));

    ptopLayout =new QGridLayout;

    ptopLayout->addWidget(plblName,0,0); ptopLayout->addWidget(ptxtName,0,1);
    ptopLayout->addWidget(pcmdSubmit,1,0); ptopLayout->addWidget(pcmdCancel,1,1);

    setLayout(ptopLayout);

}


QString ItemDialog::GetName() const
{
    return ptxtName->text();
}

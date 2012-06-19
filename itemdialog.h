#ifndef ITEMDIALOG_H
#define ITEMDIALOG_H

#include <QtGui>
#include <QDialog>
#include "workerdialog.h"

class ItemDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ItemDialog(QWidget *parent = 0);
    QString GetName() const;
    QString GetWorker() const;

private:
    QLabel *plblName;
    QLabel *plblWorker;

    QLineEdit *ptxtName;
    QLineEdit *ptxtWorker;

    QPushButton *pcmdAddWorker;
    QPushButton *pcmdSubmit;
    QPushButton *pcmdCancel;

    QGridLayout *ptopLayout;

    WorkerDialog *pWorkDialog;

public slots:
    void slotAddWorker();

};

#endif // ITEMDIALOG_H

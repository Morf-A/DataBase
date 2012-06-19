#ifndef WORKERDIALOG_H
#define WORKERDIALOG_H

#include<QtGui>
#include <QDialog>

class WorkerDialog : public QDialog
{
    Q_OBJECT
public:
    explicit WorkerDialog(QWidget *parent = 0);
    QString GetName() const;
    QString GetAddress() const;
    QString GetSuperior() const;

private:
    QLabel *plblName;
    QLabel *plblAddress;
    QLabel *plblSuperior;

    QLineEdit *ptxtName;
    QLineEdit *ptxtAddress;
    QLineEdit *ptxtSuperior;

    QPushButton *pcmdSubmit;
    QPushButton *pcmdCancel;

    QGridLayout *ptopLayout;


};

#endif // WORKERDIALOG_H

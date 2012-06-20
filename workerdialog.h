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
    QString GetTelephone() const;
    QString GetSuperior() const;
    QString GetEmail() const;

private:
    QLabel *plblName;
    QLabel *plblTelephone;
    QLabel *plblSuperior;
    QLabel *plblEmail;

    QLineEdit *ptxtName;
    QLineEdit *ptxtTelephone;
    QLineEdit *ptxtEmail;
    QComboBox *pcbxSuperior;

    QPushButton *pcmdSubmit;
    QPushButton *pcmdCancel;

    QGridLayout *ptopLayout;


};

#endif // WORKERDIALOG_H

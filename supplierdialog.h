#ifndef SUPPLIERDIALOG_H
#define SUPPLIERDIALOG_H
#include<QtGui>
#include <QDialog>

class supplierdialog : public QDialog
{
    Q_OBJECT
public:
    explicit supplierdialog(QWidget *parent = 0);
    QString GetName() const;
    QString GetAddress() const;
    QString GetTelephone() const;
    QString GetEmail() const;
private:
    QLabel *plblName;
    QLabel *plblAddress;
    QLabel *plblTelephone;
    QLabel *plblEmail;

    QLineEdit *ptxtName;
    QLineEdit *ptxtAddress;
    QLineEdit *ptxtTelephone;
    QLineEdit *ptxtEmail;

    QPushButton *pcmdSubmit;
    QPushButton *pcmdCancel;

    QGridLayout *ptopLayout;
};

#endif // SUPPLIERDIALOG_H

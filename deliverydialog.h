#ifndef DELIVERYDIALOG_H
#define DELIVERYDIALOG_H
#include <QtGui>
#include <QDialog>
#include "supplierdialog.h"

class DeliveryDialog : public QDialog
{
    Q_OBJECT
public:
    explicit DeliveryDialog(QWidget *parent = 0);
    QString GetDate() const;
    QString GetSupliers() const;

private:
    //�������� ����������
    QLabel *pLabelS; QComboBox *pComboBoxS; QPushButton*pcmdS;
    QLabel* pLabelDate; QDateEdit *pDateEdit;
    QLabel *pLabelItem;
    QTableWidget *pTableItem; QPushButton *pcmdItem;  QPushButton *pcmdAddRow;
    QPushButton *pcmdSubmit; QPushButton *pcmdCansel;

    //����������
    QGridLayout *ptopLayout;

    //�������
    supplierdialog *pSupDialog;

public slots:
    void slotAddRow();
    void slotAddSupplier();
};

#endif // DELIVERYDIALOG_H
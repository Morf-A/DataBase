#ifndef DELIVERYDIALOG_H
#define DELIVERYDIALOG_H
#include <QtGui>
#include <QtSQL>
#include <QDialog>
#include "supplierdialog.h"
#include "itemdialog.h"

class DeliveryDialog : public QDialog
{
    Q_OBJECT
public:
    explicit DeliveryDialog(QWidget *parent = 0);
    QString GetDate() const;
    QString GetSupliers() const;

private:
    //Элементы управления
    QLabel *pLabelS; QComboBox *pComboBoxS; QPushButton*pcmdS;
    QLabel* pLabelDate; QDateEdit *pDateEdit;
    QLabel *pLabelItem;
    QTableWidget *pTableItem; QPushButton *pcmdItem;  QPushButton *pcmdAddRow;
    QPushButton *pcmdWorker;
    QPushButton *pcmdSubmit; QPushButton *pcmdCansel;

    //Размещение
    QGridLayout *ptopLayout;

    //Диалоги
    supplierdialog *pSupDialog;
    ItemDialog *pItemDialog;
    WorkerDialog *pWorkDialog;

    //SQL
    QSqlQuery *query;
    QSqlRecord *rec;

public slots:
    void slotAddRow();
    void slotAddSupplier();
    void slotAddItem();
    void slotAddWorker();
};

#endif // DELIVERYDIALOG_H

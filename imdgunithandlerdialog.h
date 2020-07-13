#ifndef IMDGUNITHANDLERDIALOG_H
#define IMDGUNITHANDLERDIALOG_H

#include <QDialog>
#include <QtWidgets>
#include "container.h"
#include "imdgunit.h"
#include "containerhandlerdialog.h"

static QList<IMDGunit*>             imdgUnitsDialogDataCopy;

namespace Ui {

class ImdgUnitHandlerDialog;
}

class ImdgUnitHandlerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ImdgUnitHandlerDialog(QWidget *parent = nullptr);
    ~ImdgUnitHandlerDialog();



    void setUnnoList(QVector<Container>* containersData, QString idNumber,
                                                         QList<IMDGunit*> &imdgUnitsDialogData);
    void clearListWidget();



private slots:
    void on_listWidget_itemClicked(QListWidgetItem *item);

private:
    Ui::ImdgUnitHandlerDialog *ui;

    void setGroupBoxElements(QWidget *widget, QString element, QString value);

};

#endif // IMDGUNITHANDLERDIALOG_H

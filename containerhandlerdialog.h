#ifndef CONTAINERHANDLERDIALOG_H
#define CONTAINERHANDLERDIALOG_H

#include <QDialog>
#include <QtWidgets>
#include <QAbstractListModel>


#include "container.h"
#include "imdgunithandlerdialog.h"
#include "imdgunit.h"

static QVector<Container>*          containers = nullptr;
static QList<IMDGunit*>             imdgUnitsCopy;
static QList<IMDGunit*>             imdgUnitsDialogData;

namespace Ui {
class ContainerHandlerDialog;
}

class ContainerHandlerDialog : public QDialog
{
    Q_OBJECT




public:
    explicit ContainerHandlerDialog(QWidget *parent = nullptr);

    ~ContainerHandlerDialog();

    void clearListWidget();
    void  setContainerList(QVector<Container>*, QList<IMDGunit*> &imdgUnitsData) const;





private slots:


   // void on_treeWidget_itemClicked(QT  QList<IMDGunit>              objectList;reeWidgetItem *item, int column);


    void on_listWidget_itemClicked(QListWidgetItem *item);

private:

    Ui::ContainerHandlerDialog*  ui;
    QStringListModel             containersModel;
    QStringList                  containerIDList;
    QString str;



    void getContainerData() const;



};

#endif // CONTAINERHANDLERDIALOG_H

#include "imdgunithandlerdialog.h"
#include "ui_imdgunithandlerdialog.h"

ImdgUnitHandlerDialog::ImdgUnitHandlerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ImdgUnitHandlerDialog)
{
    ui->setupUi(this);
    ui->listWidget->clear();
}


ImdgUnitHandlerDialog::~ImdgUnitHandlerDialog()
{
    delete ui;
}


void ImdgUnitHandlerDialog::clearListWidget(){
    ui->listWidget->clear();
}

void ImdgUnitHandlerDialog::setGroupBoxElements(QWidget *widget, QString element, QString value){



}

void ImdgUnitHandlerDialog::setUnnoList(QVector<Container>* containersData,
                                        QString idNumber,
                                        QList<IMDGunit*> &imdgUnitsDialogDataRcvd) {

    ui->label->setText(idNumber);

    int     index = 0;
    int     qty = imdgUnitsDialogDataRcvd.size();

    imdgUnitsDialogDataCopy = imdgUnitsDialogDataRcvd;

    QString str;



    while ((index < qty) ){

         str.append(imdgUnitsDialogDataRcvd.at(index)->getUnitValueOnTag(NetWeight) + "\n");
         ui->listWidget->addItem(imdgUnitsDialogDataRcvd.at(index)->getUnitValueOnTag(UNNo));
         ++index;

    }

   // imdgUnitsDialogData.at(0)->setValueOnIndex(2, "test");
    ui->textBrowser->setText(str);



}

void ImdgUnitHandlerDialog::on_listWidget_itemClicked(QListWidgetItem *item)
{

   //int     imdgUnitsQty = imdgUnits.size();
    int     qty = imdgUnitsDialogDataCopy.size();
    int     index = 0;
    QString strDebug;
    strDebug.append(QString::number(qty) + "  asdsa\n");


    while (index < qty ){

        if (imdgUnitsDialogDataCopy.at(index)->getDagoUNNo().contains(item->text() )){
            strDebug.append(imdgUnitsDialogDataCopy.at(index)->getDataToString());
            break;


        }

        ++index;
    }

    ui->textBrowser->setText(strDebug);
    //imdgUnitsDialogDataCopy.at(index)->setValueOnIndex(2, "-------test--------");

}

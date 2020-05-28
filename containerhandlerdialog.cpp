#include "containerhandlerdialog.h"
#include "ui_containerhandlerdialog.h"



ContainerHandlerDialog::ContainerHandlerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ContainerHandlerDialog)
{
    ui->setupUi(this);
}




ContainerHandlerDialog::~ContainerHandlerDialog()
{
    delete ui;
}


void ContainerHandlerDialog::clearListWidget(){
      ui->listWidget->clear();
}


void ContainerHandlerDialog::setContainerList(QVector<Container> *containersData,
                                              QList<IMDGunit*> &imdgUnitsCopyData) const{

    QList<QTreeWidgetItem>    items;
    QTreeWidgetItem           item;
    int                       containersQty = containersData->size();

    containers = containersData;
    for (int index = 0; index < imdgUnitsCopyData.size();++index){
    imdgUnitsCopy.append(imdgUnitsCopyData.at(index));
    }

    for (int index=0; index < containersQty; ++index){

        ui->listWidget->addItem(containersData->at(index).getContainerIdNumber());


    }


    ui->label->setText("Loaded containers: " + QString::number(containersQty)+
                       " listWIdget = " + QString::number(ui->listWidget->count()));
    QString strDebug;

    for (int index=0; index < imdgUnitsCopyData.size(); ++index){

      strDebug.append(imdgUnitsCopy.at(index)->getDataToString() + "\n");


    }

//    ui->textEdit->setText(strDebug);


}



void ContainerHandlerDialog::getContainerData() const{

}



void ContainerHandlerDialog::on_listWidget_itemClicked(QListWidgetItem *item)
{
    ImdgUnitHandlerDialog imdgUnitHandler;

    QString               eid, strDebug;
    int                   unnoCounter = 0;
    int                   imdgUnitsCopyQty = imdgUnitsCopy.size();
    int                   containersQty = containers->size();
    int                   index = 0;
    int                   indexInner = 0;
    bool                  ok;


    imdgUnitsDialogData.clear();

    while (index < containersQty){

        if (containers->at(index).getContainerIdNumber().contains(item->text())){
            eid = containers->at(index).getContainerEIDNumber();
            //getting qty of imdg units for the container found
            unnoCounter = containers->at(index).getValueOnIndex(5).toInt(&ok, 10);


            while (indexInner < imdgUnitsCopyQty){
                if (imdgUnitsCopy.at(indexInner)->getDagoEID().contains("FE6699B0DC9B4E8191E8C3F34CB3C400")){

                    //for (int i = indexInner; i < (indexInner + unnoCounter); ++i){
                        imdgUnitsDialogData.push_back(imdgUnitsCopy.at(indexInner));

                        strDebug.append(//imdgUnitsCopy.at(indexInner)->getDataToString() + "eid=" +
                                        imdgUnitsCopy.at(indexInner)->getDagoEID() + "::i=" +
                                        QString::number(unnoCounter) + "----\n");
                    //}

                   // break;
                }
                ++indexInner;
            }//end inner while

            break;
        }

        ++index;

    }//end outer while
    strDebug.clear();

    for (int i = 0; i < imdgUnitsCopyQty; ++i){


         strDebug.append(imdgUnitsCopy.at(i)->getDagoEID());
    }


    ui->textEdit->setText(strDebug);

    imdgUnitHandler.clearListWidget();
    imdgUnitHandler.setWindowTitle(item->text());
    imdgUnitHandler.setUnnoList(containers, item->text(), imdgUnitsDialogData);
    imdgUnitHandler.exec();
}

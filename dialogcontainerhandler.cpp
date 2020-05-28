#include "dialogcontainerhandler.h"
#include "ui_dialogcontainerhandler.h"

DialogContainerHandler::DialogContainerHandler(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogContainerHandler)
{
    ui->setupUi(this);
}

DialogContainerHandler::~DialogContainerHandler()
{
    delete ui;

}




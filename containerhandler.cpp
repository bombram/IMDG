#include "containerhandler.h"
#include "ui_containerhandler.h"

containerHandler::containerHandler(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::containerHandler)
{
    ui->setupUi(this);
}

containerHandler::~containerHandler()
{
    delete ui;
}


c

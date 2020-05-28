#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "xmltag.h"
#include "container.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->closeProgram, &QAction::triggered, this, &QCoreApplication::quit);
    connect(ui->actionIMDGUnitHandler, &QAction::triggered, this,&MainWindow::containerHandler);
    connect(ui->actionHow_to_use_it, &QAction::triggered, this, &MainWindow::menuHelpHandler);


}

MainWindow::~MainWindow()
{

    delete containers;
    delete containersCopy;
    delete newImdgUnit;
    delete ui;

}


void MainWindow::on_pushButtonOpen_clicked()
{
    QErrorMessage msg;

    clearAllDataRetreived();

    if (loadCxmlFile()){
        if ( loadTextFile() ) {
            //make a copy of containers bofore they are changed to transfer to containerHandler Dialog

           for(int index=0; index < containers->size(); ++index)
                containersCopy->push_back(containers->at(index));

           fillIMDGUnits();
           updateCounters();
           creatNewCXMLFile();

        }
        else{
            msg.showMessage("No valid IMDG Manifest file has been loaded or file is of incorrect format");
            msg.exec();
        }

    }
    else {
        msg.showMessage("No valid IMDG unit cxml file has been loaded");
        msg.exec();

    }



}


void MainWindow::on_pushButtonBrowse_clicked(){

    QString fileName = QFileDialog::getOpenFileName(this, "Open File","","*.cxml");
    ui->cxmlFileLine->setText(fileName);
    QString fileNameOnly = fileName.section("/", -1);
    int fileNameIndex = fileName.indexOf(fileNameOnly);
    QString newFileName = fileName.left(fileNameIndex) + "Filled_" + fileNameOnly;
    ui->newCXMLFileLine->setText(newFileName);

}


void MainWindow::on_pushButtonBrowse_2_clicked(){

    QString fileName = QFileDialog::getOpenFileName(this,"Open File","","*.txt");
    ui->manifestFileLine->setText(fileName);

}

void MainWindow::clearAllDataRetreived(){
    imdgUnits.clear();
    containers->clear();
    containersCopy->clear();

}

void MainWindow::updateCounters(){

    ui->totalIMDGLabel->setNum(imdgUnits.size());
    ui->totalContLabel->setNum(containers->size());


}

void MainWindow::containerHandler(){

    containerHandlerDialog.clearListWidget();
    containerHandlerDialog.setContainerList(containersCopy, imdgUnits);
    containerHandlerDialog.exec();

}

void MainWindow::menuHelpHandler(){


    helpWindow.setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    helpWindow.showNormal();


}

void MainWindow::fillIMDGUnits(){

    QMap<QString, int>::iterator                containerIter = containersMap.begin();
    QMap<QString, int>::const_iterator          containersIndexIter = containersIndexMap.begin();
    QMap<QString, IMDGunit*>::const_iterator    imdgUnitsIter = imdgUnitsMap.begin();


    QString             containerEID, str;
    QString str3;
    bool yes = false;//debug
    Container           cont;
    QVector<IMDGunit>   newUnits;
    IMDGunit*           pUnit = nullptr;


    int          containersIndex = 0;
    int          imdgUnitsIndex = 0;
    int          imdgIndex = 0;
    int          unnoCounter = 0;
    bool         isNextUnitDifferent = false;
    bool         found = false;
    int          i=0;
    QString      eidDebug;


    for (containerIter; containerIter != containersMap.end()--; ++containerIter){

        containerEID = containerIter.key();
        unnoCounter = containerIter.value();

        containersIndex = containersIndexMap.value(containerEID);//getting container index in Vector
        cont = containers->at(containersIndex);//take container on index to fill in IMDG unit
        imdgUnitsIndex = imdgUnits.indexOf(imdgUnitsMap[containerEID]);//getting imdg unit index in List

        if (imdgUnitsIndex > -1) {
           for (imdgIndex = imdgUnitsIndex; imdgIndex < (imdgUnitsIndex + unnoCounter); ++imdgIndex){
               if  ( (imdgIndex + 1 ) < imdgUnits.size() ) {
                   if (imdgUnits.at(imdgIndex + 1 )->getDagoEID().contains(containerEID)) {
                       isNextUnitDifferent = false;
                   }else isNextUnitDifferent = true;
              }

                found = imdgUnits.at(imdgIndex)->addWeightToIMDGunit(newUnits, cont, unnoCounter, isNextUnitDifferent);
                containers->replace(containersIndex, cont);//replacing container's data with changed

                if (!newUnits.isEmpty()){
                 qDebug()<<"NOT EMPTY";

                    for (int index2 = 0 ; index2 < newUnits.size(); ++index2){
                        newImdgUnit = new IMDGunit(newUnits.at(index2));
                        imdgUnits.insert(imdgIndex + index2 + 1 , newImdgUnit);

                    }
                    newUnits.clear();

                }


           }//end of inner loop (for)
            isNextUnitDifferent = false;
            yes = false;
        }//end of if


    }//end of outer loop (for)




str3.clear();


    for (int index=0; index<imdgUnits.size();index++){
        if (!imdgUnits.at(index)->getUnitValueOnTag(NetWeight).isEmpty()){
                str3.append(imdgUnits.at(index)->getDataToString() + "\n");
        }
    }


  ui->textEdit_2->setPlainText(str3);




}




bool MainWindow::loadCxmlFile(){

    QString fileToOpen;
    fileToOpen = "/home/dmitry/Qt projects/IMDG_filler/tests/IMDG Rotterdam.cxml";//ui->cxmlFileLine->text();


    //"/home/dmitry/IMDG_filler/IMDG MXATM only.cxml";

    //        ui->cxmlFileLine->text();

    //"/home/dmitry/IMDG_filler/tests/IMDG DEBRV no weight.cxml";


    /*
     * Example:
     * "/home/dmitry/IMDG_filler/IMDG DEBRV no weight.cxml"
    */
    if (fileToOpen.isEmpty()) return false;



    QFile inputFileEdi(fileToOpen);
    inputFileEdi.open(QIODevice::ReadOnly);
    QTextStream in(&inputFileEdi);

    QString readLine;

    QVector<QString>        aContainerData;
    Container*              container = nullptr;
    QString                 containerEID;
    bool                    containerFound = false;
    int                     containerCounter = 0;

    QList<QString> aIMDGunitData;
    QList<QString> aIMDGunitDataDebug;
    QString textDebug;



    QString eid;
    bool imdgUnitFound = false;
    int endPos = -1;
    int startPos = -1;



    ui->containerList->clear();


    while(in.readLineInto(&readLine)){

        //read all data of Dago units  available in cxml file

        if  (readLine.contains(xmlTags.getTagOpened(Dago))){ imdgUnitFound = true;}

        if (imdgUnitFound){


            for(int index=DagoID;index<xmlTags.getTagSize();index++){
                if (index == 7) index ++;//to ingone duplicate of EID, which is met in position 7 of TAGNAME Vector
                if (readLine.contains(xmlTags.getTagOpened(xmlTags.getTagEnumName(index)))){
                    aIMDGunitData.append(readLine);
                    continue;
                }
            }



            if (readLine.contains(xmlTags.getTagOpened(EID))){


                startPos = readLine.indexOf(
                            xmlTags.getTagOpened(EID),Qt::CaseInsensitive);
                endPos   = readLine.indexOf(
                            xmlTags.getTagClosed(EID),Qt::CaseInsensitive);


                eid = readLine.mid((startPos+xmlTags.getTagOpened(EID).length()),
                                   ((endPos) -  (startPos+xmlTags.getTagClosed(EID).length())+1));


                aIMDGunitData.append(readLine);
                startPos = -1;
                endPos = -1;


            }

        }


        if  (readLine.contains(xmlTags.getTagClosed(Dago))){
            imdgUnitFound = false;
            newImdgUnit = new IMDGunit(aIMDGunitData);
            imdgUnits.append(newImdgUnit);
            aIMDGunitData.clear();
            if (!imdgUnitsMap.contains(eid)) {
                imdgUnitsMap[eid] = newImdgUnit;
            }


            eid.clear();

        }



        //read all data of containers available in cmxl file
        if (readLine.contains(xmlTags.getTagOpened(Containers),Qt::CaseInsensitive)){
            containerFound = true;

            while (   (in.readLineInto(&readLine)) and
                      (!readLine.contains(xmlTags.getTagClosed(Containers),Qt::CaseInsensitive)) and
                      (!readLine.contains(xmlTags.getTagOpened(ISOType),Qt::CaseInsensitive))  ){

                aContainerData.append(readLine);

            }

        } //end of if

        if (containerFound) {
            container = new Container(aContainerData);
            containers->append(*container);
            containerEID = container->getContainerEIDNumber();
            containersIndexMap[containerEID] = containerCounter++;
            delete container;
            containerFound = false;
            aContainerData.clear();
        }


    }//end of outer while

    inputFileEdi.close();

    QString  str4;

    QMap<QString, int>::const_iterator iter = containersIndexMap.begin();
    for (iter;iter != containersIndexMap.end(); ++iter){

        str4.append(iter.key() + "==" + QString::number(iter.value())
                    + "==cont counter==" + QString::number(containerCounter) +"\n");

    }

// for(int index = 0 ; index < containers->size(); ++index){
//     str4.append(containers->at(index).getDataToString() + "\n");
// }
//ui->textEdit->setText(str4);


qDebug()<<"----------------";


    if (!containers->isEmpty() && (!imdgUnits.isEmpty())){
        return true;
    }

    else
        return false;

}


//getting info from the IMDG manifests and add it to Container units created
bool MainWindow::loadTextFile(){

    QString fileToOpen;
    fileToOpen = "/home/dmitry/Qt projects/IMDG_filler/tests/IMDG Manifest Rotterdam.txt"; //ui->manifestFileLine->text();


    //
    //"/home/dmitry/IMDG_filler/MXATM.txt";

    //"/home/dmitry/IMDG_filler/tests/IMDG DEBRV only.txt";

    /*
     * Example:
     * "/home/dmitry/IMDG_filler/IMDG DEBRV only.txt"
     *
     */

    if (fileToOpen.isEmpty()) return false;


    QFile inputFileTxt(fileToOpen);
    inputFileTxt.open(QIODevice::ReadWrite);
    QTextStream in(&inputFileTxt);


    QString lineRead;
    QString lastLine;


    QRegExp         ifIdNumber("[A-Z]{4}[0-9]{7}\\s-");
    QRegExp         ifIdNumberWrongType("[A-Z]{3}[-]{1}[0-9]{6}\\s-");
    QRegExp         ifUNNo("N[0-9]{4},");
    QRegExp         ifWeight("[K]{1}[g]{1}\\.");
    QRegExp         ifMarPol("[A-T]{6} [K-Z]{9}");
    QRegExp         ifClassDevider("[(][1-9][)]{1}");
    QRegExp         ifPG("I{1,3}");

    const QString   MARPOL = "MARINE POLLUTANT";
    const QString   CLASS =", CLASS";
    const QString   CLASSDEVIDER = "(";
    const QString   WEIGHTDEVIDER = "->";
    const QString   PACKINGGROUP = "PG : ";
    const QString   LIMITEDQTY = "limited quantity";


    QString          containerIdNumber,prevFound="n/a", idTemp;
    QString          unno, netWeight, imdgClass, packingGroup;
    QString          lineReadTemp;
    QVector<QString> unitIMDGdata;

    int              posStart, posEnd;
    int              posStartAdditional;
    int              atIndex = 0;
    int              unnoCounter = 0;

    bool             containerFound = false;
    bool             wrongContainerTypeFound = true;
    bool             isFormatCorrect = false;
    bool             inListContainerFound = false;
    bool             imdgInfoFound = false;
    bool             unnoFound = false;
    bool             marpolFound = false;
    bool             limitedQtyFound = false;
    int              foundCounter = 0;
    bool             atEndF = false;

    Container*       cont = nullptr;
    QMap<QString, int>::const_iterator contIter = containersIndexMap.begin();



    while( in.readLineInto(&lineRead)){

        atEndF = in.atEnd();


        if ( lineRead.contains(ifIdNumber)||lineRead.contains(ifIdNumberWrongType)||(in.atEnd()) ){

            if (atEndF) {
                prevFound = containerIdNumber;

            }

            foundCounter++;
            posStart = lineRead.indexOf(ifIdNumber, Qt::CaseInsensitive);

            if (posStart != -1){
                isFormatCorrect = true;
                containerIdNumber = lineRead.mid(posStart, 11);
                posStart = -1;
                wrongContainerTypeFound = false;
            }else{
                posStartAdditional = lineRead.indexOf(ifIdNumberWrongType, Qt::CaseInsensitive);
                if (posStartAdditional != -1){
                    isFormatCorrect = true;
                    containerIdNumber = lineRead.mid(posStartAdditional, 10);
                    posStartAdditional = -1;
                    wrongContainerTypeFound = true;

                }
            }


            if ( (!containerIdNumber.contains(prevFound)&&imdgInfoFound&&(foundCounter > 1)) || (atEndF) ){

                //compare Idnumber found in manifest and in cxml file
                for(int index=0; index < containers->size();index++){
                    idTemp  = containers->at(index).getContainerIdNumber();
                    if (prevFound.contains(idTemp) ){
                        cont = containers->data();
                        atIndex = index;
                        inListContainerFound = true;
                        containerFound = true;
                    }
                }



                if (inListContainerFound) {
                    cont[atIndex].pushBackData(QString::number(unnoCounter));
                    cont[atIndex].appendImdgContainerData(unitIMDGdata);
                    containersMap[cont[atIndex].getContainerEIDNumber()] = unnoCounter; //additionaly, inserting containerId into Map for further use
                    unnoCounter = 0;
                    inListContainerFound = false;
                    ui->containerList->addItem(
                                prevFound);


                }else{

                    unitIMDGdata.clear();
                }

                for (int index=0; index<unitIMDGdata.size();index++){
                    ui->containerList->addItem( unitIMDGdata.at(index));
                }
                imdgInfoFound = false;
                unitIMDGdata.clear();
                cont = 0;
                unnoFound = false;


            }
        }
        else containerFound = false;



        prevFound = containerIdNumber;

        if (!wrongContainerTypeFound) {

            //looking for UNNo, always consists of 4 digits
            posStart = lineRead.indexOf(ifUNNo,Qt::CaseSensitive);
            if (posStart != -1){
                unno = lineRead.mid(posStart+1,4);
                unitIMDGdata.push_back(unno);
                unnoCounter ++;
                posStart = -1;
                unnoFound = true;
                imdgInfoFound = true;


            }


            if (unnoFound){

                //looking for IMDG CLASS
                posStart = lineRead.indexOf(CLASS, Qt::CaseInsensitive);
                posEnd = lineRead.indexOf(CLASSDEVIDER,posStart,Qt::CaseInsensitive);
                if ((posStart > -1) and (posEnd > -1)){
                    imdgClass = lineRead.mid((posStart + CLASS.size() +1),
                                             (posEnd - 1) -(posStart + CLASS.size() +1) );

                    unitIMDGdata.push_back(imdgClass);
                    imdgClass.clear();
                    posEnd = - 1;
                    posStart = -1;
                }

                //looking for IMDG Packing Group
                posStart = lineRead.indexOf(PACKINGGROUP, Qt::CaseInsensitive);
                if ((posStart > -1)){
                    packingGroup = lineRead.mid((posStart + PACKINGGROUP.size()),3);
                    if ( packingGroup.indexOf(ifPG, Qt::CaseInsensitive) > -1)
                        unitIMDGdata.push_back(packingGroup.trimmed());
                    else   unitIMDGdata.push_back("-");

                    packingGroup.clear();
                    posEnd = - 1;
                    posStart = -1;
                }

                //looking for  MARPOL POLLUTANT, if found unit is Maritime pollutant
                if (lineRead.contains(MARPOL,Qt::CaseSensitive)){
                    marpolFound = true;
                }

                //looking for limited quantity
                if ( lineRead.indexOf(LIMITEDQTY, Qt::CaseInsensitive) > -1 )
                    limitedQtyFound = true;




                //looking for UNNo netto weight. Weight pattern as follows:  -> 1223.000 Kg.
                posStart = lineRead.indexOf(WEIGHTDEVIDER,Qt::CaseInsensitive);
                posEnd = lineRead.indexOf(ifWeight,Qt::CaseInsensitive);
                if ((posStart != -1) and (posEnd != -1)){
                    netWeight = lineRead.mid((posStart+3),(posEnd-1) - (posStart+3));
                    unitIMDGdata.push_back(netWeight);
                    posStart = -1;
                    posEnd = -1;
                    if (marpolFound) unitIMDGdata.push_back("1");
                    else unitIMDGdata.push_back("0");
                    if (limitedQtyFound) unitIMDGdata.push_back("true");
                    else unitIMDGdata.push_back("false");

                    marpolFound = false;
                    limitedQtyFound = false;
                    unnoFound = false;

                }
            }
        }//wrong container type found



    }//end of loop


    //debuggin
    QString str1;

    int i = 0;



    for (int index=0; index<containers->size();++index){
        str1.append(containers->at(index).getDataToString());
    }
    ui->textEdit->setPlainText(str1);

    if (isFormatCorrect && containerFound) return true;
    else
        return false;

}

void MainWindow::creatNewCXMLFile(){

    int pos = -1;

    QString fileToOpen = ui->cxmlFileLine->text();
    QString fileToCreate = ui->newCXMLFileLine->text();// by default is New_ + the name of IMDG Manifest file


    QFile inputFile(fileToOpen);
    inputFile.open(QIODevice::ReadOnly);
    QTextStream in(&inputFile);

    QFile outputFile(fileToCreate);
    outputFile.open(QIODevice::WriteOnly);
    QTextStream out(&outputFile);


    QString readLine;


    bool dagoFound = false;
    bool containersFound = false;
    bool imdgUnitsCopied = false;

    while(in.readLineInto(&readLine)) {


        if (readLine.contains(xmlTags.getTagOpened(Dago))) {
            dagoFound = true;
            readLine.clear();

        }


        if (!dagoFound) out << readLine + "\n";


        if(dagoFound && !imdgUnitsCopied){

            // writing down into the file imdgUnits
            for (int index = 0; index < imdgUnits.size();index++){

            //here we check for the NetWeight existance(allows not to write Unno which is not included into IMDG Manifest) and data of imdg unit is not empty
                if ( !(imdgUnits.at(index)->getDataToString().isEmpty()) &&
                     !(imdgUnits.at(index)->getUnitValueOnTag(NetWeight).isEmpty()) &&
                     (imdgUnits.at(index)->isWeightTagExists())
                    ){

                    out << xmlTags.getTagOpened(Dago) + "\n";
                    out << imdgUnits.at(index)->getDataToString() + "\n";
                    out << xmlTags.getTagClosed(Dago) + "\n";
                    imdgUnitsCopied = true;
                }

            }

        }




        if (readLine.contains("<Containers>")) containersFound = true;
        if (containersFound) out << readLine + "\n";

    }


    inputFile.close();
    outputFile.close();



}


void MainWindow::on_pushButton_clicked()
{
    QString str;

    for (int index=0; index<imdgUnits.size();index++){
        str.append(imdgUnits.at(index)->getDataToString() + "\n");
    }

    ui->textEdit->setText(str);
}

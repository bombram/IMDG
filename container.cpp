#include "container.h"


Container::Container(){};
Container::Container(QVector<QString>containerDataReceived){

    QString unitInfo;

    int startPos;
    int endPos;


    containerData.push_back("<Container>"); // tag <Containers> has not value
    for (int index=0; index < containerDataReceived.size(); index++){


        // enum for EID starts with 1, that is why index + 1
        startPos = containerDataReceived[index].indexOf(
                    xmlTags.getTagOpened(xmlTags.getTagEnumName(index+1)),
                    Qt::CaseInsensitive);



        if (startPos > -1) {
            endPos = containerDataReceived[index].indexOf(
                        xmlTags.getTagClosed(xmlTags.getTagEnumName(index+1)),startPos,
                        Qt::CaseInsensitive);
            unitInfo=containerDataReceived[index].mid(
                        (startPos+xmlTags.getTagOpened(xmlTags.getTagEnumName(index+1)).length()),
                        (endPos-(startPos+xmlTags.getTagClosed(xmlTags.getTagEnumName(index+1)).length()-1)));

            //unitInfo = containerDataReceived.at(index);
            containerData.push_back(unitInfo);



        }


    }
    //tag ISOType is set to null,
    //it is used only to stop reading info about contianer from cxml file
    containerData.push_back("</Container>");

    containerDataReceived.clear();

};



Container::Container(const Container &cont){

    containerData = cont.getData();

}

Container::~Container(){

}



Container & Container::operator=(const  Container &cont){
    if (this!=&cont){


        containerData = cont.getData();
        return *this;
    }
    else
        return *this;


}



QString Container::getDataToString() const{

    QString newText;



    for (int i =0; i < containerData.size(); i++) {
        newText.append(containerData.at(i) + "\n");
    }

    return newText;


}


QString Container::getValueOnIndex(int index) const {

    if (index <= getItemsQty())
        return containerData.at(index);
    else return "-1";


}

QVector<QString> Container::getContainerData() const{
    return containerData;

}


int Container::getItemsQty() const{
    return  containerData.size();

}




int Container::setValueOnIndex(int index, const QString value){


    if (index < getItemsQty()){

        containerData.replace(index, value);
        return 1;
    }
    else return 0;
}

void Container::pushBackData(QString value){

    containerData.push_back(value);
}


// to add data obtained from the manifest to the container
void Container::appendImdgContainerData(QVector<QString> dataReceived) {

    containerData.push_back(xmlTags.getTagOpened(Dago));

    for (int index=0; index < dataReceived.size();index++){
        containerData.append(dataReceived.at(index));
    }

    containerData.push_back(xmlTags.getTagClosed(Dago));




}

void Container::removeAllItems(){

    containerData.clear();

}

void Container::removeAllItems(int from , int to){

    for (int index = from; index <= to;  ++index ){
        containerData.remove(index);
    }

}



QString Container::getContainerIdNumber()const{
    return containerData.at(IdNumber);
}

QString Container::getContainerEIDNumber() const{
    return containerData.at(EID);
}













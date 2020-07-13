#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QFileDialog>
#include <QCloseEvent>
#include <QXmlStreamReader>
#include <QVector>
#include <QRegExp>
#include <QMap>
#include <QList>
#include <QAbstractListModel>
#include <QMessageBox>
#include <QErrorMessage>



#include <container.h>
#include <imdgunit.h>
#include <dialogcontainerhandler.h>
#include <containerhandlerdialog.h>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



private slots:
    void on_pushButtonOpen_clicked();
    void on_pushButtonBrowse_clicked();
    void on_pushButtonBrowse_2_clicked();


private:
    Ui::MainWindow*             ui;
    QList<IMDGunit*>            imdgUnits;
    IMDGunit*                   newImdgUnit = nullptr; //to create a new unit and keep it until application stops
    QMap<QString, IMDGunit*>    imdgUnitsMap;//contains container's EID and
                                            // pointer to the first imdgUnit in the imdgUnits list



    QVector<Container>*         containers = new QVector<Container>;
    QVector<Container>*         containersCopy = new QVector<Container>;
    QMap<QString, int>          containersMap; //contains container's EID and qty of UNNo(imdg units) in container
    QMap<QString, int>          containersIndexMap;//contians container's EID and it's index in the Vector;


    XmlTag                      xmlTags;
    ContainerHandlerDialog      containerHandlerDialog;




    bool loadCxmlFile();
    bool loadTextFile();

    void fillIMDGUnits();
    void creatNewCXMLFile();
    void clearAllDataRetreived();
    void updateCounters();
    void containerHandler();


};





#endif // MAINWINDOW_H


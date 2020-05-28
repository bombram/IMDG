#ifndef DIALOGCONTAINERHANDLER_H
#define DIALOGCONTAINERHANDLER_H

#include <QDialog>

namespace Ui {
class DialogContainerHandler;
}

class DialogContainerHandler : public QDialog
{
    Q_OBJECT

public:
    explicit DialogContainerHandler(QWidget *parent = nullptr);
    ~DialogContainerHandler();

    void deleteInstance(DialogContainerHandler *dialog);

private:
    Ui::DialogContainerHandler *ui;


};

#endif // DIALOGCONTAINERHANDLER_H

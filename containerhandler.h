#ifndef CONTAINERHANDLER_H
#define CONTAINERHANDLER_H

#include <QWidget>

namespace Ui {
class ContainerHandler;
}

class ContainerHandler : public QWidget
{
    Q_OBJECT

public:
    explicit containerHandler(QWidget *parent = nullptr);
    ~containerHandler();

private:
    Ui::containerHandler *ui;

    void showContainerHandler() const;
};

#endif // CONTAINERHANDLER_H

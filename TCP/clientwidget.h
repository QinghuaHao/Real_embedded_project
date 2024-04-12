#ifndef CLIENTWIDGET_H
#define CLIENTWIDGET_H

#include <QWidget>
#include <QTcpSocket>

QT_BEGIN_NAMESPACE
namespace Ui {
class ClientWidget;
}
QT_END_NAMESPACE

class ClientWidget : public QWidget
{
    Q_OBJECT

public:
    ClientWidget(QWidget *parent = nullptr);
    ~ClientWidget();

private slots:
    void on_pushButtonConnect_clicked();

    void on_pushButtonClose_clicked();

    void on_pushButtonOpen_clicked();

    void on_pushButtonCloseDoor_clicked();

private:
    Ui::ClientWidget *ui;
    QTcpSocket *tcpSocket; //通信套件
};
#endif // CLIENTWIDGET_H

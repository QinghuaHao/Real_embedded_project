#include "clientwidget.h"
#include "ui_clientwidget.h"

ClientWidget::ClientWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ClientWidget)
{
    ui->setupUi(this);

    setWindowTitle("Client");
    tcpSocket = nullptr;
    tcpSocket =new QTcpSocket(this);
    connect(tcpSocket,&QTcpSocket::connected,[=]()
    {

    });
    connect(ui->pushButtonOpen, &QPushButton::clicked, this, &ClientWidget::on_pushButtonOpen_clicked);
    connect(ui->pushButtonClose, &QPushButton::clicked, this, &ClientWidget::on_pushButtonClose_clicked);
}

ClientWidget::~ClientWidget()
{
    delete ui;
}

void ClientWidget::on_pushButtonConnect_clicked()
{
    if (nullptr == ui->lineEditIP||nullptr==ui->lineEditPort)
    {

        return;

    }
    //获取IP 端口号
    QString ip = ui->lineEditIP->text();
    quint16 port = ui->lineEditPort->text().toInt();
    tcpSocket->connectToHost(ip,port);

}





void ClientWidget::on_pushButtonClose_clicked()
{
    if(nullptr == tcpSocket)
        return;
    tcpSocket->disconnectFromHost();
    tcpSocket->close();
}


void ClientWidget::on_pushButtonOpen_clicked()
{
    if(tcpSocket == nullptr)
        return;
    // 发送数字1表示开门
    tcpSocket->write("1");
}


void ClientWidget::on_pushButtonCloseDoor_clicked()
{
    if(tcpSocket == nullptr)
        return;
    // 发送数字0表示关门
    tcpSocket->write("0");
}


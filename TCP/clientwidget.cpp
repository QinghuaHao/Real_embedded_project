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
    connect(tcpSocket,&QTcpSocket::connected,this,[=]()
    {
        ui->pushButtonConnect->setEnabled(false);
        ui->textEdit->setText(QString("you have connected to our server"));
    });
    connect(tcpSocket,&QTcpSocket::readyRead,this,[=]()
    {
        QByteArray array = tcpSocket->readAll();
        QString hexString = array.toHex(' ');
        ui->textEdit->append(hexString);
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
    //get ip port
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
    ui->pushButtonConnect->setEnabled(true);
}


void ClientWidget::on_pushButtonOpen_clicked()
{
    if(tcpSocket == nullptr)
        return;
    // open door
    tcpSocket->write("1");
}


void ClientWidget::on_pushButtonCloseDoor_clicked()
{
    if(tcpSocket == nullptr)
        return;
    // close door
    tcpSocket->write("0");
}


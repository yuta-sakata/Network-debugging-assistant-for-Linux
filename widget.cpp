#include "widget.h"
#include "ui_widget.h"

#include<QMessageBox>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    udpSocket=new QUdpSocket(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_openBt_clicked()
{
    if(udpSocket->bind(ui->localPort->text().toUInt())==true){
        QMessageBox::information(this,"提示","成功");
    }else{
         QMessageBox::information(this,"提示","失败");
    }
    connect(udpSocket,SIGNAL(readyRead()),this,SLOT(readyRead_slot()));
}

void Widget::readyRead_slot(){
    while(udpSocket->hasPendingDatagrams()){
        QByteArray array;
        array.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(array.data(),array.size());

        QString buf;
        buf=array.data();
        ui->recvEdit->appendPlainText(buf);
    }
}

void Widget::on_sendBt_clicked()
{
    quint16 port;
    QString sendbuff;
    QHostAddress address;


    address.setAddress(ui->targetIP->text());
    sendbuff=ui->sendEdit->text();
    port=ui->targetPort->text().toUInt();
    udpSocket->writeDatagram(sendbuff.toLocal8Bit().data(),sendbuff.length(),address,port);
}

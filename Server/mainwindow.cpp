#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QtWidgets>
#include <QtNetwork>
#include <QtCore>
#include <iostream>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    ,dto(torpedo,target)
{


    qtimer = new QTimer(this);
    qtimer->setInterval(1000);
    currentClientConnection=new QTcpSocket(this);
    ui->setupUi(this);
    this->setStyleSheet("background-color:  rgb(80,124,80) ;");
    initServer();
    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(connection()));
    connect(qtimer, &QTimer::timeout, this, &MainWindow::sendData);

}
void MainWindow::initServer()
{
    tcpServer = new QTcpServer(this);
    if (!tcpServer->listen()) {
        QMessageBox::critical(this, tr("Torpedo Server"),
                              tr("Unable to start the server: %1.")
                              .arg(tcpServer->errorString()));
        close();
        return;
    }
    QString ipAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    // use the first non-localhost IPv4 address
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
                ipAddressesList.at(i).toIPv4Address()) {
            ipAddress = ipAddressesList.at(i).toString();
            break;
        }
    }
    if (ipAddress.isEmpty())
        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
    ui->IpValue->setText(ipAddress);
    ui->portValue->setText(QString::fromStdString(std::to_string(tcpServer->serverPort())));
}
void MainWindow::connection(){
    currentClientConnection= tcpServer->nextPendingConnection();
    connect(currentClientConnection, &QAbstractSocket::disconnected,
           currentClientConnection, &QObject::deleteLater);
    connect(currentClientConnection, &QIODevice::readyRead, this, &MainWindow::read_input);
    emit connectionDoneSignal();

}
void MainWindow::read_input(){
    std::cout<<"qtimer interval is : "<<qtimer->interval()<<std::endl;
    std::cout<<"qtimer remaining time is : "<<qtimer->remainingTime()<<std::endl;

    double remainingTime = (qtimer->interval()-qtimer->remainingTime());
    if (!currentClientConnection)
        return;
    QDataStream in(currentClientConnection);
    in.setVersion(QDataStream::Qt_4_0);
    QList<double> inputs;
    in >> inputs;

    if(inputs.size()>4){
        target.setX(inputs.at(4));
        target.setY(inputs.at(5));
        target.targetActive=true;
    }
    if (qtimer->isActive() && remainingTime > 0.0 ) {
        qtimer->stop();
        std::cout<<"rem time is : "<<remainingTime<<std::endl;
        // Create a new event loop
        QEventLoop loop;
        QTimer delayTimer;
        delayTimer.setSingleShot(true);
        dto.set_dt(remainingTime/1000.0);
        dto.update();
    }
        torpedo.setSpeed(inputs.at(0));
        target.setSpeed(inputs.at(1));
        target.setCourse(inputs.at(2));
    dto.set_dt(inputs.at(3)/1000.0);
    std::cout<<"this is dt"<<inputs.at(3)<<std::endl;
    qtimer->setInterval(inputs.at(3));
    qtimer->start();
}
void MainWindow::sendData(){
    dto.update();
    std::cout<<"send data debug !!! \n";
    std::cout<<"target x is : "<<target.getX()<<std::endl;
     std::cout<<"torpedo x is : "<<torpedo.getX()<<std::endl;
    qtimer->start();
    if (!currentClientConnection){
        return ;
    }
    QList<double> editValues ;
    //------------------ index 0-3 belongs to torpedo.
    editValues.push_back(torpedo.getX());
    editValues.push_back(torpedo.getY());
    editValues.push_back(torpedo.getTemp_Deg());
    editValues.push_back(torpedo.getSpeed_ms());
    //------------------ index 4-7 belongs to target.
    editValues.push_back(target.getX());
    editValues.push_back(target.getY());
    editValues.push_back(target.getTemp_Deg());
    editValues.push_back(target.getSpeed_ms());
    // 8 belongs to boolean which controls target point in case of get hit.
    target.targetActive ? editValues.push_back(1) : editValues.push_back(0);// 0 -> false , 1 -> true
    editValues.push_back(dto.get_dt());
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);
    out << editValues;
    currentClientConnection->write(block);
}
MainWindow::~MainWindow()
{
    delete ui;
}

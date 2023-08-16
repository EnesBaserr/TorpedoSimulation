#include "mainwindow.h"
#include <QFont>
#include <QVBoxLayout>
#include<iostream>
#include <thread>
#include <chrono>
#include <QDebug>
#include <QtNetwork>
#include <QtWidgets>
#include "CoordinateDrawer.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{        
    flag = true;// to control initialization process of the target object!!!
    ui = new Ui::MainWindow;
    ui->setupUi(this);
    ui->statusLabel->setText("Ready");

    this->setStyleSheet("background-color:  white ;");
    std::cout<<ui->periodEdit_2->text().toStdString()<<std::endl;
    tcpSocket = new QTcpSocket(this);
    QString name = QHostInfo::localHostName();
    if (!name.isEmpty()) {
        ui->hostCombo->addItem(name);
        QString domain = QHostInfo::localDomainName();
        if (!domain.isEmpty())
            ui->hostCombo->addItem(name + QChar('.') + domain);
    }
    if (name != QLatin1String("localhost"))
        ui->hostCombo->addItem(QString("localhost"));
    // find out IP addresses of this machine
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    // add non-localhost addresses
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (!ipAddressesList.at(i).isLoopback())
            ui->hostCombo->addItem(ipAddressesList.at(i).toString());
    }
    // add localhost addresses
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (ipAddressesList.at(i).isLoopback())
            ui->hostCombo->addItem(ipAddressesList.at(i).toString());
    }
    connect(ui->changeButton, &QAbstractButton::clicked, this, &MainWindow::on_pushButton_clicked);
    ui->changeButton->setDefault(true);
    ui->changeButton->setEnabled(false);
    in.setDevice(tcpSocket);
    in.setVersion(QDataStream::Qt_4_0);
    connect(ui->hostCombo, &QComboBox::editTextChanged,
            this, &MainWindow::enable_button);
    connect(ui->portLineEdit, &QLineEdit::textChanged,
            this, &MainWindow::enable_button);
    connect(ui->periodEdit_2,&QLineEdit::textChanged,
            this,&MainWindow::enable_button);
    connect(ui->targetX,&QLineEdit::textChanged,
            this,&MainWindow::enable_button);
    connect(ui->targetY,&QLineEdit::textChanged,
            this,&MainWindow::enable_button);
    connect(ui->targetSpeedEdit,&QLineEdit::textChanged,
            this,&MainWindow::enable_button);
    connect(ui->angleInput,&QLineEdit::textChanged,
            this,&MainWindow::enable_button);
    connect(ui->changeButton, &QAbstractButton::clicked,
            this, &MainWindow::request_data);
    connect(tcpSocket, &QIODevice::readyRead, this, &MainWindow::read_data);

    graphicsScene = new QGraphicsScene(this);
    pointItem =nullptr;
    target_pointItem =nullptr;
    graphicsView = ui->graphicsView;
    int sceneWidth = 5000;  // Adjust the scene size to your preference
    int sceneHeight = 5000; // Adjust the scene size to your preference
    int axisLength = 4000;  // Adjust the axis length to your preference
    QRectF sceneRect(0, 0,30,30);
    graphicsView->setScene(graphicsScene);
    graphicsView->fitInView(sceneRect, Qt::KeepAspectRatio);
    target_vectorItem = nullptr;
    vectorItem=nullptr;
    CoordinateDrawer::drawCoordinate(graphicsScene,vectorItem,sceneWidth
                                    ,sceneHeight,axisLength);

}

void MainWindow::request_data(){
    ui->changeButton->setEnabled(false);
    tcpSocket->connectToHost(ui->hostCombo->currentText(),
                             ui->portLineEdit->text().toInt());

}
void MainWindow :: sendInput(){
    QList<double> input ;
    input.push_back(ui->speedInput->text().toDouble());
    input.push_back(ui->targetSpeedEdit->text().toDouble());
    input.push_back(ui->angleInput->text().toDouble());
    input.push_back(ui->periodEdit_2->text().toDouble()*1000.0);
    if(flag || (ui->checkBox->isChecked() && (int)target_active==0)){
        std::cout<< "test wheter checkbox isChecked()\n";
        input.push_back(ui->targetX->text().toDouble());
        input.push_back(ui->targetY->text().toDouble());
        target_active =1.0;
        flag = false;// target point sets and no longer needed.
    }
    std::cout<<"flag is : "<<flag<<std::endl;
    QByteArray data;
    QDataStream stream(&data, QIODevice::WriteOnly);
    stream.setVersion(QDataStream::Qt_4_0);
    stream <<input;
    tcpSocket->write(data);
}
void MainWindow :: read_data(){
    in.startTransaction();
    QList<double> data;
    in >> data;
    x = data.at(0);
    y = data.at(1);
    deg = data.at(2);
    speed = data.at(3);
    target_x = data.at(4);
    target_y = data.at(5);
    target_angle = data.at(6);
    target_speed = data.at(7);
    target_active = data.at(8);
    int(target_active) == 1 ? ui->statusLabel->setText(tr("%1%2%3%4").arg("Locked on target located at X: ").arg(target_x).arg(" Y: ").arg(QString::number(target_y)))
                            : ui->statusLabel->setText("Free Scan");
    time_period = data.at(9);
    updatePoint();
    if (!in.commitTransaction())
        return;
    ui->changeButton->setEnabled(true);
}
void MainWindow ::enable_button(){
    ui->changeButton->setEnabled(!ui->hostCombo->currentText().isEmpty()
                                 && !ui->portLineEdit->text().isEmpty()
                                 && !ui->periodEdit_2->text().isEmpty()
                                 && !ui->targetX->text().isEmpty()
                                 && !ui->targetY->text().isEmpty());
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::updatePoint()
{
    ui->angleData->setText(QString::number(deg));
    ui->speedData->setText(QString::number(speed));
    ui->periodData->setText(QString::number(time_period));


    CoordinateDrawer::addPoint(x ,y,speed
                  ,deg,vectorItem
                  ,graphicsScene
                  ,pointItem
                  );
    if((int)target_active ==1){
    CoordinateDrawer::addTargetPoint(target_x ,target_y,target_speed
                                     ,target_angle,target_vectorItem
                                     ,graphicsScene
                                     ,target_pointItem
                                     ,ui->targetX->text().toDouble()
                                     ,ui->targetY->text().toDouble());
    }
    else{
        delete target_vectorItem;
        target_vectorItem = nullptr;

        delete target_pointItem;
        target_pointItem=nullptr;
    }
}
void MainWindow::on_pushButton_clicked()
{
    updatePoint();
    ui->changeButton->hide();
}
void MainWindow::on_shutDown_clicked()
{
    close();
}
void MainWindow::on_setButton_clicked()
{
    sendInput();
}

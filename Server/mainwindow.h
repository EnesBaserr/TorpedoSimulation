#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "Torpedo.h"
#include "Target.h"
#include "DTO.h"
#include <QMainWindow>
#include <QDialog>
#include <QString>
#include <QVector>
#include <QTimer>
#include <QTcpServer>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots :
    void read_input();
    void connection();
    void sendData();



signals:
    void connectionDoneSignal();
    void recieved_data();
private :

    void initServer();
    QTcpServer *tcpServer = nullptr;

private:

    QTcpSocket *currentClientConnection;
    Ui::MainWindow *ui;
    Torpedo torpedo;
    Target target;
    DTO dto;


    QTimer* qtimer;
};
#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<QTimer>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QLineEdit>
#include <QPushButton>
//#include "Torpedo.h"
#include <QTimer>
#include <QGraphicsLineItem>
#include <QGraphicsView>
#include "ui_mainwindow.h"
#include <QDataStream>
#include <QTcpSocket>
struct torpedoInput
{
    double speed;
    double angle;
    double period;
};
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void addPoint();
public slots:
    void updatePoint( ); // Function to update the coordinate system with new x and y positions
    void on_pushButton_clicked();
    void request_data();
    void read_data();
    void enable_button();
    void sendInput();

private slots:
    void on_shutDown_clicked();
    void on_setButton_clicked();
private:
    Ui::MainWindow *ui;
    QGraphicsLineItem* vectorItem;
    QGraphicsLineItem* target_vectorItem;
    QTimer *qtimer;
    QTimer *qtimer2;
    double x=0.0;
    double y=0.0 ;
    double speed=0.0;
    double deg=0.0;
    double target_x =0.0;
    double target_y = 0.0;
    double target_angle = 0.0;
    double target_speed = 0.0;
    double target_active = 1.0;
    double time_period=0.0;
    bool flag;
    bool add_target;
    QGraphicsScene *graphicsScene;
    QGraphicsView *graphicsView; // Declare the QGraphicsView member variable
    QGraphicsEllipseItem *pointItem ;
    QGraphicsEllipseItem *target_pointItem ;
    QLineEdit *speedInput; // QLineEdit for speed input
    QLineEdit *angleInput; // QLineEdit for angle input
    /*Torpedo torpedo;*/// To store the ellipse item for update
    QTcpSocket *tcpSocket = nullptr;
    QDataStream in;
    torpedoInput inputData;
};
#endif // MAINWINDOW_H

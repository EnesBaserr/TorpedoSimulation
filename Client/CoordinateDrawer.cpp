#include "CoordinateDrawer.h"

#include <cmath>
#include <iostream>
void CoordinateDrawer::drawCoordinate(QGraphicsScene *&scene,QGraphicsLineItem *&vectorItem
                                      ,int sceneWidth, int sceneHeight, int axisLength) {
    vectorItem = scene->addLine(0,0,0,0,QPen(Qt::red));
    // Horizontal axis
    scene->addLine(-axisLength / 2, 0, axisLength / 2, 0, QPen(Qt::white));
    // Vertical axis
    scene->addLine(0, -axisLength / 2, 0, axisLength / 2, QPen(Qt::white));
    scene->setSceneRect(-sceneWidth / 2, -sceneHeight / 2, sceneWidth, sceneHeight);
    QGraphicsTextItem *xLabel = scene->addText("X", QFont("Arial", 15));
    QGraphicsTextItem *yLabel = scene->addText("Y", QFont("Arial", 15));
    // Position the labels relative to the axes
    xLabel->setPos(axisLength / 2 + 10, 5);
    yLabel->setPos(5, -axisLength / 2 - 20);
    int labelSpacing = 50; // Adjust the label spacing to your preference
    int labelOffset = 1;   // Adjust the label offset to your preference
    for (int x = -axisLength / 2 + labelSpacing; x < axisLength / 2; x += labelSpacing) {
        scene->addLine(x, -axisLength / 2, x, axisLength / 2, QPen(Qt::white));
        QGraphicsTextItem *xLabel = scene->addText(QString::number(x), QFont("Helvetica", 13));
        QFont font = xLabel->font();
        font.setBold(true);
        xLabel->setFont(font);
        xLabel->setPos(x, labelOffset);
    }

    for (int y = -axisLength / 2 + labelSpacing; y < axisLength / 2; y += labelSpacing) {
        scene->addLine(-axisLength / 2, y, axisLength / 2, y, QPen(Qt::white));
        QGraphicsTextItem *yLabel = scene->addText(QString::number(y), QFont("Helvetica", 13));
        QFont font = yLabel->font();
        font.setBold(true);
        yLabel->setFont(font);
        yLabel->setPos(labelOffset, -y);
    }
}
void CoordinateDrawer::addPoint(double x ,double y,double speed
              ,double deg,QGraphicsLineItem *&vectorItem
              ,QGraphicsScene *&scene
              ,QGraphicsEllipseItem *&pointItem
              ){
    if(vectorItem == nullptr){
        vectorItem = scene->addLine(0,0,0,0,QPen(Qt::green));
    }
    else{
        double vectorLength = speed * 5;
        vectorItem->setLine(x, -y, x + std::cos(deg * 3.14/ 180)*vectorLength, -y-std::sin(deg * 3.14/ 180)*vectorLength);
    }
    if (pointItem == nullptr) {

        pointItem = scene->addEllipse(x-5, -(y)-5, 10, 10, QPen(), QBrush(Qt::blue));
    } else {



        pointItem->setRect(x-5 ,-(y )-5, 10, 10);
    }
}
void CoordinateDrawer::addTargetPoint(double target_x, double target_y,double target_speed,
                                      double target_deg,QGraphicsLineItem *&target_vectorItem
                                                     ,QGraphicsScene *&scene
                                      ,QGraphicsEllipseItem *&target_pointItem, double init_X,double init_Y){
    if(target_vectorItem == nullptr){
      // target_vectorItem = scene->addLine(0,0,0,0,QPen(Qt::red));
               target_vectorItem = scene->addLine(init_X-5, -(init_Y)-5,init_X-5, -(init_Y)-5,QPen(Qt::red));
    }
    else{
        double vectorLength = target_speed * 5;
        target_vectorItem->setLine(target_x, -target_y, target_x + std::cos(target_deg * 3.14/ 180)*vectorLength,
                                   -target_y-std::sin(target_deg * 3.14/ 180)*vectorLength);
    }
    if (target_pointItem == nullptr) {


        target_pointItem = scene->addEllipse(init_X-5, -(init_Y)-5, 10, 10, QPen(), QBrush(Qt::black));

    } else {
        target_pointItem->setRect(target_x-5 ,-(target_y )-5, 10, 10);
    }



}

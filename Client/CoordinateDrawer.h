#ifndef COORDINATEDRAWER_H
#define COORDINATEDRAWER_H

#include <QGraphicsScene>
#include <QGraphicsLineItem>

namespace CoordinateDrawer {

     void drawCoordinate(QGraphicsScene *&scene,QGraphicsLineItem *&vectorItem
                               ,int sceneWidth, int sceneHeight, int axisLength)
     ;
     void addPoint(double x, double y,double speed,
                        double deg,QGraphicsLineItem *&vectorItem
                                       ,QGraphicsScene *&scene
                                       ,QGraphicsEllipseItem *&pointItem)
     ;
     void addTargetPoint(double target_x, double target_y,double target_speed,
                         double target_deg,QGraphicsLineItem *&target_vectorItem
                                        ,QGraphicsScene *&scene
                                        ,QGraphicsEllipseItem *&target_pointItem
                                        ,double init_X , double init_Y)
     ;
};


#endif // COORDINATEDRAWER_H

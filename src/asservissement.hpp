///
/// \file asservissement.hpp
/// \brief Fichier header pour asservissement.cpp
/// \author Quentin.OLIVIER
///

#ifndef SERVO
#define SERVO

#include <unistd.h>
#include <cstdlib>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <cmath>
#include <time.h>
#include <list>

#include "../BeagleBoneBlack-GPIO-master/GPIO/GPIOManager.h"
#include "../BeagleBoneBlack-GPIO-master/GPIO/GPIOConst.h"
#include "../eQEP/bbb-eqep.h"

///
/// \class Point asservissement.hpp
/// \brief Classe permettant d'utiliser des points/des tuples
///
class Point{
  private:
    double _x; ///< Membre 1 du tuple/coordonnées en X du point
    double _y; ///< Membre 2 du tuple/coordonnées en Y du point

  public:
    Point();
    Point(double x, double y);
    void setX(double x){this->_x=x;}
    void setY(double y){this->_y=y;}
    void set(double x, double y){
      this->_y=y;
      this->_x=x;
    }
    double getX(){return this->_x;}
    double getY(){return this->_y;}
    double dist(Point &cible);
};

Point mgi(Point &posEffecteur);
int reach_point(Point &target, Point &posInit);
int follow_path(std::list<Point> path, Point &posInit);
Point pid(Point &error, Point &integral, Point &erroPreced, double dt);
void set_speed(Point speeds);


#endif


#include "asservissement.hpp"
#include "BBBexample.hpp"

#define _USE_MATH_DEFINES
#define TIMESTEP 0.5 //En secondes
#define REDUC (10.0/19.0)
#define MAX_SPEED 6680

//#include "BBB-eQEP-master/src/bbb-eqep.cpp"
//Valeurs bornes : x(0,9), y(3, 14)

using std::cout;
using std::endl;
///using namespace BBB;

///
/// \fn Point::Point()
/// \brief Constructeur de la classe Point
///
Point::Point(){
  this->_x=0;
  this->_y=0;
}

///
/// \fn Point::Point(double x, double y)
/// \brief Constructeur de la classe Point
/// \param[in] x Membre 1 du tuple Point
/// \param[in] y Membre 2 du tuple Point
///
Point::Point(double x, double y){
  this->_x=x;
  this->_y=y;
}

///
/// \fn Point::dist(Point &cible)
/// \brief Calcule la distance entre le point considere et le point cible
/// \param[in] cible Point cible
///
double Point::dist(Point &cible){
  return sqrt((this->_y-cible.getY())*(this->_y-cible.getY())+(this->_x-cible.getX())*(this->_x-cible.getX()));
}

///
/// \fn Point mgi(Point &posEffecteur)
/// \brief Constructeur de la classe Point
/// \param[in] posEffecteur Le point desire que l'effecteur doit atteindre, en coordonnees cartesiennes d'apres le repere enonce dans le wiki
/// \param[out] Point Le tuple d'angles des moteurs correspondant
///
Point mgi(Point &posEffecteur){
  //Valeurs physiques du modele
  double a=0.065;
  double b=0.08;
  //double c=0.015;
  double dx=0.012;
  Point og(-dx/2,0);
  Point od(dx/2,0);

  double y=posEffecteur.getY();
  double x=posEffecteur.getX();
  Point effecteur(x,y);

  double distg=effecteur.dist(og);
  double distd=effecteur.dist(od);

  double thetag=atan2(y,x-og.getX());
  double thetad=atan2(y,x-od.getX());

  //Test fonctionnel precedent non optimise
  /*double betag=acos(( (x-og.getX())*(x-og.getX()) + y*y - a*a - b*b)/(2*a*b));
  double betad=acos(( (x-od.getX())*(x-od.getX()) + y*y - a*a - b*b)/(2*a*b));

  double phig=acos((a + b*cos(betag))/distg);
  double phid=acos((a + b*cos(betad))/distd);*/

  double phig=acos((a*a + distg*distg - b*b)/(2*a*distg));
  double phid=acos((a*a + distd*distd - b*b)/(2*a*distd));

  return Point(thetag+phig,thetad-phid);
}

double val_abs(double val){
  if(val<0){
    return -val;
  }
  else{
    return val;
  }
}


///
/// \fn int reach_point(Point &target, Point &PosInit)
/// \brief Fonction permettant d'atteinde le point desire
/// \param[in] target Le tuple d'angles des moteurs a atteindre
/// \param[in] posInit Le tuple d'angles des moteurs initial au démarrage du programme
/// \param[out] int Une valeur d'erreur
///
int reach_point(Point &target, Point &posInit){
  cout<<"Starting reach_point..."<<endl;
  Point angleToReach=mgi(target);
  cout<<"Angle a atteindre ="<<angleToReach.getX()<<", "<<angleToReach.getY()<<endl;
  usleep(1000000);
  //cout<<"Angle :\nAlpha :"<<angleToReach.getX()<<", Beta :"<<angleToReach.getY()<<endl;
  Point angleCurrent(read_eqep(1,posInit),read_eqep(2,posInit));
  Point integ(0,0);

  //Calcul diff entre angles
  Point diff(angleToReach.getX()-angleCurrent.getX(),angleToReach.getY()-angleCurrent.getY());
  Point diffPreced(angleToReach.getX()-angleCurrent.getX(),angleToReach.getY()-angleCurrent.getY());
  //PID ici ?
  Point commande = pid(diff, integ, diffPreced, TIMESTEP);

  //Calcul vitesse necessaire
  Point speeds(commande.getX()*60/(2*M_PI),commande.getY()*60/(2*M_PI));

  clock_t chronoPreced = clock();
  bool reached=false;

  while(!reached){
    //VERIF QUE LE POINT N'A PAS ETE ATTEINT
    //cout<<"ON A PAS ATTEINT LE POINT...."<<endl;

    angleCurrent.set(read_eqep(1,posInit),read_eqep(2,posInit));
    //cout<<"Angle courant ="<<angleCurrent.getX()<<", "<<angleCurrent.getY()<<endl;
    diff.set(angleToReach.getX()-angleCurrent.getX(),angleToReach.getY()-angleCurrent.getY());
    //cout<<"Diff ="<<diff.getX()<<", "<<diff.getY()<<endl;
    bool angle1= (val_abs(diff.getX())<0.1 && val_abs(diffPreced.getX())<0.1);
    bool angle2= (val_abs(diff.getY())<0.1 && val_abs(diffPreced.getY())<0.1);
    double dt=clock()-chronoPreced;
    commande=pid(diff, integ, diffPreced, dt);
    //cout<<"Commande ="<<commande.getX()<<", "<<commande.getY()<<endl;
    speeds.set(commande.getX()*60/(2*M_PI*TIMESTEP),commande.getY()*60/(2*M_PI*TIMESTEP));
    set_speed(speeds);

    chronoPreced=clock();

    //usleep(100000);


    if(angle1 && angle2){
      reached = true;
    }

  }
  return 1;

}

///
/// \fn Point pid(Point &error, Point &integral, Point &errorPreced, double dt)
/// \brief Fonction permettant d'asservir le moteur avec un correcteur pid
/// \param[in] error Le tuple d'erreur angulaire courante entre la position des moteurs et la position desiree
/// \param[in] integral Le tuple d'erreur angulaire courante entre la position des moteurs et la position desiree
/// \param[in] errorPreced Le tuple d'erreur angulaire precedent entre la position des moteurs et la position desiree
/// \param[in] dt Intervalle de temps entre les deux mesures
/// \param[out] Point Les commandes a envoyer a chaque moteur
///
Point pid(Point &error, Point &integral, Point &errorPreced, double dt){
  Point Kp(100,100);
  Point Kd(10,10);
  Point Ki(0,0);
  Point max(2,2);
  Point min(-2,-2);

  // Proportional term
  Point Pout(Kp.getX() * error.getX(), Kp.getY() * error.getY());

  // Integral term

  dt = (clock()-dt)/CLOCKS_PER_SEC;
  integral.set(integral.getX() + error.getX() * dt, integral.getY() + error.getY() * dt);
  Point Iout(Ki.getX() * integral.getX(), Ki.getY() * integral.getY());

  // Derivative term
  Point derivative((error.getX() - errorPreced.getX()) / dt, (error.getY() - errorPreced.getY()) / dt);
  Point Dout(Kd.getX() * derivative.getX(), Kd.getY() * derivative.getY());

  // Calculate total output
  Point output(Pout.getX() + Iout.getX() + Dout.getX(), Pout.getY() + Iout.getY() + Dout.getY());

  // Restrict to max/min
  if( output.getX() > max.getX() )
    output.setX(max.getX());
  else if( output.getX() < min.getX() )
    output.setX(min.getX());

  if( output.getY() > max.getY() )
    output.setY(max.getY());
  else if( output.getY() < min.getY() )
    output.setY(min.getY());

  // Save error to previous error
  errorPreced.set(error.getX(), error.getY());

	return output;
}

///
/// \fn void set_speed(Point speeds)
/// \brief Fonction permettant d'envoyer les vitesses desirees en rpm au moteur
/// \param[in] speeds Le tuple des vitesses a communiquer au moteur
///
void set_speed(Point speeds){
  double temp = MAX_SPEED * REDUC;
  double coef = 100 / temp;
  if(speeds.getX()>0){
    write_duty_ns(1,std::min(PERIOD,int((speeds.getX()*coef)*PERIOD)));
    sens_rotation(1,1);
  }
  else{
    write_duty_ns(1,std::min(PERIOD,int((-speeds.getX()*coef)*PERIOD)));
    sens_rotation(1,0);
  }
  if(speeds.getY()>0){
    write_duty_ns(2,std::min(PERIOD,int((speeds.getY()*coef)*PERIOD)));
    sens_rotation(2,1);
  }
  else{
    write_duty_ns(2,std::min(PERIOD,int((-speeds.getY()*coef)*PERIOD)));
    sens_rotation(2,0);
  }

}

int follow_path(std::list<Point> path, Point &PosInit){
  while(path.size() != 0){
    reach_point(path.front(), PosInit);
    path.pop_front();
  }
  return 1;
}

/*int main(){
  Point one(1.0,1.0);
  Point second(2.0,2.0);
  cout<<"Distance = "<<one.dist(second)<<endl;

  Point test(0,0.1);
  Point res=mgi(test);
  cout<<"Angle :\nAlpha :"<<res.getX()<<", Beta :"<<res.getY()<<endl;

}
*/

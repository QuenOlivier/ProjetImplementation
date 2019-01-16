#include "BBBexample.hpp"
#include "asservissement.hpp"

using std::cout;
using std::endl;
using namespace BBB;

///
/// \fn Point pid(Point &error, Point &integral, Point &errorPreced, double dt)
/// \brief Fonction permettant d'asservir le moteur avec un correcteur pid
/// \param[in] error Le tuple d'erreur angulaire courante entre la position des moteurs et la position desiree
/// \param[in] integral Le tuple d'erreur angulaire courante entre la position des moteurs et la position desiree
/// \param[in] errorPreced Le tuple d'erreur angulaire precedent entre la position des moteurs et la position desiree
/// \param[in] dt Intervalle de temps entre les deux mesures
/// \param[out] Point Les commandes a envoyer a chaque moteur
///
Point read_eqep_init(){
  std::ifstream eqep_folder_m1;
  eqep_folder_m1.open("/sys/devices/ocp.3/48300000.epwmss/48300180.eqep/position");

  std::ifstream eqep_folder_m2;
  eqep_folder_m2.open("/sys/devices/ocp.3/48304000.epwmss/48304180.eqep/position");


  //std::string copy_eqep;
  int copy_eqep1;
  int copy_eqep2;
  eqep_folder_m1 >> copy_eqep1;
  eqep_folder_m2 >> copy_eqep2;
  cout<<"posInit1 : "<< copy_eqep1<<endl;
  cout<<"posInit2 : "<< copy_eqep2<<endl;

  //Lecture encodeur
  return Point(copy_eqep1,copy_eqep2);
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
double read_eqep(int moteur, Point &posInit){
  if(moteur == 1){
    std::ifstream eqep_folder;
    eqep_folder.open("/sys/devices/ocp.3/48300000.epwmss/48300180.eqep/position");

    //std::string copy_eqep;
    int copy_eqep;
    eqep_folder >> copy_eqep;
    //double eqep = copy_eqep/(360*4);

    double pos = copy_eqep - posInit.getX();
    double posTrue = ANGLE_M1 + 10*pos/(360*4)*2*M_PI/19;

    /*cout<<"Moteur 1 "<<endl;
    cout<<"pos (brut): "<< pos<<endl;
    cout<<"pos : "<< pos/(360*4)*2*M_PI<<endl;
    cout<<"posTrue: "<< posTrue<<"\n"<<endl;

    usleep(500000);*/
    return posTrue;
  }
  else if(moteur == 2){

    std::ifstream eqep_folder;
    eqep_folder.open("/sys/devices/ocp.3/48304000.epwmss/48304180.eqep/position");

    //std::string copy_eqep;
    int copy_eqep;
    eqep_folder >> copy_eqep;
    //double eqep = copy_eqep/(360*4);

    double pos = copy_eqep - posInit.getY();
    double posTrue = ANGLE_M2 + 10*pos/(360*4)*2*M_PI/19;

    /*cout<<"Moteur 2 "<<endl;
    //cout<<"copy eqep : "<< copy_eqep<<endl;                   // -23059574
    //cout<<"posInit : "<< posInit_M2<<endl;
    cout<<"pos (brut): "<< pos<<endl;
    cout<<"pos : "<< pos/(360*4)*2*M_PI<<endl;
    cout<<"posTrue (rad): "<< posTrue<<"\n"<<endl;

    usleep(500000);*/
    return posTrue;
  }
  else{
    cout<<"Mauvais numéro de moteur"<<endl;
    return -1;
  }

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
void write_period_ns(int moteur, int p){
  if(moteur ==1){
    char buffer[50];
    char buffer2[200] = "echo ";
    char buffer3[100] = " > /sys/class/pwm/pwm5/period_ns";
    int n;

    n=sprintf(buffer,"%d",p);
    for(int i =0; i<n;i++){
      buffer2[5+i] = buffer[i];
    }
    for(int j=0;j<35;j++){  //utiliser sprintf pour avoir la longueur !!!
      buffer2[5+n+j] = buffer3[j];
    }
    cout<<"buffer :" << buffer2 <<endl;
    std::system(buffer2);
  }
  else if(moteur ==2){
    char buffer[50];
    char buffer2[200] = "echo ";
    char buffer3[100] = " > /sys/class/pwm/pwm6/period_ns";
    int n;

    n=sprintf(buffer,"%d",p);
    for(int i =0; i<n;i++){
      buffer2[5+i] = buffer[i];
    }
    for(int j=0;j<35;j++){  //utiliser sprintf pour avoir la longueur !!!
      buffer2[5+n+j] = buffer3[j];
    }
    cout<<"buffer :" << buffer2 <<endl;
    std::system(buffer2);
  }
  else{
    cout<<"Mauvais numéro de moteur"<<endl;
  }
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
void write_duty_ns(int moteur, int d){
  if(moteur == 1){
    char buffer[50];
    char buffer2[200] = "echo ";
    char buffer3[100] = " > /sys/class/pwm/pwm5/duty_ns";
    int n;

    n=sprintf(buffer,"%d",d);
    for(int i =0; i<n;i++){
      buffer2[5+i] = buffer[i];
    }
    for(int j=0;j<33;j++){  //utiliser sprintf pour avoir la longueur !!!
      buffer2[5+n+j] = buffer3[j];
    }
    cout<<"buffer :" << buffer2 <<endl;
    std::system(buffer2);
  }
  else if(moteur == 2){
    char buffer[50];
    char buffer2[200] = "echo ";
    char buffer3[100] = " > /sys/class/pwm/pwm6/duty_ns";
    int n;

    n=sprintf(buffer,"%d",d);
    for(int i =0; i<n;i++){
      buffer2[5+i] = buffer[i];
    }
    for(int j=0;j<33;j++){  //utiliser sprintf pour avoir la longueur !!!
      buffer2[5+n+j] = buffer3[j];
    }
    cout<<"buffer :" << buffer2 <<endl;
    std::system(buffer2);
  }
  else{
    cout<<"Mauvais numéro de moteur"<<endl;
  }
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
void set_run(){
  char buffer[50];
  char buffer2_m1[200] = "echo ";
  char buffer2_m2[200] = "echo ";
  char buffer3_m1[100] = " > /sys/class/pwm/pwm5/run";
  char buffer3_m2[100] = " > /sys/class/pwm/pwm6/run";
  int n;

  n=sprintf(buffer,"%d",1);
  for(int i =0; i<n;i++){
    buffer2_m1[5+i] = buffer[i];
    buffer2_m2[5+i] = buffer[i];
  }
  for(int j=0;j<29;j++){  //utiliser sprintf pour avoir la longueur !!!
    buffer2_m1[5+n+j] = buffer3_m1[j];
    buffer2_m2[5+n+j] = buffer3_m2[j];
  }
  cout<<"buffer :" << buffer2_m1 <<endl;
  cout<<"buffer :" << buffer2_m2 <<endl;
  std::system(buffer2_m1);
  std::system(buffer2_m2);
}

// Run à 0
void reset_run(){
  char buffer[50];
  char buffer2_m1[200] = "echo ";
  char buffer2_m2[200] = "echo ";
  char buffer3_m1[100] = " > /sys/class/pwm/pwm5/run";
  char buffer3_m2[100] = " > /sys/class/pwm/pwm6/run";
  int n;

  n=sprintf(buffer,"%d",0);
  for(int i =0; i<n;i++){
    buffer2_m1[5+i] = buffer[i];
    buffer2_m2[5+i] = buffer[i];
  }
  for(int j=0;j<29;j++){  //utiliser sprintf pour avoir la longueur !!!
    buffer2_m1[5+n+j] = buffer3_m1[j];
    buffer2_m2[5+n+j] = buffer3_m2[j];
  }
  cout<<"buffer :" << buffer2_m1 <<endl;
  cout<<"buffer :" << buffer2_m2 <<endl;
  std::system(buffer2_m1);
  std::system(buffer2_m2);

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
void sens_rotation(int moteur, int sens){
  if(moteur == 1){
    if(sens==0){
      std::system("echo 0 > /sys/devices/virtual/gpio/gpio66/value");
    }
    else if(sens ==1){
      std::system("echo 1 > /sys/devices/virtual/gpio/gpio66/value");
    }
    else{
      cout<<"Sens invalide (saisir 0 pour trigo ou 1)"<<endl;
    }
  }
  else if(moteur == 2){
    if(sens==0){
      std::system("echo 0 > /sys/devices/virtual/gpio/gpio67/value");
    }
    else if(sens ==1){
      std::system("echo 1 > /sys/devices/virtual/gpio/gpio67/value");
    }
    else{
      cout<<"Sens invalide (saisir 0 pour trigo ou 1)"<<endl;
    }
  }
  else{
    cout<<"Numéro de moteur invalide (saisir 1 ou 2)"<<endl;
  }
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
void initialisation_pins(){

  std::system("config-pin overlay cape-universaln");


  //Moteur 1
  std::system("config-pin P9.27 qep" );
  std::system("config-pin P9.92 qep" );
  std::system("config-pin P8.19 pwm" );   //E1
  std::system("config-pin P8.7 output");  //(gpio66) pour commander le sens de rotation //M1
  std::system("echo 5 > /sys/class/pwm/export");

  //Moteur 2
  std::system("config-pin P8.11 qep" ); //Pour Pauline : fil jaune
  std::system("config-pin P8.12 qep" ); //Pour Pauline : fil bleu
  std::system("config-pin P8.13 pwm" );   //E2
  std::system("config-pin P8.8 output");   //(gpio67) pour commander le sens de rotation //M2
  std::system("echo 6 > /sys/class/pwm/export");




}













//Compilation
//g++ BeagleBoneBlack-GPIO-master/GPIO/GPIOConst.cpp  BeagleBoneBlack-GPIO-master/GPIO/GPIOManager.cpp BBBexample.cpp -o BBBexample


// 3674050@pc4139:/nfs/home/sasl/eleves/rob/3674050/ProjetImplementation$ scp BBBexample 3674050@134.157.104.139:debian@192.168.7.2


//scp BBBexample debian@192.168.7.2:~/


/*Pour allumer et eteindre une led à la main depuis le terminal de la beaglebone :

dans sys/class/gpio : echo 66 > export    (avec 66 le numero du GPIO qui nous interesse)
dans sys/class/gpio/gpio66 : echo "out" > direction   (pour dire que l'on veut que ce gpio soit une sortie)
dans sys/class/gpio/gpio66 : echo 1 > value   (pour allumer la led)
dans sys/class/gpio/gpio66 : echo 0 > value   (pour éteindre la led)


Pour un encodeur. Brancher le canal A de l'encodeur au pin P8_12 (EQEP2A_in en mode 4). Brancher le canal B de l'encodeur au Pin P8_11 (EQEP2B_in en mode 4).

Pour passer un pin en mode eqep
config-pin overlay cape-universaln
config-pin P8.11 qep (si le pin 8.11)

chemin des pinumx : /sys/devices/ocp.3/

*/


/*
Encodeur test :
valeur 1 :  105117929
valeur 2 :  105117929
valeur 3 : 3196839520

*/





//to do
/*
write_pwm()
read_qep()

*/








//Checker la commande resync au lieu de scp !!

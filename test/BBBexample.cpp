#include "BeagleBoneBlack-GPIO-master/GPIO/GPIOManager.h"
#include "BeagleBoneBlack-GPIO-master/GPIO/GPIOConst.h"
#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include<stdio.h>
#include <string>
#include <math.h>

#include "BBB-eQEP-master/src/bbb-eqep.cpp"


#include <fstream>      // std::ifstream


using std::cout;
using std::endl;
using namespace BBB;

#define MOTOR_TWO 2
int posInit=0;

// Retourne la pos brute  du moteur
double read_eqep_init(){
  std::ifstream eqep_folder;
  eqep_folder.open("/sys/devices/ocp.3/48304000.epwmss/48304180.eqep/position");

  //std::string copy_eqep;
  int copy_eqep;
  eqep_folder >> copy_eqep;
  cout<<"posInit : "<< copy_eqep<<endl;
  return copy_eqep; 

}

// Retourne la pos en radians  du moteur
double read_eqep(){ 
  std::ifstream eqep_folder;
  eqep_folder.open("/sys/devices/ocp.3/48304000.epwmss/48304180.eqep/position");

  //std::string copy_eqep;
  int copy_eqep;
  eqep_folder >> copy_eqep;
  //double eqep = copy_eqep/(360*4);

  double pos = copy_eqep - posInit;

  cout<<"pos (brut): "<< pos<<endl;
  cout<<"pos (nb tours): "<< pos/(360*4)<<endl;
  cout<<"pos (rad): "<< pos/(360*4)*2*M_PI<<"\n"<<endl;

  return pos/(360*4)*2*M_PI;

}

// Ecriture period_ns
void write_period_ns(int p){
  char buffer[50];
  char buffer2[200] = "echo ";
  char buffer3[100] = " > /sys/class/pwm/pwm5/period_ns";
  int n;

  n=sprintf(buffer,"%d",p);
  for(int i =0; i<n;i++){
    buffer2[5+i] = buffer[i];
  }
  int c=0;
  for(int j=0;j<35;j++){  //utiliser sprintf pour avoir la longueur !!!
    buffer2[5+n+j] = buffer3[j];
  }
  cout<<"buffer :" << buffer2 <<endl;
  std::system(buffer2);

}

// Ecriture duty_ns
void write_duty_ns(int d){
  char buffer[50];
  char buffer2[200] = "echo ";
  char buffer3[100] = " > /sys/class/pwm/pwm5/duty_ns";
  int n;

  n=sprintf(buffer,"%d",d);
  for(int i =0; i<n;i++){
    buffer2[5+i] = buffer[i];
  }
  int c=0;
  for(int j=0;j<33;j++){  //utiliser sprintf pour avoir la longueur !!!
    buffer2[5+n+j] = buffer3[j];
  }
  cout<<"buffer :" << buffer2 <<endl;
  std::system(buffer2);

}

// Run à 1
void set_run(){
  char buffer[50];
  char buffer2[200] = "echo ";
  char buffer3[100] = " > /sys/class/pwm/pwm5/run";
  int n;

  n=sprintf(buffer,"%d",1);
  for(int i =0; i<n;i++){
    buffer2[5+i] = buffer[i];
  }
  int c=0;
  for(int j=0;j<29;j++){  //utiliser sprintf pour avoir la longueur !!!
    buffer2[5+n+j] = buffer3[j];
  }
  cout<<"buffer :" << buffer2 <<endl;
  std::system(buffer2);

}

// Run à 0
void reset_run(){
  char buffer[50];
  char buffer2[200] = "echo ";
  char buffer3[100] = " > /sys/class/pwm/pwm5/run";
  int n;

  n=sprintf(buffer,"%d",0);
  for(int i =0; i<n;i++){
    buffer2[5+i] = buffer[i];
  }
  int c=0;
  for(int j=0;j<29;j++){  //utiliser sprintf pour avoir la longueur !!!
    buffer2[5+n+j] = buffer3[j];
  }
  cout<<"buffer :" << buffer2 <<endl;
  std::system(buffer2);

}




int main(int argc, char const *argv[]) {

  int eqep_num;
  uint32_t eqep_pos =0;

  if(argc < 2)
  {
    cout << "Usage: " << argv[0] << " 0|1|2" << endl;
    cout << "Requires the number for which eQEP to open\n";
    return 1;
  }
  if (strtol(argv[1],NULL,0) >= 0 && strtol(argv[1],NULL,0) <= 2) {
    eqep_num = strtol(argv[1],NULL,0);
  } 
  else {
    cout << "Try again." << endl;
    return 1;
  }

  std::system("config-pin overlay cape-universaln");
  std::system("config-pin P8.11 qep" );
  std::system("config-pin P8.12 qep" );
  std::system("config-pin P8.19 pwm" );
  
  eQEP eqep(eqep_num);

  //Lecture encodeur
  posInit = read_eqep_init(); // Stockage de la pos init brute

  //on va utiliser la pin P8_7 pour commander le sens de rotation du moteur
  std::system("config-pin P8.7 output");
  
  //std::system("echo 1 > "); //1 : sens anti-trigonometrique vu du dessus du moteur ; et 0 : sens trigo
  
 //Ecriture period, duty, run
  write_period_ns(90000);
  usleep(500000); //pour laisser le temps a write_period_ns d'ecrire dans la BBB
  write_duty_ns(75000);
  usleep(500000);
  set_run();
  usleep(500000);

  double pos = read_eqep();  //
  while(pos > -10){
    
    //Lecture encodeur
    pos = read_eqep();
    usleep(100000);
  }
  reset_run();

  return 0;
}









//Compilation
//g++ BeagleBoneBlack-GPIO-master/GPIO/GPIOConst.cpp  BeagleBoneBlack-GPIO-master/GPIO/GPIOManager.cpp BBBexample.cpp -o BBBexample


// 3674050@pc4139:/nfs/home/sasl/eleves/rob/3674050/ProjetImplementation$ scp BBBexample 3674050@134.157.104.139:debian@192.168.7.2


//scp BBBexample debian@192.168.7.2:~/


/*Connection à la carte :
ssh debian@192.168.7.2
dans un autre terminal, envoyer le fichier ProjetImplementation à la carte : scp -r ProjetImplementation debian@192.168.7.2:. 
retourner dans le terminal de la carte, puis dans ProjetImplementation compiler le tout : g++ BeagleBoneBlack-GPIO-master/GPIO/GPIOConst.cpp  BeagleBoneBlack-GPIO-master/GPIO/GPIOManager.cpp BBBexample.cpp -o BBBexample
executer le code (en root (commande : sudo su)(exit root)) : ./BBBexample 2
pour acceder a period_ns, duty_ns, run du pwm que vous avez cree dans le programme : cd /sys/class/pwm/"pwm que vous avez cree"
puis cat period_ns, cat duty_ns etc pour verifier


Pour allumer et eteindre une led à la main depuis le terminal de la beaglebone :

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
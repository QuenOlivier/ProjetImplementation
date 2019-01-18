#include "BBBexample.hpp"
#include "asservissement.hpp"
#include "../BeagleBoneBlack-GPIO-master/GPIO/GPIOManager.h"
#include "../BeagleBoneBlack-GPIO-master/GPIO/GPIOConst.h"
#include "../eQEP/bbb-eqep.h"

using std::cout;
using std::endl;
//using namespace BBB;


int main(int argc, char const *argv[]) {

  initialisation_pins();
  reset_run();

  //EQUEP
  //BBB::eQEP encodeurs=new BBB::eQEP(eqep_num);
  //Lecture encodeur
  do
  {
    cout << '\n' << "Press [ENTER] when robot is set...";
  } while (std::cin.get() != '\n');
  Point posInit=read_eqep_init(); // Stockage de la pos init brute

 //Ecriture period, duty, run
  write_period_ns(1,PERIOD);
  usleep(500000); //pour laisser le temps a write_period_ns d'ecrire dans la BBB
  write_period_ns(2,PERIOD); //P8.13
  usleep(500000);
  set_run();
  usleep(500000);

  //Valeurs bornes : x(0,0.09), y(0.03, 0.14)
  //Valeurs en metre
  Point test(-0.02, 0.1);
  Point test2(0.0, 0.1);
  Point test3(-0.04, 0.1);
  Point test4(-0.04, 0.06);
  Point test5(-0.02, 0.1);

  std::list<Point> path;

  path.push_back(test);
  path.push_back(test2);
  path.push_back(test3);
  path.push_back(test4);
  path.push_back(test5);

  follow_path(path,posInit);

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

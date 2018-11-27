#include "BeagleBoneBlack-GPIO-master/GPIO/GPIOManager.h"
#include "BeagleBoneBlack-GPIO-master/GPIO/GPIOConst.h"
#include <unistd.h>
#include <cstdlib>
 
int main() {
  GPIO::GPIOManager* gp = GPIO::GPIOManager::getInstance();
  int pin = GPIO::GPIOConst::getInstance()->getGpioByKey("P8_7");
 
  std::system("echo 66 > /sys/class/gpio/export");
  std::system("echo ""out"" > /sys/class/gpio/gpio66/direction");

  //gp->setDirection(pin, GPIO::OUTPUT);
 


  while(true){
      gp->setValue(pin, GPIO::HIGH);
      sleep(1);
      gp->setValue(pin, GPIO::LOW);
      sleep(1);
  }
 
  gp->~GPIOManager();
 
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
executer le code : ./BBBexample


Pour allumer et eteindre une led à la main depuis le terminal de la beaglebone :

dans sys/class/gpio : echo 66 > export    (avec 66 le numero du GPIO qui nous interesse)
dans sys/class/gpio/gpio66 : echo "out" > direction   (pour dire que l'on veut que ce gpio soit une sortie)
dans sys/class/gpio/gpio66 : echo 1 > value   (pour allumer la led)
dans sys/class/gpio/gpio66 : echo 0 > value   (pour éteindre la led)

*/
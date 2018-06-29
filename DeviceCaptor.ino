#include <avdweb_VirtualDelay.h>

// Basé sur le code de LadyAda traduit et modifie par moi, domaine public
#include "DHT.h"

#define DHTPIN 8 // broche ou l'on a branche le capteur
// de-commenter le capteur utilise
//#define DHTTYPE DHT11 // DHT 11
#define DHTTYPE DHT22 // DHT 22 (AM2302)
//#define DHTTYPE DHT21 // DHT 21 (AM2301)
DHT dht(DHTPIN, DHTTYPE);//déclaration du capteur

VirtualDelay singleDelay;

const int keyPin = 12; //the number of the key pin
const int ledPin = 9;//the number of the led pin
int command;
int ledState = 0;
 
void setup()
{
 
 Serial.begin(9600);
 Serial.println("Begin");
 dht.begin();


 pinMode(keyPin,INPUT);//initialize the key pin as input 
  pinMode(ledPin,OUTPUT);//initialize the led pin as output

  
  
}

void loop()
{
  
  loopled();
  singleDelay.start(2000); // calls while running are ignored
  if(singleDelay.elapsed()) loopreadDatas(); 

  
  }
  
void loopled(){
  
  char command;
  
  if(Serial.available() > 0)
    {
        command = Serial.read();

       if(command == '1')
          ledState = HIGH;
       else
          ledState = LOW;
    }

    digitalWrite(ledPin, ledState);
}

void loopreadDatas(){
 
 // La lecture du capteur prend 250ms
 // Les valeurs lues peuvet etre vieilles de jusqu'a 2 secondes (le capteur est lent)
 float h = dht.readHumidity();//on lit l'hygrometrie
 float t = dht.readTemperature();//on lit la temperature en celsius (par defaut)
 // pour lire en farenheit, il faut le paramère (isFahrenheit = true) :
 float f = dht.readTemperature(true);
 
 //On verifie si la lecture a echoue, si oui on quitte la boucle pour recommencer.
 if (isnan(h) || isnan(t) || isnan(f))
 {
   Serial.println("Failed to read from DHT sensor!");
   return;
 }
 
 // Calcul de l'indice de temperature en Farenheit
 float hif = dht.computeHeatIndex(f, h);
 // Calcul de l'indice de temperature en Celsius
 float hic = dht.computeHeatIndex(t, h, false);
 
 //Affichages :
 Serial.print("Humidite: ");
 Serial.print(h);
 Serial.print(" %\t");
 Serial.print("Temperature: ");
 Serial.print(t);
 Serial.print(" *C ");
 Serial.print(f);
 Serial.print(" *F\t");
 Serial.print("Indice de temperature: ");
 Serial.print(hic);
 Serial.print(" *C ");
 Serial.print(hif);
 Serial.println(" *F");
}

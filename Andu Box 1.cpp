/*
Ce programme a été développé dans le cadre du projet "Andu Box". 
Projet initié par l'entreprise volkeno. 

Version n°1 de Andu Box

Objectif : Découverte des réseaux wifi disponibles puis sélection et 
           connexion à un réseau wifi de notre choix

*/


//appel des librairaies nécessaires 
#include <Arduino.h>
#include "WiFi.h"
#include "HardwareSerial.h"
#include <stdlib.h>


//Variables pour stocker les infos d'accès de connexion . 
 char ssid[20] = " ";
 char pswd[20] = " ";


// configuration 
void setup() {

  Serial.begin(115200);
  WiFi.mode(WIFI_MODE_STA); // mode de découverte des réseaux wifi disponibles
  delay(100);
   int n = WiFi.scanNetworks();
   if (n==0)
   {
     Serial.println("Pas de réseaux wifi détecté");

   }else 
   {
     //On affiche le nombre de réseaux découverts 
     Serial.print(n);
     Serial.print(" réseau(x) découvert(s)\n");
     //on liste le(s) réseau(x) découvert(s) leurs noms et la force du signal.
     for (int i = 0; i < n; i++)
          {
            Serial.print(i + 1);
            Serial.print(": ");
            Serial.print(WiFi.SSID(i));//nom du réseau 
            Serial.print(" (");
            Serial.print(WiFi.RSSI(i));//intensité du signal
            Serial.print(")\n");
          }

          

   }

Serial.println("Veuillez choisir le numéro de votre wifi");
int numero;
int ok = 0;
while (ok == 0) 
{

  if (Serial.available() > 0) {
    //Lecture des bytes qui arrivent 
    numero = (Serial.parseInt());
    

    // afficher ce qui a été renvoyé 
    Serial.print("I received: ");
    Serial.println(numero);

    ok = 1;
  }

}

Serial.println("Le numéro reçu est :");
Serial.println(numero);
//SUr la base du numéro reçu on se connecte à un wifi disponible.

String re ; 
for (int i = 0; i < n; i++)
          {
            if (i == numero-1) 
            {
                re = WiFi.SSID(i);
                 re.toCharArray(ssid,sizeof(ssid));
                 Serial.println("Vous avez sélectionné le réseau wifi suivant: ");
                 Serial.println(ssid);
                 Serial.println("Entrez le mot de passe de ce réseau");
                 ok = 0;
                 re = "";
                 char t;
                 
                  while (ok == 0) 
                          {
                            
                            while (Serial.available() > 0  && ok == 0)  {
                              // read the incoming byte:
                               
                              t= Serial.read();
                              // say what you got:
                              if (t == '\r' )
                              {
                                Serial.print("I received: ");
                                Serial.println(re); 
                                 re.toCharArray(pswd,sizeof(pswd));
                               Serial.print("Le mot de passe est : ");
                                Serial.println(pswd);
                                ok = 1; 
                              }
                              else
                              {
                                re +=t;
                              }
                   
                }
                            
        }

    }
  }

//on lance la tentative de connexion sur le réseau wifi sélectionné en veillant 
//à se déconnecter de celui auquel le module est actuellement connecté 
WiFi.disconnect();
WiFi.begin(ssid,pswd);
//tant que le ESP32 ne parvient pas à se connecter au wifi cible
while (WiFi.status() != WL_CONNECTED)
{
    delay(500);
    Serial.println("Connexion au wifi en cours");

}
//Dès qu'on sort de cette boucle cela sous entned que l'ESP32 est parvenu à se connecter
//au wifi cible
Serial.println("Connecté au wifi ");

}

void loop() {
  // Rien à faire ici
}

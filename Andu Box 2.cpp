/*
Ce programme a été développé dans le cadre du projet "Andu Box". 
Projet initié par l'entreprise volkeno. 

Version n°2 de Andu Box

Objectif : Découverte des réseaux wifi disponibles puis sélection et 
           connexion à un réseau wifi de notre choix

*/

// Appel des librairies nécessaires
#include <WiFi.h>
#include "WebServer.h"
#include "SPIFFS.h"
#include "ESPAsyncWebServer.h"

// Replace with your network credentials
const char* ssid     = "Andu Box";
const char* password = "123456789";






// Définition du port d'écoute sur le port 80
AsyncWebServer server(80);

// Variable servant à stocker les requêtes HTTP 
String header;


// Configurations Générales
void setup() {
  Serial.begin(115200);//Configuration de la vitesse de communication série sur 115200 baudrate
 
  


// Configuration du Serial Peripheral Interface Flash File System
//pour la copie des fichiers sur la carte 2lectronique ESP32 qui héberge le server Andu Box
  if(!SPIFFS.begin(true)){
    Serial.println("Une erreur est survenue durant l'accès à SPIFFS");
    return;
  }
  
// Démarrage du Point d'Accès Andu Box
  Serial.print("Setting AP (Access Point)…");
WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  // Définition des chemin des fichiers utilisé pour la page web du server

//Chemin vers le fichier index.html
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html", "text/html");
  });
  
//Chemin vers le fichier style.css
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/style.css", "text/css");
  });

//Chemin vers les fichiers images
  server.on("/volkeno.png", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/volkeno.png", "image/png");
  });

  server.on("/Andu.jpg", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/Andu.jpg", "image/jpg");
  });

//Démarrage du serveur 
  server.begin();


  
}

void loop(){

// rien à faire ici 
   
}



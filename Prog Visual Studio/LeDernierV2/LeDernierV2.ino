// SM130 - seek continuosly for tags and print type and id to serial port
// MP
// Avril 2017 Attention la librairie SM130 a été modifiée : ajout d'une fonction getDataTrois()

// Controls a SonMicro SM130/mini RFID reader or RFIDuino by I2C
// Arduino analog input 4 is I2C SDA (SM130/mini pin 10/6)
// Arduino analog input 5 is I2C SCL (SM130/mini pin 9/5)
// Arduino digital input 4 is DREADY (SM130/mini pin 21/18)
// Arduino digital output 3 is RESET (SM130/mini pin 18/14)

// Following two includes are required for SM130
#include <Wire.h>
#include <SM130.h>
// Create SM130 instance for RFIDuino
SM130 RFIDuino;

byte NbreDeTicketsAEcrire = 0;   
byte NbreDeTicketsLus =0;
char msg[16];
//char numSerie[8]; 
String msgg;

void setup()
{
  // Start I2C bus master (required)
    Wire.begin();
    // Using the serial port is optional
    Serial.begin(115200);
    Serial.println("RFIDuino");
    // Reset RFIDuino, this will also configure IO pins DREADY and RESET
    RFIDuino.reset(); //envoi la cde reset 0x80  + cde antenne 0X90 + cde haltTag 0x93
    Serial.print("Version "); 
    Serial.println(RFIDuino.getFirmwareVersion()); //envoie la cde 81 firmware et stocke le résultat ds data[]
    pinMode(2,OUTPUT);

}

void loop()
{
    RFIDuino.seekTag(); //envoi la cde 0x82
  // Tag detected?
  while(!RFIDuino.available()); // lit la réponse du SM130 à la cde 0x82
  
 // Print the tag's type and serial number
    Serial.print(RFIDuino.getTagName()); // retourne le type de tag : Mifare 1K 
    Serial.print(": ");
    
 msgg = RFIDuino.getTagString();
Serial.println(msgg); //retourne le numéro de série du tag


// Serial.println(RFIDuino.getTagString()); //retourne le numéro de série du tag
    NbreDeTicketsLus = lectureDuNbreTickets();
    Serial.print(" NbreDeTicketsLus = ");
    Serial.println(NbreDeTicketsLus);
    
    if (NbreDeTicketsLus>0){
      NbreDeTicketsAEcrire= NbreDeTicketsLus-1;
    Serial.print(" NbreDeTicketsAEcrire = ");
    Serial.println(NbreDeTicketsAEcrire);
    ecritureDuNbreTickets(NbreDeTicketsAEcrire);
    digitalWrite(2,HIGH);
    delay(500);
    digitalWrite(2,LOW);
    }
    else
    {
    Serial.print(" Attention : NbreDeTicketsLus = ");
    Serial.println(NbreDeTicketsLus);
    int i = 0;
    while(i<5){
    digitalWrite(2,HIGH);
    delay(200);
    digitalWrite(2,LOW);
    delay(200);
    i++;
    }
    Serial.print(" Rechargement de la carte ");
    NbreDeTicketsAEcrire= 10;
    Serial.print(" NbreDeTicketsAEcrire = ");
    Serial.println(NbreDeTicketsAEcrire);
    RFIDuino.seekTag();
    while(!RFIDuino.available());
    ecritureDuNbreTickets(NbreDeTicketsAEcrire);   
    }
    delay(1000);
}  




  
  byte lectureDuNbreTickets()
{
  byte NbrTickLus = 0; 
  
  do{
  RFIDuino.authenticate(1); //envoi la cde 0x85
  while(!RFIDuino.available()); //attend de la réponse du SM130 et la stocke dans DATA[] 
  
  RFIDuino.readBlock(1);  //envoi la cde 0x86 au SM130
  while(!RFIDuino.available());
  NbrTickLus = RFIDuino.getDataTrois();
  } while(RFIDuino.getBlockNumber()==0x4E || RFIDuino.getBlockNumber()==0x46);

   return (NbrTickLus);
}
  
  
 void ecritureDuNbreTickets(int NbreTickAEcr)
 {
  msg[0]= char(NbreTickAEcr);
  
  RFIDuino.authenticate(1); //envoi la cde 0x85
  while(!RFIDuino.available());
  
  RFIDuino.writeBlock(1,msg); //envoi de la cde 0x89 au SM130
  while(!RFIDuino.available()); 
 } 
  



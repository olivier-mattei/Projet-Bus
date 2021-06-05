#include <Adafruit_RGBLCDShield.h>
#include <utility/Adafruit_MCP23017.h>
#include <Wire.h>
#include <SM130.h>

Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();
SM130 RFIDuino;
int cardetect;
int NbreDeTicketsAEcrire = 0;
int NbreDeTicketsLus = 0;
char msg[16];
boolean donneesALire; // création de la variable donneesALire de type boolean
String msgg;

#define BLACK 0x0
#define RED 0x1
#define GREEN 0x2
#define YELLOW 0x3
#define BLUE 0x4
#define VIOLET 0x5
#define TEAL 0x6
#define WHITE 0x7


void setup()
{
	Wire.begin();
	msgg = RFIDuino.getTagString();
	Serial.begin(9600);
	lcd.begin(16, 2); //on initialise la communication avec 16 colonnes et 2 lignes
    RFIDuino.reset();//on réinitialise le module
}

void loop()
{
	Serial.print(" NbreDeTicketsLus = ");
	Serial.println(NbreDeTicketsLus);
	RFIDuino.seekTag(); //regarde constamment s'il y a la présence d'un TAG 
	while (!RFIDuino.available()); // lit la réponse du SM130 à la cde 0x82 (Pour savoir s'il y a un TAG détecté)
	NbreDeTicketsLus = lectureDuNbreTickets();

	String Tag = RFIDuino.getTagString(); // on déclare la variable Tag de type char et on dit qu'elle est égale à la chaine de caractère (TAG de la carte)
	Serial.println(Tag);

	if (RFIDuino.getTagString() == "FAB49634")//si une réponse est reçue alors mettre la variable cartedect = Vrai
	{
		Serial.println("Carte détectée");
		cardetect == true;
	}
	else //si autre alors mettre la variable cardectect = Faux
	{
		Serial.println("Pas de détection");
		cardetect == false;
	}
	if (cardetect = true)
	{
		lcd.setBacklight(TEAL);
		lcd.setCursor(0, 0);
		lcd.print("Tickets Actuels:");
		lcd.setCursor(5, 1);
		lcd.println(NbreDeTicketsLus);
		delay(1000);
		lcd.clear();
		lcd.setCursor(0, 0); // le curseur est positionné au caractére 0 de la ligne 0
		lcd.setBacklight(TEAL);
		lcd.print("Merci de ");
		lcd.setCursor(0, 1);
		lcd.print("patienter");
		delay(500);
		lcd.setCursor(10, 1);
		lcd.print(".");
		delay(500);
		lcd.setCursor(11, 1);
		lcd.print(".");
		delay(500);
		lcd.setCursor(12, 1);
		lcd.print(".");
		delay(500);
		lcd.setCursor(13, 1);
		lcd.print(".");
		delay(500);
		lcd.setCursor(14, 1);
		lcd.print(".");
		delay(500);
		lcd.setCursor(15, 1);
		lcd.print(".");
		delay(1000);
		lcd.clear();
		lcd.setBacklight(TEAL);
		Serial.println(Tag); // Envoie le TAG de la carte au porgramme du pc
		lcd.print("Demande en cours");
		delay(320);
		lcd.setCursor(0, 1);
		lcd.print(".");
		delay(300);
		lcd.setCursor(1, 1);
		lcd.print(".");
		delay(280);
		lcd.setCursor(2, 1);
		lcd.print(".");
		delay(260);
		lcd.setCursor(3, 1);
		lcd.print(".");
		delay(240);
		lcd.setCursor(4, 1);
		lcd.print(".");
		delay(220);
		lcd.setCursor(5, 1);
		lcd.print(".");
		delay(200);
		lcd.setCursor(6, 1);
		lcd.print(".");
		delay(180);
		lcd.setCursor(7, 1);
		lcd.print(".");
		delay(160);
		lcd.setCursor(8, 1);
		lcd.print(".");
		delay(140);
		lcd.setCursor(9, 1);
		lcd.print(".");
		delay(120);
		lcd.setCursor(10, 1);
		lcd.print(".");
		delay(100);
		lcd.setCursor(11, 1);
		lcd.print(".");
		delay(80);
		lcd.setCursor(12, 1);
		lcd.print(".");
		delay(60);
		lcd.setCursor(13, 1);
		lcd.print(".");
		delay(40);
		lcd.setCursor(14, 1);
		lcd.print(".");
		delay(20);
		lcd.setCursor(15, 1);
		lcd.print(".");
		delay(20);
		lcd.clear();
		Serial.println("Verification de la base de donnée ...... ");
		delay(3000);
		int info = Serial.available(); //regarde si des caractéres ont été reçus
		int NbreDeTicketsAjouter = Serial.read(); //NbreDeTicketsAjouter est égal au caractère reçu
		NbreDeTicketsAEcrire = NbreDeTicketsAjouter + NbreDeTicketsLus;
		NbreDeTicketsAEcrire = NbreDeTicketsAEcrire - 1;
		donneesALire = info; // la variable donneesALire est égale au contenu de la variable info

		lcd.setBacklight(BLUE);
		lcd.setCursor(0, 0);
		lcd.print("Ajout de Tickets:");
		lcd.setCursor(5, 1);
		lcd.print("+");
		lcd.println(NbreDeTicketsAjouter);

		if (donneesALire == true) { //si des caractéres ont été reçu alors:
			if (NbreDeTicketsAEcrire > 3) {
				lcd.clear();
				lcd.setCursor(0, 0);
				lcd.setBacklight(GREEN);
				lcd.clear();
				lcd.print("Tickets restants:");
				lcd.setCursor(7, 1);
				lcd.print(NbreDeTicketsAEcrire); //affiche le contenu de la variable NbreDeTicketsAjouter au caractère 8 de la ligne 1
				Serial.println("information reçue"); /*afficher'information reçue'*/
				delay(3000);
				Serial.print("Tickets=");
				Serial.println(NbreDeTicketsAjouter); //afficher le contenu de NbreDeTicketsAjouter en Decimal
				RFIDuino.seekTag();
				while (!RFIDuino.available());
				ecritureDuNbreTickets(NbreDeTicketsAEcrire);
			}
			if (NbreDeTicketsAEcrire == 1, 2, 3) {
				lcd.clear();
				lcd.setCursor(0, 0);
				lcd.setBacklight(YELLOW);
				lcd.print("Tickets restants:");
				lcd.setCursor(7, 1);
				lcd.print(NbreDeTicketsAEcrire);
				delay(1500);
				lcd.clear();
				lcd.setCursor(4, 0);
				lcd.print("Penser à ");
				lcd.setCursor(4, 1);
				lcd.print("Recharger");
				delay(1000);
				lcd.clear();
				lcd.setCursor(5, 0);
				lcd.print("votre");
				lcd.setCursor(4, 1);
				lcd.print("Tickets");
				delay(2000);
				Serial.println("information reçue"); /*afficher'information reçue'*/
				delay(3000);
				lcd.setCursor(8, 1);
				lcd.println(NbreDeTicketsAEcrire); //affiche le contenu de la variable NbreDeTicketsAjouter au caractére 8 de la ligne 1
				Serial.print("Tickets=");
				Serial.println(NbreDeTicketsAjouter); //afficher le contenu de NbreDeTicketsAjouter en Decimal
				RFIDuino.seekTag();
				while (!RFIDuino.available());
				ecritureDuNbreTickets(NbreDeTicketsAEcrire);
				if (NbreDeTicketsAEcrire == 0) {
					lcd.clear();
					lcd.setCursor(0, 0);
					lcd.setBacklight(RED);
					lcd.print("Vous n'avez plus");
					lcd.setCursor(0, 1);
					lcd.print("de tickets");
					delay(6000);
					lcd.clear();
					Serial.println("Pas de retour");
					RFIDuino.seekTag();
					while (!RFIDuino.available());
					ecritureDuNbreTickets(NbreDeTicketsAEcrire);
				}

			}
		}
		if (donneesALire == false) // si aucune information reçu alors:
		{
			lcd.clear();
			lcd.setBacklight(RED);
			lcd.setCursor(4, 0);
			lcd.print("ERREUR"); //on affiche "ERREUR SYSTEME" même si normalement cette partie là ne devrait pas se produire
			lcd.setCursor(4, 1);
			lcd.print("SYSTEME");
			delay(7000);
			lcd.clear();
			lcd.setBacklight(WHITE);
			lcd.setCursor(0, 0);
			lcd.print("Relancement");
			Serial.println("Données non reçues ou pas de réponse envoyée"); //afiche sur le moniteur série que "Données non reçues ou pas de réponse envoyée"
			delay(320);
			lcd.setCursor(0, 1);
			lcd.print(".");
			delay(300);
			lcd.setCursor(1, 1);
			lcd.print(".");
			delay(280);
			lcd.setCursor(2, 1);
			lcd.print(".");
			delay(260);
			lcd.setCursor(3, 1);
			lcd.print(".");
			delay(240);
			lcd.setCursor(4, 1);
			lcd.print(".");
			delay(220);
			lcd.setCursor(5, 1);
			lcd.print(".");
			delay(200);
			lcd.setCursor(6, 1);
			lcd.print(".");
			delay(180);
			lcd.setCursor(7, 1);
			lcd.print(".");
			delay(160);
			lcd.setCursor(8, 1);
			lcd.print(".");
			delay(140);
			lcd.setCursor(9, 1);
			lcd.print(".");
			delay(120);
			lcd.setCursor(10, 1);
			lcd.print(".");
			delay(100);
			lcd.setCursor(11, 1);
			lcd.print(".");
			delay(80);
			lcd.setCursor(12, 1);
			lcd.print(".");
			delay(60);
			lcd.setCursor(13, 1);
			lcd.print(".");
			delay(40);
			lcd.setCursor(14, 1);
			lcd.print(".");
			delay(20);
			lcd.setCursor(15, 1);
			lcd.print(".");
			delay(20);
			lcd.clear();
			lcd.setCursor(4, 0);
			lcd.print("TERMINE");
			delay(5000);
			lcd.clear();
		}
	}
	if (cardetect = false)
	{
		Serial.println("Je suis en veille"); // affiche "je suis en veille" dans le moniteur série et retour à la ligne
		lcd.setBacklight(VIOLET);
		lcd.setCursor(4, 0);
		lcd.print("Mise en");
		lcd.setCursor(5, 1);
		lcd.print("veille");
		delay(1000);
		lcd.clear();
		lcd.setBacklight(BLACK); // on met la couleur en noir ce qui baisse la luminosité de l'écran pendant 10 secondes (mise en veille)
								 //  RFIDuino.sleep(); // on met le SM 130 en mode veille
		delay(8000);
		lcd.clear();
	}
}
byte lectureDuNbreTickets()
{
	byte NbrTickLus = 0;

	do {
		RFIDuino.authenticate(1); //envoi la cde 0x85
		while (!RFIDuino.available()); //attend de la réponse du SM130 et la stocke dans DATA[] 

		RFIDuino.readBlock(1);  //envoi la cde 0x86 au SM130
		while (!RFIDuino.available());
		NbrTickLus = RFIDuino.getDataTrois();
	} while (RFIDuino.getBlockNumber() == 0x4E || RFIDuino.getBlockNumber() == 0x46);

	return (NbrTickLus);
}
void ecritureDuNbreTickets(int NbreTickAEcr)
{
	msg[0] = char(NbreTickAEcr);

	RFIDuino.authenticate(1); //envoi la cde 0x85
	while (!RFIDuino.available());

	RFIDuino.writeBlock(1, msg); //envoi de la cde 0x89 au SM130
	while (!RFIDuino.available());
}

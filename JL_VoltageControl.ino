//#include <LiquidCrystal_I2C.h>
#include <Base64.h>
#include <UTFT_Geometry.h>
#include <UTFT.h>
#include <memorysaver.h>
#include <EthernetUdp.h>
#include <EthernetServer.h>
#include <EthernetClient.h>
#include <Ethernet.h>
#include <Dns.h>
#include <Dhcp.h>
#include <SD.h>
#include <Adafruit_ADS1015.h>


// -----------------------------------------------------------Network
byte mac[] = { 0x00, 0xAA, 0xBB, 0xCC, 0xDA, 0x02 };
//IPAddress ip(172, 19, 200, 180); //Define o endereco IP
//IPAddress gateway(172, 19, 200, 254); //Define o gateway
//IPAddress subnet(255, 255, 255, 0); //Define a máscara de rede
EthernetServer myServer(80);
EthernetClient myClient;
bool isConnectedToNetwork = false;
bool isConnectedToServer = false;
int DiscontedTime = 0;
//const String ipserver = "172.19.200.101";
const String ipserver = "89.115.226.187";

const int port = 8888;

const String subscriptionid = "570ac520-d038-48b5-b285-6bad233b4d7a";
const String deviceid = "8de97bb3-9f2d-4544-8943-e8b28abc2969";


// -----------------------------------------------------------SD Card
File mySDCard;
bool mySDCardStatus;
// -----------------------------------------------------------TFT
//LiquidCrystal_I2C lcd(0x27, 16, 2); 
//VCC
//GND
#define _cs 2
#define _rst 3
#define _dc 4
#define _mosi 5
#define _sclk 6
//3.5v
#define _miso 7
//
UTFT myGLCD(ILI9341_S5P, _mosi, _sclk, _cs, _rst, _dc);
UTFT_Geometry	geo(&myGLCD);

int max_x, max_y;

extern uint8_t SmallFont[];
extern uint8_t BigFont[];
extern uint8_t SevenSegNumFont[];
//Adafruit_ILI9340 tft = Adafruit_ILI9340(_cs, _dc, _mosi, _sclk, _rst, _miso);
// -----------------------------------------------------------ADS
// 0x48,0x49,0x4A,0x4B
Adafruit_ADS1115 SensorADS(0x48);

int _Panel1Port[15];
float _Panel1Voltage[15];
int _Panel2Port[15];
float _Panel2Voltage[15];
int myDelay = 0;
double VMax = 4.5;
// -----------------------------------------------------------Divers

int myTimerToConnect = 0;
int myTimer = 0;
int N_Celulas = 14;


typedef struct MySettings {
	String DeviceID;
	String Server;
	String Port;
	int RefreshTime;
} MySettings;

MySettings _Settings; 

int myport = A8;


//Declare pins for ATtiny inputs

const int Cell1 = 22;//2;
const int Cell2 = 23;//3;
const int Cell3 = 24;//1;
const int Cell4 = 25;//5;
const int Cell5 = 26;//6;
const int Cell6 = 27;//7;
const int Cell7 = 28;//8;
const int Cell8 = 29;//2;
const int Cell9 = 30;//3;
const int Cell10 = 31;//1;
const int Cell11 = 32;//5;
const int Cell12 = 33;//6;
const int Cell13 = 34;//7;
const int Cell14 = 35;//8;

					  //Declare booleans for auto-detect Cell count
boolean CellON1 = false;
boolean CellON2 = false;
boolean CellON3 = false;
boolean CellON4 = false;
boolean CellON5 = false;
boolean CellON6 = false;
boolean CellON7 = false;
boolean CellON8 = false;
boolean CellON9 = false;
boolean CellON10 = false;
boolean CellON11 = false;
boolean CellON12 = false;
boolean CellON13 = false;
boolean CellON14 = false;

//Common variable declarations for converting pwm to mV
int CellV[14];
unsigned long z;
unsigned long y;
unsigned long x;

//Declare boolean for LVC warning and cutoff
boolean LVWarn = false;
boolean LVCutoff = false;

//Declare LVC output to motor control MCU
const int throttleBack = 8;
const int throttleCut = 9;

//Manual Variables
int LVW = 3600;  //Warning mV
int LVC = 3400;  //Cutoff mV
int batteryCellCount = 0;  //variable to add up active Cells
float totalvolt = 0;





void setup(){
	Serial.begin(9600);
	//while (!Serial);
	Serial.println("SL Lab Starting...");


	//lcd.init();
	//lcd.backlight();
	//lcd.print("Starting Sensor");

	// Display init
	myGLCD.InitLCD();
	myGLCD.clrScr();
	myGLCD.fillScr(VGA_BLACK);
	myGLCD.setBackColor(VGA_BLACK);
	max_x = myGLCD.getDisplayXSize();
	max_y = myGLCD.getDisplayYSize();
	Serial.println((String)"X:" + max_x + " Y:" + max_y);

	// Network
	//isConnectedToNetwork = ConnectToNetwork();
	//isConnectedToServer = ConnectToServer();
	//delay(2000);

	// SD Card
	//mySDCardStatus = InitSDCard();
	//WriteToSDCard("Teste");
	//GetFiles();

	//SensorADS.begin();
	//_SensorInit();

	_ShowHeader();
	myTimerToConnect = millis();


	pinMode(Cell1, INPUT);
	pinMode(Cell2, INPUT);
	pinMode(Cell3, INPUT);
	pinMode(Cell4, INPUT);
	pinMode(Cell5, INPUT);
	pinMode(Cell6, INPUT);
	pinMode(Cell7, INPUT);
	pinMode(Cell8, INPUT);
	pinMode(Cell9, INPUT);
	pinMode(Cell10, INPUT);
	pinMode(Cell11, INPUT);
	pinMode(Cell12, INPUT);
	pinMode(Cell13, INPUT);
	pinMode(Cell14, INPUT);

	delay(800);  //Ensure all ATtiny85s are initiated

				 //Check for active Cells
	int CellCheck1 = pulseIn(Cell1, HIGH, 100000);
	int CellCheck2 = pulseIn(Cell2, HIGH, 100000);
	int CellCheck3 = pulseIn(Cell3, HIGH, 100000);
	int CellCheck4 = pulseIn(Cell4, HIGH, 100000);
	int CellCheck5 = pulseIn(Cell5, HIGH, 100000);
	int CellCheck6 = pulseIn(Cell6, HIGH, 100000);
	int CellCheck7 = pulseIn(Cell7, HIGH, 100000);
	int CellCheck8 = pulseIn(Cell8, HIGH, 100000);
	int CellCheck9 = pulseIn(Cell9, HIGH, 100000);
	int CellCheck10 = pulseIn(Cell10, HIGH, 100000);
	int CellCheck11 = pulseIn(Cell11, HIGH, 100000);
	int CellCheck12 = pulseIn(Cell12, HIGH, 100000);
	int CellCheck13 = pulseIn(Cell13, HIGH, 100000);
	int CellCheck14 = pulseIn(Cell14, HIGH, 100000);

	Serial.print("Detecting active Cells: ");

	//Toggle active Cells ON and print out
	if (CellCheck1 > 1) {
		CellON1 = true;
		Serial.print("1");
		batteryCellCount++;
	}
	if (CellCheck2 > 1) {
		CellON2 = true;
		Serial.println("2");
		batteryCellCount++;
	}
	if (CellCheck3 > 1) {
		CellON3 = true;
		Serial.print("3");
		batteryCellCount++;
	}
	if (CellCheck4 > 1) {
		CellON4 = true;
		Serial.print("4");
		batteryCellCount++;
	}
	if (CellCheck5 > 1) {
		CellON5 = true;
		Serial.print("5");
		batteryCellCount++;
	}
	if (CellCheck6 > 1) {
		CellON6 = true;
		Serial.print("6");
		batteryCellCount++;
	}
	if (CellCheck7 > 1) {
		CellON7 = true;
		Serial.print("7");
		batteryCellCount++;
	}
	if (CellCheck8 > 1) {
		CellON8 = true;
		Serial.print("8");
		batteryCellCount++;
	}
	if (CellCheck9 > 1) {
		CellON9 = true;
		Serial.println("9");
		batteryCellCount++;
	}
	if (CellCheck10 > 1) {
		CellON10 = true;
		Serial.print("10");
		batteryCellCount++;
	}
	if (CellCheck11 > 1) {
		CellON11 = true;
		Serial.print("11");
		batteryCellCount++;
	}
	if (CellCheck12 > 1) {
		CellON12 = true;
		Serial.print("12");
		batteryCellCount++;
	}
	if (CellCheck13 > 1) {
		CellON13 = true;
		Serial.print("13");
		batteryCellCount++;
	}
	if (CellCheck14 > 1) {
		CellON14 = true;
		Serial.print("14");
		batteryCellCount++;
	}
	delay(100);
	Serial.println();
	Serial.print(batteryCellCount);
	Serial.println(" Cells detected");

	myGLCD.setFont(SmallFont);
	myGLCD.setColor(VGA_AQUA);
	myGLCD.print((String)batteryCellCount + " Cells", 100, 220);

	delay(2000);


}

void loop(){
	ReadVoltageBloco1();
	_ShowCelulas(1);
	//ReadVoltageBloco2();
	//_ShowCelulas(2);
	float total = 0;
	for (int i = 0; i < N_Celulas; i++) total += _Panel1Voltage[i];
	//total = total / batteryCellCount;
	myGLCD.setFont(SmallFont);
	myGLCD.setColor(VGA_AQUA);
	myGLCD.print((String)total + " Volts", 200, 220);

	delay(1000);
	//String MSG1 = "";

	//for (int x = 0; x < N_Celulas; x++) {
	//	MSG1 += String(_Panel1Voltage[x]) + "|";
	//}

		/*if (CheckServer()) {
			SendDataToWEB("P1", MSG1, "");
			DiscontedTime = 0;
		} else {
			DiscontedTime += 1;
		}

		if (DiscontedTime == 3) {
		ConnectToNetwork();
		DiscontedTime = 0;
		}*/
			
}




bool InitSDCard() {
	Serial.println("Initializing SD card...");
	myGLCD.fillScr(VGA_BLACK);
	myGLCD.setColor(VGA_BLUE);
	myGLCD.setFont(BigFont);
	myGLCD.print("SLApps LAB v1.0", CENTER, 0);
	myGLCD.setColor(VGA_GREEN);
	myGLCD.print("Init SD card.", CENTER, 100);
	delay(3000);
	myGLCD.setFont(SmallFont);

	if (!SD.begin(4)) {
		Serial.println("initialization failed!");
		myGLCD.setColor(VGA_RED);
		myGLCD.print("Initialization failed!", CENTER, 130);
		delay(5000);
		return false;
	}

	Serial.println("initialization done.");
	myGLCD.setColor(VGA_GREEN);
	myGLCD.print("Initialization done.", CENTER, 130);

	delay(5000);
	return true;
}

void GetFiles() {
	myGLCD.fillScr(VGA_BLACK);
	myGLCD.setColor(VGA_BLUE);
	myGLCD.setFont(BigFont);
	myGLCD.print((String)"Files : " + mySDCard.name(), CENTER, 0);

	myGLCD.setColor(VGA_WHITE);

	myGLCD.setFont(SmallFont);
	mySDCard = SD.open("/");
	printDirectory(mySDCard, 0);
	delay(5000);
}

void printDirectory(File dir, int numTabs) {
	int Row = 25;
	while (true) {

		File entry = dir.openNextFile();
		if (!entry) {
			// no more files
			break;
		}
		for (uint8_t i = 0; i < numTabs; i++) {
			Serial.print('\t');
		}
		Serial.print(entry.name());
	
		if (entry.isDirectory()) {
			Serial.println("/");
			myGLCD.setColor(VGA_FUCHSIA);
			myGLCD.print(entry.name(), 0, Row);
			printDirectory(entry, numTabs + 1);
		}
		else {
			// files have sizes, directories do not
			Serial.print("\t\t");
			Serial.println(entry.size(), DEC);
			myGLCD.setColor(VGA_NAVY);
			myGLCD.print((String)entry.name() + " - " + entry.size(), 0, Row);
		}
		entry.close();
		Row += 10;
	}
}


void WriteToSDCard(String Value) {
	File dataFile = SD.open("datalog.txt", FILE_WRITE);

	// if the file is available, write to it:
	if (dataFile) {
		dataFile.println(Value);
		dataFile.close();
		// print to the serial port too:
		Serial.println(Value);
	}
	// if the file isn't open, pop up an error:
	else {
		Serial.println("error opening datalog.txt");
		mySDCardStatus = false;
	}

}


String ReadLineFromSDCard() {


}
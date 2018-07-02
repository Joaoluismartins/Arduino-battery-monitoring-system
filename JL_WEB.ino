// Network
bool ConnectToNetwork() {
	myGLCD.fillScr(VGA_BLACK);
	myGLCD.setColor(VGA_BLUE);
	myGLCD.setFont(BigFont);
	myGLCD.print("SLApps LAB v1.0", CENTER, 0);

	myGLCD.setColor(VGA_GREEN);
	myGLCD.print("Connecting...", CENTER, 100);

	if (Ethernet.begin(mac) == 0) {
		Serial.println("Failed to configure Ethernet using DHCP");

		myGLCD.setFont(SmallFont);
		myGLCD.setColor(VGA_RED);
		myGLCD.print("Failed to configure Ethernet using DHCP", CENTER, 130);
		return false;
	}
	else
	{
		Serial.print("My IP address: ");
		for (byte thisByte = 0; thisByte < 4; thisByte++) {
			Serial.print(Ethernet.localIP()[thisByte], DEC);
			Serial.print(".");
			}
		Serial.println();
		myGLCD.print("Connected to network", CENTER, 100);
		myGLCD.setFont(BigFont);
		myGLCD.setColor(VGA_AQUA);
		myGLCD.print(DisplayAddress(Ethernet.localIP()), CENTER, 220);
		return true;
	}
}


bool ConnectToServer() {
	char myIP[15];
	ipserver.toCharArray(myIP, 15);

	Serial.println("Try Connect to " + (String)myIP + ":" + port);
	myClient.connect(myIP, port);

	if (myClient.connected()) {

		String MSGToSend = "LOGIN|" + subscriptionid + "|" + deviceid;

		// ToBase64
		char input[256];
		MSGToSend.toCharArray(input, 256);
		int inputLen = MSGToSend.length();
		int encodedLen = base64_enc_len(inputLen);
		char encoded[encodedLen];
		base64_encode(encoded, input, inputLen);

		// Send MSG
		myClient.print(encoded);
		String Result = myClient.readString();
		Serial.println(Result);

		if (Result.length() == 0) { 
			CloseConnection();
			Serial.println("Disconnected");
			myGLCD.setFont(SmallFont);
			myGLCD.setColor(VGA_RED);
			myGLCD.print("******", 260, 220);
			return false;
		} else { 
			Serial.println("Connected");
			myGLCD.setFont(SmallFont);
			myGLCD.setColor(VGA_GREEN);
			myGLCD.print("******", 260, 220);
			return true;
		}
	}	
}

bool CheckServer() {
	if (myClient.connected()) {
		myGLCD.setFont(SmallFont);
		myGLCD.setColor(VGA_GREEN);
		myGLCD.print("******", 260, 220);
		return true;
	} else {
		myGLCD.setFont(SmallFont);
		myGLCD.setColor(VGA_RED);
		myGLCD.print("******", 260, 220);
		CloseConnection();
		ConnectToServer();
		return myClient.connected();
	}
}




String DisplayAddress(IPAddress address)
{
	return String(address[0]) + "." +
		String(address[1]) + "." +
		String(address[2]) + "." +
		String(address[3]);
}



// DATA|subscriptionid|deviceid|
void SendDataToWEB(String ID, String MSG, String Date) {
	String MSGToSend = "DATA|" + subscriptionid + "|" + deviceid + "|" + ID + "|" + Date + "|" + MSG;

	char input[256];
	MSGToSend.toCharArray(input, 256);
	int inputLen = MSGToSend.length();
	int encodedLen = base64_enc_len(inputLen);
	char encoded[encodedLen];
	base64_encode(encoded, input, inputLen);
	myClient.print(encoded);

	Serial.println("********************************************************************************");
	Serial.println("Send to WEB - " + ipserver + ":" + port);
	Serial.println(MSGToSend);
	Serial.println(encoded);
	Serial.println("********************************************************************************");

	String Result = myClient.readString();
	Serial.println(Result);

	if (Result.length() == 0) {
		//DataLog(MSG);
		CloseConnection();
	}
}



void CloseConnection() {
	isConnectedToServer = false;
	myClient.flush();
	myClient.stop();
}


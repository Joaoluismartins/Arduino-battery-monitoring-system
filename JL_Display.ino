


void _ShowHeader() {
	myGLCD.fillScr(VGA_BLACK);
	myGLCD.setColor(VGA_BLUE);
	myGLCD.setFont(BigFont);
	//myGLCD.print("SLApps LAB v1.0", CENTER, 0);
  myGLCD.print("Battery Monitoring", CENTER, 0);

	//myGLCD.setFont(SmallFont);
	//myGLCD.setColor(VGA_AQUA);
	//myGLCD.print(DisplayAddress(Ethernet.localIP()), CENTER, 220);
}


void _ShowCelulas(int Bloco) {
	myGLCD.setFont(BigFont);
	myGLCD.setColor(VGA_WHITE);
	myGLCD.print((String)"Pack " + Bloco, 140, 22);
	myGLCD.setFont(SmallFont);
	double Celulas[14];

	if (Bloco == 1) {
		for (int i = 0; i < N_Celulas; i++) Celulas[i] = _Panel1Voltage[i];
	}

	if (Bloco == 2) {
		for (int i = 0; i < N_Celulas; i++) Celulas[i] = _Panel2Voltage[i];
	}

	int Pos = (max_x - 70) / N_Celulas;
	int Max = Pos;

	int tposx = 5;
	int tposy = 25;

	for (int i = 0; i < N_Celulas; i++) {
		int posx = Pos + 60;
		int posy = 200;
		double var = Celulas[i] * 135 / VMax;

		myGLCD.setFont(SmallFont);
		myGLCD.setColor(VGA_BLACK);
		myGLCD.fillRect(posx, posy, posx + 13, 40);

		myGLCD.setColor(VGA_BLUE);
		if ((Celulas[i]>4.2) && (Celulas[i]<VMax))myGLCD.setColor(VGA_RED);
		if ((Celulas[i]>3.2) && (Celulas[i]<4.1))myGLCD.setColor(VGA_LIME);
		if ((Celulas[i] >= 0) && (Celulas[i]<3.2)) myGLCD.setColor(VGA_YELLOW);
		
		int CelulaNumber = i + 1;
		float ValueToDisplay = Celulas[i];

		String Value = (String)CelulaNumber + ":" + ValueToDisplay + "  ";
		Serial.println(Value);
		myGLCD.print(Value, tposx, tposy);
		tposy += 15;
		
		myGLCD.fillRect(posx, posy, posx + 13, posy - var);
		myGLCD.setColor(VGA_WHITE);
		myGLCD.drawRect(posx, posy, posx + 13, posy - var);
		myGLCD.printNumI(i + 1, posx, posy + 5);
		Pos += 17;
	}
}

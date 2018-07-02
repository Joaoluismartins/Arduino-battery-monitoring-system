

void _SensorInit(){
	_Panel1Port[0] = 22;
	_Panel1Port[1] = 23;
	_Panel1Port[2] = 24;
	_Panel1Port[3] = 25;
	_Panel1Port[4] = 26;
	_Panel1Port[5] = 27;
	_Panel1Port[6] = 28;
	_Panel1Port[7] = 29;
	_Panel1Port[8] = 30;
	_Panel1Port[9] = 31;
	_Panel1Port[10] = 32;
	_Panel1Port[11] = 33;
	_Panel1Port[12] = 34;
	_Panel1Port[13] = 35;

	_Panel2Port[0] = 36;
	_Panel2Port[1] = 37;
	_Panel2Port[2] = 38;
	_Panel2Port[3] = 39;
	_Panel2Port[4] = 40;
	_Panel2Port[5] = 41;
	_Panel2Port[6] = 42;
	_Panel2Port[7] = 43;
	_Panel2Port[8] = 44;
	_Panel2Port[9] = 45;
	_Panel2Port[10] = 46;
	_Panel2Port[11] = 47;
	_Panel2Port[12] = 48;
	_Panel2Port[13] = 49;

	for (int x = 0; x < N_Celulas; x++) {
		pinMode(_Panel1Port[x], OUTPUT);
		digitalWrite(_Panel1Port[x], LOW);
		_Panel1Voltage[x] = 0.0;

		pinMode(_Panel2Port[x], OUTPUT);
		digitalWrite(_Panel2Port[x], LOW);
		_Panel2Voltage[x] = 0.0;
	}
}

void ReadVoltageBloco1() {
	//for (int x = 0; x < N_Celulas; x++) {
	//	digitalWrite(_Panel1Port[x], HIGH);

	//	delay(myDelay);

	//	float var1 = GetVoltage1();

	//	_Panel1Voltage[x] = var1;

	//	Serial.println((String)"Bloco : 1 - Porta : " + _Panel1Port[x] + " - " + _Panel1Voltage[x]);

	//	digitalWrite(_Panel1Port[x], LOW);

	//	delay(myDelay);
	//}

	float Value = 0;

	if (CellON1 == true) {
		y = pulseIn(Cell1, HIGH, 100000);
		z = pulseIn(Cell1, LOW, 100000);
		Value = pwmConvert(z, y);
		_Panel1Voltage[0] = Value /1000;
	}
	if (CellON2 == true) {
		y = pulseIn(Cell2, HIGH, 100000);
		z = pulseIn(Cell2, LOW, 100000);
		Value = pwmConvert(z, y);
		_Panel1Voltage[1] = Value / 1000;
	}
	if (CellON3 == true) {
		y = pulseIn(Cell3, HIGH, 100000);
		z = pulseIn(Cell3, LOW, 100000);
		Value = pwmConvert(z, y);
		_Panel1Voltage[2] = Value / 1000;
	}
	if (CellON4 == true) {
		y = pulseIn(Cell4, HIGH, 100000);
		z = pulseIn(Cell4, LOW, 100000);
		Value = pwmConvert(z, y);
		_Panel1Voltage[3] = Value / 1000;
	}
	if (CellON5 == true) {
		y = pulseIn(Cell5, HIGH, 100000);
		z = pulseIn(Cell5, LOW, 100000);
		Value = pwmConvert(z, y);
		_Panel1Voltage[4] = Value / 1000;
	}
	if (CellON6 == true) {
		y = pulseIn(Cell6, HIGH, 100000);
		z = pulseIn(Cell6, LOW, 100000);
		Value = pwmConvert(z, y);
		_Panel1Voltage[5] = Value / 1000;
    }
	if (CellON7 == true) {
		y = pulseIn(Cell7, HIGH, 100000);
		z = pulseIn(Cell7, LOW, 100000);
		Value = pwmConvert(z, y);
		_Panel1Voltage[6] = Value / 1000;
	}
	if (CellON8 == true) {
		y = pulseIn(Cell8, HIGH, 100000);
		z = pulseIn(Cell8, LOW, 100000);
		Value = pwmConvert(z, y);
		_Panel1Voltage[7] = Value / 1000;
	}
	if (CellON9 == true) {
		y = pulseIn(Cell9, HIGH, 100000);
		z = pulseIn(Cell9, LOW, 100000);
		Value = pwmConvert(z, y);
		_Panel1Voltage[8] = Value / 1000;
	}
	if (CellON10 == true) {
		y = pulseIn(Cell10, HIGH, 100000);
		z = pulseIn(Cell10, LOW, 100000);
		Value = pwmConvert(z, y);
		_Panel1Voltage[9] = Value / 1000;
	}
	if (CellON11 == true) {
		y = pulseIn(Cell11, HIGH, 100000);
		z = pulseIn(Cell11, LOW, 100000);
		Value = pwmConvert(z, y);
		_Panel1Voltage[10] = Value / 1000;
	}
	if (CellON12 == true) {
		y = pulseIn(Cell12, HIGH, 100000);
		z = pulseIn(Cell12, LOW, 100000);
		Value = pwmConvert(z, y);
		_Panel1Voltage[11] = Value / 1000;
	}
	if (CellON13 == true) {
		y = pulseIn(Cell13, HIGH, 100000);
		z = pulseIn(Cell13, LOW, 100000);
		Value = pwmConvert(z, y);
		_Panel1Voltage[12] = Value / 1000;
	}
	if (CellON14 == true) {
		y = pulseIn(Cell14, HIGH, 100000);
		z = pulseIn(Cell14, LOW, 100000);
		Value = pwmConvert(z, y);
		_Panel1Voltage[13] = Value / 1000;
	}
}

void ReadVoltageBloco2() {
	for (int x = 0; x < N_Celulas; x++) {
		digitalWrite(_Panel2Port[x], HIGH);

		delay(myDelay);

		float var2 = GetVoltage2();

		_Panel2Voltage[x] = var2;

		Serial.println((String)"Bloco : 2 - Porta : " + _Panel2Port[x] + " - " + _Panel2Voltage[x]);

		digitalWrite(_Panel2Port[x], LOW);

		delay(myDelay);
	}
}


float GetVoltage1() {
	delay(500);
	int16_t adc0;
	adc0 = SensorADS.readADC_SingleEnded(0);
	float  myVoltage = (adc0*0.1875) / 1000;
	return myVoltage + random(2, 5);
}

float GetVoltage2() {
	delay(500);
	int16_t adc0;
	adc0 = SensorADS.readADC_SingleEnded(0);
	float  myVoltage = (adc0*0.1875) / 1000;
	return myVoltage + random(2, 5);
}


int pwmConvert(int z, int y)
{
	int x = z + y;
	int v = (int)(4975UL * z / x);
	return v;
}
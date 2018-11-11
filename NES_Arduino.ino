/*
BSD 2-Clause License

Copyright (c) Skyliegirl33 2018,
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice,
this list of conditions and the following disclaimer in the documentation
and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/*
 Name:		NES_arduino.ino
 Created:	10/27/2018 7:50:44 PM
 Author:	lucy
*/

#include "Joystick.h"

const int buttons[8] = { 0, 1, 2, 3, 4, 5, 6, 7 };

int clkPin = 2; // Red wire
int latchPin = 3; // Orange wire
int dataPin = 4; // Yellow wire

byte ctrlRegister = 0;
byte lastState = 0;

Joystick_ joystick;

void setup() {
	joystick.begin(false);
	joystick.setXAxisRange(-1, 1);
	joystick.setYAxisRange(-1, 1);

	pinMode(dataPin, INPUT);

	pinMode(clkPin, OUTPUT);
	pinMode(latchPin, OUTPUT);

	digitalWrite(clkPin, LOW);
	digitalWrite(latchPin, LOW);
}

void loop() {
	ctrlRegister = readNESCtrl();

	delay(10);

	if (bitRead(ctrlRegister, buttons[0]) == 0)
		joystick.setButton(buttons[0], 1);
	else
		joystick.setButton(buttons[0], 0);

	if (bitRead(ctrlRegister, buttons[1]) == 0)
		joystick.setButton(buttons[1], 1);
	else
		joystick.setButton(buttons[1], 0);

	if (bitRead(ctrlRegister, buttons[2]) == 0)
		joystick.setButton(buttons[2], 1);
	else
		joystick.setButton(buttons[2], 0);

	if (bitRead(ctrlRegister, buttons[3]) == 0)
		joystick.setButton(buttons[3], 1);
	else
		joystick.setButton(buttons[3], 0);


	if (bitRead(ctrlRegister, buttons[4]) == 0)
		joystick.setHatSwitch(0, 0);

	if (bitRead(ctrlRegister, buttons[5]) == 0)
		joystick.setHatSwitch(0, 180);

	if (bitRead(ctrlRegister, buttons[6]) == 0)
		joystick.setHatSwitch(0, 270);

	if (bitRead(ctrlRegister, buttons[7]) == 0)
		joystick.setHatSwitch(0, 90);

	if (bitRead(ctrlRegister, buttons[4]) == 1
		&& bitRead(ctrlRegister, buttons[5]) == 1
		&& bitRead(ctrlRegister, buttons[6]) == 1
		&& bitRead(ctrlRegister, buttons[7]) == 1)
		joystick.setHatSwitch(0, -1);

	joystick.sendState();
}


byte readNESCtrl() {
	int tmp = 0xFF;

	digitalWrite(latchPin, HIGH);
	digitalWrite(latchPin, LOW);

	if (digitalRead(dataPin) == 0)
		bitClear(tmp, B_A);

	digitalWrite(clkPin, HIGH);
	digitalWrite(clkPin, LOW);

	if (digitalRead(dataPin) == 0)
		bitClear(tmp, B_B);

	digitalWrite(clkPin, HIGH);
	digitalWrite(clkPin, LOW);

	if (digitalRead(dataPin) == 0)
		bitClear(tmp, B_SELECT);

	digitalWrite(clkPin, HIGH);
	digitalWrite(clkPin, LOW);

	if (digitalRead(dataPin) == 0)
		bitClear(tmp, B_START);

	digitalWrite(clkPin, HIGH);
	digitalWrite(clkPin, LOW);

	if (digitalRead(dataPin) == 0)
		bitClear(tmp, B_UP);

	digitalWrite(clkPin, HIGH);
	digitalWrite(clkPin, LOW);

	if (digitalRead(dataPin) == 0)
		bitClear(tmp, B_DOWN);

	digitalWrite(clkPin, HIGH);
	digitalWrite(clkPin, LOW);

	if (digitalRead(dataPin) == 0)
		bitClear(tmp, B_LEFT);

	digitalWrite(clkPin, HIGH);
	digitalWrite(clkPin, LOW);

	if (digitalRead(dataPin) == 0)
		bitClear(tmp, B_RIGHT);

	return tmp;
}
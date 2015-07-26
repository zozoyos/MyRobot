#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7); //These are the pins used on this shield

// Buttons
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

int lcd_key = 0;
int adc_key_in = 0;
int adc_key_prev = 0;

char **programs;
int index;
int max;
double time = 1;

int start = 48;
//
int d31 = 31;
int d33 = 33;
int d35 = 35;
int d37 = 37;

int o1 = 52;//3;
int o2 = 50;//4;
int o3 = 48;//5;
int o4 = 46;//6;

//
void setup() {
	//
	index = 0;
	int size = 10;
	programs = (char**)malloc(sizeof(char*) * size);
	for (int i = 0; i < size; i++) {
		programs[i] = (char*)malloc(sizeof(char) * 16);
	}
	programs[0] = "GO FRONT";
	programs[1] = "GO BACK";
	programs[2] = "GO RIGHT";
	programs[3] = "GO LEFT";
	programs[4] = "BLACK LINE";
	programs[5] = "BLUETOOTH";
	max = 5;

	Serial.begin(9600);
	Serial2.begin(9600);
	
		pinMode(d31, INPUT);
		pinMode(d33, INPUT);
		pinMode(d35, INPUT);
		pinMode(d37, INPUT);

		pinMode(o1, OUTPUT);
		pinMode(o2, OUTPUT);
		pinMode(o3, OUTPUT);
		pinMode(o4, OUTPUT);

		

	lcd.begin(16, 2);
	lcd.setCursor(0, 0);
	lcd.print("* Zohar Robot *");
	lcd.setCursor(0, 1);
	lcd.print("***************");
	delay(2000);
	


}

void whereToGo() {
	if (index == 0) {
		digitalWrite(o1, HIGH);
		digitalWrite(o2, LOW);
		digitalWrite(o3, HIGH);
		digitalWrite(o4, LOW);
		delay(time * 1000);
	}

	if (index == 1) {
		digitalWrite(o1, LOW);
		digitalWrite(o2, HIGH);
		digitalWrite(o3, LOW);
		digitalWrite(o4, HIGH);
		delay(time * 1000);
	}

	if (index == 2) {
		digitalWrite(o1, LOW);
		digitalWrite(o2, HIGH);
		digitalWrite(o3, HIGH);
		digitalWrite(o4, LOW);
		delay(400);
	}

	if (index == 3) {
		digitalWrite(o1, HIGH);
		digitalWrite(o2, LOW);
		digitalWrite(o3, LOW);
		digitalWrite(o4, HIGH);
		delay(400);
	}

	digitalWrite(o1, LOW);
	digitalWrite(o2, LOW);
	digitalWrite(o3, LOW);
	digitalWrite(o4, LOW);

}

void loop()
{
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print("SELECT PROGRAM:");

	adc_key_prev = lcd_key;       // Looking for changes
	lcd_key = read_LCD_buttons();  // read the buttons


	lcd.setCursor(0, 1);            // move to the begining of the second line

	switch (lcd_key)               // depending on which button was pushed, we perform an action
	{
	case btnRIGHT:
	{
		lcd.print("RIGHT ");
		break;
	}
	case btnLEFT:
	{
		lcd.print("LEFT   ");
		break;
	}
	case btnUP:
	{
		if (index == 0) index = max;
		else index--;
		lcd.print("                ");
		//lcd.print("UP    ");
		break;
	}
	case btnDOWN:
	{
		if (index == max) index = 0;
		else index++;
		lcd.print("                ");
		//lcd.print("DOWN  ");
		break;
	}
	case btnSELECT:
	{
		if (index == 0 || index == 1) {
			time = 1;
			lcd.clear();
			lcd.setCursor(0, 0);
			lcd.print("select time: ");
			delay(300);
			lcd_key = read_LCD_buttons();  // read the buttons
			while (lcd_key != btnSELECT) {
				lcd_key = read_LCD_buttons();  // read the buttons
				delay(200);
				if (lcd_key == btnLEFT && time > 0) time--;
				if (lcd_key == btnRIGHT && time < 10) time++;
				if (lcd_key == btnNONE) {
					lcd.setCursor(0, 1);
					lcd.print(time);
					lcd.setCursor(1, 1);
					lcd.print(" Sec");
				}
			}
			whereToGo();
		}

		if (index == 2 || index == 3) {
			time = 1;
			lcd.clear();
			lcd.print("I turn around");
			delay(300);
			whereToGo();
		}

		if (index == 4) {
			lcd.clear();
			lcd.setCursor(0, 0);
			lcd.print("BE READY...!");
			delay(1500);
			lcd.clear();
			lcd.setCursor(0, 0);
			lcd.print("the value of sensor is: ");
			int a = 0;
			int b = 0;
			int c = 0;
			int d = 0;
			
			digitalWrite(o1, HIGH);
			digitalWrite(o2, LOW);
			digitalWrite(o3, HIGH);
			digitalWrite(o4, LOW);

			while ((a != 1 || d != 1) && (b != 1 || c != 1) && (a != 1 || b != 1) && (c != 1 || d != 1)) {
				lcd.setCursor(3, 1);
				lcd.print(a);
				lcd.setCursor(6, 1);
				lcd.print(b);
				lcd.setCursor(9, 1);
				lcd.print(c);
				lcd.setCursor(12, 1);
				lcd.print(d);

				a = digitalRead(d31);
				b = digitalRead(d33);
				c = digitalRead(d35);
				d = digitalRead(d37);
				Serial.print(a);
				Serial.print(b);
				Serial.print(c);
				Serial.println(d);
				delay(20);
			}
			digitalWrite(o1, LOW);
			digitalWrite(o2, LOW);
			digitalWrite(o3, LOW);
			digitalWrite(o4, LOW);
		}

		if (index == 5) {
			lcd.clear();
			lcd.setCursor(0, 0);
			start = 48;
			lcd.print("** BLUE-TOOTH **");
			lcd.setCursor(0, 1);
			lcd.print("Connect via APP");
			delay(1000);
			while (start != 49) {
				while (Serial2.available() == 0);
				start = Serial2.read() - '0';
				Serial.println(start);
				if (start == 8) {
					lcd.setCursor(0, 1);
					lcd.print("GO BACK via BT  ");
					digitalWrite(o1, HIGH);
					digitalWrite(o2, LOW);
					digitalWrite(o3, HIGH);
					digitalWrite(o4, LOW);
				}

				if (start == 2) {
					lcd.setCursor(0, 1);
					lcd.print("GO FRONT via BT ");
					digitalWrite(o1, LOW);
					digitalWrite(o2, HIGH);
					digitalWrite(o3, LOW);
					digitalWrite(o4, HIGH);
				}

				if (start == 4) {
					lcd.setCursor(0, 1);
					lcd.print("GO LEFT via BT  ");
					digitalWrite(o1, HIGH);
					digitalWrite(o2, LOW);
					digitalWrite(o3, LOW);
					digitalWrite(o4, HIGH);
				}

				if (start == 6) {
					lcd.setCursor(0, 1);
					lcd.print("GO RIGHT via BT ");
					digitalWrite(o1, LOW);
					digitalWrite(o2, HIGH);
					digitalWrite(o3, HIGH);
					digitalWrite(o4, LOW);
				}

				if (start == 5) {
					lcd.setCursor(0, 1);
					lcd.print("S-T-O-P via BT  ");
					digitalWrite(o1, LOW);
					digitalWrite(o2, LOW);
					digitalWrite(o3, LOW);
					digitalWrite(o4, LOW);
				}
				
			}
			lcd.clear();
			
			lcd.print("return to");
			lcd.setCursor(6, 1);
			lcd.print("keypad...");
			index = 0;

			delay(2000);

		}
		break;
	}
	case btnNONE:
	{
		lcd.print(programs[index]);
		break;
	}
	}
	delay(300);
}

int read_LCD_buttons()
{
	adc_key_in = analogRead(0);      // read the value from the sensor 
	delay(5); //switch debounce delay. Increase this delay if incorrect switch selections are returned.
	int k = (analogRead(0) - adc_key_in); //gives the button a slight range to allow for a little contact resistance noise
	if (5 < abs(k)) return btnNONE;  // double checks the keypress. If the two readings are not equal +/-k value after debounce delay, it tries again.
	// my buttons when read are centered at these valies: 0, 144, 329, 504, 741
	// we add approx 50 to those values and check to see if we are close
	if (adc_key_in > 1000) return btnNONE; // We make this the 1st option for speed reasons since it will be the most likely result
	if (adc_key_in < 50)   return btnRIGHT;
	if (adc_key_in < 195)  return btnUP;
	if (adc_key_in < 380)  return btnDOWN;
	if (adc_key_in < 555)  return btnLEFT;
	if (adc_key_in < 790)  return btnSELECT;
	return btnNONE;  // when all others fail, return this...
}
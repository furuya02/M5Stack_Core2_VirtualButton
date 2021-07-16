#include <M5Core2.h>
#include "VButton.h"

VButton *red_button;
VButton *blue_button;
VButton *green_button;

void button_callback(char *title, bool use_toggle, bool is_toggled){
	if (use_toggle) {
		Serial.printf("%s Toggled. %d\n", title, is_toggled);
	} else {
		Serial.printf("%s Tapped.\n", title);
	}
}

void setup() {
	M5.begin(true, true, true, true);
	M5.Lcd.setBrightness(200);
	M5.Lcd.fillScreen(WHITE);
 
	red_button = new VButton("red_button", button_callback, true, -70);
	blue_button = new VButton("blue_button", button_callback, false, 0, BLUE);	
	green_button = new VButton("green_button", button_callback, false, 70, TFT_DARKGREEN);
}

void loop() {
	red_button->loop();
	blue_button->loop();
	green_button->loop();
}

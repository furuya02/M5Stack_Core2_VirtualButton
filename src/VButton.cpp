#include <M5Core2.h>
#include "VButton.h"

VButton::VButton(char *title, void (* callback)(char *, bool, bool), bool use_toggle, int position, uint color){
	this->title = title;
	this->callback = callback;
	this->use_toggle = use_toggle;

	line_color = color;
	background_color_normal = this->create_background_color_normal(color);
	background_color_toggle = this->create_background_color_toggle(color);

	int default_width = 150;
	int default_height = 50;
	int default_line_width = 3;
	width = default_width;
	height = default_height;
	line_width = default_line_width;

	display_center_x = M5.Lcd.width()/2;
	display_center_y = M5.Lcd.height()/2;

	rx = display_center_x -  width/2;
	y = display_center_y + position;
	lx = display_center_x +  width/2;
	h = height/2;

	this->position = position;

	dispButton(position, false);
}

void VButton::loop(){
	if(M5.Touch.ispressed()) {
		TouchPoint_t atTouchPoint;
		atTouchPoint = M5.Touch.getPressPoint();
		if(rx <= atTouchPoint.x && atTouchPoint.x < lx){
			if(y-h <= atTouchPoint.y && atTouchPoint.y < y+h){
				// Serial.printf("use_toggle:[%d] is_toggled:[%d]\n", use_toggle, is_toggled);
				if (use_toggle) {
					is_toggled ^= 1;
					dispButton(position, is_toggled);
					delay(100);
				} else {
					dispButton(position, true);
					delay(100);
					dispButton(position, false);
				}
				callback(title, use_toggle, is_toggled);
			}
		}
	}
}

// rgb = {RED, GREEN, BLUE}
void VButton::get_rgb(ushort color, uint rgb[3]){
	rgb[0] = (color & 0xF800) >> 8;
	rgb[1] = (color & 0x07E0) >> 3;
	rgb[2] = (color & 0x001F) << 3;
}

ushort VButton::create_color(uint rgb[3]){
  return ((rgb[0]>>3)<<11) | ((rgb[1]>>2)<<5) | (rgb[2]>>3);
}

ushort VButton::create_background_color_normal(uint color){
	uint rgb[3];
	this->get_rgb(color, rgb);
	for(int i=0; i<3; i++) {
		rgb[i] += 200;
		if (rgb[i] > 0xFF) {
			rgb[i] = 0xFF;
		}
	}
	return this->create_color(rgb);
}

ushort VButton::create_background_color_toggle(uint color){
	uint rgb[3];
	this->get_rgb(color, rgb);
	for(int i=0; i<3; i++) {
		rgb[i] += 100;
		if (rgb[i] > 0xFF) {
			rgb[i] = 0xFF;
		}
	}
	return this->create_color(rgb);
}

void VButton::dispButton(int position, bool toggle){
	
	uint background_color = toggle ? background_color_toggle : background_color_normal;
	uint text_color = toggle ? WHITE : line_color; 

	// 左円 
	M5.Lcd.fillEllipse(rx, y, h, h, background_color);
	for( int i=0; i < line_width; i++){
		M5.Lcd.drawEllipse(rx, y, h - i, h - i, line_color);
	}  
	// 右円 
	M5.Lcd.fillEllipse(lx, y, h, h, background_color);
	for(int i=0; i < line_width; i++){
		M5.Lcd.drawEllipse(lx, y, h - i, h - i, line_color);
	}  
	// 長方形
	M5.Lcd.fillRect(rx, y - h, width, height, background_color); 
	// 上線
	for(int i=0; i < line_width; i++){
		M5.Lcd.drawLine(rx, y - h + i, lx, y - h  + i, line_color);
	}
	// 下線
	for(int i=0; i < line_width; i++){
		M5.Lcd.drawLine(rx, y + h - i, lx, y + h - i, line_color);
	}

	M5.Lcd.setTextSize(1);
	M5.Lcd.setTextColor(text_color);
	M5.Lcd.drawCentreString(title, display_center_x, display_center_y + position - h/2, 4);
}


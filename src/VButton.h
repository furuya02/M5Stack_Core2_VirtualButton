#ifndef VButton_h
#define VButton_h

class VButton {
	public:
		VButton(char *title, void (* callback)(char *, bool, bool), bool use_toggle = false,int position = 0, uint color = RED);  
		void loop();

	private:
		char *title;
		bool use_toggle;
		bool is_toggled = false;

		// Coordinate
		int position;
		int display_center_x;
		int display_center_y;
		int width;
		int height;
		int line_width;
		int rx;
		int lx;
		int y;
		int h;

		// Callback
		void (* callback)(char *, bool, bool);

		// Color
		uint line_color;
		uint background_color_normal;
		uint background_color_toggle;

		void get_rgb(ushort color, uint rgb[3]);
		ushort create_color(uint rgb[3]);
		ushort create_background_color_normal(uint color);
		ushort create_background_color_toggle(uint color);
	
		// Display
		void dispButton(int position, bool toggle);

};

#endif

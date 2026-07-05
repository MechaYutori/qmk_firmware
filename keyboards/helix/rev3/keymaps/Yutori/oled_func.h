#ifndef OLED_FUNCTIONS
#define OLED_FUNCTIONS

void layout_display(void);
//void display_os_logo(uint8_t args);
void status_led_display(void);
void current_layer_display(void);
void draw_host_akanechan(uint8_t count);
void render_rgbled_status(uint8_t count);
void draw_cliant_akanechan(uint8_t count);
void draw_twitch_logo(uint8_t count);
const char *u8_str_mod(uint8_t curr_num, char curr_pad);

#endif
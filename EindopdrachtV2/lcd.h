/*
 * lcd.h
 *
 * Created: 13-2-2019 14:40:41
 *  Author: Maarten
 */ 


#ifndef LCD_H_
#define LCD_H_

void init_lcd(void);
void display_test(void);
void lcd_strobe_lcd(void);
void lcd_write_string(char *string);
void lcd_write_data(unsigned char byte);
void set_cursor(unsigned int posHex);
void clear_display();
#endif /* LCD_H_ */
#include "lcd_i2c.h"
#include "string.h"

#define LCD_ADDR 0x4E
static I2C_HandleTypeDef *lcd_i2c;

void lcd_send_cmd(char cmd) {
  uint8_t data[2] = {0x00, cmd};
  HAL_I2C_Master_Transmit(lcd_i2c, LCD_ADDR, data, 2, HAL_MAX_DELAY);
}

void lcd_send_data(char data) {
  uint8_t data_arr[2] = {0x40, data};
  HAL_I2C_Master_Transmit(lcd_i2c, LCD_ADDR, data_arr, 2, HAL_MAX_DELAY);
}

void lcd_init(I2C_HandleTypeDef *hi2c) {
  lcd_i2c = hi2c;
  HAL_Delay(50);
  lcd_send_cmd(0x38);
  lcd_send_cmd(0x0C);
  lcd_send_cmd(0x01);
  HAL_Delay(2);
}

void lcd_setCursor(uint8_t col, uint8_t row) {
  lcd_send_cmd(0x80 | (row ? 0x40 : 0x00) | col);
}

void lcd_print(char *str) {
  while(*str) lcd_send_data(*str++);
}

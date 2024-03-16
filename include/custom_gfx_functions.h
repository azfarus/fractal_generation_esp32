#include <Arduino.h>
#include <Arduino_GFX_Library.h>

#define WR 1 << 21
#define DC 1 << 20


extern uint16_t * frameBuffer;

void draw_line(int x1, int y1, int x2, int y2, uint16_t COLOR);
void init_frameBuffer();
void writeData(uint32_t d);
void draw_frame();
void clear_frame(uint16_t COLOR = BLACK);
void draw_triangle(int x1 , int y1 , int x2 , int y2 , int x3 , int y3 , uint16_t COLOR);
void draw_rect(int x1 , int y1 , int x2 , int y2 , int x3 , int y3 , int x4 , int y4 , uint16_t COLOR);
void draw_point(int x1 , int y1 , uint16_t COLOR);
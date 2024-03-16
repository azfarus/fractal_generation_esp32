#include <custom_gfx_functions.h>

uint16_t *frameBuffer = NULL;

void init_frameBuffer()
{
    frameBuffer = (uint16_t *)heap_caps_malloc(sizeof(uint16_t) * 320 * 480, MALLOC_CAP_SPIRAM);
    clear_frame();
}

void IRAM_ATTR clear_frame(uint16_t COLOR)
{
    memset(frameBuffer, COLOR, sizeof(uint16_t) * 320 * 480);
}

void IRAM_ATTR writeData(uint32_t d)
{

    REG_WRITE(GPIO_OUT_REG, d << 1 | DC);
    REG_WRITE(GPIO_OUT_W1TS_REG, WR);
}

void draw_line(int x1, int y1, int x2, int y2, uint16_t COLOR)
{
    if (x2 == x1)
    {

        int del = (y2 - y1) > 0 ? 1 : -1;

        for (int y = y1; y != y2; y += del)
        {
            frameBuffer[y * 480 + x2] = COLOR;
        }
        return;
    }

    float slope = (y2 - y1) / (float)(x2 - x1);
    int bigdel = 0;
    if (x2 > x1)
        bigdel = 1;
    else
        bigdel = -1;

    int yend, yprev = y1;
    //frameBuffer[y1 * 480 + x1] = COLOR;
    for (int x = x1; x != x2; x += bigdel)
    {
        yend = slope * (x - x1) + y1;
        
        if(yend < 0 ) yend = 0;
        if(yend >=320) yend = 319;
        
        int del = (yend - yprev) > 0 ? 1 : -1;
        frameBuffer[yprev * 480 + x] = COLOR;
        for (int y = yprev; y != yend; y += del)
        {
            frameBuffer[y * 480 + x] = COLOR;
        }
        yprev = yend;
    }

    return;
}

void IRAM_ATTR draw_frame()
{

    for (int i = 0; i < 320; i++)
    {
        for (int j = 0; j < 480; j++)
        {
            writeData(frameBuffer[i * 480 + j]);
        }
    }

    return;
}

void draw_triangle(int x1 , int y1 , int x2 , int y2 , int x3 , int y3 , uint16_t COLOR){
    draw_line(x1 , y1 , x2 , y2  , COLOR);
    draw_line(x2 , y2 , x3 , y3  , COLOR);
    draw_line(x3 , y3 , x1 , y1  , COLOR);
}

void draw_rect(int x1 , int y1 , int x2 , int y2 , int x3 , int y3 ,int x4 , int y4 , uint16_t COLOR){
    draw_line(x1 , y1 , x2 , y2  , COLOR);
    draw_line(x2 , y2 , x4 , y4  , COLOR);
    draw_line(x3 , y3 , x4 , y4  , COLOR);
    draw_line(x3 , y3 , x1 , y1  , COLOR);
}

void draw_point(int x1 , int y1 , uint16_t COLOR){
    if(x1 < 480 && y1 < 320 && x1 >= 0 && y1 >= 0){
        //int pixel = y1*480 + x1;
        frameBuffer[y1*480 + x1] = COLOR;
    }
    
}
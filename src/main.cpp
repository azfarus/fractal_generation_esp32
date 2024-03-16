#include <Arduino.h>
#include<esp_task_wdt.h>
#include <Arduino_GFX_Library.h>
#include <Car.h>
#include <esp_partition.h>
#include <custom_gfx_functions.h>

Arduino_ESP32PAR16 *bus = new Arduino_ESP32PAR16(20 /* DC */, GFX_NOT_DEFINED /* CS */, 21 /* WR */, GFX_NOT_DEFINED /* RD */,
                                                 1 /* D0 */, 2 /* D1 */, 3 /* D2 */, 4 /* D3 */, 5 /* D4 */, 6 /* D5 */, 7 /* D6 */, 8 /* D7 */,
                                                 9 /* D8 */, 10 /* D9 */, 11 /* D10 */, 12 /* D11 */, 13 /* D12 */, 14 /* D13 */, 15 /* D14 */, 16 /* D15 */);

Arduino_ILI9486 *gfx = new Arduino_ILI9486(bus, DF_GFX_RST, 3 /* rotation */, false /* IPS */);


TaskHandle_t Task1;

void render_task(void *pv)
{
  esp_task_wdt_init(30, false);
  while (true)
  {
    gfx->writeAddrWindow(0, 0, 480, 320);
    for (int i = 0; i < 320; i++)
    {
        for (int j = 0; j < 480; j++)
        {
            writeData(frameBuffer[i*480 + j]);
        }
    }
  }
}

void setup()
{
  esp_task_wdt_init(30, false);
  Serial.begin(115200);
  gfx->begin(80000000);

  for (int i = 0; i < 210; i++)
  {
    for (int j = 0; j < 240; j++)
    {

      images[i * 240 + j] &= 0b01111011111111100;
    }
  }

  init_frameBuffer();

  xTaskCreatePinnedToCore(render_task, "render_task", 4096, &Task1 , 10, NULL, 0);
}
void mandlebrot(int x1 , int y1 , int x2 , int y2 , int x3 , int y3 , uint16_t COLOR , int level ){

    if(level > 5) return;
    draw_triangle(x1 , y1 , x2 , y2 , x3 , y3 , COLOR);
    delay(100);
    int midx_a= (x1+x2)/2; 
    int midy_a= (y1+y2)/2;

    int midx_b= (x3+x2)/2; 
    int midy_b= (y3+y2)/2;

    int midx_c= (x1+x3)/2; 
    int midy_c= (y1+y3)/2;

    level++;
    mandlebrot(x1 , y1 , midx_a , midy_a , midx_c , midy_c , COLOR , level);
    mandlebrot(x2 , y2 , midx_a , midy_a , midx_b , midy_b , COLOR , level);
    mandlebrot(x3 , y3 , midx_b , midy_b , midx_c , midy_c , COLOR , level);
}

void fractal_square(int x1 , int y1 , int x2 , int y2 , int x3 , int y3,int x4  ,int y4 , uint16_t COLOR , int level){
    if(level > 10) return;
    draw_rect(x1 , y1 , x2 , y2 , x3 , y3 ,x4, y4, COLOR);
    delay(100);
    int midx_a= (x1+x2)/2; 
    int midy_a= (y1+y2)/2;

    int midx_b= (x4+x2)/2; 
    int midy_b= (y4+y2)/2;

    int midx_c= (x4+x3)/2; 
    int midy_c= (y4+y3)/2;
    
    int midx_d= (x1+x3)/2; 
    int midy_d= (y1+y3)/2;

    level++;
    mandlebrot(x1 , y1 , midx_a , midy_a , midx_d , midy_d , COLOR , level);
    mandlebrot(x2 , y2 , midx_a , midy_a , midx_b , midy_b , COLOR , level);
    mandlebrot(x3 , y3 , midx_d , midy_d , midx_c , midy_c , COLOR , level);
    mandlebrot(x4 , y4 , midx_b , midy_b , midx_c , midy_c , COLOR , level);

    fractal_square(midx_a , midy_a ,midx_b , midy_b ,midx_d , midy_d,midx_c , midy_c , COLOR , level);
}

double x = 0.0 , y = 0.64 , ca = 0.0 , cb = 0.64;
void IRAM_ATTR loop()
{




  //draw_line(240, 160, 240 + 100*sin(i*DEG_TO_RAD), 160 + 100*cos(i*DEG_TO_RAD), BLUE);
  //draw_triangle(80 , 320 , 400 , 320 , 240 , 0 , BLUE);

   //fractal_square(0 , 0 , 480 , 0 , 0 , 320 ,480 , 320, ORANGE , 0);
  mandlebrot(0 , 320 , 480 , 320 , 240 , 0 , BLUE , 0);
  // delay(50);
  //clear_frame();

  // for(int i = 0 ; i < 480 ; i++){
  //   for(int j = 0 ; j < 320 ; j++){

  //     double x = (i-240)/160.0 - 0.5 , y = (j -160)/160.0 ;
  //     double x0 = x , y0 = y;

      
  //     for(int it = 0 ; it < 30 ; it++){
  //         double tempx = x*x -y*y +x0;
  //         double tempy = 2*x*y +y0;
  //         x = tempx;
  //         y = tempy;
  //         //Serial.printf("%f %f \n", x , y );
  //     }
      
  //     if(x > 1e15 || y > 1e15 || x < -1e15 || y < -1e15 || isnan(x) || isnan(y) ){
  //       draw_point(i , j , RED);
  //     }
  //     else{
  //       draw_point(i , j , BLACK);
  //     }
  //   }
  // }
  //delay(300);
}
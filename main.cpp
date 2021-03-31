#include "mbed.h"
#include "uLCD_4DGL.h"
// Initialize a pins to perform analog and digital output functions
// Adjust analog output pin name to your board spec.
AnalogOut aout(PA_4);
DigitalOut dout(LED1);
DigitalIn up(PA_2);
DigitalIn down(PA_7);
DigitalIn selec(PA_6);
AnalogIn Ain(A0);
float ADCdata[100];
uLCD_4DGL uLCD(D1, D0, D2); // serial tx, serial rx, reset pin;


void sel(const int A[], int count)
{
   uLCD.text_width(1); //4X size text
   uLCD.text_height(2);
   uLCD.color(BLUE);
   uLCD.textbackground_color(GREEN);
   uLCD.background_color(GREEN);
   uLCD.printf("Frequency:\n");
   uLCD.locate(0, 2);
   for (int i = 0; i < 4; i++)
   {
      if (i + 1 == count)
      {
         // uLCD.locate(0, 2);
         uLCD.text_width(1); //4X size text
         uLCD.text_height(2);
         uLCD.color(RED);
      }
      else
      {
         uLCD.text_width(1); //4X size text
         uLCD.text_height(2);
         uLCD.color(BLACK);
      }
      uLCD.printf("%d Hz\n", A[i]);
   }
}

void signal(const int freq)
{

   int s = 0;
   int ID[9] = {1, 0, 8, 0, 6, 1, 1, 1, 8};
   for (int i = 0; i < 9; i++)
      s += ID[i];
   s = s % 10;
   int sample = 1000;
 

   while (1)
   {
      if (freq == 200)
      {
         for (float i = 0.0f; i < 1.0f; i += 0.1f)
         {
            aout = i;
            dout = (aout > 0.5f) ? 1 : 0;
            wait_us(200);
         }

         for (float i = 1.0f; i > 0.0f; i -= 0.1f)
         {
            aout = i;
            dout = (aout > 0.5f) ? 1 : 0;
            wait_us(300);
         }
      }
      else if (freq == 100)
      {
         for (float i = 0.0f; i < 1.0f; i += 0.1f)
         {
            aout = i;
            dout = (aout > 0.5f) ? 1 : 0;
            wait_us(400);
         }

         for (float i = 1.0f; i > 0.0f; i -= 0.1f)
         {
            aout = i;
            dout = (aout > 0.5f) ? 1 : 0;
            wait_us(600);
         }
      }
      else if (freq == 10)
      {
         for (float i = 0.0f; i < 1.0f; i += 0.1f)
         {
            aout = i;
            dout = (aout > 0.5f) ? 1 : 0;
            ThisThread::sleep_for(4ms);
         }

         for (float i = 1.0f; i > 0.0f; i -= 0.1f)
         {
            aout = i;
            dout = (aout > 0.5f) ? 1 : 0;
            ThisThread::sleep_for(6ms);
         }
      }
      else
      {
         for (float i = 0.0f; i < 1.0f; i += 0.1f)
         {
            aout = i;
            dout = (aout > 0.5f) ? 1 : 0;
            ThisThread::sleep_for(60ms);
         }

         for (float i = 1.0f; i > 0.0f; i -= 0.1f)
         {
            aout = i;
            dout = (aout > 0.5f) ? 1 : 0;
            ThisThread::sleep_for(40ms);
         }
      }
      for(int i = 0; i< sample; i++)
      {
          ADCdata[i]= Ain;
   
         ThisThread::sleep_for(1ms/sample);
      }
        for(int i = 0; i< sample; i++)
      {
      
           printf("%f\r\n", ADCdata[i]);
         ThisThread::sleep_for(1ms);
      }
  
   }
}

int main(void)
{

   //uLCD.printf("500 Hz\n");

   const int freq[4] = {200, 100, 10, 1};
   int count = 0;

   while (1)
   {
      if (up)
      {
         uLCD.cls();
         if (count >= 4)
         {
            count = 1;
            ThisThread::sleep_for(2ms);
         }
         else
         {
            count++;
            ThisThread::sleep_for(8ms);
         }
         sel(freq, count);
      }
      else if (down)
      {
         uLCD.cls();
         if (count <= 1)
         {
            count = 4;
            ThisThread::sleep_for(50ms);
         }
         else
         {
            count--;
            ThisThread::sleep_for(50ms);
         }
         sel(freq, count);
      }
      else if (selec)
      {
         break;
         ThisThread::sleep_for(50ms);
      }

      ThisThread::sleep_for(50ms);
   }
   uLCD.cls();
   uLCD.text_width(1); //4X size text
   uLCD.text_height(2);
   uLCD.color(BLACK);
   uLCD.printf("\nYou select %d Hz\n", freq[count - 1]);
   signal(freq[count - 1]);
}
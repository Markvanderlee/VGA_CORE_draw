//--------------------------------------------------------------
// File     : main.c
// Datum    : 30.03.2016
// Version  : 1.0
// Autor    : UB
// mods by	: J.F. van der Bent
// CPU      : STM32F4
// IDE      : CooCox CoIDE 1.7.x
// Module   : CMSIS_BOOT, M4_CMSIS_CORE
// Function : VGA_core DMA LIB 320x240, 8bit color
//--------------------------------------------------------------

#include "main.h"
#include "stm32_ub_vga_screen.h"
#include <math.h>
#include "delay.h"
#include "APIio.h"
#include <includes.h>


int main(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	GPIOD -> MODER |= ( 1 << 26 );
	GPIOD -> MODER |= ( 1 << 30 );


	SystemInit(); // System speed to 168MHz
	DELAY_init();
	UART_init();

	UB_VGA_Screen_Init(); // Init VGA-Screen


	int kleur = 50;

	UB_VGA_FillScreen(VGA_COL_BLACK);

	char tekst[] = {'m', 'a', 'r', 'k', ' ', 'i', 's', ' ', 'g', 'e', 'k'};

	int i = 0;

	int lengte = sizeof(tekst) / sizeof(tekst[0]) -1;

	int width = 222;
	int height = 227;


	//int y = 150;
	//int x = 150;

	int plaatje[] = {55,55,55,55,55,55,55,55,55,55,55,55,55,59,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55
			,55,55,55,55,55,55,55,55,55,55,55,55,55,123,59,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55
			,55,59,59,59,55,55,55,55,55,55,55,55,55,59,59,55,55,55,55,55,55,55,55,55,59,55,55,55,55,55
			,55,55,91,123,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,123,123,55,55,55,55
			,55,91,187,155,91,55,55,59,123,155,191,191,191,191,191,191,155,159,155,191,155,123,59,55,59,91,55,55,55,55
			,55,59,91,123,55,91,191,223,191,123,91,59,55,55,55,55,55,55,55,55,91,155,223,123,55,55,55,55,55,55
			,55,55,55,59,55,223,155,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,59,223,91,55,55,123,91,55
			,55,55,55,55,59,255,91,55,55,55,55,55,59,91,91,91,91,59,55,55,55,55,55,123,187,55,55,123,91,55
			,55,55,55,55,123,255,55,55,55,55,119,78,73,36,36,32,36,73,77,118,59,55,55,59,223,55,55,59,55,55
			,55,55,55,86,174,215,114,55,91,77,36,32,32,32,32,32,32,32,32,32,73,87,55,87,251,55,55,55,55,55
			,55,55,110,224,224,224,224,197,73,32,32,36,141,177,178,178,177,141,68,32,32,36,197,192,228,197,114,55,55,55
			,55,114,224,224,224,224,224,192,32,32,141,250,250,250,250,250,250,250,250,177,36,64,224,224,224,224,224,169,55,55
			,55,137,224,224,224,224,224,224,32,105,250,250,250,250,250,250,250,250,250,250,145,96,224,224,224,224,224,224,86,55
			,55,169,224,224,224,224,224,160,32,214,250,250,250,250,250,250,250,250,250,250,250,100,224,224,224,224,224,224,82,55
			,55,197,224,224,224,224,224,192,32,250,250,250,141,214,250,250,246,141,246,250,250,132,224,224,224,224,224,224,110,55
			,55,169,224,224,224,224,224,224,64,250,250,214,32,68,250,250,105,32,177,250,250,100,224,224,224,224,224,224,197,55
			,55,142,224,224,224,224,224,224,64,246,250,246,36,36,250,250,72,32,214,250,250,68,192,224,224,224,224,224,110,55
			,55,82,224,224,224,224,224,224,96,214,250,250,177,141,250,250,177,141,250,250,250,100,224,224,224,224,224,224,86,55
			,55,55,110,224,224,224,224,224,64,141,250,250,250,250,250,250,250,250,250,250,214,96,224,224,224,224,224,165,55,55
			,55,55,55,142,197,224,224,165,73,73,250,250,250,250,250,250,250,250,250,250,141,100,224,224,224,197,169,86,55,55
			,59,91,59,55,55,86,82,123,182,109,250,250,250,145,178,214,109,250,250,250,145,146,150,142,82,55,55,55,55,55
			,59,155,91,55,91,187,250,250,250,250,250,250,250,250,250,250,250,250,250,250,250,250,250,250,187,91,55,55,55,55
			,55,59,55,123,250,250,250,250,250,250,250,250,250,250,250,250,250,250,250,250,250,250,250,250,250,250,155,55,55,55
			,55,55,59,250,250,250,250,250,246,242,237,237,233,233,233,233,233,233,237,237,242,246,250,250,250,250,250,91,55,55
			,55,55,91,250,246,237,233,228,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,229,237,242,250,155,55,55
			,55,55,59,250,250,242,233,228,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,233,241,246,250,91,55,55
			,55,55,55,123,250,250,250,250,246,241,237,233,229,229,229,229,229,229,233,233,237,242,250,250,250,250,155,55,55,55
			,55,91,59,55,59,187,250,250,250,250,250,250,250,250,250,250,250,250,250,250,250,250,250,250,187,91,55,59,55,55
			,55,155,123,55,55,55,59,123,187,218,250,250,250,250,250,250,250,250,250,250,250,187,155,91,55,55,55,123,123,55
			,55,55,59,55,55,55,55,55,55,55,59,91,123,123,123,123,123,123,91,91,55,55,55,55,55,55,55,59,59,55
};

	int teller = 0;
	int yPos = 0;
	int xPos =0;





  while(1)
  {

	 /*
	  for(y=-height; y<=height; y++) {
	      for(x=-width; x<=width; x++) {
	          if(x*x*height*height+y*y*width*width <= height*height*width*width)
	        	  UB_VGA_SetPixel(150+x, 150+y, 150);
	      }
	  }
	*/
		/*for(yPos = 0; yPos <= height; yPos++){
			for (xPos =0; xPos<=width; xPos++){
				UB_VGA_SetPixel(xPos, yPos, plaatje[teller]);
				teller++;
			}

		}*/
		put_char_a(100,100,150);
		DELAY_ms(1000);
		UB_VGA_FillScreen(VGA_COL_BLACK);
/*
	  y = 50;
	  x = 0;

	  for (i=0; i<=lengte; i++)
	  {
		  char letter = tekst[i];
		  x = i*3+2;

			switch (letter){
			case 'a':
				put_char_a(x,y,kleur);
				break;
			case 'b':
				put_char_b(x,y,kleur);
				break;
			case 'c':
				put_char_c(x,y,kleur);
				break;
			case 'd':
				put_char_d(x,y,kleur);
				break;
			case 'e':
				put_char_e(x,y,kleur);
				break;
			case 'f':
				put_char_f(x,y,kleur);
				break;
			case 'g':
				put_char_g(x,y,kleur);
				break;
			case 'h':
				put_char_h(x,y,kleur);
				break;
			case 'i':
				put_char_i(x,y,kleur);
				break;
			case 'j':
				put_char_j(x,y,kleur);
				break;
			case 'k':
				put_char_k(x,y,kleur);
				break;
			case 'l':
				put_char_l(x,y,kleur);
				break;
			case 'm':
				put_char_m(x,y,kleur);
				break;
			case 'n':
				put_char_n(x,y,kleur);
				break;
			case 'o':
				put_char_o(x,y,kleur);
				break;
			case 'p':
				put_char_p(x,y,kleur);
				break;
			case 'q':
				put_char_q(x,y,kleur);
				break;
			case 'r':
				put_char_r(x,y,kleur);
				break;
			case 's':
				put_char_s(x,y,kleur);
				break;
			case 't':
				put_char_t(x,y,kleur);
				break;
			case 'u':
				put_char_u(x,y,kleur);
				break;
			case 'v':
				put_char_v(x,y,kleur);
				break;
			case 'w':
				put_char_w(x,y,kleur);
				break;
			case 'x':
				put_char_x(x,y,kleur);
				break;
			case 'y':
				put_char_y(x,y,kleur);
				break;
			case 'z':
				put_char_z(x,y,kleur);
				break;
			case ' ':
				put_char_spatie(x,y,kleur);
				break;
		  }

	  // DELAY_ms(100);
	  }
	  //DELAY_ms(1000);
	 // UB_VGA_FillScreen(VGA_COL_BLACK);
	  */
  }

}

void put_char_a(x,y,kleur){
	UB_VGA_SetPixel(1+x,y+1,0);
	UB_VGA_SetPixel(1+x,y+2,kleur);
	UB_VGA_SetPixel(1+x,y+3,kleur);
	UB_VGA_SetPixel(1+x,y+4,kleur);
	UB_VGA_SetPixel(1+x,y+5,kleur);
	UB_VGA_SetPixel(1+x,y+6,kleur);

	UB_VGA_SetPixel(2+x,y+1,kleur);
	UB_VGA_SetPixel(2+x,y+2,0);
	UB_VGA_SetPixel(2+x,y+3,0);
	UB_VGA_SetPixel(2+x,y+4,kleur);
	UB_VGA_SetPixel(2+x,y+5,0);
	UB_VGA_SetPixel(2+x,y+6,0);

	UB_VGA_SetPixel(3+x,y+1,0);
	UB_VGA_SetPixel(3+x,y+2,kleur);
	UB_VGA_SetPixel(3+x,y+3,kleur);
	UB_VGA_SetPixel(3+x,y+4,kleur);
	UB_VGA_SetPixel(3+x,y+5,kleur);
	UB_VGA_SetPixel(3+x,y+6,kleur);
}

void put_char_b(x,y,kleur){
	UB_VGA_SetPixel(1+x,y+1,kleur);
	UB_VGA_SetPixel(1+x,y+2,kleur);
	UB_VGA_SetPixel(1+x,y+3,kleur);
	UB_VGA_SetPixel(1+x,y+4,kleur);
	UB_VGA_SetPixel(1+x,y+5,kleur);
	UB_VGA_SetPixel(1+x,y+6,kleur);

	UB_VGA_SetPixel(2+x,y+1,kleur);
	UB_VGA_SetPixel(2+x,y+2,0);
	UB_VGA_SetPixel(2+x,y+3,kleur);
	UB_VGA_SetPixel(2+x,y+4,0);
	UB_VGA_SetPixel(2+x,y+5,0);
	UB_VGA_SetPixel(2+x,y+6,kleur);

	UB_VGA_SetPixel(3+x,y+1,0);
	UB_VGA_SetPixel(3+x,y+2,kleur);
	UB_VGA_SetPixel(3+x,y+3,0);
	UB_VGA_SetPixel(3+x,y+4,kleur);
	UB_VGA_SetPixel(3+x,y+5,kleur);
	UB_VGA_SetPixel(3+x,y+6,kleur);
}

void put_char_c(x,y,kleur){
	UB_VGA_SetPixel(1+x,y+1,0);
	UB_VGA_SetPixel(1+x,y+2,kleur);
	UB_VGA_SetPixel(1+x,y+3,kleur);
	UB_VGA_SetPixel(1+x,y+4,kleur);
	UB_VGA_SetPixel(1+x,y+5,kleur);
	UB_VGA_SetPixel(1+x,y+6,0);

	UB_VGA_SetPixel(2+x,y+1,kleur);
	UB_VGA_SetPixel(2+x,y+2,0);
	UB_VGA_SetPixel(2+x,y+3,0);
	UB_VGA_SetPixel(2+x,y+4,0);
	UB_VGA_SetPixel(2+x,y+5,0);
	UB_VGA_SetPixel(2+x,y+6,kleur);

	UB_VGA_SetPixel(3+x,y+1,0);
	UB_VGA_SetPixel(3+x,y+2,kleur);
	UB_VGA_SetPixel(3+x,y+3,0);
	UB_VGA_SetPixel(3+x,y+4,0);
	UB_VGA_SetPixel(3+x,y+5,kleur);
	UB_VGA_SetPixel(3+x,y+6,0);
}

void put_char_d(x,y,kleur){
	UB_VGA_SetPixel(1+x,y+1,kleur);
	UB_VGA_SetPixel(1+x,y+2,kleur);
	UB_VGA_SetPixel(1+x,y+3,kleur);
	UB_VGA_SetPixel(1+x,y+4,kleur);
	UB_VGA_SetPixel(1+x,y+5,kleur);
	UB_VGA_SetPixel(1+x,y+6,kleur);

	UB_VGA_SetPixel(2+x,y+1,kleur);
	UB_VGA_SetPixel(2+x,y+2,0);
	UB_VGA_SetPixel(2+x,y+3,0);
	UB_VGA_SetPixel(2+x,y+4,0);
	UB_VGA_SetPixel(2+x,y+5,0);
	UB_VGA_SetPixel(2+x,y+6,kleur);

	UB_VGA_SetPixel(3+x,y+1,0);
	UB_VGA_SetPixel(3+x,y+2,kleur);
	UB_VGA_SetPixel(3+x,y+3,kleur);
	UB_VGA_SetPixel(3+x,y+4,kleur);
	UB_VGA_SetPixel(3+x,y+5,kleur);
	UB_VGA_SetPixel(3+x,y+6,0);
}

void put_char_e(x,y,kleur){
	UB_VGA_SetPixel(1+x,y+1,kleur);
	UB_VGA_SetPixel(1+x,y+2,kleur);
	UB_VGA_SetPixel(1+x,y+3,kleur);
	UB_VGA_SetPixel(1+x,y+4,kleur);
	UB_VGA_SetPixel(1+x,y+5,kleur);
	UB_VGA_SetPixel(1+x,y+6,kleur);

	UB_VGA_SetPixel(2+x,y+1,kleur);
	UB_VGA_SetPixel(2+x,y+2,0);
	UB_VGA_SetPixel(2+x,y+3,kleur);
	UB_VGA_SetPixel(2+x,y+4,0);
	UB_VGA_SetPixel(2+x,y+5,0);
	UB_VGA_SetPixel(2+x,y+6,kleur);

	UB_VGA_SetPixel(3+x,y+1,kleur);
	UB_VGA_SetPixel(3+x,y+2,0);
	UB_VGA_SetPixel(3+x,y+3,kleur);
	UB_VGA_SetPixel(3+x,y+4,0);
	UB_VGA_SetPixel(3+x,y+5,0);
	UB_VGA_SetPixel(3+x,y+6,kleur);
}

void put_char_f(x,y,kleur){
	UB_VGA_SetPixel(1+x,y+1,kleur);
	UB_VGA_SetPixel(1+x,y+2,kleur);
	UB_VGA_SetPixel(1+x,y+3,kleur);
	UB_VGA_SetPixel(1+x,y+4,kleur);
	UB_VGA_SetPixel(1+x,y+5,kleur);
	UB_VGA_SetPixel(1+x,y+6,kleur);

	UB_VGA_SetPixel(2+x,y+1,kleur);
	UB_VGA_SetPixel(2+x,y+2,0);
	UB_VGA_SetPixel(2+x,y+3,0);
	UB_VGA_SetPixel(2+x,y+4,kleur);
	UB_VGA_SetPixel(2+x,y+5,0);
	UB_VGA_SetPixel(2+x,y+6,0);

	UB_VGA_SetPixel(3+x,y+1,kleur);
	UB_VGA_SetPixel(3+x,y+2,0);
	UB_VGA_SetPixel(3+x,y+3,0);
	UB_VGA_SetPixel(3+x,y+4,0);
	UB_VGA_SetPixel(3+x,y+5,0);
	UB_VGA_SetPixel(3+x,y+6,0);
}

void put_char_g(x,y,kleur){
	UB_VGA_SetPixel(1+x,y+1,kleur);
	UB_VGA_SetPixel(1+x,y+2,kleur);
	UB_VGA_SetPixel(1+x,y+3,kleur);
	UB_VGA_SetPixel(1+x,y+4,kleur);
	UB_VGA_SetPixel(1+x,y+5,kleur);
	UB_VGA_SetPixel(1+x,y+6,kleur);

	UB_VGA_SetPixel(2+x,y+1,kleur);
	UB_VGA_SetPixel(2+x,y+2,0);
	UB_VGA_SetPixel(2+x,y+3,0);
	UB_VGA_SetPixel(2+x,y+4,kleur);
	UB_VGA_SetPixel(2+x,y+5,0);
	UB_VGA_SetPixel(2+x,y+6,kleur);

	UB_VGA_SetPixel(3+x,y+1,kleur);
	UB_VGA_SetPixel(3+x,y+2,kleur);
	UB_VGA_SetPixel(3+x,y+3,0);
	UB_VGA_SetPixel(3+x,y+4,kleur);
	UB_VGA_SetPixel(3+x,y+5,kleur);
	UB_VGA_SetPixel(3+x,y+6,kleur);
}

void put_char_i(x,y,kleur){
	UB_VGA_SetPixel(1+x,y+1,kleur);
	UB_VGA_SetPixel(1+x,y+2,0);
	UB_VGA_SetPixel(1+x,y+3,0);
	UB_VGA_SetPixel(1+x,y+4,0);
	UB_VGA_SetPixel(1+x,y+5,0);
	UB_VGA_SetPixel(1+x,y+6,kleur);

	UB_VGA_SetPixel(2+x,y+1,kleur);
	UB_VGA_SetPixel(2+x,y+2,kleur);
	UB_VGA_SetPixel(2+x,y+3,kleur);
	UB_VGA_SetPixel(2+x,y+4,kleur);
	UB_VGA_SetPixel(2+x,y+5,kleur);
	UB_VGA_SetPixel(2+x,y+6,kleur);

	UB_VGA_SetPixel(3+x,y+1,kleur);
	UB_VGA_SetPixel(3+x,y+2,0);
	UB_VGA_SetPixel(3+x,y+3,0);
	UB_VGA_SetPixel(3+x,y+4,0);
	UB_VGA_SetPixel(3+x,y+5,0);
	UB_VGA_SetPixel(3+x,y+6,kleur);
}

void put_char_j(x,y,kleur){
	UB_VGA_SetPixel(1+x,y+1,0);
	UB_VGA_SetPixel(1+x,y+2,0);
	UB_VGA_SetPixel(1+x,y+3,0);
	UB_VGA_SetPixel(1+x,y+4,0);
	UB_VGA_SetPixel(1+x,y+5,kleur);
	UB_VGA_SetPixel(1+x,y+6,kleur);

	UB_VGA_SetPixel(2+x,y+1,kleur);
	UB_VGA_SetPixel(2+x,y+2,0);
	UB_VGA_SetPixel(2+x,y+3,0);
	UB_VGA_SetPixel(2+x,y+4,0);
	UB_VGA_SetPixel(2+x,y+5,0);
	UB_VGA_SetPixel(2+x,y+6,kleur);

	UB_VGA_SetPixel(3+x,y+1,kleur);
	UB_VGA_SetPixel(3+x,y+2,kleur);
	UB_VGA_SetPixel(3+x,y+3,kleur);
	UB_VGA_SetPixel(3+x,y+4,kleur);
	UB_VGA_SetPixel(3+x,y+5,kleur);
	UB_VGA_SetPixel(3+x,y+6,kleur);
}
void put_char_h(x,y,kleur){
	UB_VGA_SetPixel(1+x,y+1,kleur);
	UB_VGA_SetPixel(1+x,y+2,kleur);
	UB_VGA_SetPixel(1+x,y+3,kleur);
	UB_VGA_SetPixel(1+x,y+4,kleur);
	UB_VGA_SetPixel(1+x,y+5,kleur);
	UB_VGA_SetPixel(1+x,y+6,kleur);

	UB_VGA_SetPixel(2+x,y+1,0);
	UB_VGA_SetPixel(2+x,y+2,0);
	UB_VGA_SetPixel(2+x,y+3,kleur);
	UB_VGA_SetPixel(2+x,y+4,0);
	UB_VGA_SetPixel(2+x,y+5,0);
	UB_VGA_SetPixel(2+x,y+6,0);

	UB_VGA_SetPixel(3+x,y+1,kleur);
	UB_VGA_SetPixel(3+x,y+2,kleur);
	UB_VGA_SetPixel(3+x,y+3,kleur);
	UB_VGA_SetPixel(3+x,y+4,kleur);
	UB_VGA_SetPixel(3+x,y+5,kleur);
	UB_VGA_SetPixel(3+x,y+6,kleur);
}

void put_char_k(x,y,kleur){
	UB_VGA_SetPixel(1+x,y+1,kleur);
	UB_VGA_SetPixel(1+x,y+2,kleur);
	UB_VGA_SetPixel(1+x,y+3,kleur);
	UB_VGA_SetPixel(1+x,y+4,kleur);
	UB_VGA_SetPixel(1+x,y+5,kleur);
	UB_VGA_SetPixel(1+x,y+6,kleur);

	UB_VGA_SetPixel(2+x,y+1,0);
	UB_VGA_SetPixel(2+x,y+2,0);
	UB_VGA_SetPixel(2+x,y+3,kleur);
	UB_VGA_SetPixel(2+x,y+4,0);
	UB_VGA_SetPixel(2+x,y+5,0);
	UB_VGA_SetPixel(2+x,y+6,0);

	UB_VGA_SetPixel(3+x,y+1,kleur);
	UB_VGA_SetPixel(3+x,y+2,kleur);
	UB_VGA_SetPixel(3+x,y+3,0);
	UB_VGA_SetPixel(3+x,y+4,kleur);
	UB_VGA_SetPixel(3+x,y+5,kleur);
	UB_VGA_SetPixel(3+x,y+6,kleur);
}

void put_char_l(x,y,kleur){
	UB_VGA_SetPixel(1+x,y+1,kleur);
	UB_VGA_SetPixel(1+x,y+2,kleur);
	UB_VGA_SetPixel(1+x,y+3,kleur);
	UB_VGA_SetPixel(1+x,y+4,kleur);
	UB_VGA_SetPixel(1+x,y+5,kleur);
	UB_VGA_SetPixel(1+x,y+6,kleur);

	UB_VGA_SetPixel(2+x,y+1,0);
	UB_VGA_SetPixel(2+x,y+2,0);
	UB_VGA_SetPixel(2+x,y+3,0);
	UB_VGA_SetPixel(2+x,y+4,0);
	UB_VGA_SetPixel(2+x,y+5,0);
	UB_VGA_SetPixel(2+x,y+6,kleur);

	UB_VGA_SetPixel(3+x,y+1,0);
	UB_VGA_SetPixel(3+x,y+2,0);
	UB_VGA_SetPixel(3+x,y+3,0);
	UB_VGA_SetPixel(3+x,y+4,0);
	UB_VGA_SetPixel(3+x,y+5,0);
	UB_VGA_SetPixel(3+x,y+6,kleur);
}

void put_char_m(x,y,kleur){
	UB_VGA_SetPixel(1+x,y+1,kleur);
	UB_VGA_SetPixel(1+x,y+2,kleur);
	UB_VGA_SetPixel(1+x,y+3,kleur);
	UB_VGA_SetPixel(1+x,y+4,kleur);
	UB_VGA_SetPixel(1+x,y+5,kleur);
	UB_VGA_SetPixel(1+x,y+6,kleur);

	UB_VGA_SetPixel(2+x,y+1,0);
	UB_VGA_SetPixel(2+x,y+2,kleur);
	UB_VGA_SetPixel(2+x,y+3,0);
	UB_VGA_SetPixel(2+x,y+4,0);
	UB_VGA_SetPixel(2+x,y+5,0);
	UB_VGA_SetPixel(2+x,y+6,0);

	UB_VGA_SetPixel(3+x,y+1,kleur);
	UB_VGA_SetPixel(3+x,y+2,kleur);
	UB_VGA_SetPixel(3+x,y+3,kleur);
	UB_VGA_SetPixel(3+x,y+4,kleur);
	UB_VGA_SetPixel(3+x,y+5,kleur);
	UB_VGA_SetPixel(3+x,y+6,kleur);
}

void put_char_n(x,y,kleur){
	UB_VGA_SetPixel(1+x,y+1,kleur);
	UB_VGA_SetPixel(1+x,y+2,kleur);
	UB_VGA_SetPixel(1+x,y+3,kleur);
	UB_VGA_SetPixel(1+x,y+4,kleur);
	UB_VGA_SetPixel(1+x,y+5,kleur);
	UB_VGA_SetPixel(1+x,y+6,kleur);

	UB_VGA_SetPixel(2+x,y+1,kleur);
	UB_VGA_SetPixel(2+x,y+2,0);
	UB_VGA_SetPixel(2+x,y+3,0);
	UB_VGA_SetPixel(2+x,y+4,0);
	UB_VGA_SetPixel(2+x,y+5,0);
	UB_VGA_SetPixel(2+x,y+6,0);

	UB_VGA_SetPixel(3+x,y+1,kleur);
	UB_VGA_SetPixel(3+x,y+2,kleur);
	UB_VGA_SetPixel(3+x,y+3,kleur);
	UB_VGA_SetPixel(3+x,y+4,kleur);
	UB_VGA_SetPixel(3+x,y+5,kleur);
	UB_VGA_SetPixel(3+x,y+6,kleur);
}

void put_char_o(x,y,kleur)
{
	UB_VGA_SetPixel(1+x,y+1,0);
	UB_VGA_SetPixel(1+x,y+2,kleur);
	UB_VGA_SetPixel(1+x,y+3,kleur);
	UB_VGA_SetPixel(1+x,y+4,kleur);
	UB_VGA_SetPixel(1+x,y+5,kleur);
	UB_VGA_SetPixel(1+x,y+6,0);

	UB_VGA_SetPixel(2+x,y+1,kleur);
	UB_VGA_SetPixel(2+x,y+2,0);
	UB_VGA_SetPixel(2+x,y+3,0);
	UB_VGA_SetPixel(2+x,y+4,0);
	UB_VGA_SetPixel(2+x,y+5,0);
	UB_VGA_SetPixel(2+x,y+6,kleur);

	UB_VGA_SetPixel(3+x,y+1,0);
	UB_VGA_SetPixel(3+x,y+2,kleur);
	UB_VGA_SetPixel(3+x,y+3,kleur);
	UB_VGA_SetPixel(3+x,y+4,kleur);
	UB_VGA_SetPixel(3+x,y+5,kleur);
	UB_VGA_SetPixel(3+x,y+6,0);
}

void put_char_p(x,y,kleur){
	UB_VGA_SetPixel(1+x,y+1,kleur);
	UB_VGA_SetPixel(1+x,y+2,kleur);
	UB_VGA_SetPixel(1+x,y+3,kleur);
	UB_VGA_SetPixel(1+x,y+4,kleur);
	UB_VGA_SetPixel(1+x,y+5,kleur);
	UB_VGA_SetPixel(1+x,y+6,kleur);

	UB_VGA_SetPixel(2+x,y+1,kleur);
	UB_VGA_SetPixel(2+x,y+2,0);
	UB_VGA_SetPixel(2+x,y+3,kleur);
	UB_VGA_SetPixel(2+x,y+4,0);
	UB_VGA_SetPixel(2+x,y+5,0);
	UB_VGA_SetPixel(2+x,y+6,0);

	UB_VGA_SetPixel(3+x,y+1,0);
	UB_VGA_SetPixel(3+x,y+2,kleur);
	UB_VGA_SetPixel(3+x,y+3,kleur);
	UB_VGA_SetPixel(3+x,y+4,0);
	UB_VGA_SetPixel(3+x,y+5,0);
	UB_VGA_SetPixel(3+x,y+6,0);
}

void put_char_q(x,y,kleur){
	UB_VGA_SetPixel(1+x,y+1,0);
	UB_VGA_SetPixel(1+x,y+2,kleur);
	UB_VGA_SetPixel(1+x,y+3,kleur);
	UB_VGA_SetPixel(1+x,y+4,0);
	UB_VGA_SetPixel(1+x,y+5,0);
	UB_VGA_SetPixel(1+x,y+6,0);

	UB_VGA_SetPixel(2+x,y+1,kleur);
	UB_VGA_SetPixel(2+x,y+2,0);
	UB_VGA_SetPixel(2+x,y+3,0);
	UB_VGA_SetPixel(2+x,y+4,kleur);
	UB_VGA_SetPixel(2+x,y+5,0);
	UB_VGA_SetPixel(2+x,y+6,0);

	UB_VGA_SetPixel(3+x,y+1,0);
	UB_VGA_SetPixel(3+x,y+2,kleur);
	UB_VGA_SetPixel(3+x,y+3,kleur);
	UB_VGA_SetPixel(3+x,y+4,kleur);
	UB_VGA_SetPixel(3+x,y+5,kleur);
	UB_VGA_SetPixel(3+x,y+6,kleur);
}

void put_char_r(x,y,kleur){
	UB_VGA_SetPixel(1+x,y+1,kleur);
	UB_VGA_SetPixel(1+x,y+2,kleur);
	UB_VGA_SetPixel(1+x,y+3,kleur);
	UB_VGA_SetPixel(1+x,y+4,kleur);
	UB_VGA_SetPixel(1+x,y+5,kleur);
	UB_VGA_SetPixel(1+x,y+6,kleur);

	UB_VGA_SetPixel(2+x,y+1,kleur);
	UB_VGA_SetPixel(2+x,y+2,0);
	UB_VGA_SetPixel(2+x,y+3,kleur);
	UB_VGA_SetPixel(2+x,y+4,0);
	UB_VGA_SetPixel(2+x,y+5,0);
	UB_VGA_SetPixel(2+x,y+6,0);

	UB_VGA_SetPixel(3+x,y+1,0);
	UB_VGA_SetPixel(3+x,y+2,kleur);
	UB_VGA_SetPixel(3+x,y+3,0);
	UB_VGA_SetPixel(3+x,y+4,kleur);
	UB_VGA_SetPixel(3+x,y+5,kleur);
	UB_VGA_SetPixel(3+x,y+6,kleur);
}

void put_char_s(x,y,kleur){
	UB_VGA_SetPixel(1+x,y+1,0);
	UB_VGA_SetPixel(1+x,y+2,kleur);
	UB_VGA_SetPixel(1+x,y+3,kleur);
	UB_VGA_SetPixel(1+x,y+4,0);
	UB_VGA_SetPixel(1+x,y+5,0);
	UB_VGA_SetPixel(1+x,y+6,kleur);

	UB_VGA_SetPixel(2+x,y+1,kleur);
	UB_VGA_SetPixel(2+x,y+2,0);
	UB_VGA_SetPixel(2+x,y+3,0);
	UB_VGA_SetPixel(2+x,y+4,kleur);
	UB_VGA_SetPixel(2+x,y+5,0);
	UB_VGA_SetPixel(2+x,y+6,kleur);

	UB_VGA_SetPixel(3+x,y+1,0);
	UB_VGA_SetPixel(3+x,y+2,kleur);
	UB_VGA_SetPixel(3+x,y+3,0);
	UB_VGA_SetPixel(3+x,y+4,0);
	UB_VGA_SetPixel(3+x,y+5,kleur);
	UB_VGA_SetPixel(3+x,y+6,0);
}

void put_char_t(x,y,kleur){
	UB_VGA_SetPixel(1+x,y+1,kleur);
	UB_VGA_SetPixel(1+x,y+2,0);
	UB_VGA_SetPixel(1+x,y+3,0);
	UB_VGA_SetPixel(1+x,y+4,0);
	UB_VGA_SetPixel(1+x,y+5,0);
	UB_VGA_SetPixel(1+x,y+6,0);

	UB_VGA_SetPixel(2+x,y+1,kleur);
	UB_VGA_SetPixel(2+x,y+2,kleur);
	UB_VGA_SetPixel(2+x,y+3,kleur);
	UB_VGA_SetPixel(2+x,y+4,kleur);
	UB_VGA_SetPixel(2+x,y+5,kleur);
	UB_VGA_SetPixel(2+x,y+6,kleur);

	UB_VGA_SetPixel(3+x,y+1,kleur);
	UB_VGA_SetPixel(3+x,y+2,0);
	UB_VGA_SetPixel(3+x,y+3,0);
	UB_VGA_SetPixel(3+x,y+4,0);
	UB_VGA_SetPixel(3+x,y+5,0);
	UB_VGA_SetPixel(3+x,y+6,0);
}

void put_char_u(x,y,kleur){
	UB_VGA_SetPixel(1+x,y+1,kleur);
	UB_VGA_SetPixel(1+x,y+2,kleur);
	UB_VGA_SetPixel(1+x,y+3,kleur);
	UB_VGA_SetPixel(1+x,y+4,kleur);
	UB_VGA_SetPixel(1+x,y+5,kleur);
	UB_VGA_SetPixel(1+x,y+6,kleur);

	UB_VGA_SetPixel(2+x,y+1,0);
	UB_VGA_SetPixel(2+x,y+2,0);
	UB_VGA_SetPixel(2+x,y+3,0);
	UB_VGA_SetPixel(2+x,y+4,0);
	UB_VGA_SetPixel(2+x,y+5,0);
	UB_VGA_SetPixel(2+x,y+6,0);

	UB_VGA_SetPixel(3+x,y+1,kleur);
	UB_VGA_SetPixel(3+x,y+2,kleur);
	UB_VGA_SetPixel(3+x,y+3,kleur);
	UB_VGA_SetPixel(3+x,y+4,kleur);
	UB_VGA_SetPixel(3+x,y+5,kleur);
	UB_VGA_SetPixel(3+x,y+6,kleur);
}

void put_char_v(x,y,kleur){
	UB_VGA_SetPixel(1+x,y+1,kleur);
	UB_VGA_SetPixel(1+x,y+2,kleur);
	UB_VGA_SetPixel(1+x,y+3,kleur);
	UB_VGA_SetPixel(1+x,y+4,kleur);
	UB_VGA_SetPixel(1+x,y+5,kleur);
	UB_VGA_SetPixel(1+x,y+6,0);

	UB_VGA_SetPixel(2+x,y+1,0);
	UB_VGA_SetPixel(2+x,y+2,0);
	UB_VGA_SetPixel(2+x,y+3,0);
	UB_VGA_SetPixel(2+x,y+4,0);
	UB_VGA_SetPixel(2+x,y+5,0);
	UB_VGA_SetPixel(2+x,y+6,kleur);

	UB_VGA_SetPixel(3+x,y+1,kleur);
	UB_VGA_SetPixel(3+x,y+2,kleur);
	UB_VGA_SetPixel(3+x,y+3,kleur);
	UB_VGA_SetPixel(3+x,y+4,kleur);
	UB_VGA_SetPixel(3+x,y+5,kleur);
	UB_VGA_SetPixel(3+x,y+6,0);
}

void put_char_w(x,y,kleur){
	UB_VGA_SetPixel(1+x,y+1,kleur);
	UB_VGA_SetPixel(1+x,y+2,kleur);
	UB_VGA_SetPixel(1+x,y+3,kleur);
	UB_VGA_SetPixel(1+x,y+4,kleur);
	UB_VGA_SetPixel(1+x,y+5,kleur);
	UB_VGA_SetPixel(1+x,y+6,kleur);

	UB_VGA_SetPixel(2+x,y+1,0);
	UB_VGA_SetPixel(2+x,y+2,0);
	UB_VGA_SetPixel(2+x,y+3,0);
	UB_VGA_SetPixel(2+x,y+4,0);
	UB_VGA_SetPixel(2+x,y+5,kleur);
	UB_VGA_SetPixel(2+x,y+6,0);

	UB_VGA_SetPixel(3+x,y+1,kleur);
	UB_VGA_SetPixel(3+x,y+2,kleur);
	UB_VGA_SetPixel(3+x,y+3,kleur);
	UB_VGA_SetPixel(3+x,y+4,kleur);
	UB_VGA_SetPixel(3+x,y+5,kleur);
	UB_VGA_SetPixel(3+x,y+6,kleur);
}

void put_char_x(x,y,kleur){
	UB_VGA_SetPixel(1+x,y+1,kleur);
	UB_VGA_SetPixel(1+x,y+2,kleur);
	UB_VGA_SetPixel(1+x,y+3,kleur);
	UB_VGA_SetPixel(1+x,y+4,0);
	UB_VGA_SetPixel(1+x,y+5,kleur);
	UB_VGA_SetPixel(1+x,y+6,kleur);

	UB_VGA_SetPixel(2+x,y+1,0);
	UB_VGA_SetPixel(2+x,y+2,0);
	UB_VGA_SetPixel(2+x,y+3,0);
	UB_VGA_SetPixel(2+x,y+4,kleur);
	UB_VGA_SetPixel(2+x,y+5,0);
	UB_VGA_SetPixel(2+x,y+6,0);

	UB_VGA_SetPixel(3+x,y+1,kleur);
	UB_VGA_SetPixel(3+x,y+2,kleur);
	UB_VGA_SetPixel(3+x,y+3,kleur);
	UB_VGA_SetPixel(3+x,y+4,0);
	UB_VGA_SetPixel(3+x,y+5,kleur);
	UB_VGA_SetPixel(3+x,y+6,kleur);
}

void put_char_y(x,y,kleur){
	UB_VGA_SetPixel(1+x,y+1,kleur);
	UB_VGA_SetPixel(1+x,y+2,kleur);
	UB_VGA_SetPixel(1+x,y+3,0);
	UB_VGA_SetPixel(1+x,y+4,0);
	UB_VGA_SetPixel(1+x,y+5,0);
	UB_VGA_SetPixel(1+x,y+6,0);

	UB_VGA_SetPixel(2+x,y+1,0);
	UB_VGA_SetPixel(2+x,y+2,0);
	UB_VGA_SetPixel(2+x,y+3,kleur);
	UB_VGA_SetPixel(2+x,y+4,kleur);
	UB_VGA_SetPixel(2+x,y+5,kleur);
	UB_VGA_SetPixel(2+x,y+6,kleur);

	UB_VGA_SetPixel(3+x,y+1,kleur);
	UB_VGA_SetPixel(3+x,y+2,kleur);
	UB_VGA_SetPixel(3+x,y+3,0);
	UB_VGA_SetPixel(3+x,y+4,0);
	UB_VGA_SetPixel(3+x,y+5,0);
	UB_VGA_SetPixel(3+x,y+6,0);
}

void put_char_z(x,y,kleur){
	UB_VGA_SetPixel(1+x,y+1,kleur);
	UB_VGA_SetPixel(1+x,y+2,0);
	UB_VGA_SetPixel(1+x,y+3,0);
	UB_VGA_SetPixel(1+x,y+4,kleur);
	UB_VGA_SetPixel(1+x,y+5,kleur);
	UB_VGA_SetPixel(1+x,y+6,kleur);

	UB_VGA_SetPixel(2+x,y+1,kleur);
	UB_VGA_SetPixel(2+x,y+2,0);
	UB_VGA_SetPixel(2+x,y+3,kleur);
	UB_VGA_SetPixel(2+x,y+4,0);
	UB_VGA_SetPixel(2+x,y+5,0);
	UB_VGA_SetPixel(2+x,y+6,kleur);

	UB_VGA_SetPixel(3+x,y+1,kleur);
	UB_VGA_SetPixel(3+x,y+2,kleur);
	UB_VGA_SetPixel(3+x,y+3,0);
	UB_VGA_SetPixel(3+x,y+4,0);
	UB_VGA_SetPixel(3+x,y+5,0);
	UB_VGA_SetPixel(3+x,y+6,kleur);
}

void put_char_spatie(x,y,kleur){
	UB_VGA_SetPixel(1+x,y+1,0);
	UB_VGA_SetPixel(1+x,y+2,0);
	UB_VGA_SetPixel(1+x,y+3,0);
	UB_VGA_SetPixel(1+x,y+4,0);
	UB_VGA_SetPixel(1+x,y+5,0);
	UB_VGA_SetPixel(1+x,y+6,0);

	UB_VGA_SetPixel(2+x,y+1,0);
	UB_VGA_SetPixel(2+x,y+2,0);
	UB_VGA_SetPixel(2+x,y+3,0);
	UB_VGA_SetPixel(2+x,y+4,0);
	UB_VGA_SetPixel(2+x,y+5,0);
	UB_VGA_SetPixel(2+x,y+6,0);

	UB_VGA_SetPixel(3+x,y+1,0);
	UB_VGA_SetPixel(3+x,y+2,0);
	UB_VGA_SetPixel(3+x,y+3,0);
	UB_VGA_SetPixel(3+x,y+4,0);
	UB_VGA_SetPixel(3+x,y+5,0);
	UB_VGA_SetPixel(3+x,y+6,0);
}


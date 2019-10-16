// --------- LED LIGHT CHART ---------
// LEGS RGB 
// TORSO WS 54
// SHOULDER_RED EL 
// SHOULDER_BLUE EL
// FOREARM RGB
// INNER_PALM WS! 2
// OUTER_PALM WS! 2
// THIGH WS! 6
// MASK WS 5
// BELT WS 25
// TIMESTONE WS! 1


// Include LED libraries. 
#include <noise.h>
#include <bitswap.h>
#include <fastspi_types.h>
#include <pixelset.h>
#include <fastled_progmem.h>
#include <led_sysdefs.h>
#include <hsv2rgb.h>
#include <fastled_delay.h>
#include <colorpalettes.h>
#include <color.h>
#include <fastspi_ref.h>
#include <fastspi_bitbang.h>
#include <controller.h>
#include <fastled_config.h>
#include <colorutils.h>
#include <chipsets.h>
#include <pixeltypes.h>
#include <fastspi_dma.h>
#include <fastpin.h>
#include <fastspi_nop.h>
#include <platforms.h>
#include <lib8tion.h>
#include <cpp_compat.h>
#include <fastspi.h>
#include <FastLED.h>
#include <dmx.h>
#include <power_mgt.h>

// Light segment definitions.

#define LEG_R 1
#define LEG_G 2
#define LEG_B 3

#define TORSO 4

#define SHOULDER_R 5
#define SHOULDER_B 6

#define FOREARM_R 7
#define FOREARM_G 8
#define FOREARM_B 9

#define RIGHT_INNER_PALM 10
#define LEFT_INNER_PALM 11

#define RIGHT_OUTER_PALM 12
#define LEFT_OUTER_PALM 13

#define LEFT_THIGH 14
#define RIGHT_THIGH 15

#define MASK 16

#define BELT 17

// WS2811 arrays.
CRGB torso[54];
CRGB right_inner_palm[2];
CRGB left_inner_palm[2];
CRGB right_outer_palm[2];
CRGB left_outer_palm[2];
CRGB mask[5];
CRGB belt[25];

// --------------------Functions to make writing code easier-------
void wsFillColor(CRGB* light_strip, int len_strip, CRGB fill_color)
{
	for (int i = 0; i < len_strip; i++)
	{
		light_strip[i] = fill_color;
	}
	FastLED.show();
}

void rgbFillColor(int r_pin, int g_pin, int b_pin, int r, int g, int b)
{
	analogWrite(r_pin, r);
	analogWrite(g_pin, g);
	analogWrite(b_pin, b);
}

void transitionWS(CRGB* strip, int len_strip, int* c1, int* c2, int total_time, int steps)
{
	int red_step = (c2[0] - c1[0]) / steps;
	int green_step = (c2[1] - c1[1]) / steps;
	int blue_step = (c2[2] - c1[2]) / steps;
	
	int r, g, b;
	for (int i = 0; i < steps; i++)
	{
		delay(total_time / steps);
		r += red_step;
		g += green_step;
		b += blue_step;
		wsFillColor(strip, len_strip, CRGB(r, g, b));
		FastLED.show();	
	}
}

//---------------------------------------------------------------
void setup()
{
	// Leg
	pinMode(LEG_R, OUTPUT);
	pinMode(LEG_G, OUTPUT);
	pinMode(LEG_B, OUTPUT);

	// Torso
	FastLED.addLeds<WS2811, TORSO, RGB>(torso, 54);
	
	// Shoulder pads
	pinMode(SHOULDER_R, OUTPUT);
	pinMode(SHOULDER_B, OUTPUT);

	// Forearms
	pinMode(FOREARM_R, OUTPUT);
	pinMode(FOREARM_G, OUTPUT);
	pinMode(FOREARM_B, OUTPUT);
	
	// Palms
	FastLED.addLeds<WS2811, RIGHT_INNER_PALM, RGB>(right_inner_palm, 2);
	FastLED.addLeds<WS2811, LEFT_INNER_PALM, RGB>(left_inner_palm, 2);
	FastLED.addLeds<WS2811, RIGHT_OUTER_PALM, RGB>(right_outer_palm, 2);
	FastLED.addLeds<WS2811, LEFT_OUTER_PALM, RGB>(left_outer_palm, 2);
	
	// Mask
	FastLED.addLeds<WS2811, MASK, RGB>(mask, 5);
	
	// Belt
	FastLED.addLeds<WS2811, BELT, RGB>(belt, 25);
}

void loop()
{
// Variable to keep track of time
// Make sure all operations involving time are stored in long unsigned.
	long unsigned time_count = 0;
	
// Sequential suit boot up. 
// Legs -> Torso -> Shoulder+Forearms+Mask
	
	// LEGS ON
	rgbFillColor(LEG_R, LEG_G, LEG_B, 0, 0, 50);
	delay(2400 - time_count);
	time_count = 2400;
	
	// TORSO ON	
	wsFillColor(torso, 54, CRGB(0, 0, 50));
	delay(2800 - time_count);
	// AUXILLARY ON
	digitalWrite(SHOULDER_R, HIGH);
	rgbFillColor(FOREARM_R, FOREARM_G, FOREARM_B, 50, 0, 0);
	delay(14366 - time_count);
	time_count = 14366;
	
// Takes mushroom frenzy
	for (int i = 0; i < 4; i++)
	{
		// Luigi
		rgbFillColor(LEG_R, LEG_G, LEG_B, 0, 50, 0);
		wsFillColor(torso, 54, CRGB(0, 50, 0));
		digitalWrite(SHOULDER_R, LOW);
		rgbFillColor(FOREARM_R, FOREARM_G, FOREARM_B, 20, 20, 20);
		wsFillColor(mask, 5, CRGB(50, 0, 0));
		delay(200);
		
		// Mario
		rgbFillColor(LEG_R, LEG_G, LEG_B, 0, 0, 50);
		digitalWrite(SHOULDER_R, LOW);
		rgbFillColor(FOREARM_R, FOREARM_G, FOREARM_B,50, 0, 0);
		wsFillColor(mask, 5, CRGB(50, 0, 0));
		delay(200);
	}
	time_count = 15333;
	
	delay(34933 - time_count);
	time_count = 34933;

// Sequential suit shutdown. 
	digitalWrite(SHOULDER_R, LOW);
	rgbFillColor(FOREARM_R, FOREARM_G, FOREARM_B, 0, 0, 0);
	wsFillColor(mask, 5, CRGB(0, 0, 0));
	delay(200);
	wsFillColor(torso, 54, CRGB(0, 0, 0));
	delay(200);
	
	time_count = 37500;
	delay(39800 - time_count);
	
// Respawn blinking. 
	for (int i = 0; i < 5; i++)
	{
		// OFF
		rgbFillColor(LEG_R, LEG_G, LEG_B, 0, 0, 0);
		wsFillColor(torso, 54, CRGB(0, 0, 0));
		digitalWrite(SHOULDER_R, HIGH);
		rgbFillColor(FOREARM_R, FOREARM_G, FOREARM_B, 0, 0, 0);
		delay(300);

		// ON
		rgbFillColor(LEG_R, LEG_G, LEG_B, 0, 0, 50);
		wsFillColor(torso, 54, CRGB(0, 0, 50));
		digitalWrite(SHOULDER_R, HIGH);
		rgbFillColor(FOREARM_R, FOREARM_G, FOREARM_B, 0, 0, 50);
		
	}
	
// Frenzy mode.
	for (int i = 0; i < 19; i++)
	{
		// Luigi
		rgbFillColor(LEG_R, LEG_G, LEG_B, 0, 50, 0);
		wsFillColor(torso, 54, CRGB(0, 50, 0));
		digitalWrite(SHOULDER_R, LOW);
		rgbFillColor(FOREARM_R, FOREARM_G, FOREARM_B, 20, 20, 20);
		wsFillColor(mask, 5, CRGB(50, 0, 0));
		delay(200);
		
		// Mario
		rgbFillColor(LEG_R, LEG_G, LEG_B, 0, 0, 50);
		digitalWrite(SHOULDER_R, LOW);
		rgbFillColor(FOREARM_R, FOREARM_G, FOREARM_B,50, 0, 0);
		wsFillColor(mask, 5, CRGB(50, 0, 0));
		delay(200);
	}
	
}

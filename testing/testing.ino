// Code to sequentially test the whole suit. 
// Start each segment for 4 seconds.
// Test starts ~10 seconds after boot. 

// Face : R -> G -> B ->
// Shoulders
// Torso
// Forearms
// Hand gloves
// Palms 
// Legs
// Thigh plates
// Symbols
// 

#define POWER_IN 21
#define LEG_R 7 
#define LEG_G 8
#define LEG_B 9

#define TORSO 30

#define SHOULDER_R 53
#define SHOULDER_B 52

#define FOREARM_R 10
#define FOREARM_G 11
#define FOREARM_B 12

#define RIGHT_INNER_PALM 31
#define LEFT_INNER_PALM 32

#define RIGHT_OUTER_PALM 12
#define LEFT_OUTER_PALM 13

#define LEFT_THIGH 33
#define RIGHT_THIGH 34

#define MASK 35

#define SUPERMAN 51
#define IRONCIRCLE 50
#define FLASH 49
#define KMHM 48
#define	HANDS 47
#define HAIR 46


// WS2811 arrays.
CRGB torso[54];
CRGB right_inner_palm[2];
CRGB left_inner_palm[2];
CRGB right_outer_palm[2];
CRGB left_outer_palm[2];
CRGB left_thigh[6];
CRGB right_thigh[6];
CRGB mask[11];

// Colors
CRGB R = CRGB(50, 0, 0);
CRGB G = CRGB(0, 50, 0);
CRGB B = CRGB(0, 0, 50);
CRGB M = CRGB(50, 0, 0);

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
	FastLED.addLeds<WS2811, TORSO, BRG>(torso, 54);

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
	FastLED.addLeds<WS2811, MASK, RGB>(mask, 11);

	// Hands
	pinMode(HANDS, OUTPUT);
	
	// Thighs
	FastLED.addLeds<WS2811, LEFT_THIGH, RGB>(left_thigh, 6);
	FastLED.addLeds<WS2811, RIGHT_THIGH, RGB>(right_thigh, 6);
	
	//Auxillary ELs
	pinMode(SUPERMAN, OUTPUT);
	pinMode(IRONCIRCLE, OUTPUT);
	pinMode(FLASH, OUTPUT);
	pinMode(KMHM, OUTPUT);
 
}


void loop() {
	// POWER IN PIN DO NOT MESS.
	digitalWrite(POWER_IN, HIGH);

	// Set everything to 0. 
	// WS -> RGB -> EL
	
	wsFillColor(left_thigh, 6, CRGB(0, 0, 0));
	wsFillColor(right_thigh, 6, CRGB(0, 0, 0));
	wsFillColor(torso, 54, CRGB(0, 0, 0));
	wsFillColor(mask, , CRGB(0, 0, 0));
	wsFillColor(left_outer_palm, 2, CRGB(0, 0, 0));
	wsFillColor(right_outer_palm, 2, CRGB(0, 0, 0));
	wsFillColor(left_inner_palm, 2, CRGB(0, 0, 0));

	rgbFillColor(LEG_R, LEG_G, LEG_B, 0, 0, 0);
	rgbFillColor(FOREARM_R, FOREARM_G, FOREARM_B, 0, 0, 0);

	digitalWrite(SHOULDER_R, LOW);
	digitalWrite(SHOULDER_B, LOW);
	digitalWrite(HANDS, LOW);
	digitalWrite(HAIR, LOW);
	digitalWrite(SUPERMAN, LOW);
	digitalWrite(IRONCIRCLE, LOW);
	digitalWrite(FLASH, LOW);
	digitalWrite(KMHM, LOW);

	delay(4000);
	// INIT TESTING

	// Going down the body.

	// Hair
	digitalWrite(HAIR, HIGH);
	delay(2000);
	digitalWrite(HAIR, LOW);
	
	// Face
	wsFillColor(mask, 11, R);	
	wsFillColor(mask, 11, G);	
	wsFillColor(mask, 11, B);
	wsFillColor(mask, 11, M);
	delay(4000);
	// Shoulder
	digitalWrite(SHOULDER_R, HIGH);
	digitalWrite(SHOULDER_B, HIGH);
	delay(4000);

	// Torso
	wsFillColor(mask, 11, R);	
	wsFillColor(mask, 11, G);	
	wsFillColor(mask, 11, B);
	wsFillColor(mask, 11, M);
	delay(4000);

	// Forearms
	rgbFillColor(FOREARM_R, FOREARM_G, FOREARM_B, 50, 0, 0);	
	rgbFillColor(FOREARM_R, FOREARM_G, FOREARM_B, 0, 50, 0);	
	rgbFillColor(FOREARM_R, FOREARM_G, FOREARM_B, 0, 0, 50);	
	rgbFillColor(FOREARM_R, FOREARM_G, FOREARM_B, 50, 20, 0);
	delay(4000);

	// Hands 
	digitalWrite(HANDS, HIGH);
	delay(4000);
	
	//Inner palms
	wsFillColor(left_inner_palm, 11, R);	
	wsFillColor(left_inner_palm, 11, G);	
	wsFillColor(left_inner_palm, 11, B);
	wsFillColor(left_inner_palm, 11, M);
	delay(4000);
	
	wsFillColor(right_inner_palm, 11, R);	
	wsFillColor(right_inner_palm, 11, G);	
	wsFillColor(right_inner_palm, 11, B);
	wsFillColor(right_inner_palm, 11, M);
	delay(4000);
	
	// Outer palm
	wsFillColor(right_outer_palm, 11, R);	
	wsFillColor(right_outer_palm, 11, G);	
	wsFillColor(right_outer_palm, 11, B);
	wsFillColor(right_outer_palm, 11, M);
	delay(4000);
	
	wsFillColor(left_outer_palm, 11, R);	
	wsFillColor(left_outer_palm, 11, G);	
	wsFillColor(left_outer_palm, 11, B);
	wsFillColor(left_outer_palm, 11, M);
	delay(4000);
	
	// Legs 
	rgbFillColor(LEG_R, LEG_G, LEG_B, 50, 0, 0);
	rgbFillColor(LEG_R, LEG_G, LEG_B, 0, 50, 0);
	rgbFillColor(LEG_R, LEG_G, LEG_B, 50, 0, 0);
	rgbFillColor(LEG_R, LEG_G, LEG_B, 0, 0, 50);
	
	// Thigh plates.
	wsFillColor(left_thigh, R);
	wsFillColor(left_thigh, G);
	wsFillColor(left_thigh, B);
	wsFillColor(left_thigh, M);

	// Symbols
	digitalWrite(IRONCIRCLE, HIGH);
	digitalWrite(FLASH, HIGH);
	digitalWrite(KMHM, HIGH);
	digitalWrite(SUPERMAN, HIGH);
}

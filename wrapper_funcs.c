#include <FastLED.h>

void wsFillColor(CRGB* light_strip, CRGB fill_color)
{
	int len_strip = sizeof(light_strip) / sizeof(CRGB);
	
	for (int i = 0; i < len_strip; i++)
	{
		light_strip[i] = fill_color;
	}
}

void rgbFillColor(int* pin_numbers, int* color)
{
	analogWrite(pin_numbers[0], color[0]);
	analogWrite(pin_numbers[1], color[1]);
	analogWrite(pin_numbers[2], color[2]);
}

void transitionWS(CRGB* strip, int* c1, int* c2, int total_time, int steps)
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
		wsFillColor(strip, CRGB(r, g, b));
		FastLED.show();	
	}
}	

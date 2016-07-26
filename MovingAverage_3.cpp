/* MovingAverage_3
 * 		A class to encapsulate the code required to compute a moving average
 *		Implemented for embedded microcontrollers; optimized use, minimal resources
 *		Uses a window size of 3
 *		Uses unsigned integers
 */
#ifndef uint8_t
#include <stdint.h>		//C99 data types, e.g. uint8_t etc
#endif
#include <math.h>		//rounding
#include <string.h> 	//memset 
//#include <stdio.h>		//printf debugging
#include "MovingAverage_3.h"


//NOTE: fmin is defined in math.h, but we will use Arduino macro from Arduino.h instead
#ifndef min
#define min(a,b) ((a)<(b)?(a):(b))
#endif


//Constructor
MovingAverage_3::MovingAverage_3()
	: 	w_idx(0),
		cur_avg(0),
		prev_avg(0),
		count(0)
{
	memset(window, 0, WDO_SIZE);
}


//Add sample to window & calculate moving average
//
//Three possible scenarios:
//
// 1) After adding the new sample we will have an exactly full window of samples (no more, no less)
//	  So we don't yet have a previous average. Use the average (mean) formula:
//		cur avg = sum of all samples / number of samples (i.e. window size)
//
// 2) We already have a full window of samples, so the previous average has already been calculated.
//	  Use the moving average (sliding window) formula: 
//		cur avg = prev avg + (new sample - oldest sample) / window size
//
// 3) We do not have a full window of samples, even after adding the new sample.
//	  An average value cannot yet be calculated
//
//TODO: optimize by using 2^n window size. Then use bit shifting instead of divide function.
//
//Pseudo-code:
//		If window will be exactly full after adding new sample:
//			add new sample to window buffer
//			calculate mean (average)
//			incr write index
//			save mean into prev avg
//		Else if window is already full (tap count >= window size) then calculate running average:
//			cur avg = prev avg + (new sample - oldest sample) / window size
//			write new sample to window buffer; overwrites oldest sample
//			incr write index
//			save mean into prev avg
//		Else, (window not full, and will not be full after adding sample)
//			add new sample to window buffer
//			incr write index
//	
void MovingAverage_3::add(unsigned int new_sample)
{
	count++;
	
	//window will just be newly full after adding sample; +1 because we store time deltas, thus need n+1 taps to get n time deltas
	if( count == WDO_SIZE ) {											
		add_(new_sample);									//store sample		
		avg_f = mean_();									//Calculate the mean (avg)
		cur_avg = roundf(avg_f);							//round to nearest int
		prev_avg = cur_avg;									//save for next invocation / tap capture
	}	
	//window is already full
	else if( count > WDO_SIZE ) {	
		//printf("old sample: %d ms\n\r", window[w_idx]);
		int diff =(int)new_sample - (int)window[w_idx];		//calc as signed in case difference is negative
		//printf("sample diff: %d ms\n\r", diff);						
		avg_f = (float)(diff) / (float)WDO_SIZE;			//calculate division part of equation first, using float variable; oldest sample is pointed to by idx
		//printf("windowed avg: %.3f\n\r", avg_f);
		cur_avg = prev_avg + roundf(avg_f);					//calculate rest of equation, rounding to nearest integer
		prev_avg = cur_avg;									//save for next invocation / sample capture
		
		add_(new_sample);									//store sample
	}
	//window is not already full, and it won't be even after adding new sample
	else  {																	
		add_(new_sample);									//store sample
	}

}

//get average value
unsigned int MovingAverage_3::get_avg()
{
	if( count < WDO_SIZE ) {						//we don't have enough samples; use average of two points
		avg_f = mean_();
		cur_avg = roundf(avg_f);					//round to nearest int
	}
	//else, we have enough samples; use curent value of moving average
	
	return cur_avg;
}			

//reset window
void MovingAverage_3::reset()				
{
	w_idx = 0;									
	count = 0;									
	cur_avg=0;									
	prev_avg=0;									
}

//Store the newest sample (time delta); overwrites the oldest sample; updates array index
void MovingAverage_3::add_(unsigned int new_sample)
{
	window[w_idx] = new_sample;
	w_idx = (w_idx >= WDO_SIZE-1) ? 0 : ++w_idx;		//keep write index within bounds of array; faster to do this than to use modulus (%) operator	
}

//calculates average (mean) of any values in window. Window need not be completely full
float MovingAverage_3::mean_() 
{
	unsigned int sum = 0;
	uint8_t wdo_count = min(count,WDO_SIZE);				//number of elements currently stored in the window
	for( uint8_t i = 0; i < wdo_count; i++ ) {				//sum all values in window
		sum += window[i];
	}
	
	return ( (float)sum / (float)wdo_count );				//calculate the average (mean)
}
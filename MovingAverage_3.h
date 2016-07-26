/* MovingAverage_3
 * 		A class to encapsulate the code required to compute a moving average
 *		Implemented for embedded microcontrollers; optimized use, minimal resources
 *		Uses a window size of 3
 *		Uses unsigned integers
 */
 
 
class MovingAverage_3 
{
	public:
		MovingAverage_3();
		void add(unsigned int);			//add sample to window
		unsigned int get_avg();			//get average value
		void reset();					//reset window
	
	private:
		void add_(unsigned int);					//handles circular buffer, indices, etc
		float mean_();								//calculates average (mean) of any values in window. Window need not be completely full
		
		static const uint8_t WDO_SIZE = 3;
		unsigned int window[WDO_SIZE];				//moving average window of time deltas; limited to 200 - 2000 ms (30 - 300 bpm); OK to use size < long
		uint8_t	w_idx;								//write index for the window buffer/array; points to oldest sample before writing new sample; 
													// points to new sample after writing; zero-based
		unsigned int cur_avg;						//calculated average time deltas
		unsigned int prev_avg;						//""
		float avg_f;								//temp float variable for calculations
		//unsigned long new_sample;					//holding place for new time delta; need long for comparing big time deltas
		//static unsigned long prev_time=0;			//timestamp of previous capture
		//unsigned long cur_time;					//timestamp of this capture
		uint8_t count;								//counter for number of samples; indicates if we have a full window of samples; 1-based
													// also if/when we have a new capture session	
		
};
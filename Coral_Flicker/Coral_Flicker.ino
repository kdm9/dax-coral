const int delay_msec = 15;
int ch1_pin =  12;
int ch2_pin =  15;
int ch3_pin =  14;
#define CYCLE_LEN 360
const int ch2_offset = CYCLE_LEN/3;
const int ch3_offset = 2 * ch2_offset;
unsigned char cycle_intensities[CYCLE_LEN];

void setup()   {
  pinMode(ch1_pin, OUTPUT);
  pinMode(ch2_pin, OUTPUT);
  pinMode(ch3_pin, OUTPUT);
  const int peak = (CYCLE_LEN / 2 - 1);
  const int half_way = (CYCLE_LEN / 2);
  for (int idx = 0; idx < CYCLE_LEN; idx++) {
	/* 0,1,...,255,255-(256%256==0),255-(257%256==1),...0 */
	/* Or, for humans:
	   0,1,...,255,255,254,...,0 */
    cycle_intensities[idx] = idx > peak ? peak - (idx % half_way) : idx;
  }
}

void loop()
{
  for (int idx = 255; idx < CYCLE_LEN; idx--) {
    unsigned ch1_idx = idx % CYCLE_LEN;
    unsigned ch2_idx = (idx + ch2_offset) % CYCLE_LEN;
    unsigned ch3_idx = (idx + ch3_offset) % CYCLE_LEN;
    analogWrite(ch1_pin, cycle_intensities[idx]);
    analogWrite(ch2_pin, cycle_intensities[ch2_idx]);
    analogWrite(ch3_pin, cycle_intensities[ch3_idx]);
    delay(delay_msec);
  }
}

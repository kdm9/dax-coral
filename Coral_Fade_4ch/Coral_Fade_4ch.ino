const int delay_msec = 12;
int ch1_pin =  12;
int ch2_pin =  15;
int ch3_pin =  14;
int ch4_pin =  10;
#define CYCLE_LEN 360

const int ch2_offset = CYCLE_LEN/4;
const int ch3_offset = CYCLE_LEN/2;
const int ch4_offset = 3 * ch2_offset;

int delay_ch2_msec = delay_msec*1.05;
int delay_ch3_msec = delay_msec*0.95;
int delay_ch4_msec = delay_msec*0.90;
unsigned char cycle_intensities[CYCLE_LEN];

void setup()   {
  pinMode(ch1_pin, OUTPUT);
  pinMode(ch2_pin, OUTPUT);
  pinMode(ch3_pin, OUTPUT);
  pinMode(ch4_pin, OUTPUT);
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
  for (int idx = 0; idx < CYCLE_LEN; idx++) {
    /* ch1 is just idx */
    unsigned ch2_idx = (idx + ch2_offset) % CYCLE_LEN;
    unsigned ch3_idx = (idx + ch3_offset) % CYCLE_LEN;
	unsigned ch4_idx = (idx + ch4_offset) % CYCLE_LEN;
    analogWrite(ch1_pin, cycle_intensities[idx]);
    analogWrite(ch2_pin, cycle_intensities[ch2_idx]);
    analogWrite(ch3_pin, cycle_intensities[ch3_idx]);
	analogWrite(ch4_pin, cycle_intensities[ch4_idx]);
    delay(delay_msec);
  }
}
#define DELAY_MSEC      25
#define CH1_PIN         12
#define CH2_PIN         15
#define CH3_PIN         14
#define CYCLE_LEN       576

#define PEAK_INTENSITY  180
#define CH1_CYCLE_LEN   96
#define CH2_CYCLE_LEN   72
#define CH3_CYCLE_LEN   64

unsigned char ch1_intensities[CYCLE_LEN];
unsigned char ch2_intensities[CYCLE_LEN];
unsigned char ch3_intensities[CYCLE_LEN];

void set_channel(unsigned char *channel_intensitites, size_t channel_cycle_len)
{
    const int peak  = (channel_cycle_len / 2) - 1;
    Serial.println(channel_cycle_len);
    for (size_t index = 0; index < CYCLE_LEN; index += channel_cycle_len) {
        for (size_t ch_index = 0; ch_index < channel_cycle_len; ch_index++) {
            int vector_index = index + ch_index;
            int val;
            if (ch_index > peak) {
                val = peak - (ch_index % (channel_cycle_len/2));
            } else {
                val = ch_index;
            }
            val *= (float)PEAK_INTENSITY/(float)channel_cycle_len;
            channel_intensitites[vector_index] = val;
            Serial.print(vector_index);
            Serial.print(" ");
            Serial.print(val);
            Serial.print("\n");
        }
    }
    Serial.flush();
}

void setup()
{
    pinMode(CH1_PIN, OUTPUT);
    pinMode(CH2_PIN, OUTPUT);
    pinMode(CH3_PIN, OUTPUT);

    Serial.begin(9600); // USB is always 12 Mbit/sec

    set_channel(ch1_intensities, CH1_CYCLE_LEN);
    set_channel(ch2_intensities, CH2_CYCLE_LEN);
    set_channel(ch3_intensities, CH3_CYCLE_LEN);
}

void loop()
{
    for (size_t index = 0; index < CYCLE_LEN; index++) {
        analogWrite(CH1_PIN, ch1_intensities[index]);
        analogWrite(CH2_PIN, ch2_intensities[index]);
        analogWrite(CH3_PIN, ch3_intensities[index]);
        delay(DELAY_MSEC);
    }
}

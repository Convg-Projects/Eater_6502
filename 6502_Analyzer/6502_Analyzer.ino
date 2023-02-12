bool clockLow;

const char ADDR[] = {22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 42, 44, 46, 48, 50, 52};
const char DATA[] = {39, 41, 43, 45, 47, 49, 51, 53};
#define CLOCK 2
#define READ_WRITE 3

void setup() {
  for (int i = 0; i < 16; ++i) {
    pinMode(ADDR[i], INPUT);
  }
  for (int i = 0; i < 8; ++i) {
    pinMode(DATA[i], INPUT);
  }
  pinMode(CLOCK, INPUT_PULLUP);
  pinMode(READ_WRITE, INPUT);

  Serial.begin(57600);
}

void loop() {
  if (digitalRead(CLOCK) && clockLow) {
    //Serial.println(clockLow);
    clockLow = false;
    
    char output[64];
    
    unsigned int address = 0;
    unsigned int data = 0;
    
    Serial.print("Address: ");
    for (int i = 0; i < 16; ++i) {
      int bit = digitalRead(ADDR[i]) ? 1 : 0;
      Serial.print(bit);
      address = (address << 1) + bit;
    }
    
    Serial.print("   Data: ");
    for (int i = 0; i < 8; ++i) {
      int bit = digitalRead(DATA[i]) ? 1 : 0;
      Serial.print(bit);
      data = (data << 1) + bit;
    }

    sprintf(output, " | Byte 0x%02X %s Address 0x%04X", data, digitalRead(READ_WRITE) ? "read from" : "stored at", address);
    Serial.println(output);
  }

  if (!digitalRead(CLOCK) && !clockLow) {
    //Serial.println(clockLow);
    clockLow = true;
  }
}

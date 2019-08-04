#define A0  A0  
#define A1  A1
#define A2  A2
#define A3  A3
#define A4  A4
#define A5  A5
#define A6  A6
#define A7  A7
#define A8  A8
#define A9  A9
#define A10 A10

#define D0  2
#define D1  3
#define D2  4
#define D3  5
#define D4  6
#define D5  7
#define D6  8
#define D7  9

#define OE  10
#define WE  11

int DState = 0;   //define the state of data pin, 2 == Write, 1 == Read, 0 == Unset

void setup() {
  // put your setup code here, to run once:
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A4, OUTPUT);
  pinMode(A5, OUTPUT);
  pinMode(A6, OUTPUT);
  pinMode(A7, OUTPUT);
  pinMode(A8, OUTPUT);
  pinMode(A9, OUTPUT);
  pinMode(A10, OUTPUT);

  pinMode(OE, OUTPUT);
  pinMode(WE, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("writing 0xDE at 0x0201");
  Serial.println(ramWrite(0x0201, 0xDE,'n'));
  Serial.println(ramRead(0x0201));
}

int ramWrite(uint16_t waddr, uint8_t wdata, uint8_t check){
  //check pin state and assign pinmode for the data pins:
  if (DState != 2) {
    pinMode(D0, OUTPUT);
    pinMode(D1, OUTPUT);
    pinMode(D2, OUTPUT);
    pinMode(D3, OUTPUT);
    pinMode(D4, OUTPUT);
    pinMode(D5, OUTPUT);
    pinMode(D6, OUTPUT);
    pinMode(D7, OUTPUT);
    DState = 2;  //set pin state register as WRITE
    
  }

  //set address pins
  Serial.print(waddr,HEX);
  Serial.print("\n\r");
  digitalWrite(A0, (waddr & 0x0001 == 0x0001)?HIGH:LOW);
  digitalWrite(A1, (waddr & 0x0002 == 0x0002)?HIGH:LOW);
  digitalWrite(A2, (waddr & 0x0004 == 0x0004)?HIGH:LOW);
  digitalWrite(A3, (waddr & 0x0008 == 0x0008)?HIGH:LOW);
  digitalWrite(A4, (waddr & 0x0010 == 0x0010)?HIGH:LOW);
  digitalWrite(A5, (waddr & 0x0020 == 0x0020)?HIGH:LOW);
  digitalWrite(A6, (waddr & 0x0040 == 0x0040)?HIGH:LOW);
  digitalWrite(A7, (waddr & 0x0080 == 0x0080)?HIGH:LOW);
  digitalWrite(A8, (waddr & 0x0100 == 0x0100)?HIGH:LOW);
  digitalWrite(A9, (waddr & 0x0200 == 0x0200)?HIGH:LOW);
  digitalWrite(A10, (waddr & 0x0400 == 0x0400)?HIGH:LOW);

  digitalWrite(OE, HIGH); //disable output enable

  Serial.print(wdata,HEX);
  Serial.print("\n\r");

  //set data pins
  digitalWrite(D0, (wdata & 0x01 == 0x01)?HIGH:LOW);
  digitalWrite(D1, (wdata & 0x02 == 0x02)?HIGH:LOW);
  digitalWrite(D2, (wdata & 0x04 == 0x04)?HIGH:LOW);
  digitalWrite(D3, (wdata & 0x08 == 0x08)?HIGH:LOW);
  digitalWrite(D4, (wdata & 0x10 == 0x10)?HIGH:LOW);
  digitalWrite(D5, (wdata & 0x20 == 0x20)?HIGH:LOW);
  digitalWrite(D6, (wdata & 0x40 == 0x40)?HIGH:LOW);
  digitalWrite(D7, (wdata & 0x80 == 0x80)?HIGH:LOW);
  
  
  digitalWrite(WE, LOW); //enable write enable
  
  
  if (check == 'c') {
    if (ramRead(waddr) == wdata) {
      return 1;
    }
    else {
      Serial.println("Write Failed!");
      return 0;
    }
  }
  
  digitalWrite(WE, HIGH); //clear pin states
  digitalWrite(OE, HIGH);
  digitalWrite(A0, LOW);
  digitalWrite(A1, LOW);
  digitalWrite(A2, LOW);
  digitalWrite(A3, LOW);
  digitalWrite(A4, LOW);
  digitalWrite(A5, LOW);
  digitalWrite(A6, LOW);
  digitalWrite(A7, LOW);
  digitalWrite(A8, LOW);
  digitalWrite(A9, LOW);
  digitalWrite(A10, LOW);
  digitalWrite(D0, LOW);
  digitalWrite(D1, LOW);
  digitalWrite(D2, LOW);
  digitalWrite(D3, LOW);
  digitalWrite(D4, LOW);
  digitalWrite(D5, LOW);
  digitalWrite(D6, LOW);
  digitalWrite(D7, LOW);
  
  return 1;
}

uint8_t ramRead(uint16_t raddr){
  Serial.println(DState);
  uint8_t rdata = 0;
  //check Data pin state and change accordingly
  if (DState != 1) {
    pinMode(D0, INPUT);
    pinMode(D1, INPUT);
    pinMode(D2, INPUT);
    pinMode(D3, INPUT);
    pinMode(D4, INPUT);
    pinMode(D5, INPUT);
    pinMode(D6, INPUT);
    pinMode(D7, INPUT);
    DState = 1;  //set pin state register as READ
    
  }
  
  //set address pins
  digitalWrite(A0, (raddr & 0x0001 == 0x0001)?HIGH:LOW);
  digitalWrite(A1, (raddr & 0x0002 == 0x0002)?HIGH:LOW);
  digitalWrite(A2, (raddr & 0x0004 == 0x0004)?HIGH:LOW);
  digitalWrite(A3, (raddr & 0x0008 == 0x0008)?HIGH:LOW);
  digitalWrite(A4, (raddr & 0x0010 == 0x0010)?HIGH:LOW);
  digitalWrite(A5, (raddr & 0x0020 == 0x0020)?HIGH:LOW);
  digitalWrite(A6, (raddr & 0x0040 == 0x0040)?HIGH:LOW);
  digitalWrite(A7, (raddr & 0x0080 == 0x0080)?HIGH:LOW);
  digitalWrite(A8, (raddr & 0x0100 == 0x0100)?HIGH:LOW);
  digitalWrite(A9, (raddr & 0x0200 == 0x0200)?HIGH:LOW);
  digitalWrite(A10, (raddr & 0x0400 == 0x0400)?HIGH:LOW);
  
  digitalWrite(WE, HIGH); //disable write enable
  digitalWrite(OE, LOW); //enable output enable
  
  
  //read bytes from the data pins
  if (digitalRead(D0) == HIGH) rdata |= 0x01;
  if (digitalRead(D1) == HIGH) rdata |= 0x02;
  if (digitalRead(D2) == HIGH) rdata |= 0x04;
  if (digitalRead(D3) == HIGH) rdata |= 0x08;
  if (digitalRead(D4) == HIGH) rdata |= 0x10;
  if (digitalRead(D5) == HIGH) rdata |= 0x20;
  if (digitalRead(D6) == HIGH) rdata |= 0x40;
  if (digitalRead(D7) == HIGH) rdata |= 0x80;
  
  digitalWrite(WE, HIGH); //clear pin states
  digitalWrite(OE, HIGH);
  digitalWrite(A0, LOW);
  digitalWrite(A1, LOW);
  digitalWrite(A2, LOW);
  digitalWrite(A3, LOW);
  digitalWrite(A4, LOW);
  digitalWrite(A5, LOW);
  digitalWrite(A6, LOW);
  digitalWrite(A7, LOW);
  digitalWrite(A8, LOW);
  digitalWrite(A9, LOW);
  digitalWrite(A10, LOW);
  digitalWrite(D0, LOW);
  digitalWrite(D1, LOW);
  digitalWrite(D2, LOW);
  digitalWrite(D3, LOW);
  digitalWrite(D4, LOW);
  digitalWrite(D5, LOW);
  digitalWrite(D6, LOW);
  digitalWrite(D7, LOW);
  
  return (rdata);
} 

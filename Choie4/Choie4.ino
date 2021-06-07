//////// 7 SEGMENT ///////////
#define CLK_PIN   (D4)
#define DIO_PIN   (D5)

////////// ULTRA SONIC ///////
#define echoPin D6
#define trigPin D7
long duration , cm;
int capacity;
///////////////////////////////////////////////////////////////////////////
#define bit_delay()   asm("nop\n nop\n nop\n nop\n")

#define TM1637_CMD1  (0x40)
#define TM1637_CMD2  (0xC0)
#define TM1637_CMD3  (0x80)

const uint8_t SEVEN_SEG_DIGITS[] = {
 //  gfedcba
  0b00111111, // 0
  0b00000110, // 1
  0b01011011, // 2
  0b01001111, // 3
  0b01100110, // 4
  0b01101101, // 5
  0b01111101, // 6
  0b00000111, // 7
  0b01111111, // 8
  0b01101111, // 9
 };
 
void tm1637_init() {
  pinMode( CLK_PIN, OUTPUT );
  pinMode( DIO_PIN, OUTPUT );
  digitalWrite( CLK_PIN, HIGH );
  digitalWrite( DIO_PIN, HIGH );
}

void tm1637_start_bit() {
  digitalWrite( DIO_PIN, LOW );  bit_delay();
  digitalWrite( CLK_PIN, LOW );  bit_delay();
}

void tm1637_stop_bit() {
  digitalWrite( CLK_PIN, HIGH ); bit_delay();
  digitalWrite( DIO_PIN, HIGH ); bit_delay();
}

int tm1637_send_byte( uint8_t data ) {
  uint8_t ack;
  for( uint8_t i = 0; i < 8; i++ ) { // Send 8-bit data, LSB first
    digitalWrite( CLK_PIN, LOW );
    digitalWrite( DIO_PIN, ( data & 0x01 ) ? HIGH : 0 ); 
    digitalWrite( CLK_PIN, HIGH );
    data >>= 1; // shift bit to the right
  }
  digitalWrite( CLK_PIN, LOW );
  pinMode( DIO_PIN, INPUT );     // make DIO pin floating (input)
  digitalWrite( DIO_PIN, HIGH ); // enable pull-up
  digitalWrite( CLK_PIN, HIGH );
  ack = digitalRead( DIO_PIN );  // read ACK bit
  digitalWrite( DIO_PIN, LOW );
  pinMode( DIO_PIN, OUTPUT );
  digitalWrite( CLK_PIN, LOW );
  return (ack==0);
}

boolean showDigits( uint8_t digits[],
       boolean colon=false, uint8_t brightness=7 ) 
{ 
  // send the first command
  tm1637_start_bit();
  tm1637_send_byte( TM1637_CMD1 );
  tm1637_stop_bit();
  // send the second command
  tm1637_start_bit();
  tm1637_send_byte( TM1637_CMD2 ); 
  for ( uint8_t i=0, value; i < 4; i++ ) {
    value = SEVEN_SEG_DIGITS[ digits[i] ];
    if ( (i == 1) && colon ) {
      value |= 0x80; // turn on the colon on the display
    }
    tm1637_send_byte( value ); 
  }
  tm1637_stop_bit();
  // send the third command
  tm1637_start_bit();
  tm1637_send_byte( TM1637_CMD3 | (brightness & 0x07) | 0x08 );
  tm1637_stop_bit();
}

////////////////////////////////////////////////////////////////////////////
uint32_t ts;


void setup() {
Serial.begin(9600);
pinMode(echoPin,INPUT);
pinMode(trigPin,OUTPUT);

tm1637_init();
ts = millis();
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  cm = duration*0.034/2;
  Serial.print("Distance: ");
  Serial.println(cm);
  static boolean colon=false;
  static uint8_t data[4];
  static uint16_t count = 0, temp;
    temp  = count;
    count = cm;
    for (uint8_t i=0; i < 4; i++) {
      data[1-i] = temp%10;
      temp /= 10;
    }
    showDigits( data,!colon );
    delay(250);
    if(cm < 5){
      tone(D8,1000);
    }else{
      noTone(D8);
    }
  }

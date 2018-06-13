int  T0=-1;        // T0 counter
int  next=0;        // index to next change
int  nseq=20;       // number of pulses in sequence
int  data=0;        // read state
int  i=0;       // counter
char pulse[]={0, 5, 10, 15, 9999};  // pulse number to make change
char state[]={0x07, 0x05, 0x06, 0x04};  // state to change to that pulse

void setup() {
  pinMode(2, INPUT);      // read T0
  for (i=3; i<13;++i) {     // initialize outputs
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }
  Serial.begin(9600);
}

void loop() {
  Serial.println("looking for low");
  while (digitalRead(2)==HIGH) {};  // wait for rising edge
  Serial.println("looking for high");
  while (digitalRead(2)==LOW) {};
  T0=T0+1;        // advance T0
  if (T0==nseq) {     // wrap around
    T0=0;
    next=pulse[0];
  };
  Serial.println(T0);
  if (T0==pulse[next]) {    // next step of sequence
    data=state[next];     // read new state
   Serial.println(data);
    for (i=3; i<13;++i) {
      digitalWrite(i, data&1);// write each led
      data=data>>1;     // push next bit to front
    Serial.println(data);
    }
    next=next+1;
  }
  Serial.println("before delay");
  delay(50);        // prevent bouncing
Serial.println("after delay");
}

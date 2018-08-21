int ledpin = 13;

void setup() 
{
  pinMode(ledpin, OUTPUT);
  attachInterrupt(0, stuffHappened, RISING);
}

void loop() 
{
  
}

void stuffHappened()
{
  digitalWrite(ledpin, HIGH);
}


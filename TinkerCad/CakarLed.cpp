// C++ code
//
void setup()
{
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
}

void loop()
{
  digitalWrite(13, HIGH);
  digitalWrite(12, LOW);
  delay(200); // Wait for 200 millisecond(s)
  digitalWrite(13, LOW);
  digitalWrite(12, HIGH);
  delay(200); // Wait for 200 millisecond(s)
}
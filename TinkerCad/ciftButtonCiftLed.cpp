// C++ code
//
int BUTTON1 = 0;

int BUTTON2 = 0;

void setup()
{
    pinMode(3, INPUT);
    pinMode(2, INPUT);
    pinMode(6, OUTPUT);
    pinMode(5, OUTPUT);
}

void loop()
{
    BUTTON1 = digitalRead(3);
    BUTTON2 = digitalRead(2);
    if (BUTTON1 == 1) {
        digitalWrite(6, HIGH);
        delay(1000); // Wait for 1000 millisecond(s)
    }
    if (BUTTON2 == 1) {
        digitalWrite(5, HIGH);
        delay(1000); // Wait for 1000 millisecond(s)
    }
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
}
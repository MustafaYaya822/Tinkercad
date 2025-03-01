// C++ code
//
int BUTTON = 0;

int LED = 0;

void setup()
{
    pinMode(2, INPUT);
    pinMode(4, OUTPUT);
}

void loop()
{
    BUTTON = digitalRead(2);
    if (BUTTON == 1 && LED == 0) {
        LED = 1;
        delay(500); // Wait for 500 millisecond(s)
    }
    else {
        if (BUTTON == 1 && LED == 1) {
            LED = 0;
            delay(500); // Wait for 500 millisecond(s)
        }
    }

    if (LED == 1) {
        digitalWrite(4, HIGH);
    }
    else {
        digitalWrite(4, LOW);
    }
}
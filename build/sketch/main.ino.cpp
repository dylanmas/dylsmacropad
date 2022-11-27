#include <Arduino.h>
#line 1 "/home/dylanmasulis/Documents/macropad/main/main.ino"
#include <Mouse.h>
#include <Keyboard.h>

bool trig = false;

int PIEZO = 6;

char table[4][4] = {
  {'A', 'B', 'C', 'D'},
  {'E', 'F', 'G', 'H'},
  {'I', 'J', 'K', 'L'},
  {'M', 'N', 'O', 'P'}
};



/*char convert(int o, int i) {
  return table[o][i];
}*/

#line 21 "/home/dylanmasulis/Documents/macropad/main/main.ino"
void setup();
#line 44 "/home/dylanmasulis/Documents/macropad/main/main.ino"
void loop();
#line 21 "/home/dylanmasulis/Documents/macropad/main/main.ino"
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Keyboard.begin();

  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);

  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);

  pinMode(A3, INPUT_PULLUP);
  pinMode(A2, INPUT_PULLUP);
  pinMode(A1, INPUT_PULLUP);
  pinMode(A0, INPUT_PULLUP);

  pinMode(6, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  for (size_t i = 2; i <= 5; i++)
  {
    digitalWrite(i, LOW);
    while (analogRead(A3) < 500)
    {
      if (trig == false) {
        trig = true;
        Keyboard.write(table[i-2][3]);
        tone(PIEZO, 200);
        delay(5);
        noTone(PIEZO);
      }
    }
    while (analogRead(A2) < 500)
    {
      if (trig == false) {
        trig = true;
        Keyboard.write(table[i-2][2]);
        tone(PIEZO, 400);
        delay(5);
        noTone(PIEZO);
      }
    }
    while (analogRead(A1) < 500)
    {
      if (trig == false) {
        trig = true;
        Keyboard.write(table[i-2][1]);
        tone(PIEZO, 600);
        delay(5);
        noTone(PIEZO);
      }
    }
    while (analogRead(A0) < 500)
    {
      if (trig == false) {
        trig = true;
        Keyboard.write(table[i-2][0]);
        tone(PIEZO, 800);
        delay(5);
        noTone(PIEZO);
      }
    }
    trig = false;
    digitalWrite(i, HIGH);
  }

  //delay(500);
  /*
  if (analogRead(A3) < 140 && analogRead(A3) > 110 && trig == false)
  {
    Serial.println("A");
    Keyboard.write('A');
    tone(PIEZO, 200);
    delay(10);
    noTone(PIEZO);
    trig = true;
  }

  else if (analogRead(A3) < 180 && analogRead(A3) > 150 && trig == false)
  {
    Serial.println("B");
    Keyboard.write('B');
    tone(PIEZO, 400);
    delay(10);
    noTone(PIEZO);
    trig = true;
  }
  
  else if (analogRead(A3) < 230 && analogRead(A3) > 200 && trig == false)
  {
    Serial.println("C");
    Keyboard.write('C');
    tone(PIEZO, 600);
    delay(10);
    noTone(PIEZO);
    trig = true;
  }

  else if (analogRead(A3) < 270 && analogRead(A3) > 230 && trig == false)
  {
    Serial.println("D");
    Keyboard.write('D');
    tone(PIEZO, 800);
    delay(10);
    noTone(PIEZO);
    trig = true;
  }

  else if (analogRead(A2) < 140 && analogRead(A2) > 110 && trig == false)
  {
    Serial.println("E");
    Keyboard.write('E');
    tone(PIEZO, analogRead(A2));
    delay(10);
    noTone(PIEZO);
    trig = true;
  }*/
}


// !SECTION - PROGRAM EDITABLE END - DO NOT EDIT THIS COMMENT

void printSection(int x, int y, String toPrint[4], int drawColor, int drawColorBox) {
  u8g2.setDrawColor(drawColorBox);
  
  u8g2.drawBox(x, y+0, 32, 38);

  u8g2.setDrawColor(drawColor);
  
  u8g2.setCursor(x+1, y+9);
  u8g2.print(toPrint[0]);

  u8g2.setCursor(x+1, y+18);
  u8g2.print(toPrint[1]);

  u8g2.setCursor(x+1, y+27);
  u8g2.print(toPrint[2]);

  u8g2.setCursor(x+1, y+36);
  u8g2.print(toPrint[3]);

  u8g2.drawLine(x-1, 0, x-1, 37);
}

void macroSel(int sel) {
  
  u8g2.setFont(u8g2_font_nerhoe_tf);
  
  u8g2.drawLine(0, 38, 128, 38);
  //anything below y=38 will be inside the status bar.

  int S1 = 0x01;
  int S2 = 0x20;

  switch (sel)
  {
  case 1:
  S1 = 0x01;
  S2 = 0x20;
    break;

  case 2:
  S1 = 0x20;
  S2 = 0x01;
    break;

  case 3:
  S1 = 0x01;
  S2 = 0x20;
    break;

  case 4:
  S1 = 0x01;
  S2 = 0x20;
    break;
  
  default:
    break;
  }

  
  
  u8g2.drawButtonUTF8(4, 51, S1, 0, 2, 2, "Layer 1");
  u8g2.drawButtonUTF8(41, 51, S2, 0, 2, 2, "2");
  u8g2.setDrawColor(0);
  
  printSection(0, 0, namesTable[0], 1, 0);
  printSection(32, 0, namesTable[1], 0, 1);
  printSection(64, 0, namesTable[2], 1, 0);
  printSection(96, 0, namesTable[3], 0, 1);

}

void writeOut(String word) {
  delay(50);
  for (size_t i = 0; i < word.length(); i++)
  {
    Keyboard.write(word.charAt(i));
  }
}

void note(int freq) {
  tone(PIEZO, freq);
  delay(10);
  noTone(PIEZO);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Keyboard.begin();
  u8g2.begin();

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

  u8g2.clearBuffer();
  macroSel(1);
  u8g2.sendBuffer();
  //TODO add for loop to iterate through macroMap and grab info to display on the screen.
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
      }
    }
    while (analogRead(A2) < 500)
    {
      if (trig == false) {
        trig = true;
        Keyboard.write(table[i-2][2]);
      }
    }
    while (analogRead(A1) < 500)
    {
      if (trig == false) {
        trig = true;
        macroMap(table[i-2][1]);
        /*Keyboard.press(128);
        Keyboard.write('l');
        Keyboard.release(128);
        //Keyboard.print("layer 1");

        writeOut("layer 1");
        

        Keyboard.write(224);*/
      }
    }
    while (analogRead(A0) < 500)
    {
      if (trig == false) {
        trig = true;
        note(1000);
        delay(50);
        note(300);
        macroMap(table[i-2][0]);
      }
    }
    trig = false;
    digitalWrite(i, HIGH);
  }
}

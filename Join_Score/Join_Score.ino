
void setup() {
  // put your setup code here, to run once:

}

void loop() {
  if(digitalRead(Button1 == HIGH)){
    Selected = 1;
    lcd.print("Now Select 1");
  }
  if(digitalRead(Button2 == HIGH)){
    Selected = 2;
    lcd.print("Now Select 2");
  }
  if(digitalRead(Button3 == HIGH)){
    Selected = 3;
    lcd.print("Now Select 3");
  }
  if(digitalRead(Button4 == HIGH)){
    Selected = 4;
    lcd.print("Now Select 4");
  }
  if(digitalRead(Button5 == HIGH)){
    Selected = 5;
    lcd.print("Now Select 5");
  }
  if(digitalRead(Button6 == HIGH)){
    Selected = 6;
    lcd.print("Now Select 6");
  }
  while(digitalRead(Button7 == HIGH)){
    tone(8,1000,500);
    delay(250);
    tone(8,1000,500);
    lcd.print("Select Complete");
    lcd.cursor(0,1);
    lcd.print("You join");
    lcd.print(Selected);
    while(digitalRead(Button7 == HIGH)){
      delay(50);
    }
  }
}

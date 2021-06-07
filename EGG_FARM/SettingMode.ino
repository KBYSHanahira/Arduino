void SettingMode(){
  if (digitalRead(D5) == 0){
    tone (D8,2000,500);
    Modes = Modes + 1;
  }
    while(digitalRead(D5) == 0){
      delay(10);
    }
   Serial.print(Modes);
  /////////////////////////
  if(Modes == 0){
    SettingTemp();
  }else if(Modes == 1){
    SettingHisterresis();
  }
  /////////////////////////
  if(Modes > 1){
    Modes = 0;
  }
  
}


void SettingTemp(){
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("  Setting Mode  ");
  display.setCursor(0, 25);
  display.print("-->");
  display.print("Average = ");
  display.println(Average);
  display.setCursor(0, 50);
  display.print("   Hyster = ");
  display.println(Histerresis);
  display.display();
  delay(200);
  if(digitalRead(D6)==0){
    Average = Average + 1;
  }
  if(Average > 30){
    Average = 23;
  }
}

void SettingHisterresis(){
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("  Setting Mode  ");
  display.setCursor(0, 25);
  display.print("   Average = ");
  display.println(Average);
  display.setCursor(0, 50);
  display.print("-->");
  display.print("Hyster = ");
  display.println(Histerresis);
  display.display();
  delay(200);
  if(digitalRead(D6)==0){
    Histerresis = Histerresis + 1;
  }
  if(Histerresis > 5){
    Histerresis = 1;
  }
}

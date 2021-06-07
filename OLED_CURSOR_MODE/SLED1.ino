void Second(){ 
  int vol = analogRead(A0);
  int volumem = map(vol,0,1024,1,6);
  
  if(volumem == 1){
  Second1();
  }
  if(volumem == 2){
  Second2();
  }
  if(volumem == 3){
  Second3();
  }
  if(volumem == 4){
  Second4();
  }
  if(volumem == 5){
  Second5();
  }
  if(volumem == 6){
  Second6();
  }
}

void Second1(){
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.print("-->");
  display.print(" RED");
  display.setCursor(0,25);
  display.print("   ");
  display.print(" GREEN");
  display.setCursor(0,50);
  display.print("   ");
  display.print(" BLUE");
  display.display();
  delay(200);
  if(digitalRead(13)== 0){
    while(digitalRead(13) == 0){
      delay(1);
    }
    SLEDs.setPixelColor(0, SLEDs.Color(255,0,0));
    SLEDs.show();
  }
}

void Second2(){
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.print("   ");
  display.print(" RED");
  display.setCursor(0,25);
  display.print("-->");
  display.print(" GREEN");
  display.setCursor(0,50);
  display.print("   ");
  display.print(" BLUE");
  display.display();
  delay(200);
  if(digitalRead(13)== 0){
    while(digitalRead(13) == 0){
      delay(1);
    }
    SLEDs.setPixelColor(0, SLEDs.Color(0,255,0));
    SLEDs.show();
  }
}

void Second3(){
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.print("   ");
  display.print(" RED");
  display.setCursor(0,25);
  display.print("   ");
  display.print(" GREEN");
  display.setCursor(0,50);
  display.print("-->");
  display.print(" BLUE");
  display.display();
  delay(200);
  if(digitalRead(13)== 0){
    while(digitalRead(13) == 0){
      delay(1);
    }
    SLEDs.setPixelColor(0, SLEDs.Color(0,0,255));
    SLEDs.show();
  }
}

void Second4(){
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.print("   ");
  display.print(" GREEN");
  display.setCursor(0,25);
  display.print("   ");
  display.print(" BLUE");
  display.setCursor(0,50);
  display.print("-->");
  display.print(" WHITE");
  display.display();
  delay(200);
  if(digitalRead(13)== 0){
    while(digitalRead(13) == 0){
      delay(1);
    }
    SLEDs.setPixelColor(0, SLEDs.Color(255,255,255));
    SLEDs.show();
  }
}

void Second5(){
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.print("   ");
  display.print(" BLUE");
  display.setCursor(0,25);
  display.print("   ");
  display.print(" WHITE");
  display.setCursor(0,50);
  display.print("-->");
  display.print(" OFF");
  display.display();
  delay(200);
  if(digitalRead(13)== 0){
    while(digitalRead(13) == 0){
      delay(1);
    }
    SLEDs.setPixelColor(0, SLEDs.Color(0,0,0));
    SLEDs.show();
  }
}

void Second6(){
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.print("   ");
  display.print(" WHITE");
  display.setCursor(0,25);
  display.print("   ");
  display.print(" OFF");
  display.setCursor(0,50);
  display.print("-->");
  display.print(" EXIT");
  display.display();
  delay(200);
  if(digitalRead(13)== 0){
    while(digitalRead(13) == 0){
      delay(1);
    }
    Mode = 0;
  }
}

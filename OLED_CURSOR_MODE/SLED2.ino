void Third(){ 
  int vol = analogRead(A0);
  int volumee = map(vol,0,1024,1,5);
  
  if(volumee == 1){
  Third1();
  }
  if(volumee == 2){
  Third2();
  }
  if(volumee == 3){
  Third3();
  }
  if(volumee == 4){
  Third4();
  }
  if(volumee == 5){
  Third5();
  }
  if(volumee == 6){
  Third6();
  }
}

void Third1(){
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
  if(digitalRead(D7)== 0){
    SLEDs.setPixelColor(1, SLEDs.Color(255,0,0));
    SLEDs.show();
  }
}

void Third2(){
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
  if(digitalRead(D7)== 0){
    SLEDs.setPixelColor(1, SLEDs.Color(0,255,0));
    SLEDs.show();
  }
}

void Third3(){
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
  if(digitalRead(D7)== 0){
    SLEDs.setPixelColor(1, SLEDs.Color(0,0,255));
    SLEDs.show();
  }
}

void Third4(){
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
  if(digitalRead(D7)== 0){
    SLEDs.setPixelColor(1, SLEDs.Color(255,255,255));
    SLEDs.show();
  }
}

void Third5(){
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
  if(digitalRead(D7)== 0){
    SLEDs.setPixelColor(1, SLEDs.Color(0,0,0));
    SLEDs.show();
  }
}

void Third6(){
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
    Mode = 0;
  }
}

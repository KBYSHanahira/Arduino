void Force(){ 
  int vol = analogRead(A0);
  int volumem = map(vol,0,1024,1,4);
  
  if(volumem == 1){
  Force1();
  }
  if(volumem == 2){
  Force2();
  }
  if(volumem == 3){
  Force3();
  }
  if(volumem == 4){
  Force4();
  }
}

void Force1(){
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.print("-->");
  display.print(" 500Hz");
  display.setCursor(0,25);
  display.print("   ");
  display.print(" 1KHz");
  display.setCursor(0,50);
  display.print("   ");
  display.print(" 2KHz");
  display.display();
  delay(200);
  if(digitalRead(D7)== 0){
    tone(D8,500,1000);
  }
}

void Force2(){
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.print("   ");
  display.print(" 500Hz");
  display.setCursor(0,25);
  display.print("-->");
  display.print(" 1KHz");
  display.setCursor(0,50);
  display.print("   ");
  display.print(" 2KHz");
  display.display();
  delay(200);
  if(digitalRead(D7)== 0){
    tone(D8,1000,1000);
  }
}

void Force3(){
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.print("   ");
  display.print(" 500Hz");
  display.setCursor(0,25);
  display.print("   ");
  display.print(" 1KHz");
  display.setCursor(0,50);
  display.print("-->");
  display.print(" 2KHz");
  display.display();
  delay(200);
  if(digitalRead(D7)== 0){
    tone(D8,2000,1000);
  }
}

void Force4(){
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.print("   ");
  display.print(" 1KHz");
  display.setCursor(0,25);
  display.print("   ");
  display.print(" 2KHz");
  display.setCursor(0,50);
  display.print("-->");
  display.print(" EXIT");
  display.display();
  delay(200);
  if(digitalRead(13)== 0){
    while(digitalRead(13) == 0){
      delay(1);
    }
    noTone(D8);
    Mode = 0;
  }
}

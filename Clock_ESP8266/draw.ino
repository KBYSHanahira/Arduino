extern byte font_number[10][5] ;
extern byte font_colon[3] ;

void drawTime(String strTime, int offset) {
  int pos_x = offset;
  for (int i=0;i<strTime.length();i++) {
    pos_x += drawChar(strTime.charAt(i), pos_x);
  }
  lmd.display();
}

int drawChar(char c, int offset_x) {
  int width;
  byte dataWrite[5];
  if (c >= '0' && c <= '9') {
    width = 6;
    memcpy(dataWrite, font_number[c - '0'], 5);
  } else if (c == ':') {
    width = 4;
    memcpy(dataWrite, font_colon, 3);
  } else {
    width = 4;
    for (int i=0;i<4;i++) dataWrite[i] = 0;
  }
  dataWrite[width-1] = 0;

  for (int x=0;x<width;x++) {
    for (int y=0;y<8;y++) {
      lmd.setPixel(x + offset_x, 7 - y, dataWrite[x]&(0x01<<y));
    }
  }
  
  return width;
}

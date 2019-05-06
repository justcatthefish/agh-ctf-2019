void setup() {
  for (char i=0; i<8; i++) {
    pinMode(i, OUTPUT);
  }

}

short decrypt_char(char i, char chr){
  char c = 255 - i;
  return chr ^ c;
}

void show_pw () {
  char pw[] = {<flag was here> ;)};
  char len = sizeof(pw);
  char chr;
  for (char i=0; i<len; i++){
    chr = decrypt_char(i, pw[i]);
    for (char b=0; b<8; b++){
      digitalWrite(b, (chr >> b) & 1);
    }    
    delay(1500);
  }
}

void loop() {
  delay(1000);
  show_pw();

}

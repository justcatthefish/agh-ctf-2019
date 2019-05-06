void setup() {
  // put your setup code here, to run once:
  

  for (char i=0; i<8; i++) {
    pinMode(i, OUTPUT);
  }

}

short decrypt_char(char i, char chr){
  char c = 255 - i;
  return chr ^ c;
}

void show_pw () {
  char pw[] = {0x95, 0x9d, 0x89, 0x9a, 0x80, 0x8f, 0xcc,
                0xc9, 0x99, 0xc0, 0xaa, 0xc4, 0x9d, 0xc1,
                0xae, 0x80, 0xdb, 0xdb, 0xd8, 0x9b, 0xdb,
                0x98, 0x8d, 0xb7, 0xd4, 0x90, 0xd6, 0x96,
                0x9a, 0x95, 0x89, 0xd3, 0xad, 0xed, 0x82,
                0xed, 0xee, 0x85, 0xbb, 0xec, 0xb3, 0xab};
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

}// put your main code here, to run repeatedly:

// Author: Ivan Vlahov
// http://youtube.com/user/ivanvlahov922

// LED Morse Coder 
// 21.11.2019.
// Download Serial Bluetooth Terminal on your smartphone and connect it to the HC-05 (pin is 1234)
// Send strings to the HC-05, and the LED will light up

#define ledPin 7  // pin where we will put our LED
#define ditDuration 150 // duration of one dit (or dot) in ms
int state = 0;

String s = "";
int counter = 0;


void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  Serial.begin(9600); // default communication rate of the Bluetooth module
}


void loop() {
  if(Serial.available() > 0){ // checks whether data is comming from the serial port
    state = Serial.read(); // reads the data from the serial port
    
    if(state != 13){
      s.concat((char) state);
      counter++;
    }
    else{
      for(int i=0; i<counter; i++){
        morse(s[i]);
      }
      counter=0;
      s="";
    }
  }
}

void morse(char c){
  int n;
  bool cond = false;
  static String arr[26] = {".-", "-...", "-.-.", "-.." , ".",
                           "..-.", "--.", "...." , "..", ".---", 
                           "-.-" , ".-..", "--", "-.", "---", 
                           ".--.", "--.-", ".-.", "...", "-", 
                           "..-", "...-", ".--", "-..-", "-.--", "--.."};
                           // array of morse letters in alphabetical order where a is 0, b is 1 etc.
                           
  if(c!=' '){
    if(c>='A' && c<='Z'){
      n = (int)c - (int)('A');
      cond = true;
    }else if(c>='a' && c<='z'){
      n = (int)c - (int)('a');
      cond = true;
    }

    // cond is true if and only if c is a letter
    // n is the c's number in the alphabet, minus one
    
    if(cond){
      for(int i=0; i<arr[n].length(); i++){
        if(arr[n][i]=='.'){
          digitalWrite(ledPin, HIGH);
          delay(1*ditDuration);
          digitalWrite(ledPin, LOW);
          delay(1*ditDuration);
        }else{
          digitalWrite(ledPin, HIGH);
          delay(3*ditDuration);
          digitalWrite(ledPin, LOW);
          delay(1*ditDuration);
        }
      }
    }
  }else{
    delay(4*ditDuration); // space is just a delay 
  }

  delay(2*ditDuration); // pause after a letter or a space
}

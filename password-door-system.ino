#include <Servo.h>
#include <Keypad.h>

Servo ServoMotor;
char* password1 = "A748";
char* password2 = "37B9";
char* password3 = "C2A1B";
char* password4 = "5C06D";
char* password5 = "4D9BA7";
char* password6 = "D3CA13";

char key;

String TempPass = "";
int position = 0;
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = { 9, 8, 7, 6 };
byte colPins[COLS] = { 5, 4, 3, 2 };
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
int LedRed = 12;
int LedGreen = 13;

void setup(){
  Serial.begin(9600);
  pinMode(LedRed, OUTPUT);
  pinMode(LedGreen, OUTPUT);
  ServoMotor.attach(10);
  LockedPosition(true);
}

void loop(){
key = keypad.getKey();
  if (key != NULL){
  if (key != '*') {SimPass();
  Serial.print("Tekan pin ke-");
  Serial.print(String(position)+":  ");
  Serial.println(key);
  }
}
  if (key == '*'){
    Serial.println(TempPass);
    if ((TempPass==password1)
    ||(TempPass==password2)
    ||(TempPass==password3)
    ||(TempPass==password4)
    ||(TempPass==password5)
    ||(TempPass==password6)){
      AksesOK();
    } else {
      Serial.println("PASSWORD SALAH!");
    }
    TempPass = ""; position = 0;
  }
}

void AksesOK(){
  LockedPosition(false);
  delay(5000);
  LockedPosition(true); 
}

void SimPass(){
  TempPass = TempPass + String(key);
  position++;
}

void LockedPosition(int locked){
  if (locked){
    digitalWrite(LedRed, HIGH);
    digitalWrite(LedGreen, LOW);
    ServoMotor.write(0);
    Serial.println("Kondisi saat ini: Pintu Tertutup");
  }
   else {
    digitalWrite(LedRed, LOW);
    digitalWrite(LedGreen, HIGH);
    ServoMotor.write(100);
    Serial.println("Kondisi saat ini: Pintu Terbuka");
  }
}

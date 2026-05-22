#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd1(0x27, 16, 2);
LiquidCrystal_I2C lcd2(0x26, 16, 2);

const int pot1 = A0;
const int pot2 = A1;

const int tou1 = 8;
const int tou2 = 7;

const int butPin = 4;

const int buzzer = 10;

long randnum;

void setup() {
  
  lcd1.init();
  lcd1.backlight();

  lcd2.init();
  lcd2.backlight();
  
  pinMode(pot1, INPUT);
  pinMode(pot2, INPUT);

  pinMode(tou1, INPUT_PULLUP);
  pinMode(tou2, INPUT_PULLUP);

  pinMode(butPin, INPUT_PULLUP);

  pinMode(buzzer, OUTPUT);

  Serial.begin(9600);

  randomSeed(analogRead(A3));

}

void gameCode(){

  lcd1.clear();
  lcd2.clear();

  delay(2000);

  randnum = random(0, 100);    

  lcd1.setCursor(0, 0);
  lcd1.print("Target number:");
  lcd1.setCursor(6, 1);
  lcd1.print(randnum);

  lcd2.setCursor(0, 0);
  lcd2.print("Target number:");
  lcd2.setCursor(6, 1);
  lcd2.print(randnum);    

  delay(3000);

  lcd1.clear();
  lcd2.clear();

  delay(1000);

  tone(buzzer, 500);
  delay(500);
  noTone(buzzer);

  delay(1000);

  tone(buzzer, 500);
  delay(500);
  noTone(buzzer);

  delay(1000);

  tone(buzzer, 800);
  delay(1000);
  noTone(buzzer);

  int guess1 = analogRead(pot1);
  guess1 = map(guess1, 0, 1023, 0, 100);

  int guess2 = analogRead(pot2);
  guess2 = map(guess2, 0, 1023, 0, 100);

  delay(50);

  lcd1.setCursor(6, 0);
  lcd1.print(guess1);

  lcd2.setCursor(6, 0);
  lcd2.print(guess2);

  int player1 = (abs(randnum - guess1));
  int player2 = (abs(randnum - guess2));

  delay(2000);

  lcd1.clear();
  lcd2.clear();

  if(player1<player2){

    lcd1.setCursor(0, 0);
    lcd1.print("Point for");
    lcd1.setCursor(0, 1);
    lcd1.print("Player 1!");

    lcd2.setCursor(0, 0);
    lcd2.print("Point for");
    lcd2.setCursor(0, 1);
    lcd2.print("Player 1!");

  } else if(player1>player2){

    lcd1.setCursor(0, 0);
    lcd1.print("Point for");
    lcd1.setCursor(0, 1);
    lcd1.print("Player 2!");

    lcd2.setCursor(0, 0);
    lcd2.print("Point for");
    lcd2.setCursor(0, 1);
    lcd2.print("Player 2!");

  } else{

    lcd1.setCursor(0, 0);
    lcd1.print("Draw!");

    lcd2.setCursor(0, 0);
    lcd2.print("Draw!");
  }

  delay(1500);

  lcd1.clear();
  lcd2.clear();

  delay(3000);
}

void loop() {

  if(digitalRead(butPin) == HIGH){

    lcd1.clear();
    lcd2.clear();
  
    delay(1000);

    lcd1.setCursor(0, 0);
    lcd1.print("You are");
    lcd1.setCursor(0, 1);
    lcd1.print("Player 1");  

    lcd2.setCursor(0, 0);
    lcd2.print("You are");
    lcd2.setCursor(0, 1);
    lcd2.print("Player 2");  

    delay(2000);
    
    while(digitalRead(tou1) == LOW && digitalRead(tou2) == LOW){

      gameCode();

    }

    if(digitalRead(tou1) == HIGH){

      lcd1.clear();
      lcd2.clear();

      delay(1500);

      lcd1.setCursor(0, 0);
      lcd1.print("Player 1");
      lcd1.setCursor(0, 1);
      lcd1.print("is the winner!");  

      lcd2.setCursor(0, 0);
      lcd2.print("Player 1");
      lcd2.setCursor(0, 1);
      lcd2.print("is the winner!"); 

      delay(2000);

      lcd1.clear();
      lcd2.clear();

    } else if(digitalRead(tou2) == HIGH){

      lcd1.clear();
      lcd2.clear();

      delay(1500);

      lcd1.setCursor(0, 0);
      lcd1.print("Player 2");
      lcd1.setCursor(0, 1);
      lcd1.print("is the winner!");  

      lcd2.setCursor(0, 0);
      lcd2.print("Player 2");
      lcd2.setCursor(0, 1);
      lcd2.print("is the winner!"); 

      delay(2000);

      lcd1.clear();
      lcd2.clear();

    }

  } else {

    lcd1.setCursor(0, 0);
    lcd1.print("Press button");
    lcd1.setCursor(0, 1);
    lcd1.print("to start");

    lcd2.setCursor(0, 0);
    lcd2.print("Press button");
    lcd2.setCursor(0, 1);
    lcd2.print("to start");

    
  
  }

}







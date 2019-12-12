/* Orginal Code By: Seaver Olson 
 *  Intro to Innovative Tech Class Period 5
 *  Final Project for Maker fair
 *  09 47 BE 99
 */
#include <SPI.h>
#include <MFRC522.h>
 
#define SS_PIN 10
#define RST_PIN 9

MFRC522 mfrc522(SS_PIN, RST_PIN);  


int fail_count = 0;
int end_program = 3;
int lock_PIN = 7;

void setup()
{
  Serial.begin(9600);   
  SPI.begin();      
  mfrc522.PCD_Init();   
  Serial.println("Put your card to the reader...");
  Serial.println();
  pinMode(lock_PIN, OUTPUT);
  
}


void open_lock() {
  digitalWrite(lock_PIN,HIGH);
  delay(1000);
  digitalWrite(lock_PIN,LOW);
}

void check_attempts() {
    if (fail_count == end_program)
    {
      Serial.println("authentication attempts max contact Seaver for help");
      Serial.println(""); 
      Serial.println("NOTE: DO NOT ATTEMPT AGAIN WITHOUT CORRECT CARD");
      String lastattempt= "";
      if (lastattempt.substring(1) == "No Access")
      {
        Serial.println("Access Authorized");
        open_lock();
      }
      else
      {
        Serial.println("INCORRECT");
        delay(1000);
        Serial.end();
      }
      
    }
}



void loop() 
{
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "09 47 BE 99")
  {
    Serial.println("Authorized access");
    Serial.println();
    open_lock();
    delay(5000);
  }
 
 else   {
    Serial.println(" Access denied");
    fail_count++;
    Serial.println(fail_count);
    delay(3000);
    check_attempts();
  }
} 

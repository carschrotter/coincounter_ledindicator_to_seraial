#define LED_COIN_1 2
#define LED_COIN_2 3
#define LED_COIN_3 4
#define LED_COIN_4 5
#define LED_COIN_5 6
#define LED_COIN_6 7
#define INTERNAL_LED 13
#define LED_TIMEOUT_MS 147 // time its glow led
#define LED_MIN_MS 145 // time its glow led
//flicker led is 116ms

int creditInCents = 0;
long lastCreditChangeTime = 0;
int lastCoin = 0;

void setup() {
  // put your setup code here, to run once:
  // Debugging output
  Serial.begin(115200);
  Serial.println("Initializing... ");
  pinMode(LED_COIN_1, INPUT);
  pinMode(LED_COIN_2, INPUT);
  pinMode(LED_COIN_3, INPUT);
  pinMode(LED_COIN_4, INPUT);
  pinMode(LED_COIN_5, INPUT);
  pinMode(LED_COIN_6, INPUT);
  pinMode(INTERNAL_LED, OUTPUT);

  Serial.println("Wilkommen beim Drinkomator coin Interface!");
}

void loop() {
  int ledCoin1 = digitalRead(LED_COIN_1);
  int ledCoin2 = digitalRead(LED_COIN_2);
  int ledCoin3 = digitalRead(LED_COIN_3);
  int ledCoin4 = digitalRead(LED_COIN_4);
  int ledCoin5 = digitalRead(LED_COIN_5);
  int ledCoin6 = digitalRead(LED_COIN_6);
  int curLed = 0;
  bool ledHasTriggerd = ledCoin1 == HIGH ^ //XOR
         ledCoin2 == HIGH ^
         ledCoin3 == HIGH ^
         ledCoin4 == HIGH ^
         ledCoin5 == HIGH ^
         ledCoin6 == HIGH;

  curLed = ledCoin1 ? 1 : ledCoin2 ? 2 : ledCoin3 ? 3 : ledCoin4 ? 4 : ledCoin5 ? 5 : ledCoin6 ? 6 : 0;
  //if(curLed) Serial.println(curLed);
  
  if(ledCoin1 == HIGH ) {
    curLed = 1;
  }
  else if(ledCoin2 == HIGH) {
    curLed = 2;
  }
  else if(ledCoin3 == HIGH) {
    curLed = 3;
  }
  else if (ledCoin4 == HIGH) {
    curLed = 4;
  }
  else if (ledCoin5 == HIGH) {
    curLed = 5; //extra coin water
  }
  else if(ledCoin6 == HIGH) {
    curLed == 6; //extra coin coffe
  }
                      
  digitalWrite(INTERNAL_LED,LOW);
  // put your main code here, to run repeatedly:
  if ( (ledHasTriggerd

       ) && lastCreditChangeTime == 0 ) {
        
        if(ledCoin1 == HIGH ) {
          lastCoin = 1;
        }
        else if(ledCoin2 == HIGH) {
          lastCoin = 2;
        }
        else if(ledCoin3 == HIGH) {
          lastCoin = 3;
        }
        else if (ledCoin4 == HIGH) {
          lastCoin = 4;
        }
        else if (ledCoin5 == HIGH) {
          lastCoin = 5; //extra coin water
        }
        else if(ledCoin6 == HIGH) {
          lastCoin == 6; //extra coin coffe
        }
    lastCreditChangeTime = millis();
    digitalWrite(INTERNAL_LED,HIGH);
    // Serial.println(printf("coin insert time: %d", lastCreditChangeTime));
  } else if(ledHasTriggerd) {
    long now = millis();
     if (
       (
         ledCoin1 == HIGH ^ //XOR
         ledCoin2 == HIGH ^
         ledCoin3 == HIGH ^
         ledCoin4 == HIGH ^
         ledCoin5 == HIGH ^
         ledCoin6 == HIGH
    ) && (lastCreditChangeTime + LED_TIMEOUT_MS) >= now && 
          lastCreditChangeTime + LED_MIN_MS <= now) {

        if(lastCoin == 1 ) {
          creditInCents=10;
        }
        else if(lastCoin == 2) {
          creditInCents=20;
        }
        else if(lastCoin == 3) {
          creditInCents=50;
        }
        else if (lastCoin == 4) {
          creditInCents=100;
        }
        else if (lastCoin == 5) {
          creditInCents=2000; //extra coin water
        }
        else if(lastCoin == 6) {
          creditInCents=3000; //extra coin coffe
        }
        digitalWrite(INTERNAL_LED, HIGH);
        //Serial.print(creditInCents);
        //Serial.print(" on ");
        //Serial.println(lastCreditChangeTime);
        //Serial.print(printf("creditInCents: %d", creditInCents));
        //lastCreditChangeTime=0;
    }
    //if(lastCreditChangeTime!=0) Serial.println(lastCreditChangeTime);
  }  else {
      if(creditInCents) Serial.print(creditInCents);
      creditInCents = 0;
      lastCreditChangeTime=0;
    }


}

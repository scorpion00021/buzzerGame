
const int player1_button = 2;     // the number of the pushbutton pin
const int player2_button = 3;
const int player3_button = 4;
const int player4_button = 5;
const int MASTER_button = 6;

const int buzzer_pin = 8;

const int player1_light =  9;      // the number of the LED pin
const int player2_light =  10;
const int player3_light =  11;
const int player4_light =  12;
const int MASTER_light =  13;

// variables will change:
int player1_buttonState = 0;         // variable for reading the pushbutton status
int player2_buttonState = 0;
int player3_buttonState = 0;
int player4_buttonState = 0;
int MASTER_buttonState = 0;

int gameState = 0;  //gameState tracks whats going on.  0 = open, 1 1 4 = latched on player

void setup() {
  // initialize the LED pin as an output:
  pinMode(player1_light, OUTPUT);
  pinMode(player2_light, OUTPUT);
  pinMode(player3_light, OUTPUT);
  pinMode(player4_light, OUTPUT);
  pinMode(MASTER_light, OUTPUT);
  pinMode(buzzer_pin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(player1_button, INPUT_PULLUP);
  pinMode(player2_button, INPUT_PULLUP);
  pinMode(player3_button, INPUT_PULLUP);
  pinMode(player4_button, INPUT_PULLUP);
  pinMode(MASTER_button, INPUT_PULLUP);

  Serial.begin(9600);  
}

void loop() {

    player1_buttonState = digitalRead(player1_button);
    player2_buttonState = digitalRead(player2_button);
    player3_buttonState = digitalRead(player3_button);
    player4_buttonState = digitalRead(player4_button);
    MASTER_buttonState = digitalRead(MASTER_button);
  
  if (gameState == 0){ //waiting for player press


    if(player1_buttonState == LOW){//these are pullup.  They drop to low when button is pressed.
      LatchGameState(1);
    }else if(player2_buttonState == LOW){
      LatchGameState(2);
    }else if(player3_buttonState == LOW){
      LatchGameState(3);
    }else if(player4_buttonState == LOW){
      LatchGameState(4);
    }
  }
  if(MASTER_buttonState == LOW){
      ResetGameState();
  }
  
  Serial.println(player2_buttonState);
}
void LatchGameState(int playerNum){
  gameState = playerNum;

  //reset lights
  digitalWrite(player1_light, LOW);
  digitalWrite(player2_light, LOW);
  digitalWrite(player3_light, LOW);
  digitalWrite(player4_light, LOW);
  
  if(playerNum == 1){
    digitalWrite(player1_light, HIGH);
  }else if(playerNum == 2){
    digitalWrite(player2_light, HIGH);
  }else if(playerNum == 3){
    digitalWrite(player3_light, HIGH);
  }else if(playerNum == 4){
    digitalWrite(player4_light, HIGH);
  }

  //buzzer
  tone(buzzer_pin, 1000);
  delay(800);
  noTone(buzzer_pin);

  
  //illuminate MASTER
  digitalWrite(MASTER_light, HIGH);

}

void ResetGameState(){
  gameState = 0;
  
  digitalWrite(MASTER_light, LOW);
  digitalWrite(player1_light, LOW);
  digitalWrite(player2_light, LOW);
  digitalWrite(player3_light, LOW);
  digitalWrite(player4_light, LOW);
}

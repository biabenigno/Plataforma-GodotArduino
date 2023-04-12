#define btn_1 22
#define btn_2 23
#define X_AXIS 26
#define Y_AXIS 25
#define led_G 5
#define led_B 18
#define led_R 19
#define led_R2 21
#define led_MORRE 33

int flag_btn1 = 0;
int flag_btn2 = 0;
unsigned long lastTime = 0;
const unsigned long interval = 400;

void setup() {
  pinMode(btn_1, INPUT_PULLUP);
  pinMode(btn_2, INPUT_PULLUP);
  pinMode(led_G, OUTPUT);
  pinMode(led_B, OUTPUT);
  pinMode(led_R, OUTPUT);
  pinMode(led_R2, OUTPUT);
  pinMode(led_MORRE, OUTPUT);
  Serial.begin(115200);

}


void loop() {

  int y = map(analogRead(Y_AXIS), 0 , 4095, 10, -10);
  Serial.println((String)y);

  //botao1 (azul)
  if(deBounce(flag_btn1,btn_1)==LOW){
    if(flag_btn1 == 0){
    Serial.write("PULA\n");
    digitalWrite(led_G, HIGH);
    }
    flag_btn1 = 1;
  }

  if(flag_btn1 == 1 && deBounce(flag_btn1,btn_1)==HIGH){
    Serial.write("CAI\n");
    digitalWrite(led_G, LOW);
    flag_btn1 = 0;
  }


  //botao 2 (amarelo)

  if(deBounce(flag_btn2,btn_2)==LOW){
    if(flag_btn2 == 0){
    Serial.write("ACELERA\n");
    digitalWrite(led_B, HIGH);
    }
    flag_btn2 = 1;
  }

  if(flag_btn2 == 1 && deBounce(flag_btn2,btn_2)==HIGH){
    Serial.write("DESACELERA\n");
    digitalWrite(led_B, LOW);
    flag_btn2 = 0;
  }
  
  while (Serial.available())
  {
    char character = (char)Serial.read();
    if (character == '1'){
      digitalWrite(led_R, HIGH);
    }
    if (character == '2'){
      digitalWrite(led_R2, HIGH);
    }
    if (character == '4'){
      Ganhou();
    }
    if (character == '6'){
      while(true){
        digitalWrite(led_MORRE, HIGH);
        delay(120);
        digitalWrite(led_MORRE, LOW);
        delay(120);
      }
    }
    if (character == '0'){
      Reiniciar();
      character = '1';
    }
  }
}

  /*while (Serial.available())
  {
    char character = (char)Serial.read();
    if (character != '\n')
    {
      txt = txt + character;
    }
    else
    {
      if (txt == "L ON")
      {
        digitalWrite(LED_R2, HIGH);
      }
      else if (txt == "L OFF")
      {
        digitalWrite(led_R2, LOW);
      }
      txt = "";
    }
  }*/

int deBounce (int estado, int pino){
  int estadoAtual = digitalRead(pino);

  if(estado!=estadoAtual){
    delay(5);
    estadoAtual = digitalRead(pino);
  }
  return estadoAtual;
}

void Ganhou(){
  bool leds[4];
  while(true){
    for (int i = 0; i<4; i++){
      leds[i % 4] = true;
      leds[(i % 4) - 1] = true;

      digitalWrite(led_G, leds[0]);
      delay(30);
      //Zenitsu
      digitalWrite(led_B, leds[1]);
      delay(30);
      digitalWrite(led_R, leds[2]);
      delay(30);
      digitalWrite(led_R2, leds[3]);
      delay(30);
      for (int j = 0; j < 4; j++){
        leds[j] = 0;
      }
    }
    for (int i = 0; i<4; i++){
      leds[i % 4] = true;
      leds[(i % 4) - 1] = true;

      digitalWrite(led_R2, leds[0]);
      delay(30);
      //Zenitsu
      digitalWrite(led_R, leds[1]);
      delay(30);
      digitalWrite(led_B, leds[2]);
      delay(30);
      digitalWrite(led_G, leds[3]);
      delay(30);
      for (int j = 0; j < 4; j++){
        leds[j] = 0;
      }
    }
  }
}
void Reiniciar(){
  digitalWrite(led_G, LOW);
  digitalWrite(led_B, LOW);
  digitalWrite(led_R, LOW);
  digitalWrite(led_R2, LOW);
  digitalWrite(led_MORRE, LOW);
}





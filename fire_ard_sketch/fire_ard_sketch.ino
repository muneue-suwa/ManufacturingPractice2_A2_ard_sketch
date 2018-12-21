const int LED_PIN = 3;
const int RPI_INPUT_PIN = 12;
const int BUTTON_INPUT_PIN = 5;
const int BOARD_LED = 13;
int isOn = 0;
int led_values[] = {255, 100, 255, 50};
int led_value_fig = 0;  // 0 - 3
int rpi_high_times = 0;
int button_high_times = 0;

void setup() {
  pinMode(RPI_INPUT_PIN, INPUT);
  pinMode(BUTTON_INPUT_PIN, INPUT);  // could change isOn status without Raspberry PI
  pinMode(BOARD_LED, OUTPUT);  // describe changed isOn with LED on the board in change_isOn()
  Serial.begin(9600);
}

void loop() {
  change_isOn(&rpi_high_times, RPI_INPUT_PIN);
  change_isOn(&button_high_times, BUTTON_INPUT_PIN);

  if(isOn > 0){
    fire(&led_value_fig);
  }else{
    analogWrite(LED_PIN, 0); // LED OFF
  }
  Serial.print("rpi_high_times   : ");
  Serial.println(rpi_high_times);
  Serial.print("button_high_times: ");
  Serial.println(button_high_times);
  delay(100);
}

void fire(int *value_fig){
    analogWrite(LED_PIN, led_values[*value_fig]); // 0 - 255
    *value_fig += 1;
    if(*value_fig > 3){
      *value_fig = 0;
    }
    return;
}

void change_isOn(int *high_times, int INPUT_PIN){
  if(*high_times < 0){
    // do not change status immediately after status changed
    *high_times += 1;
    digitalWrite(BOARD_LED, LOW);
  }else if(digitalRead(INPUT_PIN) == HIGH){
    *high_times += 1;
    if(*high_times > 3){  // pushing 0.4 secs
      isOn = 1 - isOn;
      *high_times = -50; // wait 5 secs after status changed
      digitalWrite(BOARD_LED, HIGH);
    }
  }else{
    *high_times = 0;
    digitalWrite(BOARD_LED, LOW);
  }
  return;
}

const int LED_PIN = 1;
const int RPI_INPUT_PIN = 2;
int isOn = 0;
int led_values[] = {255, 200, 255, 150};
int led_value_fig = 0;  // 0 - 3
int rpi_high_times = 0;

void setup() {
  pinMode(RPI_INPUT_PIN, INPUT);
}

void loop() {
  if(rpi_high_times < 0){
    // do not change status immediately after status changed
    rpi_high_times += 1;
  }else if(digitalRead(RPI_INPUT_PIN) == HIGH){
    rpi_high_times += 1;
    if(rpi_high_times > 4){  // pushing 0.4 secs
      isOn = 1;
      rpi_high_times = -50; // wait 5 secs after status changed
    }
  }else{
    rpi_high_times = 0;
  }

  if(isOn > 0){
    fire(&led_value_fig);
  }
  delay(100);
}

int fire(int *value_fig){
    analogWrite(LED_PIN, led_values[*value_fig]); // 0 - 255
    *value_fig += 1;
    if(*value_fig > 3){
      *value_fig = 0;
    }
}


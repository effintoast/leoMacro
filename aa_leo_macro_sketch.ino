char* key_combos[10];
volatile int active_key = 0;
long button_bounce = 0;

void button_handler(int index){
  if((millis() - button_bounce) >= 200){
    if(index == active_key){
      active_key = 0;
      Serial.println("toggle btn"+String(index)+" off");
    }else{
      active_key = index;
      Serial.println("toggle btn"+String(index)+" on");
    }
    button_bounce = millis();
  }
}

//trigger macro 1
void pin2_handler(){ button_handler(1); }
//trigger macro 2
void pin3_handler(){ button_handler(2); }

void setup() {
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  attachInterrupt(digitalPinToInterrupt(2), pin2_handler, FALLING);
  attachInterrupt(digitalPinToInterrupt(3), pin3_handler, FALLING);
  Serial.begin(9600);

  //simple buff test
  key_combos[1] = "84,delay_1435,81,delay_1466,69,delay_2138,116,delay_10000";
  key_combos[2] = "114,delay_3230,122,delay_3198,53,delay_2480,54,delay_16000";
}

void key_loop(int index){
  
  String keys = key_combos[index];
  int index_pos = 0;
  while(index_pos >= 0 && active_key == index){
    index_pos = keys.indexOf(',');
    String current_key = keys.substring(0,index_pos);
    if(current_key != ""){
       Serial.println(current_key);
      if(current_key.indexOf('delay_') != -1){
        current_key = current_key.substring(6);
        long tmp_delay = current_key.toInt()+random(200,400);
        Serial.println(String(tmp_delay));
        while(tmp_delay > 0 && active_key == index){
          delay(50);
          tmp_delay = tmp_delay-50;
        }
      }else{
         Keyboard.write(current_key.toInt());
      }
    }
    //Serial.println(current_key);
    keys = keys.substring(index_pos+1);
  }
  
}


void loop() {
  
  if(active_key > 0){
    key_loop(active_key);
  }

}

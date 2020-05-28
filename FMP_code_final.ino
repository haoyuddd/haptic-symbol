/*(c) 2020 Haoyu Dong
   for FMP -final
   Industrial Design, TU Eindhoven
   Personal website: http://www.haoyudong.me
*/
#include <timer.h>
Timer<40>timer; //based on how many timer s

#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
uint8_t vibPin[] = {0, 1, 2, 3, 4, 5, 7, 10, 9};
int vibnum = 0;
char datastatus = 0;
int dataval = 0;
int vibstatus = 0;

bool Lvib_on(int vibnum) {
  Serial.println(F("Low vibration"));
  int i = vibnum - 1;
  pwm.setPin(vibPin[i], 800, false);
  return true;
}

bool Hvib_on(int vibnum) {
  Serial.println(F("High vibration"));
  int i = vibnum - 1;
  pwm.setPin(vibPin[i], 2000, false);
  return true;
}

bool vib_off(int vibnum) {
  int i = vibnum - 1;
  pwm.setPin(vibPin[i], 0, false);
}
bool ALLvib_on(void *) {
  //  Serial.println("ALL vib runing on");
  Lvib_on(1);
  Lvib_on(2);
  Lvib_on(3);
  Lvib_on(4);
  Lvib_on(5);
  Lvib_on(6);
  Lvib_on(7);
  Lvib_on(8);
  Lvib_on(9);
  return true;
}

bool ALLvib_off (void *) {
  //  Serial.println("ALL vib runing off");
  for (int i = 0; i < 9; i++) {
    pwm.setPin(vibPin[i], 0, false);
  }
  return true;
}

bool showproblem_1(void *) {
  pwm.setPin(vibPin[0], 700, false);
  //  pwm.setPin(vibPin[1], 700, false);
  pwm.setPin(vibPin[2], 700, false);
}
bool showproblem_2(void *) {
  pwm.setPin(vibPin[3], 600, false);
  //  pwm.setPin(vibPin[4], 600, false);
  pwm.setPin(vibPin[5], 600, false);
}
bool showproblem_3(void *) {
  pwm.setPin(vibPin[6], 500, false);
  //  pwm.setPin(vibPin[7], 500, false);
  pwm.setPin(vibPin[8], 500, false);
}
bool reminder_1(void *) {
  pwm.setPin(vibPin[0], 600, false);
  pwm.setPin(vibPin[1], 600, false);
  //  pwm.setPin(vibPin[2], 600, false);
  pwm.setPin(vibPin[3], 600, false);
  pwm.setPin(vibPin[5], 600, false);
  //  pwm.setPin(vibPin[6], 600, false);
  pwm.setPin(vibPin[7], 600, false);
  pwm.setPin(vibPin[8], 600, false);
}

bool emergency (void *) {
  Hvib_on(1);
  Hvib_on(3);
  Hvib_on(5);
  Hvib_on(7);
  Hvib_on(9);
}

bool wave_1(int vibnum) {
  int i = vibnum - 1;
  Serial.println(F("wave1"));
  for (int s = 0; s < 1500; s ++) {
    pwm.setPWM(vibPin[i], 0, 1000 * sin((PI / 3000) * s)) ;
  }
}

bool wave_2(int vibnum) {
  int i = vibnum - 1;
  Serial.println(F("wave2"));
  for (int s = 1500; s > 0; s --) {
    pwm.setPWM(vibPin[i], 900 * sin((PI / 3000) * s ), 0) ;
  }
}

bool active(void *) {
  Lvib_on(2);
  Lvib_on(4);
  Lvib_on(6);
  Lvib_on(8);
}
bool reject_1(void *) {
  Lvib_on(1);
  Lvib_on(5);
  Lvib_on(9);

}
bool reject_2(void *) {
  Lvib_on(3);
  Lvib_on(5);
  Lvib_on(7);
}

void setup() {
  Serial.begin(9600);//Initialize serial communications at a 9600 baud rate
  Serial.println(F("PWM ready"));
  pwm.begin();
  for (int i = 0; i < 10; i++) {
    pwm.setPin(vibPin[i], 0, false);
  }
  pwm.setPWMFreq(800);
}

void loop() {
  timer.tick();
  if (Serial.available()) { //Checking if Processing
    Serial.println("sending datastatus");
    String datastatus = Serial.readString(); //Reading the value and store it in val
    datastatus.trim();
    Serial.print(F("datastatus "));
    Serial.println (datastatus);
    if (datastatus.equals("1")) {
      vibstatus = 1;
      Serial.println("vibstatus =1");
    }
    if (datastatus.equals("2")) {
      vibstatus = 2;
      Serial.println("vibstatus =2");
    }
    if (datastatus.equals("3")) {
      vibstatus = 3;
      Serial.println("vibstatus =3");
    }
    if (datastatus.equals("4")) {
      vibstatus = 4;
      Serial.println("vibstatus =4");
    }
    if (datastatus.equals("5")) {
      vibstatus = 5;
      Serial.println("vibstatus =5");
    }
    if (datastatus.equals("6")) {
      vibstatus = 6;
      Serial.println("vibstatus =6");
    }
    if (datastatus.equals("7")) {
      vibstatus = 7;
      Serial.println("vibstatus =7");
    }
    if (datastatus.equals("8")) {
      vibstatus = 8;
      Serial.println("vibstatus =8");
    }
    if (datastatus.equals("9")) {
      vibstatus = 9;
      Serial.println("vibstatus =9");
    }
  }
  //----------------------Haptic Patterns:---------------------------
  if (vibstatus == 1) {
    Serial.println(F("The haptic pattern is (1) CONFIRM "));
    timer.in(500 , Lvib_on, 2);//2
    timer.in(500 + 300 , vib_off, 5);
    timer.in(900, Hvib_on, 2);//3
    timer.in(900 + 300, vib_off, 2); //3
    timer.in(1200, Lvib_on, 2);//3
    timer.in(1200 + 300, vib_off, 2); //3
    vibstatus = 0;
  }
  if (vibstatus == 2) {
    Serial.println(F("The haptic pattern is (2) REJECT"));
    timer.in(500, reject_1);
    timer.in(500 + 500, ALLvib_off);
    timer.in(1300 + 200, reject_2);
    timer.in(1800 + 500, ALLvib_off);
    vibstatus = 0;
  }
  if (vibstatus == 3) {
    Serial.println(F("The haptic pattern is (3) SHOW NORMAL PROBLEM"));
    timer.in (500, showproblem_1);
    //    timer.in(500, wave_2, 2);
    timer.in(500 + 500, ALLvib_off);
    timer.in(1100, showproblem_2);
    //    timer.in(500, wave_2, 5);
    timer.in(1100 + 500, ALLvib_off);
    timer.in(1700, showproblem_3);
    //    timer.in(500, wave_2, 8);
    timer.in(1700 + 500, ALLvib_off);
    vibstatus = 0;
  }
  if (vibstatus == 4) {
    Serial.println(F("The haptic pattern is (4) EMERGENCY"));
    timer.in(500, emergency);
    timer.in(500 + 300, ALLvib_off);
    timer.in(900 + 200, emergency);
    timer.in(1100 + 400, ALLvib_off);
    timer.in(1600 + 200, emergency);
    timer.in(1800 + 300, ALLvib_off);
    vibstatus = 0;
  }
  if (vibstatus == 5) {
    Serial.println(F("The haptic pattern is (5) REQUEST"));
    timer.in(500, Lvib_on, 8); //28
    timer.in(500 + 500, vib_off, 8);
    timer.in(1100, Lvib_on, 5);//29
    timer.in(1100 + 400, vib_off, 5);
    timer.in(1500, Lvib_on, 2); //30
    timer.in(1500 + 300, vib_off, 2);
    vibstatus = 0;
  }
  if (vibstatus == 6) {
    Serial.println(F("The haptic pattern is (6) BOOTING"));
    timer.in(500, wave_1, 5);
    timer.in(500 + 1500, vib_off, 5);
    timer.in(2000, active);
    timer.in(2000 + 300, ALLvib_off);
    vibstatus = 0;
  }
  if (vibstatus == 7) {
    Serial.println(F("The haptic pattern is (7) REMINDER"));
    timer.in(500, reminder_1);
    timer.in(500 + 400, ALLvib_off);
    timer.in(900, Lvib_on, 5);
    timer.in(1500 + 500, vib_off, 5);

    vibstatus = 0;
  }
  if (vibstatus == 8) {
    Serial.println(F("The haptic pattern is (8) SHOW PROGRESS"));
    timer.in(500, Lvib_on, 1);//12
    timer.in(500 + 500, vib_off, 1);//12
    timer.in(1000, Lvib_on, 2);//13
    timer.in(1000 + 500, vib_off, 2);//12
    timer.in(1500, Lvib_on, 3);//14
    timer.in(1500 + 500, vib_off, 3); //12
    timer.in(2000, Lvib_on, 6);//15
    timer.in(2000 + 500, vib_off, 6); //12
    timer.in(2500, Lvib_on, 9);//16
    timer.in(2500 + 500, vib_off, 9); //12
    timer.in(3000, Lvib_on, 8);//17
    timer.in(3000 + 500, vib_off, 8); //12
    timer.in(3500, Lvib_on, 7);//18
    timer.in(3500 + 500, vib_off, 7); //12
    timer.in(4000, Lvib_on, 4);//19
    timer.in(4000 + 500, vib_off, 4); //12
    timer.in(4500, Lvib_on, 1);//20
    timer.in(4500 + 500, vib_off, 1); //12
    vibstatus = 0;
  }
  if (vibstatus == 9) { //TRIAL
    timer.in(500, Lvib_on, 1);//12
    timer.in(500 + 500, vib_off, 1);//12
    timer.in(1000, Lvib_on, 2);//13
    timer.in(1000 + 500, vib_off, 2);//12
    timer.in(1500, Lvib_on, 3);//14
    timer.in(1500 + 500, vib_off, 3); //12
    timer.in(2000, Lvib_on, 4);//15
    timer.in(2000 + 500, vib_off, 4); //12
    timer.in(2500, Lvib_on, 5);//16
    timer.in(2500 + 500, vib_off, 5); //12
    timer.in(3000, Lvib_on, 6);//17
    timer.in(3000 + 500, vib_off, 6); //12
    timer.in(3500, Lvib_on, 7);//18
    timer.in(3500 + 500, vib_off, 7); //12
    timer.in(4000, Lvib_on, 8);//19
    timer.in(4000 + 500, vib_off, 8); //12
    timer.in(4500, Lvib_on, 9);//20
    timer.in(4500 + 500, vib_off, 9); //12
    vibstatus = 0;
  }
}

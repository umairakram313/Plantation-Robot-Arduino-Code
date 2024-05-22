#include <Servo.h>

const int A = 2;  //left backward
const int B = 3;  //left forward
const int C = 4;  //right backward
const int D = 5;  //right forward
const int right_foll = 22;
const int left_junc = 28;
const int right_junc = 26;
const int left_foll = 24;
const int servo_pwm = 40;
const int back_left_follow = 48;
const int back_right_follow = 50;
int junction_no = 0;
int aa = 700;  //delay

const int maxspeed = 700;
const int stope = 1500;
Servo servo;

float Kp = 120;
float Ki = 0;
float Kd = 30;

float error = 0, P = 0, I = 0, d = 0, PID_value = 0;
float previous_error = 0, previous_I = 0;

int initial_motor_speed = 80;

bool stopp = false;
int backing = 300;
int stall = 500;
int thoraAgay = 200;
int move_back_drop = 360;
int move_after_drop = 760;

int track_no = 0;

const int b1 = 34;
const int b2 = 32;
const int b3 = 30;
const int b4 = 36;

void setup() {
  // put your setup code here, to run once:
  //servo.attach(9); // PIN 9

  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(left_foll, INPUT);
  pinMode(right_foll, INPUT);
  pinMode(left_junc, INPUT);
  pinMode(right_junc, INPUT);
  pinMode(servo_pwm, OUTPUT);

  Serial.begin(9600);
  delay(500);
   phase1();
   phase2();
  // track4();
}

void loop() {  //not utilized
 
}


void phase1()
{
  while(junction_no<5)
  {
    follower();
    if(digitalRead(left_junc) ==HIGH && digitalRead(right_junc)==HIGH)
    {
      junction_no++;
      switch(junction_no)
      {
        case 2:
          moveForward(50);
          left90();
          for(int i =0 ; i<=13;i++){
          follower();
          delay(30);
          }
          
          for(int i =0 ; i<=54;i++){
          backFollower();
          delay(30);
          }
          stop();
          scan();
          while(!(digitalRead(left_junc) ==HIGH && digitalRead(right_junc)==HIGH))
          {
            follower();
          }
          moveBackward(50);
          right90();
          left();
          delay(50);
          break;
        case 4:
          left90();
          break;
        case 5:
          moveForward(150);
          break;
        default:
          moveForward(250);
          break;
      }
    }

  }
}

void phase2() {
  switch (track_no) {
    case 1:
      track1();
      break;
    case 2:
      track2();
      break;
    case 3:
      track3();
      break;
    case 4:
      track4();
      break;
    case 5:
      track5();
      break;
    default:
      break;
  }
}

void track1() {
  while (!stopp) {
    follower();
    if ((digitalRead(left_junc) == HIGH && digitalRead(right_junc) == HIGH)) {
      junction_no++;
      switch (junction_no) {
        case 7:
          left90();
          break;
        case 10:
          moveForward(200);
          stop();
          delay(500);
          lift();  //1st rock lift
          delay(700);
          moveBackward(300);
          halfrev();
          moveForward(200);
          break;
        case 13:
          left90();
          break;
        case 17:
          stop(500);
          moveBackward(move_back_drop-110);
          stop(500);
          drop();  //1st rock drop
          delay(500);
          moveBackward(move_after_drop);
          left90();
          break;
        case 18:
          right90();
          break;
        case 19:
          moveForward(200);
          stop(500);
          lift();  //1st tree lift
          delay(500);
          stop(500);
          moveBackward(500);
          halfrev();
          while (!(digitalRead(left_junc) == HIGH && digitalRead(right_junc) == HIGH)) {
            follower();
          }
          moveBackward(50);
          right90();
          break;
        case 21:
          left90();
          break;
        case 24:
          stop(500);
          moveBackward(move_back_drop-110);
          stop(500);
          drop();  //1st tree drop
          delay(500);
          moveBackward(move_after_drop+200);
          right90();
          break;
        case 25:
          halfrev();
          break;
        case 27:
          moveForward(200);
          stop();
          delay(500);  //2nd rock lift
          lift();
          delay(500);
          moveForward(200);
          break;
        case 29:
          left90();
          break;
        case 31:
          left90();
          break;
        case 32:
          right90();
          break;
        case 33:
          stop(500);
          moveBackward(move_back_drop-110);
          stop(500);
          drop();  //2nd rock drop
          delay(500);
          moveBackward(move_after_drop+150);
          left90();
          break;
        case 34:
          right90();
          break;
        case 35:
          moveForward(200);
          stop(500);
          lift();  //2nd tree lift
          delay(500);
          stop(500);
          moveBackward(500);
          halfrev();
          while (!(digitalRead(left_junc) == HIGH && digitalRead(right_junc) == HIGH)) {
            follower();
          }
          moveForward(150);
          break;
        case 37:
          stop(500);
          moveBackward(move_back_drop-110);
          stop(500);
          drop();  //2nd tree drop
          delay(500);
          moveBackward(move_after_drop+200);
          right90();
          break;
        case 39:
          halfrev();
          break;
        case 42:
          moveForward(200);
          stop(500);
          lift();  //3rd rock lift
          delay(500);
          stop(500);
          moveBackward(move_after_drop + 600);
          left90();
          break;
        case 44:
          stop(500);
          moveBackward(move_back_drop-110);
          stop(500);
          drop();  //3rd rock drop
          delay(500);
          moveBackward(move_after_drop);
          halfrev();
          moveForward(150);
          break;
        case 45:
          right90();
          break;
        case 46:
          right90();
          break;
        case 48:
          moveForward(200);
          stop(500);
          lift();  //3rd tree lift
          delay(500);
          stop(500);
          moveBackward(500);
          halfrev();
          while (!(digitalRead(left_junc) == HIGH && digitalRead(right_junc) == HIGH)) {
            follower();
          }
          moveForward(150);
          break;
        case 49:
          left90();
          break;
        case 51:
          stop(500);
          moveBackward(move_back_drop-110);
          stop(500);
          drop();  //3rd tree drop
          delay(500);
          moveBackward(move_after_drop+200);
          left90();
          break;
        case 52:
          right90();
          break;
        case 55:
          moveForward(1000);
          stop(2000);
          stopp = true;
          break;
        default:
          moveForward(300);
          break;
      }
    }
  }
}

void track2() {
  while (!stopp) {
    follower();
    if ((digitalRead(left_junc) == HIGH && digitalRead(right_junc) == HIGH)) {
      junction_no++;
      switch (junction_no) {
        case 6:
          left90();
          break;
        case 10:
          right90();
          break;
        case 11:
          right90();
          break;
        case 14:
          moveForward(200);
          stop();
          delay(500);
          lift();  //1st rock lift
          delay(1000);
          stop(500);
          moveForward(200);
          break;
        case 15:
          left90();
          break;
        case 19:
          stop(500);
          moveBackward(move_back_drop-110);
          stop(500);
          drop();  //1st rock drop
          delay(500);
          moveBackward(move_after_drop);
          halfrev();
          moveForward(50);
          break;
        case 21:
          right90();
          break;
        case 22:
          right90();
          break;
        case 25:
          moveForward(200);
          stop(500);
          lift();  //1st tree lift
          delay(500);
          stop(500);
          moveBackward(500);
          halfrev();
          while (!(digitalRead(left_junc) == HIGH && digitalRead(right_junc) == HIGH)) {
            follower();
          }
          //right();
          //delay(150);
          moveForward(250);
          break;
        case 28:
          stop(500);
          moveBackward(move_back_drop-110);
          stop(500);
          drop();  //1st tree drop
          delay(500);
          moveBackward(move_after_drop);
          halfrev();
          moveForward(50);
          break;
        case 30:
          left90();
          break;
        case 31:
          left90();
          break;
        case 33:
          moveForward(200);
          stop();
          delay(500);
          lift();  //2nd rock lift
          delay(500);
          stop(1000);
          moveBackward(move_after_drop + 550);
          left90();
          break;
        case 34:
          left90();
          break;
        case 36:
          stop(500);
          moveBackward(move_back_drop-110);
          stop(500);
          drop();  //2nd rock drop
          delay(500);
          moveBackward(move_after_drop);
          moveBackward(150);
          halfrev();
          moveForward(50);
          break;
        case 37:
          right90();
          break;
        case 38:
          right90();
          break;
        case 40:
          moveForward(200);
          stop(500);
          lift();  //2nd tree lift
          delay(500);
          stop(1000);
          moveBackward(500);
          halfrev();
          while (!(digitalRead(left_junc) == HIGH && digitalRead(right_junc) == HIGH)) {
            follower();
          }
          //right();
          //delay(150);
          moveForward(250);
          break;
        case 42:
          stop(500);
          moveBackward(move_back_drop-110);
          stop(500);
          drop();  //2nd tree drop
          delay(500);
          moveBackward(move_after_drop + 50);
          left90();
          break;
        case 44:
          halfrev();
          moveForward(50);
          break;
        case 47:
          moveForward(200);
          stop();
          delay(500);
          lift();  //3rd rock lift
          delay(500);
          stop(1000);
          moveBackward(150);
          halfrev();
          break;
        case 48:
          left90();
          break;
        case 50:
          stop(500);
          moveBackward(move_back_drop-110);
          stop(500);
          drop();  //3rd rock drop
          delay(500);
          moveBackward(move_after_drop);
          moveBackward(150);
          halfrev();
          break;
        case 51:
          right90();
          break;
        case 52:
          right90();
          break;
        case 54:
          moveForward(200);
          stop(500);
          lift();  //3rd tree lift
          delay(500);
          stop(1000);
          moveBackward(500);
          halfrev();
          while (!(digitalRead(left_junc) == HIGH && digitalRead(right_junc) == HIGH)) {
            follower();
          }
          //right();
          //delay(150);
          moveForward(150);
          break;
        case 55:
          stop(500);
          moveBackward(move_back_drop-110);
          stop(500);
          drop();  //3rd tree drop
          delay(500);
          moveBackward(move_after_drop + 50);
          left90();
          break;
        case 59:
          moveForward(1000);
          stopp = true;
          stop(2000);
          break;
        default:
          moveForward(300);
          break;
      }
    }
  }
}

void track3() {
  while (!stopp) {
    follower();
    if ((digitalRead(left_junc) == HIGH && digitalRead(right_junc) == HIGH)) {
      junction_no++;
      switch (junction_no) {
       case 8:
          stop(stall);
          left90();
          break;
        case 10:
          moveForward(200);
          stop(500);
          lift();  //1st rock lift
          delay(1000);
          stop(500);
          moveBackward(100);
          halfrev();
          break;
        case 12:
          left90();
          break;
        case 15:
          stop(500);
          moveBackward(move_back_drop-110);
          stop(500);
          drop();  //1st rock drop
          delay(500);
          moveBackward(move_after_drop);
          halfrev();
          moveForward(50);
          break;
        case 17:
          right90();
          break;
        case 18:
          right90();
          break;
        case 21:
          moveForward(200);
          stop(500);
          lift();  //1st tree lift
          delay(500);
          stop(500);
          moveBackward(300);
          halfrev();
          while (!(digitalRead(left_junc) == HIGH && digitalRead(right_junc) == HIGH)) {
            follower();
          }
          moveForward(250);
          break;
        case 23:
          right90();
          break;
        case 24:
          stop(500);
          moveBackward(move_back_drop-110);
          stop(500);
          drop();  //1st tree drop
          delay(500);
          moveBackward(move_after_drop);
          halfrev();
          moveForward(50);
          break;
        case 25:
          left90();
          break;
        case 26:
          left90();
          break;
        case 28:
          moveForward(200);
          stop(500);
          lift();  //2nd rock lift
          delay(500);
          stop(1000);
          moveBackward(200);
          moveBackward(move_after_drop + 500);
          right90();
          break;

        case 30:
          stop(500);
          moveBackward(move_back_drop-110);
          stop(500);
          drop();  //2nd rock drop
          delay(500);
          moveBackward(move_after_drop);
          moveBackward(150);
          halfrev();
          moveForward(50);
          break;

        case 31:
          right90();
          break;

        case 32:
          right90();
          break;

        case 34:
          moveForward(200);
          stop(500);
          lift();  //2nd tree lift
          delay(500);
          stop(1000);
          //right();
          //delay(150);
          moveForward(250);
          break;

        case 35:
          stop(300);
          moveBackward(250);
          halfrev();
          break;

        case 38:
          stop(500);
          moveBackward(move_back_drop-160);
          stop(500);
          drop();  //2nd tree drop
          delay(500);
          moveBackward(move_after_drop + 200);
          right90();
          break;

        case 39:
          left90();
          break;

        case 41:
          moveForward(200);
          stop(500);
          lift();  //3rd rock lift
          delay(500);
          stop(500);
          moveBackward(300);
          halfrev();
          break;

        case 43:
          right90();
          break;

        case 44:
          left90();
          break;

        case 45:
          stop(500);
          moveBackward(move_back_drop-140);
          stop(500);
          drop();  //3rd rock drop
          delay(500);
          moveBackward(move_after_drop);
          left90();
          break;

        case 46:
          left90();
          break;

        case 47:
          halfrev();
          break;

        case 49:
          moveForward(200);
          stop(500);
          lift();  //3rd tree lift
          delay(500);
          stop(500);
          moveForward(200);
          break;

        case 50:
          halfrev();
          break;

        case 54:
          stop(500);
          moveBackward(move_back_drop-160);
          stop(500);
          drop();  //3rd tree drop
          delay(500);
          moveBackward(move_after_drop);
          halfrev();
          break;

        case 55:
          right90();
          break;

        case 59:
          moveForward(700);
          stop(2000);
          stopp = true;
          break;

        default:
          moveForward(300);
          break;
      }
    }
  }
}

void track4() {
  while (!stopp) {
    follower();
    if (digitalRead(left_junc) == HIGH && digitalRead(right_junc) == HIGH) {
      junction_no++;
      switch (junction_no) {
       case 6:
          left90();
          break;

        case 7:
          right90();
          break;

        case 9:
          moveForward(200);
          stop(500);
          lift();  //1st rock lift
          delay(1000);
          stop(500);
          moveForward(150);
          break;
        case 10:
          right90();
          break;
        case 11:
          left90();
          break;
        case 13:
          stop(500);
          moveBackward(move_back_drop - 100);
          stop(500);
          drop();  //1st rock drop
          delay(500);
          moveBackward(move_after_drop);
          stop(stall);
          halfrev();
          moveForward(50);
          break;
        case 15:
          right90();
          break;
        case 16:
          right90();
          break;
        case 19:
          moveForward(200);
          stop(500);
          lift();  //1st tree lift
          delay(500);
          stop(500);
          moveForward(200);
          break;
        case 20:
          stop(stall);
          moveBackward(100);
          halfrev();
          break;
        case 24:
          stop(500);
          moveBackward(move_back_drop-110);
          stop(500);
          drop();  //1st tree drop
          delay(500);
          moveBackward(move_after_drop+150);
          stop(stall);
          left90();
          moveForward(50);
          break;
        case 25:
          stop(stall);
          moveBackward(100);
          halfrev();
          break;
        case 27:
          moveForward(200);
          stop(500);
          lift();  //2nd rock lift
          delay(500);
          stop(1000);
          moveBackward(move_after_drop + 800);
          stop(stall);
          right90();
          break;
        case 29:
          stop(500);
          moveBackward(move_back_drop-110);
          stop(500);
          drop();  //2nd rock drop
          delay(500);
          moveBackward(move_after_drop);
          moveBackward(150);
          stop(stall);
          halfrev();
          moveForward(50);
          break;
        case 30:
          right90();
          break;
        case 31:
          right90();
          break;
        case 33:
          moveForward(200);
          stop(500);
          lift();  //2nd tree lift
          delay(500);
          stop(1000);
          moveForward(250);
          break;
        case 34:
          stop(stall);
          moveBackward(50);
          halfrev();
          break;
        case 37:
          stop(500);
          moveBackward(move_back_drop-110);
          stop(500);
          drop();  //2nd tree drop
          delay(500);
          moveBackward(move_after_drop + 300);
          stop(stall);
          right90();
          break;
        case 39:
          left90();
          break;
        case 41:
          left90();
          break;
        case 43:
          moveForward(200);
          stop(500);
          lift();  //3rd rock lift
          delay(500);
          stop(500);
          moveBackward(300);
          stop(stall);
          halfrev();
          break;
        case 44:
          right90();
          break;
        case 46:
          right90();
          break;
        case 47:
          left90();
          break;
        case 48:
          stop(500);
          moveBackward(move_back_drop-110);
          stop(500);
          drop();  //3rd rock drop
          delay(500);
          moveBackward(move_after_drop);
          stop(stall);
          left90();
          break;
        case 49:
          left90();
          break;
        case 51:
          stop(stall);
          moveBackward(100);
          halfrev();
          break;
        case 54:
          moveForward(200);
          stop(500);
          lift();  //3rd tree lift
          delay(500);
          stop(500);
          moveForward(200);
          break;
        case 55:
          stop(stall);
          moveBackward(100);
          halfrev();
          break;
        case 59:
          left90();
          break;
        case 60:
          stop(500);
          moveBackward(move_back_drop-110);
          stop(500);
          drop();  //3rd tree drop
          delay(500);
          moveBackward(move_after_drop+250);
          stop(stall);
          left90();
          break;
        case 62:
          right90();
          break;
        case 66:
          moveForward(1000);
          stop(2000);
          stopp = true;
          break;
        default:
          moveForward(300);
          break;
      }
    }
  }
}

void track5() {
  while (!stopp) {
    follower();
    if (digitalRead(left_junc) == HIGH && digitalRead(right_junc) == HIGH) {
      junction_no++;
      switch (junction_no) {
        case 6:
          stop(stall);
          left90();
          break;
        case 7:
          stop(stall);
          right90();
          break;
        case 10:
          moveForward(200);
          stop();
          delay(500);
          lift();  //1st rock lift
          delay(700);
          moveBackward(300);
          right90();
          break;
        case 11:
          stop(stall);
          left90();
          break;
        case 13:
          stop(500);
          moveBackward(move_back_drop - 100);
          stop(500);
          drop();  //1st rock drop
          delay(500);
          moveBackward(move_after_drop+80);
          stop(stall);
          halfrev();
          break;
        case 14:
          stop(stall);
          right90();
          break;
        case 15:
          stop(stall);
          right90();
          break;
        case 17:
          moveForward(200);
          stop(500);
          lift();  //1st tree lift
          delay(500);
          stop(500);
          moveForward(100);
          break;
        case 18:
          moveBackward(200);
          stop(stall);
          halfrev();
          break;
        case 21:
          stop(500);
          moveBackward(move_back_drop-110);
          stop(500);
          drop();  //1st tree drop
          delay(500);
          moveBackward(move_after_drop+50);
          left90();
          break;
        case 22:
          stop(stall);
          right90();
          break;
        case 25:
          stop(stall);
          right90();
          break;
        case 27:
          stop(stall);
          right90();
          break;
        case 29:
          moveForward(200);
          stop();
          delay(500);  //2nd rock lift
          lift();
          delay(500);
          moveForward(200);
          break;
        case 30:
          stop(stall);
          right90();
          break;
        case 31:
          stop(stall);
          left90();
          break;
        case 32:
          stop(500);
          moveBackward(move_back_drop - 100);
          stop(500);
          drop();  //2nd rock drop
          delay(500);
          moveBackward(move_after_drop+80);
          stop(stall);
          left90();
          break;
        case 33:
          stop(stall);
          right90();
          break;
        case 34:
          moveForward(200);
          stop(500);
          lift();  //2nd tree lift
          delay(500);
          stop(500);
          moveForward(200);
          break;
        case 35:
          moveBackward(200);
          stop(stall);
          halfrev();
          break;
        case 38:
          stop(500);
          moveBackward(move_back_drop-110);
          stop(500);
          drop();  //2nd tree drop
          delay(500);
          moveBackward(move_after_drop+200);
          right90();
          break;
        case 40:
          stop(stall);
          left90();
          break;
        case 43:
          stop(stall);
          left90();
          break;
        case 44:
          stop(stall);
          left90();
          break;
        case 46:
          moveForward(200);
          stop(500);
          lift();  //3rd rock lift
          delay(500);
          stop(500);
          moveForward(200);
          break;
        case 47:
          stop(stall);
          right90();
          break;
        case 48:
          stop(stall);
          left90();
          break;
        case 49:
          stop(500);
          moveBackward(move_back_drop - 100);
          stop(500);
          drop();  //3rd rock drop
          delay(500);
          moveBackward(move_after_drop+70);
          stop(stall);
          left90();
          break;
        case 50:
          stop(stall);
          right90();
          break;
        case 51:
          moveForward(200);
          stop(500);
          lift();  //3rd tree lift
          delay(500);
          stop(500);
          moveForward(200);
          break;
        case 52:
          moveBackward(200);
          stop(stall);
          halfrev();
          break;
        case 55:
          stop(500);
          moveBackward(move_back_drop-100);
          stop(500);
          drop();  //3rd tree drop
          delay(500);
          moveBackward(move_after_drop+70);
          stop(stall);
          left90();
          break;
        case 59:
          moveForward(1000);
          stop(2000);
          stopp = true;
          break;
        default:
          moveForward(300);
          break;
      }
    }
  }
}

void backFollower() {
  if (digitalRead(back_left_follow) == HIGH && digitalRead(back_right_follow) == LOW) {
    B_right();
  } else if (digitalRead(back_left_follow) == LOW && digitalRead(back_right_follow) == HIGH) {
    B_left();
  } else {
    moveBackward();
  }
}

void moveForward(int a) {
  analogDrive(0, 160, 0, 160);
  delay(a);
}


void moveForward() {
  analogDrive(0, 160, 0, 160);
}


void moveBackward() {
  analogDrive(130, 0, 135, 0);
}


void moveBackward(int a) {
  analogDrive(130, 0, 135, 0);
  delay(a);
}


void stop(int a) {
  digitalWrite(A, LOW);
  digitalWrite(B, LOW);
  digitalWrite(C, LOW);
  digitalWrite(D, LOW);
  delay(a);
}


void stop() {
  digitalWrite(A, LOW);
  digitalWrite(B, LOW);
  digitalWrite(C, LOW);
  digitalWrite(D, LOW);
}


void left() {
  analogDrive(0, 0, 0, 150);
}

void B_left() {
  analogDrive(0, 0, 160, 0);
}

void right() {
  analogDrive(0, 155, 0, 0);
}


void B_right() {
  analogDrive(160, 0, 0, 0);
}

void right90() {
  moveForward(210);
  analogDrive(0, 80, 80, 0);
  delay(700);
  while (digitalRead(left_foll) == LOW) {
    analogDrive(0, 80, 80, 0);
  }
  stop(500);
  moveForward(100);
}

void left90() {
  //moveBackward(120);
  moveForward(210);
  analogDrive(80, 0, 0, 80);
  delay(700);
  while (digitalRead(right_foll) == LOW) {
    analogDrive(80, 0, 0, 80);
  }
  stop(500);
  moveForward(100);
}

void right90(int a) {
  //moveBackward(120);
  analogDrive(0, 80, 80, 0);
  delay(a);
  stop(500);
}


void left90(int a) {
  //moveBackward(120);
  analogDrive(80, 0, 0, 80);
  delay(a);
}


void halfrev() {
  analogDrive(100, 0, 0, 100);
  delay(1200);
  while (digitalRead(right_foll) == LOW) {
    analogDrive(100, 0, 0, 100);
  }
  right();
  delay(60);
  stop(500);
}

void halfrev(int a) {
  stop(500);
  digitalWrite(A, LOW);
  digitalWrite(B, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(D, LOW);
  delay(a);
  stop(500);
}

void lift() {
  // if (!(digitalRead(left_foll) == HIGH && digitalRead(right_foll) == HIGH)) {
  int pos = 0;
  servo.attach(40);
  for (pos = 160; pos >= 0; pos -= 1) {  // goes from 180 degrees to 0 degrees
    servo.write(pos);                    // tell servo to go to position in variable 'pos'
    delay(15);                           // waits 15 ms for the servo to reach the position
  }
  // }
  stop(1000);
}
void drop() {
  int pos = 0;
  servo.attach(40);
  for (pos = 0; pos <= 160; pos += 1) {  // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    servo.write(pos);  // tell servo to go to position in variable 'pos'
    delay(15);         // waits 15 ms for the servo to reach the position
  }
  stop(1000);
}

void follower() {

  if (digitalRead(left_foll) == HIGH && digitalRead(right_foll) == LOW) {
    left();

  } else if (digitalRead(left_foll) == LOW && digitalRead(right_foll) == HIGH) {
    right();
  } else {
    moveForward();
  }
}

void rotate(int speed, int wait) {
  speed = map(speed, -100, +100, stope - maxspeed, stope + maxspeed);
  servo.writeMicroseconds(speed);
  delay(wait);
}

void scan() {
  stop(stall);
  while (track_no == 0) {
    if (digitalRead(b1) == HIGH && digitalRead(b2) == LOW && digitalRead(b3) == LOW && digitalRead(b4) == LOW) {
      track_no = 1;
      Serial.println("track 1");
    } else if (digitalRead(b1) == LOW && digitalRead(b2) == HIGH && digitalRead(b3) == LOW && digitalRead(b4) == LOW) {
      track_no = 2;
      Serial.println("track 2");
    } else if (digitalRead(b1) == LOW && digitalRead(b2) == LOW && digitalRead(b3) == LOW && digitalRead(b4) == HIGH) {
      track_no = 3;
      Serial.println("track 3");
    } else if (digitalRead(b1) == LOW && digitalRead(b2) == LOW && digitalRead(b3) == HIGH && digitalRead(b4) == LOW) {
      track_no = 4;
      Serial.println("track 4");
    } else if (digitalRead(b1) == HIGH && digitalRead(b2) == HIGH && digitalRead(b3) == LOW && digitalRead(b4) == LOW) {
      track_no = 5;
      Serial.println("track 5");
    } else
      track_no == 0;
  }
}

void analogDrive(int a, int b, int c, int d) {
  analogWrite(A, a);
  analogWrite(B, b);
  analogWrite(C, c);
  analogWrite(D, d);
}

void digitalDrive(int a, int b, int c, int d) {
  digitalWrite(A, a);
  digitalWrite(B, b);
  digitalWrite(C, c);
  digitalWrite(D, d);
}

void pidFollower() {
  if (digitalRead(left_foll) == HIGH && digitalRead(right_foll) == LOW) {
    error = -1;

  } else if (digitalRead(left_foll) == LOW && digitalRead(right_foll) == HIGH) {
    error = 1;
  } else {
    error = 0;
  }

  P = error;
  I += error;
  d = error - previous_error;

  PID_value = (Kp * P) + (Ki * I) + (Kd * d);

  //  previous_I = I;
  previous_error = error;

  int left_motor_speed = initial_motor_speed + PID_value;
  int right_motor_speed = initial_motor_speed - PID_value;

  // The motor speed should not exceed the max PWM value
  left_motor_speed = constrain(left_motor_speed, 0, 255);
  right_motor_speed = constrain(right_motor_speed, 0, 255);
  analogDrive(0, left_motor_speed, 0, right_motor_speed);
}
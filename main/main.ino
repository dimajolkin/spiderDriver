#include <Servo.h>
#define LEN 20
//int HEIGHT = -70;
int HEIGHT = -10;

int ARM_CENTER = 0;
int ARM_UP = -20;
int ARM_DOWN = 15;



#define MAX_HEIGHT 65

class TServo {
    Servo servo;
    public:
    int center = 0;
    TServo() {}
    TServo(int c) {
      center = c;
    }
    
    void init(int port, int center) {
      setCenter(center);
      attach(port);
    }
    
    void setCenter(int c) {
      center = c;
    }
    
    void attach(int p) {
      servo.attach(p);
    }
    
    /**
     * Устанавливает положение серво в дапазаоне [-LEN LEN]
     * где 0 - центр
     *  
     */
    void write(int pos) {
        if ((pos >= -LEN) && (pos <= LEN)) {
            servo.write(pos + center);            
        }
    }
};


/**
 * Рука
 *  - 2 серво работают синхронно
 */
class Arm {
   Servo s1;
   Servo foot;
   int _center = 0;
   int delta  = 0; //отклонение работы привода ноги

public:
   Arm(int c, int d) {
    _center = c;
    delta = d; 
   }
   
   void attach(int p1, int p2) {
       s1.attach(p1);
       foot.attach(p2);
   }

   /**
    * диапазао от -65 65
    */
   void write(int angle) {
       int t = angle + _center + ARM_CENTER;
      // if (t > MAX_HEIGHT) t = MAX_HEIGHT;
      // if ((t > -65) && (t < 65)) {
         s1.write(t);
         foot.write(t + delta); 
     //  }
   } 

   void up() {
      write(ARM_UP);
   }
   void down() {
     write(ARM_DOWN);
   }

    void center() {
      write(0);
   }
   
};


struct Shoulder {
   TServo s1;
   int _revert = 1;
   Arm *arm;
   void attach(int p1, int arm1, int arm2) {
        if (p1 !=  NULL)
           s1.attach(p1);

        if ((arm1 != NULL) && (arm2 != NULL)) {
           arm->attach(arm1, arm2);    
        }
   }

   Shoulder(int c1, Arm *_arm, int revert) {
        s1.setCenter(c1);
        arm = _arm;
        _revert = revert;
   }

   void center() {
       s1.write(0);
       arm->down();
       delay(100);
       arm->center();
       
   }

   void armTop() {
      arm->up();
   }

   void armBottom() {
     arm->down();
   }

   void armCenter() {
     arm->center();
   }
   
   void up() { 
       s1.write(LEN * _revert);
   }
   
   void down() {
       s1.write(-LEN * _revert);
   }
};



Shoulder f1(100, new Arm(75, -8), 1);
Shoulder f2(80,  new Arm(80, -8), -1);
Shoulder f3(85,  new Arm(80, -8),1);
//
Shoulder f4(115, new Arm(80, 15), 1);
Shoulder f5(90,  new Arm(65, 5),  -1);
Shoulder f6(75,  new Arm(70, +15),1);

class Spider {
  public:
  void init() {
       f1.attach(22, 23, 24);
       f2.attach(26, 27, 28);
       f3.attach(30, 31, 32);
       f4.attach(34, 35, 36);
       f5.attach(38, 39, 40);
       f6.attach(42, 43, 44); 
  }
  void allCenter() {
     f1.center();
     f2.center();
     f3.center();
     f4.center();
     f5.center();
     f6.center();
  }

  void allDown() {
     f1.armBottom();
    f2.armBottom();
    f3.armBottom();
    f4.armBottom();
    f5.armBottom();
    f6.armBottom();
  }

  void allTop() {
    f1.armTop();
    f2.armTop();
    f3.armTop();
    f4.armTop();
    f5.armTop();
    f6.armTop();
  }
};

Spider spider;
void setup() {
  Serial.begin(9600);

  spider.init();
  spider.allCenter();
  spider.allDown();

 delay(5000);
}

int step = 0;
void loop3() {
  f1.center();
 f2.center();
 f3.center();
 f4.center();
 f5.center();
 f6.center();
delay(5000);
 f1.up();
 f2.up();
 f3.up();
 f4.up();
 f5.up();
 f6.up();
 delay(5000);
 f1.center();
 f2.center();
 f3.center();
 f4.center();
 f5.center();
 f6.center();
  
  }
void loop() {
  
   Serial.print(step);
  switch(step) {
    case 0:
         f1.center();
         f2.center();
         f3.center();
         f4.center();
         f5.center();
         f6.center();
         step = 1;
         break;
         
    case 1: //первая группа подняла ноги
         f1.armTop();
         f3.armTop();
         f5.armTop();
         step = 2;
         break;
    case 2: //вторая группа верулась в цент
         f2.center();
         f4.center();
         f6.center();
         step = 3;
         break;
    case 3: //первая группа переставила ноги вперёд
         f1.down();
         f3.down();
         f5.down();
         step = 4;
         break;
    case 4: //первая группа отпустила ноги на землю
         f1.armCenter();
         f3.armCenter();
         f5.armCenter();
         step = 5;
         break;
         
    case 5: //вторая группа подняла ноги
         f2.armTop();
         f4.armTop();
         f6.armTop();
         step = 6;
         break;
    case 6://первая группа вернулась в цент
         f1.center();
         f3.center();
         f5.center();
         step = 7;
         break;
   case 7: //вторая группа переставила ноги вперёд
         f2.up();
         f4.up();
         f6.up();
         step = 8;
         break;
    case 8: //вторая группа отпустила ноги на землю
         f2.armCenter();
         f4.armCenter();
         f6.armCenter();
         step = 0;
         break;
  }

  delay(2000);
   
}

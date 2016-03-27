#include <Servo.h>

struct Foot { 
     Servo  s0, s1, s2;
     int _tick = 0;
     
     int _i = 0;
     bool f = true;
     
     int start = 0, end = 0;
     int top, bottom;
     
     void init(int p0, int p1, int p2) {
       //attach
        s0.attach(p0);
        s1.attach(p1);
        s2.attach(p2);
     }

     void inc() {
       _tick++;
       if (_tick >= end) {
         _tick = start;
         f = !f;
       }
     }

    /**
     * установка верхней и нижней точки ноги
     */
     void setLimitHeight(int _top, int _bottom) {
         top = _top;
         bottom = _bottom;
     }

     void setLimit(int _start,int _end) {
       start = _start;
       end = _end;
       _tick = _start;
     }

     void height(int angle) {
        s1.write(angle);
        s2.write(angle);
     }

     void write(int angle) {
        s0.write(angle);
     }

     bool getStatus() {
        return f;
     }

     void setTick(int t)
     {
       _tick = t;       
     }

     void inStart()
     {
        write(start);
     }

     void loop()
     { 
        inc();
        write(_tick);
     }


     void inTop()
     {
        height(top);      
     }

     void inBottom()
     {
        height(bottom); 
     }

};

Foot s[6];

Servo test;
void setup() {
 Serial.begin(9600);
 //right edge
 s[0].init(43, 44, 45);s[0].setLimit(30, 80);s[0].setLimitHeight(0, 130);
 s[1].init(21, 20, 19); s[1].setLimit(50, 100);s[1].setLimitHeight(0, 130);
 s[2].init(39, 40, 41); s[2].setLimit(110, 160);s[2].setLimitHeight(0, 130);


 
 //left edge
 s[3].init(22, 23, 24); s[3].setLimit(100, 150);s[3].setLimitHeight(0, 130);
 s[4].init(21, 20, 19); s[4].setLimit(65, 115); s[4].setLimitHeight(0, 130);
 s[5].init(17, 16, 15); s[5].setLimit(100, 150);s[5].setLimitHeight(0, 130);

}




void loop() {
  
   for (int i=0;i<6;i++) s[i].loop();
   
   if (s[0].getStatus()) {
       s[0].inTop();   
       s[1].inBottom();
       s[2].inTop();
       s[3].inBottom();
       s[4].inTop();
       s[5].inBottom();
    } else {
       s[0].inBottom();   
       s[1].inTop();
       s[2].inBottom();
       s[3].inTop();
       s[4].inBottom();
       s[5].inTop(); 
    }
 delay(80); 
}













#include <Servo.h>
#include <Math.h>
#include <stdio.h>

#include "Debug.h"
#include "MServo.h"

#define DEBUG;

typedef int INT;

INT servos[6][3][2]{
        {{133, 40}, {133, 40}, {133, 40}},  // 0
        {{133, 40}, {133, 40}, {133, 40}},  // 1
        {{133, 40}, {133, 40}, {133, 40}},  // 2
        {{133, 40}, {133, 40}, {133, 40}},  // 3
        {{133, 40}, {133, 40}, {133, 40}},  // 4
        {{133, 40}, {133, 40}, {133, 40}}   // 5
};


#define N 6
#define S 3
INT pins[N][S]{
        {30, 28, 26},
        {24, 22, 20},
        {18, 16, 14},
        {33, 35, 37},
        {39, 41, 43},
        {45, 47, 49}
};

INT angles[N][S]{
        {0, 50, 0},
        {0, 50, 0},
        {0, 50, 0},
        {0, 50, 0},
        {0, 50, 0},
        {0, 50, 0}
};


class Arm {

private:
    MServo s[3];
    int tmp_angle;

public:

    Arm(int port1, int port2, int port3) {
         s[0].attach(port1);
         s[1].attach(port2);
         s[2].attach(port3);
    }


    Arm() {

    }

    /**
     *  ports - массив лимитов
     *  n     - номер ноги
     */
    Arm(int n) {
        for (INT i = 0; i < 3; i++) {
            s[i].attach(pins[n][i]);
            Serial.println(pins[n][i]);
            s[i].setLimit(servos[n][i]);
            s[i].setPos(0);
        }
    }

    /**
     * Вращение по кругу
     */
    void circle(int radius) {
        int x = s[0].getPos();
        int y = s[1].getPos();
        int z = s[2].getPos();

//        if (tmp_angle++ > 100) tmp_angle = 0;
//        z = tmp_angle;


//        x =  50 + radius * cos(tmp_angle * M_PI / 180);
//        y =  50 + radius * sin(tmp_angle * M_PI / 180);


        s[0].setPos(x);
        s[1].setPos(y);
        s[2].setPos(z);
    }


};






void setup() {
    Serial.begin(9600);
    Arm arm(0);
}


int angle = 0;
int x = 0;
int y = 0;

void loop() {
    delay(50);
   // arm.circle(50);


}



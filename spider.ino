#include <Arduino.h>
#include <Servo.h>
#include <Math.h>
#include <stdio.h>

#include "Debug.h"
#include "MServo.h"

#define DEBUG;
#define N 6
#define S 3

typedef int INT;

INT servos[6][3][2]{
        {{133, 40}, {133, 40}, {133, 40}},  // 0
        {{133, 40}, {133, 40}, {133, 40}},  // 1
        {{133, 40}, {133, 40}, {133, 40}},  // 2
        {{133, 40}, {133, 40}, {133, 40}},  // 3
        {{133, 40}, {133, 40}, {133, 40}},  // 4
        {{133, 40}, {133, 40}, {133, 40}}   // 5
};

INT pins[N][S]{
        {30, 28, 26},
        {24, 22, 20},
        {18, 16, 14},
        {33, 35, 37},
        {39, 41, 43},
        {45, 47, 49}
};

INT angles[N][S]{
        {50, 0, 0},
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
};



MServo y;
MServo x;
MServo z;
void setup() {
    Serial.begin(9600);

    x.attach(30);
    x.setLimit(40, 130);
    x.setPos(40);

    y.attach(28);
    y.setLimit(40,130);
    y.setPos(40);

    z.attach(26);
    z.setLimit(40,130);
    z.setPos(130);
}

void lapa_max(MServo y) {
    delay(50);

    for (int i=y.getMin();i< y.getMax();i++) {
        y.setPos(i);
        delay(50);
    }

    delay(50);

    for (int i=y.getMax();i>y.getMin();i--) {
        y.setPos(i);
        delay(50);
    }
}




int r = 40;
float rad;
int angle = 0;

void loop() {

    int cx = x.getMin() + ((x.getMax() - x.getMin()) / 2);
    int cy = y.getMin() + ((y.getMax() - y.getMin()) / 2);

    if (angle++ > 360) angle = 0;

    int x1 = cx + r * cos( angle * M_PI / 180 );
    int y1 = cy + r * sin( angle * M_PI / 180 );

    x.setPos(x1);
    y.setPos(y1);
    z.setPos(y1 - 180);

    delay(35);

}



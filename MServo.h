//
// Created by jolkin on 08.09.2015.
//
struct Point {
    int x;
    int y;

    Point(int _x, int _y) {
        x = _x;
        y = _y;
    }

    Point() {
        x = 0;
        y = 0;
    }
};


class MServo
{

    Servo servo;

    Point limit;
    float step;
    int   pos;
public:

    MServo(int param[2])
    {
        if (param[0]) {
            limit.x = param[0];
        }
        if (param[1]) {
            limit.y = param[1];
        }

        pos = limit.x;

    }

    MServo()
    {

    }
    /**
     * получение позиции серво
     */
    int getPos()
    {
        return  pos;
    }

    /**
     * установить положение серво
     */
    int setPos(int position)
    {
        write(position);
        pos = position;
    }

    void setLimit(int param[2])
    {
        setLimit(param[1], param[0]);
    }

    /**
     * Установка крайних значнеий для серов
     */
    void setLimit(int min, int max)
    {
        limit.x = min;
        limit.y = max;
        step = (max - min) / 100;
    }
    /**
     * Задание порта привода
     */
    void attach(int port)
    {
        servo.attach(port);
    }

    /**
     * установка положения серво привода
     * position %
     */
    void write(int position)
    {
        servo.write(position * step);
    }


};
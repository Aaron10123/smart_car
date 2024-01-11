#include <Arduino.h>
#include <Servo.h>

//-----------------------全域變數區-----------------------//
// A1~A5為紅外線數值
int IR[5] = {A1, A2, A3, A4, A5};
// 速度控制:左邊馬達為PWM5，右邊馬達為PWM6
int mL = 5;
int mR = 6;
// 方向控制:左邊馬達為4，右邊馬達為7
int sL = 4;
int sR = 7;

Servo claw; // 宣告claw為伺服馬達

//-----------------------指令宣告區-----------------------//

void motor(int, int);    // 控制馬達的函式
void IR_test();          // 紅外線測試函式
void forward();          // 前進函式
void small_turn_left();  // 小轉彎左轉函式
void small_turn_right(); // 小轉彎右轉函式
void big_turn_left();    // 大轉彎左轉函式
void big_turn_right();   // 大轉彎右轉函式
void stop();             // 停止函式
void trail();            // 循跡函式

//-----------------------初始化-----------------------//
void setup()
{
    Serial.begin(9600);
    // 將IR設定為輸入
    for (int i = 0; i < 5; i++)
    {
        pinMode(IR[i], INPUT); // 數值為0~1023，白色為0，黑色為1023
    }
    // 將mL和mR設定為輸出
    pinMode(mL, OUTPUT);
    pinMode(mR, OUTPUT);
    // 將sL和sR設定為輸出
    pinMode(sL, OUTPUT); // HIGH為正轉，LOW為反轉
    pinMode(sR, OUTPUT); // HIGH為正轉，LOW為反轉

    claw.attach(9); // 將claw設定為3腳位
}

//-----------------------主程式-----------------------//
void loop()
{
    claw.write(50); // 伺服馬達轉到0度
    delay(1000);
    claw.write(95); // 伺服馬達轉到90度
    delay(1000);
    // claw.write(180); // 伺服馬達轉到180度
    // delay(1000);
    // claw.write(90); // 伺服馬達轉到90度
    // delay(3000);
}

//-----------------------函式區-----------------------//

/*
循跡程式
*/
void trail()
{
    if (analogRead(IR[2]) > 450)
    {
        if (analogRead(IR[1]) > 450)
        {
            small_turn_left(); // 小轉彎左轉函式
        }
        else if (analogRead(IR[3]) > 450)
        {
            small_turn_right(); // 小轉彎右轉函式
        }
        else
        {
            forward(); // 前進函式
        }
    }
    else
    {
        if (analogRead(IR[1]) > 450)
        {
            while (!(analogRead(IR[2]) > 450))
            {
                big_turn_left(); // 大轉彎左轉函式
            }
        }
        else if (analogRead(IR[3]) > 450)
        {
            while (!(analogRead(IR[2]) > 450))
            {
                big_turn_right(); // 大轉彎右轉函式
            }
        }
    }
}

/*
控制馬達的函式
speedL=左邊馬達的速度(-255 to 255)
speedR=右邊馬達的速度(-255 to 255)
*/
void motor(int speedL, int speedR)
{
    // digitalWrite(sL, speedL < 0 ? LOW : HIGH);
    if (speedL < 0)
    {
        digitalWrite(sL, LOW);
    }
    else
    {
        digitalWrite(sL, HIGH);
    }
    // digitalWrite(sR, speedR < 0 ? LOW : HIGH);
    if (speedR < 0)
    {
        digitalWrite(sR, LOW);
    }
    else
    {
        digitalWrite(sR, HIGH);
    }
    analogWrite(mL, abs(speedL));
    analogWrite(mR, abs(speedR));
}

void small_turn_left() // 小轉彎左轉函式
{
    motor(0, 100);
}

void small_turn_right() // 小轉彎右轉函式
{
    motor(100, 0);
}

void big_turn_left() // 大轉彎左轉函式
{
    motor(-100, 100);
}

void big_turn_right() // 大轉彎右轉函式
{
    motor(100, -100);
}

void stop() // 停止函式
{
    motor(0, 0);
}

void forward() // 前進函式
{
    motor(100, 100);
}

/*
紅外線測試函式
*/
void IR_test()
{
    // 顯示IR的數值
    for (int i = 0; i < 5; i++)
    {
        Serial.print(analogRead(IR[i]));
        Serial.print(" ");
    }
    Serial.println();
}

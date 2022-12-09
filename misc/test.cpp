#ifndef AUTOMOVE_H
#define AUTOMOVE_H
#include "move.h"
#include "utils.h"
#include "vex.h"

void autostop(int i, int t) {  //停止
  Brain.Screen.printAt(1, 40, "autostopping");
  stop_motor(LeftMotor1, i);
  stop_motor(LeftMotor2, i);
  stop_motor(RightMotor1, i);
  stop_motor(RightMotor2, i);
  vex::task::sleep(t);
}
void autostart(double left, double right,
               double speed) {  // left and right must smaller than 200
  //自动开始
  double minV = 1000, maxV = speed, left_error, right_error, olv, orv,
         startV = 1000, K = 40;
  double leftvelocity, rightvelocity, errorvelocity = 0;
  double k, k1 = 0.02, instant_error;
  static double left_rotation, right_rotation;
  double l = 0, r = 0;
  // read the initial value,set the target
  // reset the timer
  double left_target, right_target;
  left_target = LeftMotor1.rotation(vex::rotationUnits::deg) + left;
  right_target = RightMotor1.rotation(vex::rotationUnits::deg) + right;
  double t = Brain.timer(vex::timeUnits::msec);
  // speed up
  while (1) {
    // PID
    if (Brain.timer(vex::timeUnits::msec) - t > 150) break;
    left_error = left_target - LeftMotor1.rotation(vex::rotationUnits::deg);
    right_error = right_target - RightMotor1.rotation(vex::rotationUnits::deg);
    leftvelocity = (fabs(left - left_error) * K + startV) * left / fabs(left);
    rightvelocity =
        (fabs(right - right_error) * K + startV) * right / fabs(right);
    instant_error = fabs(left_error) - fabs(right_error);
    errorvelocity = 1 - fabs(instant_error) * 0.02;
    if (errorvelocity < 0.7) errorvelocity = 0.7;
    if (instant_error > 0)
      rightvelocity *= errorvelocity;
    else
      leftvelocity *= errorvelocity;

    leftvelocity = constrain(leftvelocity, maxV, maxV);
    rightvelocity = constrain(rightvelocity, maxV, maxV);
    mmove(leftvelocity, rightvelocity);
    if ((left >= 0 && left_error <= 0) || (left <= 0 && left_error >= 0)) l = 1;
    if ((right >= 0 && right_error <= 0) || (right <= 0 && right_error >= 0))
      r = 1;
    if (l && r) break;
  }
}

void autobrake(double left_target, double right_target, double timelimit,
               double speed) {
  //停止
  double left_Kp = 30, right_Kp = 30, Ki = 0.0002, Kd = 10,
         left_constantV = 1000, right_constantV = 500, maxV = speed;
  double left_integral = 0, left_error, left_last_error = 0, left_D;
  double right_integral = 0, right_error, right_last_error = 0, right_D;
  double leftvelocity, rightvelocity, instant_error, k, k1 = 0.1;
  double t = Brain.timer(vex::timeUnits::msec),
         time = Brain.timer(vex::timeUnits::msec), frequency = 0;
  left_error = left_target - LeftMotor1.rotation(vex::rotationUnits::deg);
  right_error = right_target - RightMotor1.rotation(vex::rotationUnits::deg);

  while (1) {
    // PID
    if (Brain.timer(timeUnits::msec) - frequency > 1) {
      frequency = Brain.timer(timeUnits::msec);
      left_error = left_target - LeftMotor1.rotation(vex::rotationUnits::deg);
      right_error =
          right_target - RightMotor1.rotation(vex::rotationUnits::deg);
    }
    if (Brain.timer(vex::timeUnits::msec) - time > timelimit) break;  // 2000
    Brain.Screen.drawRectangle(1, 1, 400, 400, vex::color::yellow);
    left_last_error = left_error;
    right_last_error = right_error;
    if (Brain.timer(timeUnits::msec) - frequency > 1) {
      frequency = Brain.timer(timeUnits::msec);
      left_error = left_target - LeftMotor1.rotation(vex::rotationUnits::deg);
      right_error =
          right_target - RightMotor1.rotation(vex::rotationUnits::deg);
    }
    left_D = left_error - left_last_error;
    right_D = right_error - right_last_error;
    left_integral = left_integral + left_error;
    right_integral = right_integral + right_error;
    leftvelocity = left_Kp * left_error + Ki * left_integral + Kd * left_D;
    rightvelocity = right_Kp * right_error + Ki * right_integral + Kd * right_D;

    leftvelocity = constrain(left_error, 0., 0., leftvelocity + left_constantV,
                             leftvelocity - left_constantV);
    rightvelocity =
        constrain(right_error, 0., 0., rightvelocity + right_constantV,
                  rightvelocity - right_constantV);
    leftvelocity = constrain(leftvelocity, maxV, maxV);
    rightvelocity = constrain(rightvelocity, maxV, maxV);
    mmove(leftvelocity, rightvelocity);
    /*if(abs(left_error)<3&&abs(right_error)<3)Brain.Screen.drawRectangle(1,1,400,400,vex::color::red);//LED
    signal else Brain.Screen.drawRectangle(1,1,400,400,vex::color::green);*/
    // if(!left_constantV&&!right_constantV)break;
    if (fabs(left_error) > 1 || fabs(right_error) > 1)
      t = Brain.timer(vex::timeUnits::msec);
    if (Brain.timer(vex::timeUnits::msec) - t >= 250) break;
  }
  if (fabs(left_error) < 2 && fabs(right_error) < 2)
    Brain.Screen.drawRectangle(1, 1, 400, 400, vex::color::red);
}
void autorun(double left_target, double right_target, double time,
             double speed) {
  double left_error, right_error, leftvelocity, rightvelocity, instant_error,
      errorvelocity;
  double t = Brain.timer(vex::timeUnits::msec), distance = speed / 35;
  while (1) {
    if (Brain.timer(vex::timeUnits::msec) - t > time) break;
    left_error = left_target - LeftMotor1.rotation(vex::rotationUnits::deg);
    right_error = right_target - RightMotor1.rotation(vex::rotationUnits::deg);
    if (fabs(left_error) <= distance || fabs(right_error) <= distance) break;
    // instant_error=abs(LeftMotor1.velocity(vex::velocityUnits::pct))-abs(RightMotor1.velocity(vex::velocityUnits::pct));
    instant_error = fabs(left_error) - fabs(right_error);
    errorvelocity = 1 - fabs(instant_error) * 0.02;
    if (errorvelocity < 0.7) errorvelocity = 0.7;
    if (instant_error > 0)
      rightvelocity *= errorvelocity;
    else
      leftvelocity *= errorvelocity;

    leftvelocity = constrain(left_error, distance, speed);
    rightvelocity = constrain(right_error, distance, speed);
    mmove(leftvelocity, rightvelocity);
  }
}
void automove(double left, double right, double time, double speed) {
  double start_left, start_right, start_distance = speed / 35, left_target,
                                  right_target;
  start_left = left / 3;
  start_right = right / 3;

  start_left = constrain(start_left, start_distance, start_distance);
  start_right = constrain(start_right, start_distance, start_distance);

  left_target = (LeftMotor1.rotation(vex::rotationUnits::deg) +
                 LeftMotor2.rotation(vex::rotationUnits::deg)) /
                    2 +
                left;
  right_target = (RightMotor1.rotation(vex::rotationUnits::deg) +
                  RightMotor2.rotation(vex::rotationUnits::deg)) /
                     2 +
                 right;
  autostart(start_left * 2, start_right * 2, speed);
  autorun(left_target, right_target, time, speed);
  autobrake(left_target, right_target, 50, speed);
  autostop(1, 25);
}

#endif
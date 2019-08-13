#include <ArduinoHardware.h>
#include <ros.h>
#include <ros_falcon/falconPos.h>

ros::NodeHandle nh;


float move_x;
int atras = 11;

void messageCb(const ros_falcon::falconPos* vel){
  
  move_x = vel->Z;
  if(move_x <  0){

    digitalWrite(atras,HIGH);
    
  
    }
    else
    digitalWrite(atras,LOW);

  }

ros::Subscriber <ros_falcon::falconPos> sub("/falconPos", messageCb);
void setup()
{
  Serial1.begin(9600);
  nh.initNode();
  nh.subscribe(sub);
  pinMode(atras, OUTPUT);

} 

void loop()
{
  nh.spinOnce();
  delay(10);
  }

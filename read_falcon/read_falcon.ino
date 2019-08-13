#include <ArduinoHardware.h>
#include <ros.h>
#include <geometry_msgs/Twist.h>
#include <ros_falcon/falconPos.h>

ros::NodeHandle nh;


float move_x;
float move_z;
const int adelante =8;
const int atras = 9;
const int derecha =10;
const int izquierda =11;

void messageCb(const geometry_msgs::Twist& vel){
  move_x = vel.linear.x;
  //move_z = vel.Z;

  if(move_x>=-50 && move_x<=-10){

    digitalWrite(8,HIGH);
    
    
    }
   if(move_x>-10){
      digitalWrite(8,LOW);
    
      }
      
    
//
//    if(move_x>=-20 || move_x<=50){
//
//    digitalWrite(atras,HIGH);
//    
//    }
//    else
//    digitalWrite(atras,LOW);
//
//     if(move_z>=1 || move_z<=5){
//
//    digitalWrite(izquierda,HIGH);
//    
//    }
//    else
//    digitalWrite(izquierda,LOW);
//
//     if(move_z>=-1 || move_z<=-5){
//
//    digitalWrite(derecha,HIGH);
//    
//    }
//
//    else
//    digitalWrite(derecha,LOW);

    
  }

ros::Subscriber <geometry_msgs::Twist> sub("/date_falcon", messageCb);

//geometry_msgs::Twist mensaje;
//ros::Publisher pub("mov", &mensaje);

void setup()
{
  
  nh.initNode();
  nh.subscribe(sub);
//  nh.advertise(pub);

  pinMode(adelante , OUTPUT);
  pinMode(atras, OUTPUT);
  pinMode(derecha , OUTPUT);
  pinMode(izquierda, OUTPUT);
} 

void loop()
{
  
//  mensaje.linear.x = move_x; 
//  mensaje.angular.z = move_z;
//  pub.publish(&mensaje);
  nh.spinOnce();
  
}

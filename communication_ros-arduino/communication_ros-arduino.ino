/*
 * rosserial PubSub Example
 * Prints "hello world!" and toggles led
 */

#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Empty.h>
#include <geometry_msgs/Twist.h>

ros::NodeHandle  nh;


void messageCb( const geometry_msgs::Twist& toggle_msg){
  //Serial.print("valor: ");   
  //Serial.println(toggle_msg);
}

ros::Subscriber<geometry_msgs::Twist> sub("recibir", messageCb );
//std_msgs::String messageCb;


std_msgs::String str_msg;
ros::Publisher chatter("chatter", &str_msg);

char hello[13] = "hello world!";

void setup()
{
  pinMode(13, OUTPUT);
  nh.initNode();
  nh.advertise(chatter);
  nh.subscribe(sub);
  Serial.begin(9600);
}

void loop()
{
  str_msg.data = hello;
  chatter.publish( &str_msg );
  nh.spinOnce();
  delay(500);
  //Serial.println(toggle_msg);
  //Serial.println(messageCb);
}

#include <ros.h>
#include <std_msgs/Float64.h>

ros::NodeHandle nh;
std_msgs::Float64 Distance,Distance_left,Distance_right;

ros::Publisher chatter("chatter_left",&Distance);




// defines pins numbers
const int trigPin = 9;
const int echoPin = 10;



// defines variables
long duration;


float distance;

void setup() {
nh.initNode();

nh.advertise(chatter);


pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input

Serial.begin(57600); // Starts the serial communication
}



//ros::Rate rate(0.5);
void loop() {
// Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);


// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10); //10
digitalWrite(trigPin, LOW);



// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);

// Calculating the distance
distance= duration*0.034/2;
if(distance>30){
  
  distance=30;
  }


  
//publishing data

Distance.data=distance;
chatter.publish(&Distance);
nh.spinOnce();


}

//Manuel Esteban Contreras Betancourt
//manuel.contreras@unipamplona.edu.co
//Antes de ejecutar este nodo primero ejecutar el nodo falcon_node y falcon_teleop_twist_ros (rosrun ros_falcon falcon_node, falcon_teleop_twist_ros)


//Incluyendo librerias
#include <iostream>
#include <string>
#include <cmath>
#include <ros/ros.h>
#include <ros_falcon/falconPos.h> 
#include <ros_falcon/falconForces.h> 
#include "geometry_msgs/Twist.h"
#include "std_msgs/String.h"
#include "std_msgs/Float32.h"
#include "sensor_msgs/Range.h"
#include "falcon/core/FalconDevice.h"
#include "geometry_msgs/Point.h"
#include <std_msgs/Float64.h>


// Se declara variables globales para la publicación de la posicion del falcon
float   force_x_desired= 0.0;
float   force_z_desired= 0.0;





void forceFront (std_msgs::Float64 for1){


  force_x_desired =(-for1.data+30)/10;


  printf("%f \n",force_x_desired );

 }

void forceRight (std_msgs::Float64 for1){

  force_z_desired =-((-for1.data+30)/10);


}


void forceLeft (std_msgs::Float64 for1){

  force_z_desired =(-for1.data+30)/10;

}

//printf("%f \n",force_x_desired );

int main(int argc, char** argv)  
{
 
  ros_falcon::falconForces msg_1;
  //msg_1.X=5;
  
  sensor_msgs::Range msg;
  ros::init(argc, argv, "sensor_arduino_node");

  ros::start();//se hace la comunicacion con el nodo maestro (roscore)
   ROS_INFO("File %s compiled on %s %s.",__FILE__, __DATE__, __TIME__);

   //creamos un nodo
   ros::NodeHandle force_node;

   //Creamos un topico para publicar la posicion del falcon en /cmd_vel
    ros::Publisher  pub_front = force_node.advertise<ros_falcon::falconForces>("/falconForce", 10);
    
    //ros::Rate loop_rate(1000);

    //Se crea un topico que suscriba la posicion del falcon en el nodo (falcon_node)

    ros::Subscriber suscriber = force_node.subscribe("chatter", 10, forceFront);
    ros::Subscriber suscriber_rigth = force_node.subscribe("chatter_right", 10, forceRight);
    ros::Subscriber suscriber_left = force_node.subscribe("chatter_left", 10, forceLeft);

    while(force_node.ok())
    {
      
    msg_1.Z = force_x_desired;
    msg_1.X = force_z_desired;
    pub_front.publish(msg_1);
    ros::spinOnce();
    

    }
 
  //Nota:Las posiciones del falcon son: X-> derecha y izquierda, Y-> arriba y abajo
    //Z-> adentro afuera
    
}

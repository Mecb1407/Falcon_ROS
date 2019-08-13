//Manuel Esteban Contreras Betancourt
//manuel.contreras@unipamplona.edu.co
//Antes de ejecutar este nodo primero ejecutar el nodo falcon_node y falcon_teleop_twist_ros (rosrun ros_falcon falcon_node, falcon_teleop_twist_ros)


//Incluyendo librerias
#include <ros/ros.h>
#include <ros_falcon/falconPos.h> 
#include <ros_falcon/falconForces.h> 
#include "geometry_msgs/Twist.h"
#include "sensor_msgs/Range.h"
#include "falcon/core/FalconDevice.h"



// Se declara variables globales para la publicación de la posicion del falcon
float   gamma_dot_desired = 0.0;
float   phi_dot_desired   = 0.0;

void ReadFalconCallback(const geometry_msgs::Twist::ConstPtr& pos) 
{
phi_dot_desired=pos->linear.x;
gamma_dot_desired=pos->angular.z;

// if (phi_dot_desired >=-30 && phi_dot_desired <=-20 ){
//   phi_dot_desired=0;
// }
// else
// phi_dot_desired=pos->linear.x;

// if (gamma_dot_desired >=-1 && gamma_dot_desired <=1){

//   gamma_dot_desired=0;
// }
// else 
//   gamma_dot_desired=pos->angular.z;
//  
}

  



int main(int argc, char** argv)  
{
	geometry_msgs::Twist msg;
  ros::init(argc, argv, "send_data_arduino_node");

  ros::start();//se hace la comunicacion con el nodo maestro (roscore)
   ROS_INFO("File %s compiled on %s %s.",__FILE__, __DATE__, __TIME__);

   //creamos un nodo
   ros::NodeHandle arduino_node;

   //Creamos un topico para publicar la posicion del falcon en /cmd_vel
    ros::Publisher  pub = arduino_node.advertise<geometry_msgs::Twist>("/read_falcon", 1000);

    //Se crea un topico que suscriba la posicion del falcon en el nodo (falcon_node)

    ros::Subscriber suscriber = arduino_node.subscribe("/date_falcon", 1000, ReadFalconCallback);

    while(arduino_node.ok())
    {

    	
		msg.linear.x = phi_dot_desired;
    
		msg.angular.z = gamma_dot_desired;
      
		pub.publish(msg);
      	ros::spinOnce();

    }
 
	
    
}

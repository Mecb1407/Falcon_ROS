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
float   force_x_desired   = 0.0;
float   force_z_desired   = 0.0;
float   force_z_desired1  = 0.0;



void forceFront (sensor_msgs::Range for1){

  force_x_desired = -for1.range+2;


  //printf("%f \n",force_x_desired );

}

void forceLeft (sensor_msgs::Range for2){

  force_z_desired = -for2.range+2;

  printf("%f \n",force_z_desired);

}

void forceRight (sensor_msgs::Range for3){

  force_z_desired1 = -(-for3.range+2);

  //printf("%f \n",force_z_desired1 );

}




int main(int argc, char** argv)  
{
 
  ros_falcon::falconForces msg_1,msg_2,msg_3;
  //msg_1.X=5;
  
	sensor_msgs::Range msg;
  ros::init(argc, argv, "falcon_teleop_force_node");

  ros::start();//se hace la comunicacion con el nodo maestro (roscore)
   ROS_INFO("File %s compiled on %s %s.",__FILE__, __DATE__, __TIME__);

   //creamos un nodo
   ros::NodeHandle force_node;

   //Creamos un topico para publicar la posicion del falcon en /cmd_vel
    ros::Publisher  pub = force_node.advertise<ros_falcon::falconForces>("/falconForce", 3);
    ros::Publisher pub1 = force_node.advertise<ros_falcon::falconForces>("/falconForce", 3);
    ros::Publisher pub2 = force_node.advertise<ros_falcon::falconForces>("/falconForce", 3);
    

    //Se crea un topico que suscriba la posicion del falcon en el nodo (falcon_node)

    ros::Subscriber suscriber = force_node.subscribe("/distance_sensor_front", 0, forceFront);
    ros::Subscriber suscriber_left = force_node.subscribe("/distance_sensor_left", 0, forceLeft);
    ros::Subscriber suscriber_right = force_node.subscribe("/distance_sensor_right", 0, forceRight);

    while(force_node.ok())
    {
      
    msg_1.Z = force_x_desired*2;
    msg_2.X = force_z_desired*2;
    msg_3.X = force_z_desired1*2;
    pub.publish(msg_1);
    pub1.publish(msg_2);
    pub2.publish(msg_3);
    ros::spinOnce();

    }
 
	//Nota:Las posiciones del falcon son: X-> derecha y izquierda, Y-> arriba y abajo
    //Z-> adentro afuera
    
}

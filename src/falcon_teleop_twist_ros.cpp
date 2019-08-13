//Manuel Esteban Contreras Betancourt
//manuel.contreras@unipamplona.edu.co
//Antes de ejecutar este nodo primero ejecutar el nodo falcon_node (rosrun ros_falcon falcon_node)


//Incluyendo librerias
#include <iostream>
#include <string>
#include <cmath>
#include <ros/ros.h>
#include <ros_falcon/falconPos.h> 
#include <ros_falcon/falconForces.h> 
#include "geometry_msgs/Twist.h"
#include "std_msgs/String.h"
#include "falcon/core/FalconDevice.h"



// Se declara variables globales para la publicación de la posicion del falcon
float   gamma_dot_desired = 0.0;
float   phi_dot_desired   = 0.0;

void PosFalconCallback(const ros_falcon::falconPosConstPtr& pos) //Esta función es para recuperar la posicion 
//del falcon. Esta posicion viene del nodo (falcon_node)
{


    phi_dot_desired   = pos->X; // El phi_dot_desired es la posicion en z del falcon (rotacion)
    gamma_dot_desired = -pos->Z; // El gamma_dot_desired es la posicion en x del falcon (velocidad lineal)



    if (gamma_dot_desired >=-1 && gamma_dot_desired <=1){

        gamma_dot_desired=0;
    }
    else
        gamma_dot_desired = -pos->Z;



    if (phi_dot_desired >=-30 && phi_dot_desired <=-10 ){
        phi_dot_desired=0;
    }
    else
        phi_dot_desired   = pos->X;





    // time_last_good_ros_command_sec = ros::Time::now().toSec();
    //ROS_INFO_STREAM("enter to cmd function to process the command");
    //ROS_INFO_STREAM("Subscriber Falcon Position:"<<" X="<< pos->X<<" Y="<< pos->Y);
    return;
}

int main(int argc, char** argv)  
{
    geometry_msgs::Twist msg,msg_1;
    ros::init(argc, argv, "falcon_teleop_twist_ros_node");

    ros::start();//se hace la comunicacion con el nodo maestro (roscore)

    ROS_INFO("File %s compiled on %s %s.",__FILE__, __DATE__, __TIME__);

    //creamos un nodo
    ros::NodeHandle falcon_node;

    //Creamos un topico para publicar la posicion del falcon en /cmd_vel
    ros::Publisher  pub = falcon_node.advertise<geometry_msgs::Twist>("/cmd_vel", 10);
    //ros::Publisher  pub1 = falcon_node.advertise<geometry_msgs::Twist>("/date_falcon", 10);

    //Se crea un topico que suscriba la posicion del falcon en el nodo (falcon_node)

    ros::Subscriber suscriber = falcon_node.subscribe("/falconPos", 10, PosFalconCallback);

    while(falcon_node.ok())
    {


        msg.linear.x = phi_dot_desired;

        msg.angular.z = 0.1*gamma_dot_desired;

        //pub1.publish(msg_1);
        pub.publish(msg);

        ros::spinOnce();

    }


    
}

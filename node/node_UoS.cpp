#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>
#include <iostream>
#include <string>
#include <cmath>


// Include UoS algorithm
#include "../modules/UoS/uosAlgorithm.cpp"
#include "../modules/UoS/MovementClassifier.cpp"

void Callback_fromRecognition(const std_msgs::String::ConstPtr& jsonEncodedResult_Input);
void Callback_fromDialogGen(const std_msgs::String::ConstPtr& jsonEncodedResult_Input);

ros::Publisher uos_pub;
ros::Subscriber sub_fromRecognition, sub_fromDialogGen;


int count = 0 ;
float loc[2]={0.0,};
bool mv_flag = true;

int main(int argc, char **argv){

	// 1. ROS Node setting
	ros::init(argc, argv, "node_UoS");
	ros::NodeHandle n;

	// 2. ROS Subscriber setting
	sub_fromRecognition = n.subscribe("json_RecogRes", 100, Callback_fromRecognition);
	sub_fromDialogGen = n.subscribe("json_DialogRes", 100, Callback_fromDialogGen);

	// 3. ROS Publisher setting
 	uos_pub = n.advertise<std_msgs::String>("json_AllTask", 100);

	ros::spin();

	return 0;
}


void Callback_fromRecognition(const std_msgs::String::ConstPtr& jsonEncodedResult_Input)
{



	std_msgs::String jsonEncodedResult_Output;
	
	// 1. Perform UoS algorithm
	uosAlgorithm(loc, jsonEncodedResult_Output, jsonEncodedResult_Input);

	// 2. mv_flag :1 --> moving
	MovementClassifier(mv_flag,loc);

	// 3. Publish the json format string
	if (!jsonEncodedResult_Output.data.empty())
	{
		if ((count == 0)&&(!mv_flag)) // Publish the topic when the person stops
		{
			std::cout << jsonEncodedResult_Output << std::endl << std::endl;
			uos_pub.publish(jsonEncodedResult_Output);
			count ++;
		}
	}

}


void Callback_fromDialogGen(const std_msgs::String::ConstPtr& jsonEncodedResult_Input)
{

//	printf("\n The message from /json_DialogRes \n");
//	ROS_INFO("I heard: [%s]", jsonEncodedResult_Input->data.c_str());

}


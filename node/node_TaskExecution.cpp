#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>
#include <iostream>
#include <string>

// Include Array msg type and TaskExtraction.cpp
#include "std_msgs/MultiArrayLayout.h"
#include "../modules/TaskExtraction/TaskExtraction.cpp"

void AllTaskCallback(const std_msgs::String::ConstPtr& jsonEncodedResult_Input);
void TaskCompletionCallback(const std_msgs::String::ConstPtr& jsonEncodedResult_Input);

ros::Publisher TaskExecution_pub;
ros::Subscriber sub_fromTaskGen, sub_fromAction;


// Extract individual task from AllTask, and store in Array
std_msgs::MultiArrayLayout jsonEncodedResult_OutputArray;
std_msgs::String currentTask;

int n = 1;
int n_Tasks;

int main(int argc, char **argv){

	// 1. ROS Node setting
	ros::init(argc, argv, "node_TaskExecution");
	ros::NodeHandle n;

	// 2. ROS Subscriber setting
	sub_fromTaskGen = n.subscribe("json_AllTask", 100, AllTaskCallback);
	sub_fromAction = n.subscribe("json_TaskComp", 100, TaskCompletionCallback);

	// 3. Ros Publisher setting
 	TaskExecution_pub = n.advertise<std_msgs::String>("json_TaskExe", 100);

	ros::spin();

	return 0;
}


void AllTaskCallback(const std_msgs::String::ConstPtr& jsonEncodedResult_Input)
{

//	ROS_INFO("I heard: [%s]", jsonEncodedResult_Input->data.c_str());

	// 1. Perform TaskExtraction
	TaskExtraction(jsonEncodedResult_OutputArray, jsonEncodedResult_Input);
	n_Tasks = 2;

	// 2. Publish 1-st task
	currentTask.data = jsonEncodedResult_OutputArray.dim[0].label;
	TaskExecution_pub.publish(currentTask);

	std::cout << currentTask << std::endl << std::endl;
}


void TaskCompletionCallback(const std_msgs::String::ConstPtr& jsonEncodedResult_Input)
{

//	ROS_INFO("I heard: [%s]", jsonEncodedResult_Input->data.c_str());

 
	// 1. Perform next task 
	n++;

	if(n <= n_Tasks) {
		currentTask.data = jsonEncodedResult_OutputArray.dim[n-1].label;
		TaskExecution_pub.publish(currentTask);

		std::cout << currentTask << std::endl << std::endl;
	}
}

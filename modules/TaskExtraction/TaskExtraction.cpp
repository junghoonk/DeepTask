#include <stdio.h>
#include <stdlib.h>

#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>
#include <iostream>
#include "../json/json.h"
#include "../jsoncpp.cpp"

#include "std_msgs/MultiArrayDimension.h"
#include "std_msgs/MultiArrayLayout.h"


std::string json_str;

//void TaskExtraction(std_msgs::String& jsonEncodedResult_OutputTask1, std_msgs::String& jsonEncodedResult_OutputTask2, const std_msgs::String::ConstPtr& jsonEncodedResult_Input){

void TaskExtraction(std_msgs::MultiArrayLayout& jsonEncodedResult_OutputArray, const std_msgs::String::ConstPtr& jsonEncodedResult_Input){
	/////////////////////////////////////////////////////////
	// Input : All tasks in single string (as json format)
	// Output : Individual task in array (as json format)
	////////////////////////////////////////////////////////




	////////////////////////////////////////////////////////
	// Input : json Parser
	////////////////////////////////////////////////////////

	// convert to json
	json_str = jsonEncodedResult_Input->data.c_str() ; // std_msgs::String ----> std::string

	// Parser
	Json::Reader reader;
	Json::Value input_root;

	// Error check
	bool parsingRet = reader.parse(json_str, input_root);
	if (!parsingRet)
	{
		std::cout << "Failed to parse Json : " << reader.getFormattedErrorMessages();
		return;
	}



	Json::Value input_Info;
	Json::Value input_Task;
	input_Info = input_root["1.INFO"];
	input_Task = input_root["2.Task"];

//	std::cout << input_Info << std::endl;
//	std::cout << input_Task << std::endl;


	// Task Extraction
	// Task 1.
	Json::Value output_root1;
	Json::Value output_Info;
	Json::Value task1;

	output_Info["MODULE"] = "TaskExecution";
	output_Info["start"] = "300";
	output_Info["end"] = 900;	
	output_root1["1.INFO"] = output_Info;

	task1 = input_Task["Task.1"];
	output_root1["2.Task"] = task1;
	
	// Task 2.
	Json::Value output_root2;
	Json::Value task2;

	output_Info["MODULE"] = "TaskExecution";
	output_Info["start"] = "900";
	output_Info["end"] = 1800;	
	output_root2["1.INFO"] = output_Info;

	task2 = input_Task["Task.2"];
	output_root2["2.Task"] = task2;


	// Write
	Json::StyledWriter writer;

	json_str = writer.write(output_root1);
	std_msgs::String jsonEncodedTask1;
	jsonEncodedTask1.data = json_str.c_str();
	
	json_str = writer.write(output_root2);
	std_msgs::String jsonEncodedTask2;
	jsonEncodedTask2.data = json_str.c_str();


	// Make Tasks to Array
	std_msgs::MultiArrayDimension tmp;
	tmp.label = jsonEncodedTask1.data;
	jsonEncodedResult_OutputArray.dim.push_back(tmp);

	tmp.label = jsonEncodedTask2.data;
	jsonEncodedResult_OutputArray.dim.push_back(tmp);


//	std::cout <<jsonEncodedResult_OutputArray << std::endl << std::endl ;

}

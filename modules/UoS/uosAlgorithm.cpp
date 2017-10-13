#include <stdio.h>
#include <stdlib.h>

#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>
#include <iostream>
#include "../json/json.h"
#include "../jsoncpp.cpp"

std::string json_str;

void uosAlgorithm(float (&loc)[2], std_msgs::String& jsonEncodedResult_Output, const std_msgs::String::ConstPtr& jsonEncodedResult_Input){
//void uosAlgorithm(float& a, std_msgs::String& jsonEncodedResult_Output, const std_msgs::String::ConstPtr& jsonEncodedResult_Input){

	/////////////////////////////////////////////////////////
	// Input : Id, Name, Age, location (as json format)
	// Output : Task - behavior, message (as json format)
	////////////////////////////////////////////////////////

//	printf("In function, %d \n", a);

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


	////////////////////////////////////////////////////////
	// Example
	////////////////////////////////////////////////////////


	Json::Value input_Info;
	Json::Value input_HumanInfo;
	Json::Value input_SocialContext;
	input_Info = input_root["1.INFO"];
	input_HumanInfo = input_root["2.Human_Info"];
	input_SocialContext = input_root["3.Social_CONTEXT"];


//	std::cout << input_Info << std::endl;
//	std::cout << input_HumanInfo["X position"] << std::endl;

//	loc[0] = input_HumanInfo["X position"].asFloat();
//	std::cout << loc[0] << std::endl;
	

	std::string x_s = input_HumanInfo["X position"].asString();
	std::string y_s = input_HumanInfo["Y position"].asString();
	std::string z_s = input_HumanInfo["Z position"].asString();
	loc[0] = (float)atof(x_s.c_str());
	loc[1] = (float)atof(y_s.c_str());
	loc[2] = (float)atof(z_s.c_str());


//	a = input_HumanInfo["X position"].asFloat();

//	std::cout << a.isArray() <<std::endl;
//	std::cout << a << std::endl;



	// Task Generation
	
	Json::Value output_root;

	// 1. Info
	Json::Value info;
	info["MODULE"] = "UoS";
	info["start"] = 300;
	info["end"] = 900;
	output_root["1.INFO"] = info;

	// 2. Task
	Json::Value task;

	// 2.1. Task 1 : Moving
	Json::Value task1;
	Json::Value output_HumanInfo;
	task1["1.TaskNumber"] = "1";
	task1["2.Behavior"] = "moving";
	task1["3.Robot_Dialog"] = "";
	output_HumanInfo = input_HumanInfo;
	task1["4.Human_Info"] = output_HumanInfo;
	task["Task.1"] = task1;

	// 2.2. Task 2 : Greeting
	Json::Value task2;
	task2["1.TaskNumber"] = "2";
	task2["2.Behavior"] = "greeting";
	task2["3.Robot_Dialog"] = "Hello, How are you doing?";
	task2["4.Human_Info"] = output_HumanInfo;
	task["Task.2"] = task2;
	output_root["2.Task"] = task;


	//
	Json::StyledWriter writer;
	json_str = writer.write(output_root);
//	std::cout << json_str << std::endl << std::endl;

	// convert json to String form
	jsonEncodedResult_Output.data = json_str.c_str();
	


}

#pragma once

#include "cocos2d.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

static int DATA_LINE_INDEX = 1;
/*
*	Function		:	mnu_to_str
*	Description		:	change the int num to string
*	Input			:	the change number
*	Return			:	the string whitch number change
*	Others			:	if num == 0 it expression null
*						so return ""
*/
static const std::string num_to_str(int num)
{
	cocos2d::log("number to string begin");
	std::stringstream ss;
	ss << num;
	std::string ret(ss.str());
	ss.str("");
	if (num == 0)return "";
	cocos2d::log("number to string end");
	return ret;
}

/*
 *	Function		:	initDataLine()
 *	Description		:	init the file line index 
 */
static void initDataLine()
{
	auto filePath = cocos2d::FileUtils::getInstance()->getWritablePath() + "save.dt";
	std::string strFile(
		cocos2d::FileUtils::getInstance()->getStringFromFile(filePath));
	cocos2d::log("file %s data: %s", filePath.c_str(), strFile.c_str());
	if (strFile == "")return;
	std::stringstream ss(strFile);
	ss >> DATA_LINE_INDEX;
}

/*
 *	Function		:	writeLineToFile()
 *	Description		:	save the file line index into the file  
 */
static void writeLineToFile()
{
	std::string str(num_to_str(DATA_LINE_INDEX));
	auto filePath = cocos2d::FileUtils::getInstance()->getWritablePath() + "save.dt";
	cocos2d::log("file %s", filePath.c_str());
	cocos2d::FileUtils::getInstance()->writeStringToFile(str, filePath);
}
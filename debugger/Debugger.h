
/****************************************************

	Debugger.h

	contains a single type : class DebugMessage
	std::string message is used to accommodate the report message.


	WARNING:***********************************

	This Object is for debugging, 
	use it carefully, because it will cause memory leak easily.

	*******************************************

	You can remove it when constructing a released version.

****************************************************/

#include <string>
#include <iostream>

#ifndef __DEBUG_MODE_ON_
#define __DEBUG_MODE_ON_
#endif

#ifndef _DEBUGGER_H_
#define _DEBUGGER_H_

namespace Debugger
{

	class DebugMessage
	{
	public:
		std::string message; 
		DebugMessage();
		DebugMessage(const char* str): message(str) {}
	};

}

#endif
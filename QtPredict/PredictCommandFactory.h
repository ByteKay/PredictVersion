/*
Time  : 2016/06/18
Author: Kay Yang (1025115216@qq.com)
*/

#ifndef _PREDICTCOMMANDFACTORY_H
#define _PREDICTCOMMANDFACTORY_H

class PredictCommand;
class PredictCommandFactory
{
public:
	static PredictCommand* CreateCommand(const short messageId);
private:
	PredictCommandFactory(){}
};

#endif
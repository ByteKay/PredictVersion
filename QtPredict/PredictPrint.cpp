#include "PredictPrint.h"
#include "PredictKeyHandleUI.h"
#pragma execution_character_set("utf-8")
namespace ClientPrint
{
#ifndef CONSOLE
	PredictKeyHandleUI* g_print = 0;

	void SetPrint(PredictKeyHandleUI* print)
	{
		g_print = print;
	}
#endif

	void PrintMessage(const DataStructures::HexString& gameName, const char* infor)
	{
#ifdef CONSOLE
		return;
#endif
#ifndef CONSOLE
		if (!g_print)
#endif
		{
			printf("%s-> %s \n", gameName.C_String(), infor);
		}
#ifndef CONSOLE
		else
		{
			g_print->PrintMessage(QStringLiteral("%1-> %2").arg(gameName.C_String()).arg(infor));
		}
#endif
		
	}
}
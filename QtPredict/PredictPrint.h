#ifndef PREDICTPRINT_H
#define PREDICTPRINT_H
#include "PredictKeyHandleUI.h"
#include "HexString.h"
namespace ClientPrint
{
#ifndef CONSOLE
	void SetPrint(PredictKeyHandleUI* print);
#endif
	// PredictKeyHandleUI* GetPrint();
	void PrintMessage(const DataStructures::HexString&, const char* infor);
}

#endif
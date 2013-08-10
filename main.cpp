#include "Precompiled.h"

#define MAX_CMD_LENGTH 80
CMDLINE user_action;
Msg outMSG;

int main(int argc, char **argv){

	char str[MAX_CMD_LENGTH];
	bool quitFound=false;

	outMSG.Welcome_Prompt(); //display welcome message to user
	
	do{
		outMSG.CMD_Prompt();
		std::cin.get(str, MAX_CMD_LENGTH);
		quitFound=user_action.Input_User_CMD(str);
		std::cin.clear();
		fflush(stdin);
	}while(!quitFound);

	return 0;
}
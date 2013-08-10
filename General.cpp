#include "Precompiled.h"

std::string* General::tokenize_Str(char *cmd){
	std::string *str=new std::string[MAX_COL];
	char *nextToken, *token;
	int i=0;
	token=strtok_s(cmd, " \t", &nextToken);
	while(token!=NULL){
		str[i++]=token;
		token=strtok_s(NULL, " \t", &nextToken);
	}
	return str;
}

void General::SetUppercase(char *cmd){
	int i=0;
	while(cmd[i]){
		cmd[i]=toupper(cmd[i]);
		i++;
	}
}

void General::DecToHex(int num){
  char buffer[33];
  itoa(num,buffer,16);
  std::cout<<buffer;
}

std::string General::DecToHex1(int num){
	char *buffer= new char(33);
	itoa(num, buffer, 16);
	return buffer;

}
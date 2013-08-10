#ifndef GENERAL_H
#define GENERAL_H
struct General{
	std::string* tokenize_Str(char *cmd);
	void SetUppercase(char *cmd);
	void DecToHex(int dec);
	std::string DecToHex1(int num);
};


#endif
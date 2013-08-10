#ifndef INPUTPROC_H
#define INPUTPROC_H

struct CMDLINE{
public:
	CMDLINE();
	bool Input_User_CMD(char *str);
private:
	Assembler assembler;
	Msg outgoing;
	std::string *cmd;
	bool exit;
	void ProcessOperation();
	void ViewDirectory();
};

#endif
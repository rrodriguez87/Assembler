#include "Precompiled.h"

CMDLINE::CMDLINE(){
	cmd=new std::string[MAX_COL];
	exit=false;
}

bool CMDLINE::Input_User_CMD(char *str){
	General general;

	/*set incoming string to all caps, tokenize, and store in cmd(char*)
	  and then process the command */
	general.SetUppercase(str); 
	cmd=general.tokenize_Str(str);
	ProcessOperation(); 

	if(!exit)
		return false;
	else
		return true;
}

void CMDLINE::ProcessOperation(){
	/*format of cmd: [OPERATION][ARG1][ARG2] */
	/*if not in this format, error is generated */
	if(cmd[0] == "EXIT"){
		outgoing.Quit_Prompt();
		exit=true;
	}
	else if(cmd[0] == "HELP"){
		outgoing.Help_Prompt();
	}
	else if(cmd[0] == "DIRECTORY"){
		ViewDirectory();
	}
	else if(cmd[0] =="DEBUG"){
		std::cout<<"\tdebug\n";
	}
	else if(cmd[0] == "DUMP"){
		std::cout<<"\tdump\n";
	}
	else if(cmd[0] == "ASSEMBLE"){
		assembler.AsmFile();
		//assembler.display();
		//assembler.displayOPtab();
	}
	else if(cmd[0] == "LOAD"){
		assembler.LoadFile(cmd[1]);
	}
	else if(cmd[0] == "EXECUTE"){
		std::cout<<"\texecute\n";
	}
	else{
		outgoing.InvalidOp_Prompt();
	}
}


void CMDLINE::ViewDirectory(){
	DIR *dpdf;
	struct dirent *epdf;
	dpdf = opendir("./");
	if (dpdf != NULL)
		while (epdf = readdir(dpdf))
			printf("\t%s\n",epdf->d_name);
}
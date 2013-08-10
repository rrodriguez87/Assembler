#include "Precompiled.h"

void Msg:: Welcome_Prompt(){
	std::cout<<"Welcome to the homebrewed Assembler by Rodrigo Rodriguez\n"
		     <<"Type 'HELP' to obtain list of available commands or\n"
			 <<"Type 'EXIT' to exit out of the application\n\n";
}

void Msg:: CMD_Prompt(){
	std::cout<<"cmd> ";
}

void Msg::Quit_Prompt(){
	std::cout<<"\nThank you for using my homebrewed Assmebler. Have a wonderful day!!!!\n";

}

void Msg::Help_Prompt(){
	std::cout<<"\tLOAD filename : Load function to load the specified file.\n"
			 <<"\tEXECUTE : Execute the program that was previously loaded in memory.\n"
			 <<"\tDEBUG : Execute in debug mode.\n"
			 <<"\tDUMP start end : Dump contents of memory.\n"
			 <<"\tHELP : List of available commands.\n"
			 <<"\tASSEMBLE : Assemble program into load module.\n"
			 <<"\tDIRECTORY : List the files stored in the current directory.\n"
			 <<"\tEXIT : Exit from the simulator.\n";
}

void Msg::InvalidOp_Prompt(){
	std::cout<<"Invalid operation. Type 'HELP' for more information.\n";
}
#ifndef ASSEMBLER_H
#define ASSEMBLER_H

struct Assembler{
public:
	Assembler();
	void LoadFile(std::string filename);
	void AsmFile();

	//void display();
	
private:
	//assembler declartions and operations
	General general;
	ASMline line[MAX_ROW];
	int LOCCTR;
	std::ifstream inData;
	std::ofstream outData;
	void PassOne();
	void PassTwo();
	int SizeOfarg(std::string arg);
	std::string ParseArg(std::string arg);

	//optab declarations and operations
	std::map <std::string, std::string> OPtab;
	std::map <std::string, std::string>::iterator OPiter;
	void displayOP();

	//symtab declarations and operations
	std::map <std::string, int> SYMtab;
	std::map <std::string, int>::iterator SYMiter;
	void displaySYM();
	
	
};

#endif
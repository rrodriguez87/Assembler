#include "Precompiled.h"
Assembler::Assembler(){
	LOCCTR=0;

	//insert commands and their machine-language equivalents to operations table
	OPtab.insert(std::pair<std::string, std::string>("ADD", "18"));
	OPtab.insert(std::pair<std::string, std::string>("AND", "58"));
	OPtab.insert(std::pair<std::string, std::string>("COMP", "28"));
	OPtab.insert(std::pair<std::string, std::string>("DIV", "24"));
	OPtab.insert(std::pair<std::string, std::string>("J", "3C"));
	OPtab.insert(std::pair<std::string, std::string>("JEQ", "30"));
	OPtab.insert(std::pair<std::string, std::string>("JGT", "34"));
	OPtab.insert(std::pair<std::string, std::string>("JLT", "38"));
	OPtab.insert(std::pair<std::string, std::string>("JSUB", "48"));
	OPtab.insert(std::pair<std::string, std::string>("LDA", "00"));
	OPtab.insert(std::pair<std::string, std::string>("LDCH", "50"));
	OPtab.insert(std::pair<std::string, std::string>("LDL", "08"));
	OPtab.insert(std::pair<std::string, std::string>("LDX", "04"));
	OPtab.insert(std::pair<std::string, std::string>("MUL", "20"));
	OPtab.insert(std::pair<std::string, std::string>("OR", "44"));
	OPtab.insert(std::pair<std::string, std::string>("RD", "D8"));
	OPtab.insert(std::pair<std::string, std::string>("RSUB", "4C"));
	OPtab.insert(std::pair<std::string, std::string>("STA", "0C"));
	OPtab.insert(std::pair<std::string, std::string>("STCH", "54"));
	OPtab.insert(std::pair<std::string, std::string>("STL", "14"));
	OPtab.insert(std::pair<std::string, std::string>("STX", "10"));
	OPtab.insert(std::pair<std::string, std::string>("SUB", "1C"));
	OPtab.insert(std::pair<std::string, std::string>("TD", "E0"));
	OPtab.insert(std::pair<std::string, std::string>("WD", "DC"));
	OPtab.insert(std::pair<std::string, std::string>("TIX", "2C"));

	//insert assembler directives into operations table
	OPtab.insert(std::pair<std::string, std::string>("START", "N/A"));
	OPtab.insert(std::pair<std::string, std::string>("BYTE", "N/A"));
	OPtab.insert(std::pair<std::string, std::string>("WORD", "N/A"));
	OPtab.insert(std::pair<std::string, std::string>("RESW", "N/A"));
	OPtab.insert(std::pair<std::string, std::string>("RESB", "N/A"));
	OPtab.insert(std::pair<std::string, std::string>("END", "N/A"));
	OPtab.insert(std::pair<std::string, std::string>("'EOF'", "3"));
}

void Assembler::LoadFile(std::string filename){
	int count=0;
	std::string temp;
	inData.open(filename);
	if(!inData)
		std::cout<<"failed to open '"<<filename<<"'."<<std::endl;

	while(inData>>temp){
		if(OPtab.find(temp) != OPtab.end()){
			line[count].label="N/A";
			line[count].opcode=temp;

			if(line[count].opcode=="RSUB"){
				line[count].argument="N/A";
				inData.ignore(256, '\n');
				count++;
				continue;
			}
			inData>>temp;
			line[count].argument=temp;
			inData.ignore(256, '\n');
			count++;
			continue;
		}
		else if(temp == "."){
			inData.ignore(256, '\n');
			continue;
		}
		else{
			line[count].label=temp;
			inData>>temp;
			line[count].opcode=temp;
			inData>>temp;
			line[count].argument=temp;
			inData.ignore(256, '\n');
			count++;
			continue;
		}		
	}		
}

void Assembler::AsmFile(){
	PassOne();
	PassTwo();
}

void Assembler::PassOne(){
	/*
		Scans the input.txt file to add addresses to the items in the symbol data field of 
		line
	*/


	char *p;
	for(int it=0;line[it].opcode != "END"; it++)
	{
		//start makes where in memory LOCCTR will begin at
		//if no start opcode is found, LOCCTR begins at 0;
		if(line[it].opcode == "START"){
			LOCCTR=strtol(line[it].argument.c_str(), &p, 16); //convert to to decimal to properally increment
			SYMtab.insert(std::pair<std::string, int>(line[it].label, LOCCTR));
			continue;
		}
		//label found, save label and current locctr to symbol table
		if(line[it].label != "N/A")
			SYMtab.insert(std::pair<std::string, int>(line[it].label, LOCCTR));

		//assembler directives found, assembler directives change the default
		//location counter increment ( 3 ) depending on which assembler directive
		//is found and their argument
		if(line[it].opcode == "BYTE"){
			LOCCTR+=SizeOfarg(line[it].argument);
		}
		else if(line[it].opcode == "RESB"){
			LOCCTR+=atoi(line[it].argument.c_str());
		}
		else if(line[it].opcode == "WORD"){
			LOCCTR+=3;
		}
		else if(line[it].opcode == "RESW"){
			LOCCTR+=(3*atoi(line[it].argument.c_str()));
		}
		else
			LOCCTR+=3;
	}
	displaySYM();
}

void Assembler::PassTwo(){
	outData.open("object.txt");
	std::string ASMconstant;
	int j=0;
	for(int i=1; line[i].opcode != "END"; i++)
	{
		//operation code in opcode field
		if((OPiter=OPtab.find(line[i].opcode)) != OPtab.end()){
			if(line[i].opcode == "BYTE"){
				ASMconstant=ParseArg(line[i].argument);				
				if(ASMconstant == "EOF")
					outData<<"454F46"<<std::endl;
				else
					outData<<ASMconstant<<std::endl;
			}
			else if(line[i].opcode == "WORD"){
				//convert to hex and send to object file
				outData<<std::setfill('0')<<std::setw(6)<<general.DecToHex1(atoi(line[i].argument.c_str()))<<std::endl;
			}
			else if(line[i].opcode == "RSUB"){
				outData<<OPiter->second<<"0000"<<std::endl;
				continue;
			}
			else if(line[i].opcode == "RESB" || line[i].opcode == "RESW")
				continue;
			else{
				outData<<OPiter->second;
			}
		}
		ASMconstant.clear();
		//symbol in argument field
		if(line[i].opcode=="STCH" || line[i].opcode=="LDCH")
		{
			j=0;
			while(line[i].argument[j] != ','){
				ASMconstant+=line[i].argument[j];
				j++;
			}
			if((SYMiter=SYMtab.find(ASMconstant)) != SYMtab.end()){
				ASMconstant=general.DecToHex1(SYMiter->second); //convert decimal to hexadecimal
				ASMconstant=std::to_string(SYMiter->second); //convert integer to string
				ASMconstant[0]=ASMconstant[ASMconstant.length()-1]; //move right most bit to left most bit
				outData<<ASMconstant.c_str()<<std::endl; //write to outdata file
			}
		}
		else{
			if((SYMiter=SYMtab.find(line[i].argument)) != SYMtab.end())
				outData<<general.DecToHex1(SYMiter->second)<<std::endl;
			else 
				continue;
		}
}

	}
int Assembler::SizeOfarg(std::string arg){
	std::string temp;
	int i=0;  //keep count

	while(arg[++i] != '\'')
		temp+=arg[i];
	if(arg[0] == 'X'){
		if(arg.length()%2 == 0)
			return (arg.length()%2)/2;
		else
			return ((arg.length()%2)+1)/2;
	}
	else if(arg[0] == 'C'){
		if((OPiter=OPtab.find(temp)) != OPtab.end())
			return atoi(OPiter->second.c_str());
		else
			return 3;
	}
	else
		return 3;
}

std::string Assembler::ParseArg(std::string arg){
	std::string temp;
	int i=1;
	while(arg[++i] != '\'')
		temp+=arg[i];
	return temp;
}
void Assembler::displaySYM(){
	for(SYMiter=SYMtab.begin(); SYMiter!=SYMtab.end(); ++SYMiter){
		std::cout<< (*SYMiter).first<<": "; 
		general.DecToHex((*SYMiter).second);
		std::cout<<"\n";
	}
}
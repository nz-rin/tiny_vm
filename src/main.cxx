
#include <iostream>

#include "Tiny_VM.hxx"

int main(){
	size_t size = 26;
	VM vm(size, size);

	/*
		0 - PUSH
		1 - CMP
		2 - JMP
		3 - FJMP
		10 - EXIT
	*/
	vm.load_instructions({
		"0", "10",			/*Push 10*/
		"0", "20", 			/*Push 20*/
		"1", 				/*Compare*/
		"0", "0", 			/*Push vflag::NE*/
		"0", "14",			/*Push address 15*/
		"3",				/*Conditional Jump, fjump*/
		"0", "69",				/*if equal, push 69*/
		"0", "16",				/*push addres of exit*/
		"2",					/*uncoditional jump*/
		"0", "420",				/*else push 420*/
		"10"				/*Exit*/
	});

	vm.run();
	vm.dump_instructions();
	vm.dump_stack();

	std::cout << "[RUN SUCCESSFULL]" << std::endl;

	return EXIT_SUCCESS;
}

#ifndef TINY_VM_HXX
#define TINY_VM_HXX

#include <stddef.h>
#include <string>
#include <vector>

#include "vlang.hxx"

typedef unsigned long vm_memory;
typedef unsigned long vm_uword;
typedef long vm_sword;

typedef unsigned long reg;
typedef char freg;

class VM{
	private:
		size_t memory_size		= 0;
		size_t stack_size		= 0;

		vm_memory *instructions	= nullptr;
		vm_memory *stack		= nullptr;

		size_t stack_pointer	= 0;
		size_t inst_pointer		= 0;

		reg jr	= 0;
		freg fr	= 0;

		bool instructions_loaded = false;
		bool check_condition(vm_sword cmp_res);

	public:
		VM(size_t memory_size, size_t stack_size);
		~VM();
		/**
		 * Function that runs the VM
		 */
		void run();

/**********************************************************************************/
//								VM Instructions CXX
/**********************************************************************************/
		/**
		 * Load instructions into the memory of the VM.
		 * If amount of instructions are greater than the memory size.
		 * loads up to memory size of instructions and logs a WARNING.
		 */
		void load_instructions(std::vector<std::string> instructions);
		/**
		 * Call this to execute a the current instruction at Instruction Pointer.
		 * Will modify the stack memory of the program or effect the next instruction.
		 */
		void execute_instruction(vasm::Opcode inst, vm_uword &ip, const vm_uword *instructions);

/**********************************************************************************/
//								VM Stack CXX
/**********************************************************************************/

		/**
		 * Returns a Signed 64-BIT Integer from the stack and Decrements the Stack Pointer.
		 * Exits and Logs an error if an issue occurs.
		 */
		vm_sword stack_pop();

		/**
		 * Adds a Signed 64-BIT Integer ontop of the stack and Increments the Stack Pointer.
		 * Exits and Logs an error if an issue occurs.
		 */
		void stack_push(vm_uword data);

/**********************************************************************************/
//								VM dump cxx
/**********************************************************************************/
		/**
		 * Logs all the instructions as signed Integers in Stdout.
		 * Will print up to VM::memory_size even if the rest are all 0.
		 */
		void dump_instructions();

		/**
		 * Logs stack values as signed 64-BIT Integers in Stdout.
		 * Will print up to VM::stack_size even if the rest are all 0
		 * prints address as an Integer starting from 0, can be changed to
		 * hex address using -DHEX_ADDR.
		 * Stack values are print in 8 values per line.
		 */
		void dump_stack();

/**********************************************************************************/
//							VM arthimetic CXX
/**********************************************************************************/

		/**
		 * Pops two 64-BIT Integers of the Stack, LHS then RHS, Adding LHS with RHS.
		 * Result is a SIGNED 64-BIT Integer that is pushed back onto the stack.
		 * Logs an error and exits if something goes wrong.
		 */
		void add();

		/**
		 * Pops two 64-BIT Integers of the Stack, LHS then RHS, Subtracting LHS with RHS.
		 * Result is a SIGNED 64-BIT Integer that is pushed back onto the stack.
		 * Logs and error and exits if something goes wrong.
		 */
		void sub();

		/**
		 * Pops two 64-BIT Integers of the Stack, LHS then RHS, Multiplying LHS with RHS.
		 * Result is a SIGNED 64-BIT Integer that is pushed back onto the stack.
		 * Logs an error and exits if something goes wrong.
		 */
		void mul();

		/**
		 * Pops two 64-BIT Integers of the Stack, LHS then RHS, Dividing LHS with RHS.
		 * Result is a SIGNED 64-BIT Integer that is pushed back onto the stack.
		 * Logs an error and exits if something goes wrong.
		 */
		void div();

/**********************************************************************************/
//								VM Conditionals CXX
/**********************************************************************************/

		/**
		 * Pops Two values of the stack and compared them.
		 * Result is pushed back ontop of the stack.
		 * results can be equal, not equal, less than, less than or equal
		 * greater than, greater than or equal.
		 * Exits and Logs an error if something goes wrong.
		 */
		void compare();

		/**
		 * Pops the Address to jump to off the stack then pops the compare result off the stack
		 * if the result matchest the jump type, jumps to the address poped off.
		 */
		void fjump();

		/**
		 * Pops the Address to jump to off the stack then preforms and uncoditional Jump to the address
		 */
		void jump();

};

#endif

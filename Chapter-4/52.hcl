#/* $begin seq-all-hcl */
#/* $begin seq-plus-all-hcl */
####################################################################
#  HCL Description of Control for Single Cycle Y86 Processor SEQ   #
#  Copyright (C) Randal E. Bryant, David R. O'Hallaron, 2002       #
####################################################################

## Your task is to implement the iaddl and leave instructions
## The file contains a declaration of the icodes
## for iaddl (IIADDL) and leave (ILEAVE).
## Your job is to add the rest of the logic to make it work

####################################################################
#    C Include's.  Don't alter these                               #
####################################################################

quote '#include <stdio.h>'
quote '#include "isa.h"'
quote '#include "sim.h"'
quote 'int sim_main(int argc, char *argv[]);'
quote 'int gen_pc(){return 0;}'
quote 'int main(int argc, char *argv[])'
quote '  {plusmode=0;return sim_main(argc,argv);}'

####################################################################
#    Declarations.  Do not change/remove/delete any of these       #
####################################################################

##### Symbolic representation of Y86 Instruction Codes #############
intsig INOP 	'I_NOP'
intsig IHALT	'I_HALT'
intsig IRRMOVL	'I_RRMOVL'
intsig IIRMOVL	'I_IRMOVL'
intsig IRMMOVL	'I_RMMOVL'
intsig IMRMOVL	'I_MRMOVL'
intsig IOPL	'I_ALU'
intsig IJXX	'I_JMP'
intsig ICALL	'I_CALL'
intsig IRET	'I_RET'
intsig IPUSHL	'I_PUSHL'
intsig IPOPL	'I_POPL'
# Instruction code for iaddl instruction
intsig IIADDL	'I_IADDL'
# Instruction code for leave instruction
intsig ILEAVE	'I_LEAVE'

##### Symbolic representation of Y86 Registers referenced explicitly #####
intsig RESP     'REG_ESP'    	# Stack Pointer
intsig REBP     'REG_EBP'    	# Frame Pointer
intsig RNONE    'REG_NONE'   	# Special value indicating "no register"

##### ALU Functions referenced explicitly                            #####
intsig ALUADD	'A_ADD'		# ALU should add its arguments

##### Signals that can be referenced by control logic ####################

##### Fetch stage inputs		#####
intsig pc 'pc'				# Program counter
##### Fetch stage computations		#####
intsig icode	'icode'			# Instruction control code
intsig ifun	'ifun'			# Instruction function
intsig rA	'ra'			# rA field from instruction
intsig rB	'rb'			# rB field from instruction
intsig valC	'valc'			# Constant from instruction
intsig valP	'valp'			# Address of following instruction

##### Decode stage computations		#####
intsig valA	'vala'			# Value from register A port
intsig valB	'valb'			# Value from register B port

##### Execute stage computations	#####
intsig valE	'vale'			# Value computed by ALU
boolsig Bch	'bcond'			# Branch test

##### Memory stage computations		#####
intsig valM	'valm'			# Value read from memory


####################################################################
#    Control Signal Definitions.                                   #
####################################################################

################ Fetch Stage     ###################################

# Does fetched instruction require a regid byte?
bool need_regids =
	icode in { IRRMOVL, IOPL, IPUSHL, IPOPL, 
		     IIRMOVL, IRMMOVL, IMRMOVL,
             IIADDL, ILEAVE };

# Does fetched instruction require a constant word?
bool need_valC =
	icode in { IIRMOVL, IRMMOVL, IMRMOVL, IJXX, ICALL };

bool instr_valid = icode in 
	{ INOP, IHALT, IRRMOVL, IIRMOVL, IRMMOVL, IMRMOVL,
	       IOPL, IJXX, ICALL, IRET, IPUSHL, IPOPL
           IIADDL, ILEAVE };

################ Decode Stage    ###################################

## What register should be used as the A source?
int srcA = [
	icode in { IRRMOVL, IRMMOVL, IOPL, IPUSHL  } : rA;
	icode in { IPOPL, IRET, ILEAVE } : RESP;
	1 : RNONE; # Don't need register
];

## What register should be used as the B source?
int srcB = [
	icode in { IOPL, IRMMOVL, IMRMOVL, IIADDL } : rB;
	icode in { IPUSHL, IPOPL, ICALL, IRET } : RESP;
    icode in { ILEAVE } : REBP;
	1 : RNONE;  # Don't need register
];

## What register should be used as the E destination?
int dstE = [
	icode in { IRRMOVL, IIRMOVL, IOPL} : rB;
	icode in { IPUSHL, IPOPL, ICALL, IRET } : RESP;
	1 : RNONE;  # Don't need register
];

## What register should be used as the M destination?
int dstM = [
	icode in { IMRMOVL, IPOPL, ILEAVE } : rA;
	1 : RNONE;  # Don't need register
];

################ Execute Stage   ###################################

## Select input A to ALU
int aluA = [
	icode in { IRRMOVL, IOPL, IIADDL } : valA;
	icode in { IIRMOVL, IRMMOVL, IMRMOVL } : valC;
	icode in { ICALL, IPUSHL } : -4;
	icode in { IRET, IPOPL } : 4;
	# Other instructions don't need ALU
];

## Select input B to ALU
int aluB = [
	icode in { IRMMOVL, IMRMOVL, IOPL, ICALL, 
		      IPUSHL, IRET, IPOPL, IIADDL } : valB;
	icode in { IRRMOVL, IIRMOVL } : 0;
	# Other instructions don't need ALU
];

## Set the ALU function
int alufun = [
	icode == IOPL : ifun;
	1 : ALUADD;
];

## Should the condition codes be updated?
bool set_cc = icode in { IOPL, IIADDL };

################ Memory Stage    ###################################

## Set read control signal
bool mem_read = icode in { IMRMOVL, IPOPL, IRET, ILEAVE };

## Set write control signal
bool mem_write = icode in { IRMMOVL, IPUSHL, ICALL };

## Select memory address
int mem_addr = [
	icode in { IRMMOVL, IPUSHL, ICALL, IMRMOVL } : valE;
	icode in { IPOPL, IRET, ILEAVE } : valA;
	# Other instructions don't need address
];

## Select memory input data
int mem_data = [
	# Value from register
	icode in { IRMMOVL, IPUSHL } : valA;
	# Return PC
	icode == ICALL : valP;
	# Default: Don't write anything
];

################ Program Counter Update ############################

## What address should instruction be fetched at

int new_pc = [
	# Call.  Use instruction constant
	icode == ICALL : valC;
	# Taken branch.  Use instruction constant
	icode == IJXX && Bch : valC;
	# Completion of RET instruction.  Use value from stack
	icode == IRET : valM;
	# Default: Use incremented PC
	1 : valP;
];
#/* $end seq-plus-all-hcl */
#/* $end seq-all-hcl */

#include "x86_instr.h"
#include "x86_tables.h"

/*

Notas: assume que se houver prefix bytes do mesmo grupo na mesma
instruçao, entao a instruçao é uma instruçao invalida

windgb ve prefixes repetidos como instruçoes invalidas mas o codigo executa
ideia para anti reverse engineering?


set prefix bytes to zero?

	Retrieves the prefixes of the instruction
	and advances one byte further.

*/
void x86_get_prefixes(unsigned char* byte)
{
	bool hasPrefix = true;
	uint8_t nPrefs = 0;
	int8_t group = 0;
	
	do
	{
		// Get group of prefix
		switch(byte)
		{
			// Group 1 prefixes
			case x86_PREFIX_LOCK:
			case x86_PREFIX_REPNE_REPNZ:
			case x86_PREFIX_REP_REPE_REPZ:
				group = 0;
				break;
			
			// Group 2 prefixes
			case x86_PREFIX_SEGMENT_CS:
			case x86_PREFIX_SEGMENT_SS:
			case x86_PREFIX_SEGMENT_DS:
			case x86_PREFIX_SEGMENT_ES:
			case x86_PREFIX_SEGMENT_FS:
			case x86_PREFIX_SEGMENT_GS:
			case x86_PREFIX_BRANCH_NOT_TAKEN:
			case x86_PREFIX_BRANCH_TAKEN:
				group = 1;
				break;
			
			// Group 3 prefixes
			case x86_PREFIX_OPERAND_OVERRIDE:
				group = 2;
				break;
			
			// Group 4 prefixes
			case x86_PREFIX_ADDRESS_OVERRIDE:
				group = 3;
				break;
				
			// Non prefix
			default:
				hasPrefix = false;
				group = -1;
				break;
		}
		
		// Set group prefix
		if(hasPrefix)
		{
			if(inst->prefix[group] != 0)
			{
				return;
				
				/*
					Invalid instruction
					
					 For each instruction, it is only useful to 
					 include up to one prefix code from each of the four groups.
					 
					 source: 	Intel 64 and IA-32 Architectures
								Software Developer’s Manual
								Volume 2 (2A, 2B, 2C & 2D)
								
					No instructions can have more than one prefix of each group.
				*/
			}
			else inst->prefix[group] = byte;
			
			inst->size++;
			nPrefs++;
		}
		
		*byte++;
	}
	while(hasPrefix && nPrefs < 4)
	/*
		nPrefs >= 4
		
		Invalid Instruction
		
		For each instruction, it is only useful to 
		include up to one prefix code from each of the four groups.
		 
		source: 	Intel 64 and IA-32 Architectures
					Software Developer’s Manual
					Volume 2 (2A, 2B, 2C & 2D)
					
		No instructions can have more than one prefix of each group,
		therefore it can only have 1 prefix of each group up to a total
		of 4 prefixes.
	*/
}

void x86_escape_code()
{
	switch(byte)
	{
		case 0x0F:
		case 0x38
	}
}

void x86_get_opcode(unsigned char* byte)
{
	// Handle escape codes
	
	if(byte == 0x0F)
	{
		*byte++;
		
		if(byte == 0x3A) table = 31 byte++
		else if (byte == 0x38) table = 32 byte++
		else table = 1
		
	}
	
	// Get opcode
	
	attr = table[byte];
	
	// Handle modrm
	
	if(attr & MODRM)
	{
		modrm = byte;
		*byte++;
	}
	
	// Handle definite
	
	// Handle immediate
}

bool x86_has_modrm(size_t size, byte opcode)
{
	if(size < 0 || size >= 3) return false;
	
	return *(x86_opcode_attribute_table[size])[opcode] & x86_OPCODE_ATTR_MODRM_MASK;
}

/*

rex is 64 bits mode only

Only one REX prefix is allowed per instruction. If used, the REX prefix byte must immediately precede the opcode
byte or the escape opcode byte (0FH). When a REX prefix is used in conjunction with an instruction containing a
mandatory prefix, the mandatory prefix must come before the REX so the REX prefix can be immediately preceding
the opcode or the escape byte. For example, CVTDQ2PD with a REX prefix should have REX placed between F3 and
0F E6. Other placements are ignored. The instruction-size limit of 15 bytes still applies to instructions with a REX
prefix. 

*/
void x86_handle_rex()
{
}

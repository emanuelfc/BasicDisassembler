// Includes
#include <stdint.h>

#define x86_MAX_INST_SIZE 15
#define x86_MAX_PREFIX_GROUPS 4
#define x86_MAX_OPCODE_SIZE 3

// REX PREFIXES

/*
	REX prefixes are a set of 16 opcodes that span one row of the opcode map and occupy entries 40H to 4FH. These
	opcodes represent valid instructions (INC or DEC) in IA-32 operating modes and in compatibility mode. In 64-bit
	mode, the same opcodes represent the instruction prefix REX and are not treated as individual instructions
*/

#define REX_1 	0x40
#define REX_1 	0x41
#define REX_1 	0x42
#define REX_1 	0x43
#define REX_1 	0x44
#define REX_1 	0x45
#define REX_1 	0x46
#define REX_1 	0x47
#define REX_1 	0x48
#define REX_1 	0x49
#define REX_1 	0x4A
#define REX_1 	0x4B
#define REX_1 	0x4C
#define REX_1 	0x4D
#define REX_1 	0x4E
#define REX_16 	0x4F

// VEX

#define VEX_2BYTE 0xC5
#define VEX_3BYTE 0xC4

typedef unsigned char byte;

namespace x86
{

	// Attributes/Masks

	static const enum attributes
	{
		no_attribute = 0,
		
		// Prefix related - 2rd byte
		
		prefix = 1 << 20,
		rex = 1 << 19,
		vex = 1 << 18,
		
		// Opcode related - 1rd byte
		
		escape_code = 1 << 13,
		opcode = 1 << 12,
		
		// Additional opcode related - 0 byte
		
		modrm = 1 << 7,
		sib = 1 << 6,
		displacement = 1 << 5,
		immediate = 1 << 4
	}

	// Registers

	static const enum registers
	{
		rax = 0,
		rcx = 1,
		rdx = 2,
		rbx = 3,
		rsp = 4,
		rbp = 5,
		rsi = 6,
		rdi = 7
	}

	/*

		Optimizations:
						use stack instead of * for bytes?

	*/
	struct inst
	{
		//byte* addr
		
		byte prefix[4];
		
		byte* rex;
		byte* vex;
		
		byte* opcode[3];
		
		byte* modrm;
		byte* sib;
		
		uint32_t attr;
		uint8_t size;
	};

	/*

		All functions are very similar and could be
		easely simplified to encompass one function only
		howerver since we want to inline the function it
		doesn't matter because the code will be the same
		whether or one one simplifies or leaves it like it
		now.

	*/

	static inline uint8_t isPrefix(uint8_t attr)
	{
		return attr & attributes.prefix;
	}

	static inline uint8_t isEscapeCode(uint8_t attr)
	{
		return attr & attributes.escape_code;
	}

	static inline uint8_t isOpcode(uint8_t attr)
	{
		return attr & attributes.opcode;
	}
	static inline uint8_t hasRex(uint8_t attr)
	{
		return attr & attributes.rex;
	}

	static inline uint8_t hasVex(uint8_t attr)
	{
		return attr & attributes.vex;
	}

	static inline uint8_t hasModRM(uint8_t attr)
	{
		return attr & attributes.modrm;
	}

	static inline uint8_t hasSib(uint8_t attr)
	{
		return attr & attributes.sib;
	}

	static inline uint8_t hasDisplacement(uint8_t attr)
	{
		return attr & attributes.displacement;
	}

	static inline uint8_t hasImmediate(uint8_t attr)
	{
		return attr & attributes.immediate;
	}

	// ModR/M
	
	namespace modrm
	{
	
		static inline uint8_t mod(byte modrm)
		{
			return modrm >> 6;
		}

		static inline uint8_t reg(byte modrm)
		{
			return (modrm & 0x38) >> 3;
		}

		static inline uint8_t rm(byte modrm)
		{
			return modrm & 0x07;
		}
	
	}

	// SIB
	
	namespace sib
	{
		static inline uint8_t scale(byte sib)
		{
			return sib >> 6;
		}

		static inline uint8_t index(byte sib)
		{
			return (sib & 0x38) >> 3;
		}

		static inline uint8_t base(byte sib)
		{
			return sib & 0x07;
		}
	}
}
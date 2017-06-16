/* Model Specific Register Access */

#include "instruction.h"

void readmsr(uint32_t msr, byte* b_array_8);
void writemsr(uint32_t msr, byte* b_array_8);

void wrmsr(uint32_t msr_id, uint64_t msr_value)
{
	writemsr(msr_id, (byte*)&msr_value);
}


uint64_t rdmsr(uint32_t msr_id)
{
	byte arr[8];
	readmsr(msr_id, arr);
	return *(uint64_t*)(arr);
}


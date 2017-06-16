#ifndef _KLIB_BIT_OP_H_
#define _KLIB_BIT_OP_H_


/*
Bitwise immediate operations

not changing the given var
*/
#define SETBIT(var,pos) ((var) | ((uintptr_t)1<<(pos)))
#define CLEARBIT(var,pos) ((var) & ~((uintptr_t)1<<(pos)))
#define FLIPBIT(var,pos) ((var) ^ ((uintptr_t)1<<(pos)))
#define TESTBIT(var,pos) ((var) & ((uintptr_t)1<<(pos)))


/*
Bitwise immediate value

*/
#define IMMEDIATE_SETBIT(pos) (1<<pos)

/*
Bitwise modifications

*/
#define setbit(pVal,pos) (*(pVal) |= ((uintptr_t)1<<(pos)))
#define clearbit(pVal,pos) (*(pVal) &= ~((uintptr_t)1<<(pos)))
#define flipbit(pVal,pos) (*(pVal) ^= ((uintptr_t)1<<(pos)))
#define testbit(pVal,pos) (*(pVal) & ((uintptr_t)1<<(pos)))

/*
inline void setbit(uint32_t* uint_p, uint32_t bit)
{
	(*uint_p) |= 1 << bit;
}
inline void clearbit(uint32_t* uint_p, uint32_t bit)
{
	(*uint_p) &= ~(1 << bit);
}
inline void flipbit(uint32_t* uint_p, uint32_t bit)
{
	(*uint_p) ^= 1 << bit;
}
inline bool testbit(uint32_t* uint_p, uint32_t bit)
{
	return (bool)((*uint_p) & (1 << bit));
}
*/
#endif


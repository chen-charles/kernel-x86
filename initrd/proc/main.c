
int main()
{
    __asm__ volatile ("xor eax, eax");
    while (1) __asm__ volatile ("inc eax");
    return 0;
}

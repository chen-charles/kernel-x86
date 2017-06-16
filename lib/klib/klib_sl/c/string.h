// Copyright 2016 Jianye Chen All Rights Reserved.

#ifndef _KLIB_STRING_H_
#define _KLIB_STRING_H_

#include <klib_sl/type.h>

//Copying
void * memcpy ( void * destination, const void * source, size_t num );
void * memmove ( void * destination, const void * source, size_t num );
char * strcpy ( char * destination, const char * source );
char * strncpy ( char * destination, const char * source, size_t num );

//Concatenation
char * strcat ( char * destination, const char * source );
char * strncat ( char * destination, const char * source, size_t num );

//Comparison
int memcmp ( const void * ptr1, const void * ptr2, size_t num );
int strcmp ( const char * str1, const char * str2 );
//int strcoll ( const char * str1, const char * str2 );
int strncmp ( const char * str1, const char * str2, size_t num );
//size_t strxfrm ( char * destination, const char * source, size_t num );

//Searching
void * memchr ( const void * ptr, int value, size_t num ); //Locate character in block of memory
char * strchr ( const char * str, int character );
size_t strcspn ( const char * str1, const char * str2 );
char * strpbrk ( const char * str1, const char * str2 );
char * strrchr ( const char * str, int character );
size_t strspn ( const char * str1, const char * str2 );
char * strstr(const char *str1, const char *str2);
char * strtok(char *str, const char *delimiters);


void * memset ( void * ptr, int value, size_t num );
char * strerror ( int errnum );
size_t strlen ( const char * str );

#endif

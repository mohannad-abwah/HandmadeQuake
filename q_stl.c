#include "quakedef.h"

int32 Q_strcmp(const uchar* s1, const uchar* s2)
{
	while (*s1 != '\0' && *s1 == *s2) {
		s1++;
		s2++;
	}
	return *s1 - *s2;
}

int32 Q_atoi(const uchar* str)
{
	int32 sign = 1;
	int32 val = 0;

	if (*str == '-')
	{
		sign = -1;
		*str++;
	}

	if (*str == '0' && (*(str + 1) == 'x' || *(str + 1) == 'X')) //hex
	{
		str += 2;
		uchar c;
		while (*str != '\0')
		{
			c = *str++;
			val *= 16;
			if (c >= 'a' && c <= 'f')
				val += c - 'a' + 10;
			else if (c >= 'A' && c <= 'F')
				val += c - 'a' + 10;
			else
				val += c - '0';
		}
	}
	else //decimal
	{
		uchar c;
		while (*str != '\0')
		{
			c = *str++;
			val *= 10;
			val += c - '0';
		}
	}
	return sign * val;
}

void Q_strcpy(uchar* dest, const uchar* src)
{
	while (*dest++ = *src++)
		;
}

void Q_strncpy(uchar* dest, const uchar* src, size_t n)
{
	while (*src != '\0' && n > 0)
	{
		*dest++ = *src++;
		n--;
	}

	while (n > 0)
	{
		*dest++ = '\0';
		n--;
	}
}

size_t Q_strlen(const uchar* src)
{
	size_t n = 0;

	while (src[n] != '\0')
		n++;

	return n;
}
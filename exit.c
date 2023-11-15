#include "shell.h"

/**
 **_strcp -this copies a string
 *@des: the destination string to be copied to
 *@stc:it is the source string
 *@no: the amount of characters to be copied
 *Return: the concatenated string
 */
char *_strcp(char *des, char *stc, int no)
{
	int j, l;
	char *s = des;

	j = 0;
	while (stc[j] != '\0' && j < no - 1)
	{
		des[j] = stc[j];
		j++;
	}
	if (j < no)
	{
		l = j;
		while (l < no)
		{
			des[l] = '\0';
			l++;
		}
	}
	return (s);
}

/**
 **str_cat -it concatenates two strings
 *@des:it is the first string
 *@st: the second string
 *@no:it is the amount of bytes to be maximally used
 *Return: the string concatenated
 */
char *str_cat(char *des, char *st, int no)
{
	int j, l;
	char *n = des;

	j = 0;
	j = 0;
	while (des[j] != '\0')
		j++;
	while (st[j] != '\0' && j < no)
	{
		des[j] = st[l];
		j++;
		l++;
	}
	if (j < no)
		des[j] = '\0';
	return (n);
}

/**
 **st_ch -it locates a character in a string
 *@so:string to be parsed
 *@ch:character to look for
 *Return: (so) a pointer to the memory area so
 */
char *st_ch(char *so, char ch)
{
	do {
		if (*so == ch)
			return (so);
	} while (*so++ != '\0');

	return (NULL);
}

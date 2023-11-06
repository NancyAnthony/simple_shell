#include "shell.h"

/**
 * **splwrd - handles spliting of string to words.
 * Repeated delimiters are ignored
 * @string: the string input
 * @delim: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **splwrd(char *string, char *delim)
{
	int n, l, s, m, num_words = 0;
	char **c;

	if (string == NULL || string[0] == 0)
		return (NULL);
	if (!delim)
		delim = " ";
	for (n = 0; string[n] != '\0'; n++)
		if (!check_delimeter(string[n], delim) &&
				(check_delimeter(string[n + 1], delim) || !string[n + 1]))
			num_words++;

	if (num_words == 0)
		return (NULL);
	c = malloc((1 + num_words) * sizeof(char *));
	if (!c)
		return (NULL);
	for (n = 0, l = 0; l < num_words; l++)
	{
		while (check_delimeter(string[n], delim))
			n++;
		s = 0;
		while (!check_delimeter(string[n + s], delim) && string[n + s])
			s++;
		c[l] = malloc((s + 1) * sizeof(char));
		if (!c[l])
		{
			for (s = 0; s < l; s++)
				free(c[s]);
			free(c);
			return (NULL);
		}
		for (m = 0; m < s; m++)
			c[l][m] = string[n++];
		c[l][m] = 0;
	}
	c[l] = NULL;
	return (c);
}

/**
 * **splwrd2 - handles spliting of a string to words
 * @string: the string input
 * @delim: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **splwrd2(char *string, char delim)
{
	int n, l, s, m, num_words = 0;
	char **c;

	if (string == NULL || string[0] == 0)
		return (NULL);
	for (n = 0; string[n] != '\0'; n++)
		if ((string[n] != delim && string[n + 1] == delim) ||
		    (string[n] != delim && !string[n + 1]) || string[n + 1] == delim)
			num_words++;
	if (num_words == 0)
		return (NULL);
	c = malloc((1 + num_words) * sizeof(char *));
	if (!c)
		return (NULL);
	for (n = 0, l = 0; l < num_words; l++)
	{
		while (string[n] == delim && string[n] != delim)
			n++;
		s = 0;
		while (string[n + s] != delim && string[n + s] && string[n + s] != delim)
			s++;
		c[l] = malloc((s + 1) * sizeof(char));
		if (!c[l])
		{
			for (s = 0; s < l; s++)
				free(c[s]);
			free(c);
			return (NULL);
		}
		for (m = 0; m < s; m++)
			c[l][m] = string[n++];
		c[l][m] = 0;
	}
	c[l] = NULL;
	return (c);
}

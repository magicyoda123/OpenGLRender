#include <string.h>
int searchText(char *text, char* fragment)
{
	int res = 0;
	for (int i = 0; i < strlen(text); i++)
	{
		res = 0;
		if (text[i] == fragment[0] && (i + strlen(fragment)) <= strlen(text))
		{
			res = 1;
			for (int j = 1; j < strlen(fragment); j++)
			{
				if (text[i + j] == fragment[j])
				{
					res++;
				}


			}
			if (res == (strlen(fragment)))
			{
				res = 0;
				return i;
			}
			else
			{
				res = 0;
			}
		}
	}
	return -1;
}
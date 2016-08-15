#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "url_parse.h"

int UrlParse(parse_t *parse, const char *px, int data_length)
{
	int i;
	for (i = 0; i < data_length; i++)
	{
		switch (parse->state)
		{
			case HTTP__Find_Method:
			{
				//The first non-space is the beginning of the method
				if ((*(&px[i])!=' '))
				{
					printf("\nMethod     :%c", *(&px[i]));
					parse->state = HTTP__Method;
				}
				if ((data_length-1) == i)
					return(PARSE_SUCCESS);
			}break;
				
			case HTTP__Method:
			{
				if ((*(&px[i])!=' '))
				{
					printf("%c", *(&px[i]));
					if ((data_length-1) == i)
						return(PARSE_SUCCESS);
				}
				//The end of the method can be found by a delimiting space
				else
				{
					parse->state = HTTP__Find_Url;
					if ((data_length-1) == i)
						return(PARSE_SUCCESS);
				}
			}break;
				
			case HTTP__Find_Url:
			{
				if ((*(&px[i])!=' '))
				{
					printf("\nUrl        :%c", *(&px[i]));
					parse->state = HTTP__Url;
				}
				if ((data_length-1) == i)
					return(PARSE_SUCCESS);
			}break;
				
			case HTTP__Url:
			{
				//Possible argument
				if(*(&px[i])=='?')
				{
					printf("\nArgument   :");
					parse->state = HTTP__Argument;
					if ((data_length-1) == i)
						return(PARSE_SUCCESS);
				}
				//Print URL
				else if ((*(&px[i])!=' '))
				{
					printf("%c", *(&px[i]));
					if ((data_length-1) == i)
						return(PARSE_SUCCESS);
				}
				//If there is no argument change parse_state in HTTP__Find_Version
				else
				{
					parse->state = HTTP__Find_Version;
					if ((data_length-1) == i)
						return(PARSE_SUCCESS);
				}
			}break;
				
			case HTTP__Find_Version:
			{
				if ((*(&px[i])!=' '))
				{
					printf("\nVersion    :%c", *(&px[i]));
					parse->state = HTTP__Version;
				}
				if ((data_length-1) == i)
					return(PARSE_SUCCESS);
			}break;
				
			case HTTP__Version:
			{
				if (*(&px[i])!=' ')
				{
					if ((*(&px[i])=='\n')||(*(&px[i])=='\r'))
					{
						printf("\n");
						return(PARSE_FINISHED);
					}
					printf("%c", *(&px[i]));
					if ((data_length-1) == i)
						return(PARSE_SUCCESS);
				}
				//Output just the first version identifier.
				else
				{
					printf("\n");
					return(PARSE_FINISHED);
				}
			}break;
				
			case HTTP__Argument:
			{
				if ((*(&px[i])!=' '))
				{
					printf("%c", *(&px[i]));
					if ((data_length-1) == i)
						return(PARSE_SUCCESS);
				}
				else
				{
					parse->state = HTTP__Find_Version;
					if ((data_length-1) == i)
						return(PARSE_SUCCESS);
				}
			}break;
		}
	}
	printf("\n");
	return(PARSE_FINISHED);
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "url_parse.h"

char *URL[] = {
	"GET /index_1.html HTTP/1.0\r\n",
	"GET /index_2.html/ HTTP/1.0 HTTP/1.1\n",
	"HEAD  /index_3.htm HTTP/1.2\r\n",
	"    FOO /index_4.htm     HTTP/1.1\r\r",
	"POST /cgi-bin/hostsvc_5.sh?arg1=/../etc/passwdi&x=?data1&y=data2  HTTP/1.0 \n\r",
	" GET /cgi-bin/hostsvc_6.sh??arg1=/../etc/passwdi&x=data1&y=data2 HTTP/1.0\r\n",
	" POST  /index_7.sh?arg1= HTTP/1.2 .....\r\n",
	"\0\0",
};

int main(int argc, char** argv)
{
	parse_t *parse;
	int i;
	
	parse = (parse_t*) malloc(sizeof (parse_t));
	if ( !parse )
	{
		perror("Could not allocate memory for parse structure");
		return(1);
	}
	
	printf("\n***********************************\n");
	printf(   "   Running Test 1: Full Strings\n");
	printf("***********************************\n");
	
	for (i = 0; URL[i][0]; i++)
	{
		memset(parse, 0, sizeof(parse_t));
		
		/* We send an entire string at a time, but the
		 * length provided does not include a null terminator.
		 * When the parser returns, we give the next
		 * string */
		UrlParse(parse, URL[i], strlen(URL[i]));
	}
	
	printf("\n*************************************\n");
	printf(" Running Test 2: Character at a time\n");
	printf("*************************************\n");
	
	for (i = 0; URL[i][0]; i++)
	{
		char ch[1];
		size_t x;
		
		memset(parse, 0, sizeof(parse_t));
		for (x = 0; x < strlen(URL[i]); x++)
		{
			ch[0] = URL[i][x];
			/* We send a character at a time.  The parser
			 * tells us when it's done and we give the next
			 * string */
			if (UrlParse(parse, (const char*) &ch[0], 1) == PARSE_FINISHED){
				break;
			}
		}
	}
	
	printf("\n********************************************\n");
	printf(" Running Test 3: A few characters at a time\n");
	printf("********************************************\n");
	
	for (i = 0; URL[i][0]; i++)
	{
		size_t x;
		size_t stringSize = strlen(URL[i]);
		unsigned len = 3;   /* random length up to 8 bytes, seeded with 3 */
		
		memset(parse, 0, sizeof(parse_t));
		
		for (x = 0; x < stringSize; x += len)
		{
			/* We send up to 8 characters at a time.  The parser
			 * tells us when it's done and we give the next
			 * string */
			len ^= URL[i][x];
			
			//7 0x0007
			
			len &= 0x0007u;
			len++;
			if (len > stringSize - x)
				len = stringSize - x;
			
			if (UrlParse(parse, (const char*) &URL[i][x], len) == PARSE_FINISHED)
				break;
		}
	}
	
	if (parse)
		free(parse);
	
	return(0);
}


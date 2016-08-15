#ifndef _URL_PARSE_H
#define _URL_PARSE_H

enum PARSE_STATES
{
	HTTP__Find_Method = 0,
	HTTP__Method,
	HTTP__Find_Url ,
	HTTP__Url,
	HTTP__Argument,
	HTTP__Find_Version,
	HTTP__Version,
};

typedef struct PARSE
{
	enum PARSE_STATES state;
} parse_t;

enum PARSE_RESULT
{
	PARSE_FINISHED = 0,
	PARSE_SUCCESS,
};

enum PARSE_RESULT;
UrlParse(parse_t *parse, const char *px, int data_length);

#endif
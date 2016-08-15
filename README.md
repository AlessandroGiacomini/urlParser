# Project: url parser
## Description
-----------------------------------

Algorithm in C to parse url at wire speeds.

## How to Run Project
------------------

* Clone the repo with ```git clone https://github.com/AlessandroGiacomini/multiuserblog.git```
* Test the code using various Visual Studio and Cygwin GNU/GCC compilers

### Project specifications
-----------------------------------

View the example-output.txt file and the input URL table in main.c

Observe that three calls to UrlParse() are performed. 
- One call sends the entire URL string at once
- The other sends it a character at a time. 
- A few characters at a time

The url_parse() function has to produces output similar to example-output.txt when run.  For each input string, there should be an output line for the HTTP method, an output line for the URL, and an output line for the HTTP Version.  Some of the strings have mutliple version  identifiers, but you should only output the first version identifier.

Is only concerned with parsing the input strings found in main.c and producing the output in example-output.txt at wire speeds.

It has not to be concerned with the exact details of the HTTP protocol.
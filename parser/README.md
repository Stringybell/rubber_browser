
# Error list

* File Errors:
  * **EF0**: This error can be found in the `char* file_parser(const char* filename)` function. Check the filename and the directory you are linking to ensure the file exists and the program has permission to open it.
  * **EF1**: This error can be found in the `char* file_parser(const char* filename)` function. It occurs when `malloc` fails to allocate enough memory for the buffer; check available system memory or if the file size is abnormally large.
  * **EF2**: This error can be found in the `char* file_parser(const char* filename)` function. It is triggered if `fread` reads a different number of bytes than the calculated file size (`fsize`), indicating an incomplete read or file stream issue.



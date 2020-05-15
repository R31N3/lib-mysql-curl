#ifndef UNTITLED2_LIBRARY_H
#define UNTITLED2_LIBRARY_H
#include <curl/curl.h>
#include <mysql.h>

my_bool Send_init(UDF_INIT*, UDF_ARGS*, char*);

my_bool Send_deinit(UDF_INIT*, UDF_ARGS*, char*);

long long Send(UDF_INIT*, UDF_ARGS*, char*, char*);

#endif //UNTITLED2_LIBRARY_H

/*
libmsqlcurl - lib for mysql and curl binding

Copyright (C) 2020 - Nikita Smirnov

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the "Software"),
to deal in the Software without restriction, including without limitation
the rights to use, copy, modify, merge, publish, distribute, sublicense, 
and/or sell copies of the Software, and to permit persons to whom the 
Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included 
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS
OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, 
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef LIBMYSQLCURL_LIBRARY_H
#define LIBMYSQLCURL_LIBRARY_H
#include <curl/curl.h>
#include <mysql.h>

my_bool send_post_init(UDF_INIT *, UDF_ARGS *, char *);

my_bool send_post_deinit(UDF_INIT *, UDF_ARGS *, char *);

long long send_post(UDF_INIT *, UDF_ARGS *, char *, char *);

my_bool send_put_init(UDF_INIT *, UDF_ARGS *, char *);

my_bool send_put_deinit(UDF_INIT *, UDF_ARGS *, char *);

long long send_put(UDF_INIT *, UDF_ARGS *, char *, char *);

my_bool send_delete_init(UDF_INIT *, UDF_ARGS *, char *);

my_bool send_delete_deinit(UDF_INIT *, UDF_ARGS *, char *);

long long send_delete(UDF_INIT *, UDF_ARGS *, char *, char *);

my_bool wrapped_init(UDF_INIT *, UDF_ARGS *, char *);

my_bool wrapped_deinit(UDF_INIT *, UDF_ARGS *, char *);

int wrapup_request(UDF_ARGS *, const char *, CURLcode *);

void encapsulate_data(UDF_ARGS *, char **);

void json_string(char *, char *, char *, enum Item_result, int);

#endif //UNTITLED2_LIBRARY_H

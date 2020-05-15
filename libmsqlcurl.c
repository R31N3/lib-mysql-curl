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

#include "libmsqlcurl.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string.h>
#include <my_global.h>
#include <curl/curl.h>
#include "mysql.h"

my_bool Send_init(UDF_INIT *initid, UDF_ARGS *args, char *message) {
    if (args->arg_count != 2) {
        strcpy(message, "Send() requires two arguments");
        return 1;
    }
    if (args->arg_type[0] != STRING_RESULT ||
    args->arg_type[1] != INT_RESULT) {
    	strcpy(message, "Send() requires [addr:string] and [id:integer]");
    	return 1;
    }
	
    return 0;
}

my_bool Send_deinit(UDF_INIT *initid, UDF_ARGS *args, char *message) {
	if(initid->ptr){
		free(initid->ptr);
		initid->ptr = NULL;
	}
    return 0;
}

long long Send(UDF_INIT *initid, UDF_ARGS *args, char *is_null, char *error) {
	curl_global_init(CURL_GLOBAL_ALL);
	char* addr = args->args[0];
	char* json = malloc(20);
	sprintf(json, "{\"id\":\"%lld\"}", *((long long*) args->args[1]));
	CURL* handle = curl_easy_init();
	struct curl_slist *list = NULL;
	list = curl_slist_append(list, "Content-Type: application/json");
	curl_easy_setopt(handle, CURLOPT_HTTPHEADER, list);
    curl_easy_setopt(handle, CURLOPT_URL, addr);
    curl_easy_setopt(handle, CURLOPT_POSTFIELDS, json);
    CURLcode code = curl_easy_perform(handle);
    if(code != 0){
    	*error = 1;
    }
    curl_global_cleanup();
    return code;
}

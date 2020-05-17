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
#include <stdarg.h>

my_bool send_post_init(UDF_INIT *initid, UDF_ARGS *args, char *message)
{
    if (args->arg_count < 2) {
        strcpy(message, "Send() requires >=2 arguments");
        return 1;
    }
    if (args->arg_type[0] != STRING_RESULT) {
    	strcpy(message, "Send() requires [addr:string]");
    	return 1;
    }
	return 0;
}

my_bool send_post_deinit(UDF_INIT *initid, UDF_ARGS *args, char *message)
{
	if(initid->ptr){
		free(initid->ptr);
		initid->ptr = NULL;
	}
    return 0;
}

void json_string(char *res_str, char *attr_name, char *arg, enum Item_result arg_type, int trail_com)
{
	switch (arg_type)
	{
	case INT_RESULT:
		if (trail_com)
		{
			sprintf(res_str, "\"%s\":\"%lld\",", attr_name, *((long long *) arg));
		}
		else
		{
			sprintf(res_str, "\"%s\":\"%lld\"", attr_name, *((long long *)arg));
		}
		break;

	case REAL_RESULT:
		if (trail_com)
		{
			sprintf(res_str, "\"%s\":\"%f\",", attr_name, *((double *)arg));
		}
		else
		{
			sprintf(res_str, "\"%s\":\"%f\"", attr_name, *((double *)arg));
		}

	default:
		if (trail_com)
		{
			sprintf(res_str, "\"%s\":\"%s\",", attr_name, arg);
		}
		else
		{
			sprintf(res_str, "\"%s\":\"%s\"", attr_name, arg);
		}
	}
}

void encapsulate_data(UDF_ARGS* udf_args, char** res_str)
{
	unsigned int num_of_args = udf_args->arg_count;
	char **attributes = udf_args->attributes;
	unsigned long *lengths = udf_args->lengths;
	unsigned long *attribute_lengths = udf_args->attribute_lengths;
	char **args = udf_args->args;
	enum Item_result *arg_types = udf_args->arg_type;
	char **char_args = (char **)calloc(num_of_args, sizeof(char *));
	unsigned long res_len = 0;
	for(unsigned int i = 0; i < num_of_args - 1; i++)
	{
		char_args[i] = (char *)calloc(11 + attribute_lengths[i] + lengths[i], sizeof(char *));
		json_string(
			char_args[i],
			attributes[i],
			args[i],
			arg_types[i],
			1);
		res_len += strlen(char_args[i]);
	}
	char_args[num_of_args - 1] = (char *)calloc(10 + attribute_lengths[num_of_args - 1] + lengths[num_of_args - 1], sizeof(char *));
	json_string
	(
		char_args[num_of_args - 1],
		attributes[num_of_args - 1],
		args[num_of_args - 1],
		arg_types[num_of_args - 1],
		0
	);
	res_len += strlen(char_args[num_of_args - 1]);

	*res_str = (char *)calloc(res_len + 3, sizeof(char));
	**res_str = '{';
	unsigned long current_pos = 1;
	for(int i = 0; i < num_of_args; i++){
		strcpy((*res_str + current_pos), char_args[i]);
		current_pos += strlen(char_args[i]);
		free(char_args[i]);
	}
	(*res_str)[res_len + 1] = '}';
	(*res_str)[res_len + 2] = '\0';
}

long long send_post(UDF_INIT *initid, UDF_ARGS *args, char *is_null, char *error)
{
	curl_global_init(CURL_GLOBAL_ALL);
	char* addr = args->args[0];
	char* json = NULL;
	encapsulate_data(args, &json);
	if(json == NULL) {
		*error = 1;
		return 0;
	}
	CURL* handle = curl_easy_init();
	struct curl_slist *list = NULL;
	list = curl_slist_append(list, "Content-Type: application/json");
	list = curl_slist_append(list, "accept: application/json");
	curl_easy_setopt(handle, CURLOPT_HTTPHEADER, list);
    curl_easy_setopt(handle, CURLOPT_URL, addr);
    curl_easy_setopt(handle, CURLOPT_POSTFIELDS, json);
    CURLcode code = curl_easy_perform(handle);
    if(code != 0)
	{
    	*error = 1;
    }
    curl_global_cleanup();
    return 1488;
}

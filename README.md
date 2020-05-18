# MySQL UDF for curl utilities

Simple library connecting curl and MySQL

## Running

Only for Unix-compatible OS

### Requirements

``` text
libcurl4-openssl-dev
libmysqlclient development software
mysql
```

### Installation

``` bash
sudo ./install.sh
```

### Usage

``` text
SELECT send_<post/put/delete>([<URL or IP with port>], data1 as alias1, data2 as alias2, ...)
FROM ...;
```
equivalent to 
``` bash
curl -X <POST/PUT/DELETE/> "<URL or IP with port>" \
-H "Content-Type: application/json" \
-d "{
      \"alias1\":\"data1\",
      \"alias2\":\"data2\",
      ...
    }"
```


Returns response code per request if request was somehow delivered

NULL if something went wrong;

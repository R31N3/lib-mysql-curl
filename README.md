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

``` sql
SELECT send_post([<URL or IP with port>] as alias0, data1 as alias1, data2 as alias2, ...) FROM ...;
```

Returns 0 per request if request was successfully delivered (but HTTP response code could be 4xx or 5xx)
NULL if something went wrong;

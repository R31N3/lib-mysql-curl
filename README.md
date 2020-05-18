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
SELECT send_<post/put/delete>([<URL or IP with port>] as alias0, data1 as alias1, data2 as alias2, ...) FROM ...;
```

Returns response code per request if request was somehow delivered
NULL if something went wrong;

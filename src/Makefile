install:
	gcc `pkg-config --cflags libcurl` -DMYSQL_DYNAMIC_PLUGIN -Wall -fpic -I/usr/include/mysql -I. -shared libmsqlcurl.c -o ${LIBPATH}/libmsqlcurl.so `pkg-config --libs libcurl`

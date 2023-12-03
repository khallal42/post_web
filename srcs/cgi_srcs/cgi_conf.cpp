#include "../../incs/cgi_conf/cgi_conf.hpp"

Cgi_conf::Cgi_conf()
{
    cgi_initializer();
}

Cgi_conf::~Cgi_conf()
{
}

Cgi_conf::cgi_initializer()
{
    cgi_id = -1;
    // path = "";
    char *_path = getcwd();
    
    cgi_env_seter();
}

/*
AUTH_TYPE=Basic
CONTENT_LENGTH=5188
CONTENT_TYPE=multipart/form-data; boundary=----WebKitFormBoundarySinPzHAITv2F216B
DOCUMENT_ROOT=./
GATEWAY_INTERFACE=CGI/1.1
HTTP_COOKIE=1=1; 2=2; user=hello
PATH_INFO=
PATH_TRANSLATED=.//
QUERY_STRING=
REDIRECT_STATUS=200
REMOTE_ADDR=127.0.0.1:8002
REQUEST_METHOD=POST
REQUEST_URI=/cgi-bin/upload.py
SCRIPT_FILENAME=upload.py
SCRIPT_NAME=cgi-bin/upload.py
SERVER_NAME=127.0.0.1
SERVER_PORT=8080
SERVER_PROTOCOL=HTTP/1.1
SERVER_SOFTWARE=INFINITY
*/

/*
AUTH_TYPE=Basic
CONTENT_LENGTH=
CONTENT_TYPE=
DOCUMENT_ROOT=./
GATEWAY_INTERFACE=CGI/1.1
HTTP_COOKIE=1=1; 2=2; SID=ff7896505c3ee175444a59be5e4fd1db7aea7da3
PATH_INFO=
PATH_TRANSLATED=.//
QUERY_STRING=
REDIRECT_STATUS=200
REMOTE_ADDR=127.0.0.1:8002
REQUEST_METHOD=GET
REQUEST_URI=/cgi-bin/acc.py
SCRIPT_FILENAME=acc.py
SCRIPT_NAME=cgi-bin/acc.py
SERVER_NAME=127.0.0.1
SERVER_PORT=8080
SERVER_PROTOCOL=HTTP/1.1
SERVER_SOFTWARE=INFINITY
*/

Cgi_conf::cgi_env_seter()//Request &oRequest)
{
    if (method == "POST")// post method
    {
        this->["CONTENT_TYPE"] = ;
        this->["CONTENT_LENGTH"] = ;
    }
    this->_env["GATEWAY_INTERFACE"] = "CGI/1.1";
    this->_env["SERVER_NAME"] = ;
    this->_env["SERVER_PORT"] = ;
    this->_env["REQUEST_METHOD"] = ;
    this->_env["REQUEST_URI"] = ;
    this->_env["SCRIPT_NAME"] = ;
    this->_env["SCRIPT_FILENAME"] = ;
    this->_env["PATH_INFO"] = ;
    this->_env["PATH_TRANSLATED"] = ;
    this->_env["SERVER_PROTOCOL"] = "HTTP/1.1";
    this->_env["REDIRECT_STATUS"] = ;
}

Cgi_conf::cgi_executer()
{
    
}

/*

GATEWAY_INTERFACE: The version of the CGI protocol. Typically set to "CGI/1.1".
SERVER_NAME: The hostname or IP address of the server.
SERVER_PORT: The port on which the server is listening (e.g., 80 for HTTP).
REQUEST_METHOD: The HTTP request method, such as "GET", "POST", etc.
SCRIPT_NAME: The virtual path to the script being executed.
SCRIPT_FILENAME: The filesystem path to the script being executed.
PATH_INFO: The path component of the URL following the script name.
PATH_TRANSLATED: The server's internal filesystem path after any alias and translation handling.
REQUEST_URI: The full original request URI.
SERVER_PROTOCOL: The version of the protocol the client used, typically "HTTP/1.1".
REDIRECT_STATUS: The HTTP status code returned to the client.

*/
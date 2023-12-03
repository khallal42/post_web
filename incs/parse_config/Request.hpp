#pragma once

#include <map>
#include <iostream>
#include <sstream>
#include <arpa/inet.h>
#include <algorithm>

class Request
{
    public :
        std::string method;
        std::string path;
        std::string http_version;
        std::string value;
        std::string key;
        std::string Port;
        std::string Host;
        std::map<std::string, std::string> request_head;
    public :
        Request();
        ~Request();
        void read_request(char b[]);
        uint16_t Get_port();
        in_addr_t Get_host();

};



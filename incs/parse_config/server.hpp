#pragma once

#include <vector>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <unistd.h>
#include <sys/epoll.h>
#include "conf_parser.hpp"
#include <cstring>
#include <fcntl.h>
#include <algorithm>
#include "Request.hpp"
#include "/nfs/homes/khallal/Desktop/webserv/multiserver/StatusCodes.hpp"
#include <sys/types.h>
#include <dirent.h>

#define MAX_EVN 1024

class server
{
    public:
        std::vector<int> soket_fd;
        std::vector<int> client_fd;
        std::vector<int> p;
        std::map<int, Request> hand;
        bool flag;
        char buff[1024];
        Conf_parser serv;
        StatusCodes s;
        std::string header;
        std::string body;
        std::ofstream k;
        ssize_t _read;
        int readsize;
        int readflag;
        int i = 0;
        int numR;
        int epoll_fd;
        int rest;

    public:
        server();
        void rest_bady(int fd, std::ofstream &file);
        void creat_servers();
        void RecDelete(const char *path,int fd);
        void bindAnd_ListenServers();
        void Request_handling(int fd);
        bool Read_Request(int fd);
        void Get_handling(int fd);
        void Post(int fd);
        std::ofstream& creat_file(int fd);
        void Delete_handling(int fd);
        std::string GetLocationPath(int fd);
        std::string check_portAndLocation(int fd);
        std::string get_path(int fd);
        ~server();
        class Filed_creatSocket : public std::exception
        {
        public:
            const char *what() const throw();
        };
        class Filed_epoll : public std::exception
        {
        public:
            const char *what() const throw();
        };
        class Filed_bind : public std::exception
        {
        public:
            const char *what() const throw();
        };
        class Filed_listen : public std::exception
        {
        public:
            const char *what() const throw();
        };
};

#include "../incs/parse_config/server.hpp"

void server::rest_bady(int fd, std::ofstream &k)
{
    (void)fd;
    //(void)k;

    size_t pos = body.find("\r\n");
    // std::cout << "pos--->" << pos << "=== body---->" << body << std::endl;
    if (pos != std::string::npos)
    {
        std::string kh = body.substr(0, pos);
        numR = strtoul(kh.c_str(), NULL, 16);
        std::cout << "Im here : " << numR << std::endl;
        _read = rest - pos - 2;
        if (numR != 0)
        {
            k.write(body.substr(pos + 2, _read).c_str(), _read);
        }
        numR -= _read;
        i += _read;
        body.clear();
    }
}

void server::Post(int fd)
{
     std::cout << "Calling Post  " << numR << std::endl;
    // bzero(buff, 1024);
    int flags = false;
    if(numR == 0)
        flags = true;
    std::string key = "Transfer-Encoding";
    std::map<std::string, std::string>::iterator it = hand[fd].request_head.lower_bound(key);
    if (it->first == key)
    {
        if (!k.is_open())
            creat_file(fd);
        if (it->second == "chunked\r\n")
        {
            if (!body.empty())
                rest_bady(fd, k);
            if (numR > 0 && numR > readsize)
            {
                _read = recv(fd, buff, readsize, 0);
                numR -= _read;
                k.write(buff, _read);
                flags = true;
            }
            else if (numR > 0 && numR <= readsize)
            {
                _read = recv(fd, buff, numR, 0);
                numR -= _read;
                k.write(buff, _read);
                flags = true;
            }
            if (numR == 0 && flags)
            {
                _read = recv(fd, buff, readsize, 0);
                std::cout << "|||||||||      " << _read << "          |||||||||||| "  << buff<< std::endl;
                std::string l;
                if(buff[0]== '\r' && buff[1] == '\n')
                    l.append(&buff[2], _read);
                else
                    l.append(buff, _read);
                int pos = l.find("\r\n");
                if (pos != std::string::npos)
                {
                    _read -= (pos + 4);
                    numR = strtoul(l.substr(0, pos).c_str(), NULL, 16);
                    std::cout << "##################   " << l.substr(0, pos).c_str() << std::endl;
                    if (numR == 0)
                    {
                        std::cout << "heeeeeeere   " << std::endl;
                        flags = false;
                    }
                    else
                    {
                        k.write(l.substr(pos + 2, _read).c_str(), _read);
                        numR -= _read;
                    }
                }
            }
            if (numR == 0 && !flags)
            {
                std::cout << "send\n"
                          << std::endl;
                send(fd, "HTTP/1.1 200 OK\r\n", 18, 0);
                epoll_ctl(epoll_fd, EPOLL_CTL_DEL, fd, 0);
                hand.erase(fd);
                close(fd);
                k.close();
                flag = false;
                readflag = true;
            }
        }
    }
}

std::ofstream &server::creat_file(int fd)
{
    std::string key = "Content-Type";
    std::map<std::string, std::string>::iterator it = hand[fd].request_head.lower_bound(key);
    // std::cout << "-----" << it->second << "-----";
    if (it->second == "text/plain\r" || it->second == "text/html\r" || it->second == "text/css\r" || it->second == "image/jpeg\r\n" || it->second == "application/javascript\r" || it->second == "video/mp4\r\n" || it->second == "application/xml\r" || it->second == "image/gif\r\n")
    {
        // std::cout << "khaaaallllaaaaaaaaaaaal\n";
        if (it->second == "text/plain\r")
            k.open("test.txt");
        else if (it->second == "text/html\r")
            k.open("html.html");
        else if (it->second == "text/css\r")
            k.open("style.css");
        else if (it->second == "application/javascript\r")
            k.open("script.js");
        else if (it->second == "video/mp4\r\n")
            k.open("vidio.mp4");
        else if (it->second == "application/xml\r")
            k.open("dat.xml");
        else if (it->second == "image/jpeg\r\n")
            k.open("image.jpeg");
        else if (it->second == "image/gif\r\n")
            k.open("image.gif");
        // {
        //     key = "Content-Length";
        //     std::map<std::string, std::string>::iterator it = hand[fd].request_head.lower_bound(key);
        //     size_t pos = it->second.find("\r\n\r\n");
        //     k << &it->second[pos + 4] << std::endl;
        // }
    }
    return (k);
}

//         if (numR > 0 && numR < readsize)
//         {
//             _read = recv(fd, buff, numR, 0);
//             i += _read;
//             numR -= _read;
//             std::cout << "numR        : " << numR << " " << i << std::endl;
//             //std::cout.write(buff, _read);
//             flags = true;
//         }
//         else if (numR > 0 && numR >= readsize)
//         {
//             _read = recv(fd, buff, readsize, 0);
//             i += _read;
//             k.write(buff, _read);
//             numR -= _read;
//             flags = true;
//         }
//         if (numR == 0 && flags)
//         {
//             i = 0;
//            // bzero(buff, 1024);
//             _read = recv(fd, buff, 1024, 0);
//             body.append(&buff[2], _read - 2);
//             // std::cout << "((((((((((((" << buff  << "))))))))))))" <<std::endl;
//             // std::cout << "|||||" << _read << " ||||| " << strlen(buff) << std::endl;
//             int pos = body.find("\r\n");
//             if (pos != std::string::npos)
//             {
//                 rest = 1022 - pos - 2;
//                 numR = strtoul(body.substr(0, pos).c_str(), NULL, 16);
//                 if (numR == 0)
//                 {
//                     std::cout << "heeere  " << body.substr(0, pos).c_str() << std::endl;
//                     flags = false;
//                 }
//                 else
//                 {
//                     k.write(body.substr(pos + 2, rest).c_str(), rest);
//                     numR -= rest;
//                     body.clear();
//                 }
//                 i += rest;
//             }
//         }
//         if (numR == 0 && !flags)
//         {
//             std::cout << "send\n"
//                       << std::endl;
//             send(fd, "HTTP/1.1 200 OK\r\n", 18, 0);
//             epoll_ctl(epoll_fd, EPOLL_CTL_DEL, fd, 0);
//             hand.erase(fd);
//             close(fd);
//             k.close();
//             flag = false;
//             readflag = true;
//         }

//         // std::cout << "Data : " << data  << std::endl;
//     }
// }
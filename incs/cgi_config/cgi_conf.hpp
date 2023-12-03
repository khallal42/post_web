#ifdef CGI_CONF_HPP
# define CGI_CONF_HPP

# include <map>

typedef std::map<std::string, str::string> map_storage;

// class Request;

class Cgi_conf
{
    private:
        map_storage _env;
        std::string path;
        pid_t cgi_id;
        int pout[2];
        int pin[2];

    public:
        Cgi_conf();
        ~Cgi_conf();

        cgi_initializer();
        cgi_env_seter();//Request &oRequest);
        cgi_executer();

};

#endif
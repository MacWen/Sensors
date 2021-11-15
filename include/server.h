class Server
{
public:
    Server();
    ~Server();
    virtual int run(const char* port);
};
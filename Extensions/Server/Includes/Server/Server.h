// Copyright(C) 2019 Sooyeon Kim, Gyeonguk Chae, Junyeong Park

#ifndef SERVER_SERVER_H
#define SERVER_SERVER_H

#include <asio.hpp>

#include <string_view>

class Server final
{
 public:
    Server(asio::io_context& ioContext, short port, std::size_t bufSize = 8096);
    ~Server();

    void Start();

 private:
    void readComplete(const asio::error_code& error, std::size_t size);

    void write(const std::string_view& data, std::size_t size);
    void writeComplete(const asio::error_code& error, std::size_t size);

    void reset();
    void read();

	void acceptComplete(const asio::error_code& error);

 private:
    asio::ip::tcp::socket socket_;
    asio::ip::tcp::acceptor acceptor_;

    char* buffer_;
    std::size_t bufSize_;
};

#endif  // SERVER_SERVER_H

// Copyright(C) 2019 Sooyeon Kim, Gyeonguk Chae, Junyeong Park

#ifndef SERVER_SERVER_H
#define SERVER_SERVER_H

#include <Server/Connection.h>

#include <asio.hpp>
#include <mutex>
#include <vector>

class Server final
{
 public:
    Server(asio::io_context& ioContext, short port);


 private:
	void start();
    void acceptComplete(const asio::error_code& error, Connection* conn);

 private:
    asio::io_context& ioContext_;
    asio::ip::tcp::acceptor acceptor_;
    std::atomic<int> connectCount_;
};

#endif  // SERVER_SERVER_H

// Copyright(C) 2019 Sooyeon Kim, Gyeonguk Chae, Junyeong Park

#include <Server/Server.h>

using asio::ip::tcp;

Server::Server(asio::io_context& ioContext, short port)
    : ioContext_(ioContext),
      acceptor_(ioContext, tcp::endpoint(tcp::v4(), port))
{
    start();
}

void Server::start()
{
    auto connection = std::make_shared<Connection>(ioContext_);

    acceptor_.async_accept(connection->Socket(),
                           [=](const asio::error_code& error) {
                               acceptComplete(error, connection);
                           });
}

void Server::acceptComplete(const asio::error_code& error,
                            Connection::Ptr conn)
{
    if (!error)
    {
        conn->Start(connectCount_.load());
        ++connectCount_;

		start();
	}
}

// Copyright(C) 2019 Sooyeon Kim, Gyeonguk Chae, Junyeong Park

#ifndef SERVER_CONNECTION_H
#define SERVER_CONNECTION_H

#include <asio.hpp>

#include <memory>
#include <string_view>

class Connection final
{
 public:
    using Ptr = std::shared_ptr<Connection>;

 public:
    Connection(asio::io_context& ioContext, std::size_t bufSize = 8096);
    ~Connection();

	void Start(int ID);

    int ConnectionID() const;
    asio::ip::tcp::socket& Socket();

    void Write(const std::string_view& data);

 private:
    void readComplete(const asio::error_code& error, std::size_t size);

    void write(const std::string_view& data, std::size_t size);
    void writeComplete(const asio::error_code& error, std::size_t size);

    void reset();
    void read();

 private:
    int id_ = -1;
    asio::ip::tcp::socket socket_;

    char* buffer_;
    std::size_t bufSize_;
};

#endif  // SERVER_CONNECTION_H

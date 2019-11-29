// Copyright(C) 2019 Sooyeon Kim, Gyeonguk Chae, Junyeong Park

#include <Server/Connection.h>
#include <Server/GameManager.h>

#include <memory.h>
#include <spdlog/spdlog.h>

using asio::ip::tcp;

Connection::Connection(asio::io_context& ioContext, std::size_t bufSize)
    : socket_(ioContext), buffer_(new char[bufSize]), bufSize_(bufSize)
{
    // Do nothing
}

Connection::~Connection()
{
    if (buffer_)
    {
        delete buffer_;
    }
}

void Connection::Start(int ID)
{
    id_ = ID;

    GameManager::Get().JoinGame(*this);
}

int Connection::ConnectionID() const
{
    return id_;
}

tcp::socket& Connection::Socket()
{
    return socket_;
}

void Connection::Write(const std::string_view& data)
{
    write(data, data.size());
}

void Connection::read()
{
    socket_.async_read_some(asio::buffer(buffer_, bufSize_),
                            [this](asio::error_code error, std::size_t size) {
                                readComplete(error, size);
                            });
}

void Connection::readComplete(const asio::error_code& error, std::size_t size)
{
    if (error)
    {
        if (error == asio::error::eof)
        {
            spdlog::info("[Connection {}] Client disconnected.", id_);
        }
        else
        {
            spdlog::error("[Connection {}] Read error {}", id_,
                          error.message());
        }

        reset();
    }
    else
    {
        std::string_view sv(buffer_, size);

        spdlog::info(sv);

        read();
    }
}

void Connection::write(const asio::string_view& data, std::size_t size)
{
    asio::async_write(socket_, asio::buffer(data, bufSize_),
                      [this](asio::error_code error, std::size_t size) {
                          writeComplete(error, size);
                      });
}

void Connection::writeComplete(const asio::error_code&, std::size_t)
{
    // Do nothing
}

void Connection::reset()
{
    if (socket_.is_open())
    {
        socket_.close();
    }
}

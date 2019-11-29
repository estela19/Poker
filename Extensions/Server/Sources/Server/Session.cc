// Copyright(C) 2019 Sooyeon Kim, Gyeonguk Chae, Junyeong Park

#include <Server/Server.h>

#include <memory.h>
#include <spdlog/spdlog.h>

using asio::ip::tcp;

Session::Session(asio::io_context& ioContext, short port, std::size_t bufSize)
    : socket_(ioContext),
      acceptor_(ioContext, tcp::endpoint(tcp::v4(), port)),
      buffer_(new char[bufSize]),
      bufSize_(bufSize)
{
    // Do nothing
}

Session::~Session()
{
    if (buffer_)
    {
        delete buffer_;
    }
}

void Session::Start()
{
    acceptor_.async_accept(
        socket_, [this](asio::error_code error) { acceptComplete(error); });
}

void Session::Write(const std::string_view& data)
{
    write(data, data.size());
}

void Session::acceptComplete(const asio::error_code& error)
{
    if (!error)
    {
        read();
    }
    else
    {
        spdlog::error("Cannot accept");
    }
}

void Session::read()
{
    socket_.async_read_some(asio::buffer(buffer_, bufSize_),
                            [this](asio::error_code error, std::size_t size) {
                                readComplete(error, size);
                            });
}

void Session::readComplete(const asio::error_code& error, std::size_t size)
{
    if (error)
    {
        if (error == asio::error::eof)
        {
            spdlog::error("Client disconnected.");
        }
        else
        {
            spdlog::error("Read error {}", error.message());
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

void Session::write(const asio::string_view& data, std::size_t size)
{
    asio::async_write(socket_, asio::buffer(data, bufSize_),
                      [this](asio::error_code error, std::size_t size) {
                          writeComplete(error, size);
                      });
}

void Session::writeComplete(const asio::error_code&, std::size_t)
{
    // Do nothing
}

void Session::reset()
{
    if (socket_.is_open())
    {
        socket_.close();
    }

    Start();
}

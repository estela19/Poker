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
        delete[] buffer_;
    }
}

void Connection::Start(int ID)
{
    id_ = ID;

    GameManager::Get().JoinGame(*this);
}

void Connection::Stop()
{
    reset();
}

std::string Connection::Read()
{
    asio::error_code error;
    auto length = socket_.read_some(asio::buffer(buffer_, bufSize_), error);

    if (!error)
    {
        return std::string(buffer_, length);
	}
    
	return "";
}

void Connection::SetResetCallback(std::function<void()> callback)
{
    resetCallback_ = std::move(callback);
}

std::future<std::string> Connection::GetFuture()
{
    return recvPromise_.get_future();
}

int Connection::ConnectionID() const
{
    return id_;
}

tcp::socket& Connection::Socket()
{
    return socket_;
}

std::string Connection::Address() const
{
    return socket_.remote_endpoint().address().to_string();
}

void Connection::Write(const std::string& data)
{
    write(data);
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

            GameManager::Get().RemovePlayerFromGame(player_);
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
        std::string s(buffer_, size);
        recvPromise_.set_value(s);

        read();
    }
}

void Connection::write(const std::string& data)
{
    asio::async_write(socket_, asio::buffer(data),
                      [](asio::error_code error, std::size_t size) {});
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

        if (resetCallback_)
            resetCallback_();
    }
}

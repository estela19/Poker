#include <Server/Server.h>

#include <asio.hpp>

int main()
{
    asio::io_context ioContext;
    Server server(ioContext, 8080);
    server.Start();

	ioContext.run();
}

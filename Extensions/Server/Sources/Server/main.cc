#include <Server/Server.h>

#include <spdlog/spdlog.h>
#include <asio.hpp>

int main()
{
    try
    {
        asio::io_context ioContext;

        Server server(ioContext, 5252);
        ioContext.run();
    }
    catch (std::exception& e)
    {
        spdlog::error(e.what());
	}
}

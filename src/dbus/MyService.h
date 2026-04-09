#include <sdbus-c++/sdbus-c++.h>
#include "server-adaptor.h"


struct ProcessInfo {
    int pid;                // PID
    std::string user;       // USER
    double cpu_percent;     // %CPU
    double mem_percent;     // %MEM
    std::uint64_t rss;      // RSS (bytes)
    char state;             // STATE (R, S, D, Z, T, etc.)
    std::uint64_t time;     // TIME (CPU time in milliseconds or ticks)
    std::string command;    // COMMAND
};

class MyService final : public sdbus::AdaptorInterfaces<com::example::Interface_adaptor>
{
public:
    MyService(sdbus::IConnection& connection)
        : AdaptorInterfaces(connection, "/com/example/MyObject")
    {
        registerAdaptor();
    }

    ~MyService()
    {
        unregisterAdaptor();
    }

    void sendProcess(const ProcessInfo& p)
    {
        using ProcessStruct = sdbus::Struct<
        int32_t,
        std::string,
        double,
        double,
        uint64_t,
        uint8_t,
        uint64_t,
        std::string
    >;

    ProcessStruct process{
        p.pid,
        p.user,
        p.cpu_percent,
        p.mem_percent,
        p.rss,
        static_cast<uint8_t>(p.state),
        p.time,
        p.command
    };

    emitProcessUpdated(process);
    }

    // Implement methods from XML (if any)
};
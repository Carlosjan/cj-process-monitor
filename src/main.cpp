#include <iostream>
#include <memory>
#include <sdbus-c++/sdbus-c++.h>
#include <thread>
#include <string>
#include <cstdint>

#include "dbus/MyService.h"


std::atomic<bool> is_running { true };

/*struct ProcessInfo {
    int pid;                // PID
    std::string user;       // USER
    double cpu_percent;     // %CPU
    double mem_percent;     // %MEM
    std::uint64_t rss;      // RSS (bytes)
    char state;             // STATE (R, S, D, Z, T, etc.)
    std::uint64_t time;     // TIME (CPU time in milliseconds or ticks)
    std::string command;    // COMMAND
};*/

using ProcessTuple = std::tuple<
    int32_t,        // pid
    std::string,    // user
    double,         // cpu
    double,         // mem
    uint64_t,       // rss
    uint8_t,        // state
    uint64_t,       // time
    std::string     // command
>;

ProcessTuple toTuple(const ProcessInfo& p)
{
    return {
        p.pid,
        p.user,
        p.cpu_percent,
        p.mem_percent,
        p.rss,
        static_cast<uint8_t>(p.state),
        p.time,
        p.command
    };
}

int main() {

    ProcessInfo processTest = { 123, "Carlos", 12.0, 12.0, 34, 12, 34,"Test"};

    auto connection = sdbus::createSessionBusConnection();
    connection->requestName("com.example.MyService");

    MyService service(*connection);

    std::cout << "D-Bus service running..." << std::endl;

    connection->enterEventLoopAsync();

    std::jthread worker([&] {
        while (is_running) {
            service.sendProcess(processTest);

            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    });

    

    char selection = 0;
    while (selection != 'q') {

        std::cout << "enter q to quit program\n";
        std::cin >> selection;
        if (selection == 'q') {
            is_running = false;
        }
    }

    connection->leaveEventLoop();

    return 0;
}

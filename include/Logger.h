//
// Created by jon on 11/10/26.
//

#ifndef SLCOMPUTE_LOGGER_H
#define SLCOMPUTE_LOGGER_H

#include <string>
#include <vector>
#include <mutex>

#ifndef LOG_LOC
#define LOG_POS(loc) (LOG_LOC + "::" + loc)
#endif

#ifndef SL_ASSERT
#define SL_ASSERT(condition, msg) \
    if (!(condition)) Logger::LogFatal(LOG_LOC, msg); \
    assert((condition));
#endif

class Logger {
public:
    enum class Level {
        Fatal = 4,
        Error = 3,
        Warning = 2,
        Info = 1,
        Debug = 0
    };

    struct LogEntry {
    public:
        Level log_level;
        std::string source;
        std::string message;
    };


    static void Log(Level level, std::string source, const std::string message);
    static void Log(std::string source, const std::string format, ...); // LogInfo

    static void LogFatal(std::string source, const std::string format, ...);
    static void LogError(std::string source, const std::string format, ...);
    static void LogWarning(std::string source, const std::string format, ...);
    static void LogInfo(std::string source, const std::string format, ...);
    static void LogDebug(std::string source, const std::string format, ...);

    static std::vector<LogEntry> GetLogEntries();

    static void Set_Direct(bool value) { /*m_direct = value;*/ }
    static void Set_Crashing_Errors(bool value) { m_crash_on_error = value; }
    static void Set_Crashing_Warnings(bool value) { m_crash_on_warning = value; }

    static void Update(bool force = false);

private:

    static Logger m_logger;
    inline static bool m_direct{true};
    inline static bool m_crash_on_error{ false };
    inline static bool m_crash_on_warning{ false };
    std::vector<LogEntry> m_entries;

    static std::mutex m_lock;

    //std::vector<LogEntry> m_entries_processing;
};



#endif //SLCOMPUTE_LOGGER_H

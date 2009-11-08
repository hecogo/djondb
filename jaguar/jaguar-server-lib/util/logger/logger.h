#include <string>

using namespace std;

class Logger {
    private:
        bool m_debug;
        bool m_info;
        bool m_warn;
        const char* m_clazz;

    public:
        Logger(const type_info& clazz);
        bool isDebug();
        bool isInfo();
        bool isWarn();
        void debug(string message);
        void error(string error);
        void info(string message);
        void warn(string warn);
};

Logger* getLogger(const type_info& clazz);

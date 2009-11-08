#include "./logger.h"
#include <iostream>
#define PRINT(TYPE, CLAZZ, MESSAGE) \
    cout << TYPE << ": " << CLAZZ << ": " << MESSAGE << endl;

Logger* getLogger(const type_info& clazz) {
    Logger* logger = new Logger(clazz);

    return logger;
}

Logger::Logger(const type_info& clazz) {
    m_clazz = clazz.name();
    m_debug = true;
    m_info = true;
    m_warn = true;
}

void Logger::debug(string message) {
    PRINT("DEBUG", m_clazz, message);
}


void Logger::info(string message) {
    PRINT("INFO", m_clazz, message);
}


void Logger::warn(string message) {
    PRINT("WARN", m_clazz, message);
}


void Logger::error(string message) {
    cout << m_clazz << ":" << message << endl;
}

bool Logger::isDebug() {
    return m_debug;
}

bool Logger::isInfo() {
    return m_info;
}

bool Logger::isWarn() {
    return m_warn;
}

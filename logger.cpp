#include "Logger.h"
#include <QDebug>

std::shared_ptr<spdlog::logger> Logger::logger = nullptr;

void Logger::init() {
    try {
        logger = spdlog::basic_logger_mt("file_logger", "WMSIntegrator.log", true);
        spdlog::set_default_logger(logger);
        spdlog::set_level(spdlog::level::debug);
        spdlog::info("Logger initialized.");
    } catch (const spdlog::spdlog_ex &ex) {
        qWarning() << "Kon logbestand niet aanmaken: " << ex.what();
    }
}

std::shared_ptr<spdlog::logger> Logger::getLogger() {
    if (!logger) {
        init();
    }
    return logger;
}

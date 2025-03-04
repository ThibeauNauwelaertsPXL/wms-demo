#include "Logger.h"

std::shared_ptr<spdlog::logger> Logger::logger = nullptr;

void Logger::init() {
    try {
        logger = spdlog::basic_logger_mt("file_logger", "WMSIntegrator.log", true);

        logger->set_level(spdlog::level::debug);

        logger->flush_on(spdlog::level::info);

        logger->info("Logger initialized.");
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

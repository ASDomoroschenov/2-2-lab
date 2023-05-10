#ifndef LOGGER_CONCRETE_H
#define LOGGER_CONCRETE_H

#include "../logger/logger.h"
#include <iostream>

class logger_concrete final : public logger
{
private:
	std::map<std::string, std::pair<std::ofstream*, severity>> _streams_log;
public:
	logger_concrete(
        std::vector<std::pair<std::string, severity>> const& streams);

	logger* log(const std::string& target, severity level) override;

	~logger_concrete() override;
};

#endif
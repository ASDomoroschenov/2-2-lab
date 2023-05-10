#ifndef JSON_CONCRETE_H
#define JSON_CONCRETE_H

#include <fstream>
#include "../logger/logger.h"
#include "../logger_concrete/logger_concrete.h"
#include "../json/json.h"

class json_concrete final : public json
{
private:
    std::vector<std::pair<std::string, logger::severity>> _streams;
public:
    json_concrete(const std::string&);

    logger *build() const override;
};

#endif //JSON_CONCRETE_H

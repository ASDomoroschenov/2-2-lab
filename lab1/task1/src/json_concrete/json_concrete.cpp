#include "json_concrete.h"

json_concrete::json_concrete(const std::string &path)
{
    std::map<std::string, logger::severity> _configuration;
    nlohmann::json obj_json;
    std::fstream json_file;

    json_file.open(path);
    json_file >> obj_json;
    json_file.close();

    for (int i = 0; i < obj_json["configs"].size(); i++)
    {
        _configuration[obj_json["configs"][i]["target"]] = obj_json["configs"][i]["severity"];
    }

    for (auto &item: _configuration)
    {
        _streams.push_back(std::make_pair(item.first, item.second));
    }
}

logger* json_concrete::build() const
{
    return new logger_concrete(_streams);
}

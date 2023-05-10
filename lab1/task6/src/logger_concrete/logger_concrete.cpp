#include "logger_concrete.h"

std::string current_date_time()
{
    std::time_t seconds = std::time(nullptr);
    std::tm* now = std::localtime(&seconds);
 
    char buffer[BUFSIZ];
    strftime(buffer, sizeof(buffer), "[%m/%d/%Y %X]", now);
    
	return buffer;
}

std::string enum_to_string(
	logger::severity level)
{
	std::string enum_string[] = {
		"[TRACE]",
		"[DEBUG]",
		"[INFORMATION]",
		"[WARNING]",
		"[ERROR]",
		"[CRITICAL]"
	};
	
	return enum_string[static_cast<int>(level)];
}

logger_concrete::logger_concrete(
    std::vector<std::pair<std::string, severity>> const& streams)
{
    std::ofstream *stream = nullptr;

    for (int i = 0; i < streams.size(); i++)
    {
        auto global_stream_iter = _collection_streams.find(streams[i].first);

        if (global_stream_iter == _collection_streams.end())
        {
            if (streams[i].first != "console")
            {
                stream = new std::ofstream(streams[i].first, std::ios::out);	
            }
            else
            {
                stream = nullptr;
            }
            
            _collection_streams[streams[i].first] = make_pair(stream, 1);
        } 
        else
        {
            stream = _collection_streams[streams[i].first].first;
            _collection_streams[streams[i].first].second++;
        }

        auto local_stream_iter = _streams_log.find(streams[i].first);

        if (local_stream_iter == _streams_log.end())
        {
            _streams_log[streams[i].first] = make_pair(stream, streams[i].second);
        }
        else
        {
            local_stream_iter->second.second = streams[i].second;
        }
    }
    
}

logger* logger_concrete::log(
    const std::string& target,
    severity level)
{
    for (auto& item: _streams_log)
    {
        if (item.second.second == level)
        {
            if (item.second.first == nullptr)
            {
                std::cout << current_date_time() << " " << enum_to_string(level) << " " << target << std::endl;
            }
            else
            {
                *item.second.first << current_date_time() << " " << enum_to_string(level) << " " << target << std::endl;
            }
        }
    }

    return this;
}

logger_concrete::~logger_concrete()
{
    for (auto& item: _streams_log)
    {
        auto& value = _collection_streams[item.first];
        value.second--;

        if (value.second == 0)
        {
            if (value.first != nullptr)
            {
                if (value.first->is_open())
                {
                    value.first->close();
                }

                delete value.first;
            }
        }
    }
}
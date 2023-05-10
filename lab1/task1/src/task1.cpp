#include <iostream>
#include "logger/logger.h"
#include "builder/builder.h"
#include "builder_concrete/builder_concrete.h"
#include "logger_concrete/logger_concrete.h"
#include "json/json.h"
#include "json_concrete/json_concrete.h"

int main()
{
	json *logger_json = new json_concrete("../build/json/config.json");
	logger *log_1 = logger_json->build();

	log_1->log("123", logger::severity::DEBUG)
		 ->log("hello world", logger::severity::DEBUG)
		 ->log("suka", logger::severity::CRITICAL);

	delete logger_json;
	delete log_1;

	return 0;
}
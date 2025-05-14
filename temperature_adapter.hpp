#pragma once

#include <descrip.h>
#include <exception>
#include <stdlib.h>
#include <string>

#include <nlohmann/json>
#include <json-schema.hpp>

using nlohmann::json;
using nlohmann::json_schema::json_validator;

extern "C" double CONVERT_TEMPERATURE(struct  dsc$descriptor *in, struct  dsc$descriptor *out, double *tmp);

// This example uses 32bit descriptors as per fortran compiler default.
//
struct  dsc$descriptor make_descriptor(char *input)
{
  struct  dsc$descriptor result;
  result.dsc$a_pointer = (char *) _malloc32(strlen(input)+1);    // dsc$descriptor requires a 32bit pointer.
  strcpy(result.dsc$a_pointer, input);
  result.dsc$w_length = strlen(input);
  result.dsc$b_class =  DSC$K_CLASS_S;
  result.dsc$b_dtype =  DSC$K_DTYPE_T;
  return result;
}

class TemperatureAdapter
{
public:
    TemperatureAdapter();
    ~TemperatureAdapter() = default;
    int process_request(const std::string& req, std::string& rsp);
private:
    json_validator validator;
    static json temperature_schema = R"(
        "$schema": "http://json-schema.org/draft-07/schema#",
        "title": "TemperatureRequestSchema",
        "properties": {
            "in_scale":
            {
                "description": "input scale",
                "type": "string",
                "enum": ["FAHRENHEIT", "CELSIUS", "KELVIN"]
            },
            "out_scale":
            {
                "description": "output scale",
                "type": "string",
                "enum": ["FAHRENHEIT", "CELSIUS", "KELVIN"]
            },
            "in_temperature":
            {
                "description": "temperature value",
                "type": "number"
            }
        },
        "required": ["in_scale", "out_scale", "in_temperature"],
        "type": "object"
    })"_json;
}
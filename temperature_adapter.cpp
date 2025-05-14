/*******************************************************************/
/*                                                                 */
/* Function : temperature_adapter                                  */
/*      Example Adapter Pattern Function for Legacy Code Library   */
/*      Translates json input into legacy function call parameters */
/*      calls the legacy function and builds json response.        */
/*                                                                 */
/* VMS Software Incorporated                                       */
/* Author :     Alex Cornford                                      */
/* Date   :     27 Jan 2025                                        */
/*                                                                 */
/* Requires https://json.nlohmann.me/                              */
/*          https://github.com/pboettch/json-schema-validator      */
/*                                                                 */
/*******************************************************************/

#include "temperature_adapter.hpp"


TemperatureAdapter::TemperatureAdapter()
{
    try
    {
        validator.set_root_schema(temperature_schema);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        // TO DO. can we handle invalid construction error better ?
        exit(EXIT_FAILURE);
    }
    
}

int TemperatureAdapter::process_request(const std::string& req_json, std::string& rsp_json)
{
    json params, reply;
    try
    {
       params = json::parse(req_json);
    }
    catch (json::exception e)
    {
        std::stringstream error_text << "json parse error " << e.what();
        reply["error_text"] = error_text.str();
        rsp_json = reply.dump();
        return EXIT_FAILURE;
    }

    try
    {
        validator.validate(params);
    }
    catch(const std::exception& e)
    {
        std::stringstream  error_text << "temperature schema error " << e.what();
        reply["error_text"] = error_text.str();
        rsp_json = reply.dump();
        return EXIT_FAILURE;
    }
    

    std::string in_scale = params["in_scale"];
    std::string out_scale = params["out_scale"];
    double in_temp = params["in_temperature"];

    struct dsc$descriptor in_desc = make_descriptor((char *) in_scale.c_str());
    struct dsc$descriptor out_desc = make_descriptor((char *) out_scale.c_str());
    double result = CONVERT_TEMPERATURE(&in_desc, &out_desc, &in_temp);
    if (result < -500)
    {
        // conversion error 
        reply["error_text"] = "library error";
        rsp_json = reply.dump();
        return EXIT_FAILURE;
    }

    reply["scale"] = out_scale;
    reply["temperature"] =  result;
    rsp_json = reply.dump();

    return EXIT_SUCCESS;
}

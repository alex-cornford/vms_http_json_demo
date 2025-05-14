//
//  temp_rest_server.cpp
//  REST Server software to provide temperature conversions
//
//  VMS Software Incorporated
//  Author : Alex Cornford
//  Date   : 27-Jan-2025
//
//  Requires https://github.com/yhirose/cpp-httplib
//

#define CPPHTTPLIB_OPENSSL_SUPPORT
#include <httplib.h>
using namespace httplib;
#include "temperature_adapter.hpp"
#include <stdio>

// TO DO. Enable SSL with valid certificate
// #define CERTIFICATE_FILE  certificate_file_path_
// #define KEY_FILE key_file_path

int main(void)
{
  //SSLServer svr(CERTIFICATE_FILE, KEY_FILE);
  Server svr;


  std::cout << "Starting server " << std::endl;
  TemperatureAdapter temperature_adapter;
  svr.Post("/convert_temperature", [&](const Request & req, Response &res)
  {
    std::string answer;
    int status = temperature_adapter.process_request(req.body, answer);
    // TO DO handle EXIT_FAILURE
    res.status = 200;
    res.body = answer;
    res.set_content(answer, "text/json");
  });

  svr.listen("0.0.0.0", 8080);
}

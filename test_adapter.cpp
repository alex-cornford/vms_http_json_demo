/*
 * Test stub for temperature_adapter
*/
#include <iostream>
#include <string>

extern "C" double CONVERT_TEMPERATURE(struct  dsc$descriptor *in, struct  dsc$descriptor *out, double *tmp);
int temperature_adapter(const std::string& req_json, std::string& rsp_json);

int main()
{
    std::string jsn,result;
    std::cout << "Enter json : ";
    std::cin >> jsn;
    int status = temperature_adapter(jsn, result);
    std::cout << std::endl << std::endl << "Status is " << (status == 0 ? "Success" : "Failure") << std::endl;
    std::cout << std::endl << result << std::endl;
}

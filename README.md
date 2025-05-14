This code was shown at OpenVMS bootcamp in Malmo on 14th MAy 2025. It is a proof of concept webserver using the OpenVMS Clang C++ compiler, only compiled and tested om x86 OpenVMS

License : The Unlicense, copy and modify as you want. Provided as is, with no warranty.

TO DO. Add a build.com to help compilation.

json-schema-validator can be compiled using the clang compiler on x86 OpenVMS. I put the object files in a library and linked them in. Add the other library header files in appropriate directories and build.
all c++ files must be compiled using std=c++11

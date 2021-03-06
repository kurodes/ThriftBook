// Apache Thrift Binary Protocol Struct Writer in C++

#include <thrift/transport/TSimpleFileTransport.h>
#include <thrift/protocol/TProtocol.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <memory>
#include <iostream>
#include <string>

using namespace apache::thrift::transport;
using namespace apache::thrift::protocol;
using std::make_shared;

struct Trade {
   char symbol [16];
   double price;
   int size;
};

int main()
{
    auto path_name = "data";
    auto trans = make_shared<TSimpleFileTransport>(path_name, false, true);
    auto proto = make_shared<TBinaryProtocol>(trans);

    Trade trade{"F", 13.10, 2500};
    int i = 0;
    i += proto->writeStructBegin("Trade");

    i += proto->writeFieldBegin("symbol ", T_STRING, 1);
    i += proto->writeString(std::string(trade.symbol));
    i += proto->writeFieldEnd();

    i += proto->writeFieldBegin("price ", T_DOUBLE, 2);
    i += proto->writeDouble(trade.price);
    i += proto->writeFieldEnd();

    i += proto->writeFieldBegin("size ", T_I32, 3);
    i += proto->writeI32(trade.size);
    i += proto->writeFieldEnd();

    i += proto->writeFieldStop();
    i += proto->writeStructEnd();

    std::cout << "Wrote " << i << " bytes to " << path_name << std::endl;
}


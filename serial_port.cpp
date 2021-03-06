#include <unistd.h>
#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/asio/serial_port.hpp>
#include <boost/asio/serial_port_base.hpp>
#include <boost/system/error_code.hpp>
#include <boost/system/system_error.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>

using namespace std;
using namespace boost::asio;
class serial{
  char read_msg_[128];
  boost::asio::io_service ios;
  boost::asio::serial_port port;
private:
  void handler(const boost::system::error_code& error,size_t bytes_transferred)
  {
    read_msg_[bytes_transferred]=0;
    cout<<bytes_transferred<<" bytes:"<<read_msg_<<endl;
    read_some();
  }
  void read_some()
  {
    port.async_read_some(boost::asio::buffer(read_msg_,sizeof(read_msg_)),
			 boost::bind(&serial::handler,this,
				     boost::asio::placeholders::error,
				     boost::asio::placeholders::bytes_transferred));
  }

public:
  serial(const char* dev_name):ios(),port(ios,dev_name)
  {
    port.set_option(boost::asio::serial_port_base::baud_rate(9600));
    port.set_option(boost::asio::serial_port_base::character_size(8));
    port.set_option(boost::asio::serial_port_base::stop_bits(serial_port_base::stop_bits::one));
    port.set_option(boost::asio::serial_port_base::parity(serial_port_base::parity::none));
    port.set_option(boost::asio::serial_port_base::flow_control(serial_port_base::flow_control::none));

    read_some();
    boost::thread td(boost::bind(&boost::asio::io_service::run,&ios));
  }
};

int main(int argc,char* argv[])
{
  serial s(argv[1]);
  sleep(10);
  return 0;
}

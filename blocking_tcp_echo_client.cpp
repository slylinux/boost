#include <cstdlib>
#include <cstring>
#include <stdio.h>
#include <iostream>
#include <boost/asio.hpp>
using boost::asio::ip::tcp;
using boost::system::error_code;

enum { max_length = 1024 };

int main(int argc, char* argv[])
{
  try
    {
      if (argc != 3)
	{
	  std::cerr << "Usage: blocking_tcp_echo_client <host> <port>\n";
	  return 1;
	}

      boost::asio::io_service io_service;

      tcp::resolver resolver(io_service);
      tcp::resolver::query query(tcp::v4(), argv[1], argv[2]);
      tcp::resolver::iterator iterator = resolver.resolve(query);
      tcp::endpoint ep=*iterator;
      using namespace std; 
      std::cout <<ep<<std::endl;
      //boost::asio::connect(s, iterator);
      while(1){
      using namespace std; 
      std::cout << "Enter message: ";
      boost::system::error_code en;
      tcp::socket s(io_service);
      s.connect(*iterator,en);
      char request[max_length];
      std::cin.getline(request, max_length);
      size_t request_length = strlen(request);
      boost::asio::write(s, boost::asio::buffer(request, request_length));

      char reply[max_length];
      size_t reply_length = boost::asio::read(s,
					      boost::asio::buffer(reply, 64));
      std::cout << "Reply is: ";
      std::cout.write(reply, reply_length);
      std::cout << "\n";
      sleep(1);
      }
    }
  catch (std::exception& e)
    {
      std::cerr << "Exception: " << e.what() << "\n";
    }

  return 0;
}

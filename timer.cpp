#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
using namespace std;

void print(const boost::system::error_code&,boost::asio::deadline_timer* t,int* count)
{
  t->expires_at(t->expires_at()+boost::posix_time::seconds(2));
  t->async_wait(boost::bind(print,boost::asio::placeholders::error,t,count));
}

int main(int argc,char** argv)
{
  int count=0;
  boost::asio::io_service ios;
  boost::asio::deadline_timer timer(ios,boost::posix_time::seconds(3));
  timer.async_wait(boost::bind(print,boost::asio::placeholders::error,&timer,&count));
  ios.run();
  return 0;
}

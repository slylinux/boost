#include <string>
#include <iostream>
#include <boost/shared_ptr.hpp>

using namespace std;

class impl
{
public:
  ~impl(){std::cout<<"destorying impl"<<std::endl;}
  void do_something(){std::cout<<"did someting\n";}
};

void test()
{
  boost::shared_ptr<impl> sp1 (new impl);
  std::cout<<"the smaple now has "<<sp1.use_count()<<" references\n";
  sp1->do_something();
  boost::shared_ptr<impl> sp2=sp1;
  std::cout<<"the smaple now has "<<sp2.use_count()<<" references\n";
  sp1.reset();
  std::cout<<"after reset sp1,the smaple now has "<<sp2.use_count()<<" references\n";
  sp2.reset();
  std::cout<<"after reset sp2\n";

}

int main(int argc,char** argv)
{
  test();
  return 0;
}

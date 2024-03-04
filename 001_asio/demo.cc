//
// Created by jasonkay on 2024/3/4.
//

#include <iostream>
#include <boost/asio.hpp>

void timer_handler(const boost::system::error_code &code) {
  if (!code) {
    std::cout << "time out" << std::endl;
  }
}

int main() {
  boost::asio::io_context ioc;

  boost::asio::steady_timer async_timer(ioc, boost::asio::chrono::seconds(5));
  async_timer.async_wait(timer_handler);

  ioc.run();

  return 0;
}

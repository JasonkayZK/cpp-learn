//
// Created by JasonkayZK on 2022.06.21.
//

#ifndef AOTPP_DEMO_HELLOHANDLER_H
#define AOTPP_DEMO_HELLOHANDLER_H

#include "oatpp/web/server/HttpRequestHandler.hpp"

// 自定义请求处理程序
class Handler : public oatpp::web::server::HttpRequestHandler {
public:
  // 处理传入的请求，并返回响应
  std::shared_ptr<OutgoingResponse>
  handle(const std::shared_ptr<IncomingRequest> &request) override {
    return ResponseFactory::createResponse(Status::CODE_200, "Hello, World!");
  }
};

#endif // AOTPP_DEMO_HELLOHANDLER_H

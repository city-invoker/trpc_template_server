//
//
// Tencent is pleased to support the open source community by making tRPC available.
//
// Copyright (C) 2023 THL A29 Limited, a Tencent company.
// All rights reserved.
//
// If you have downloaded a copy of the tRPC source code from Tencent,
// please note that tRPC source code is licensed under the  Apache 2.0 License,
// A copy of the Apache 2.0 License is included in this file.
//
// Copyright 2023-11-08 skylanwei 

#include <memory>
#include <string>

#include "fmt/format.h"

#include "trpc/common/trpc_app.h"

#include "examples/helloworld/greeter_service.h"

namespace ssz {

class SszWeiXinOpenServer : public ::trpc::TrpcApp {
 public:
  int Initialize() override {
    const auto& config = ::trpc::TrpcConfig::GetInstance()->GetServerConfig();
    // Set the service name, which must be the same as the value of the `/server/service/name` configuration item
    // in the configuration file, otherwise the framework cannot receive requests normally.
    std::string service_name = fmt::format("{}.{}.{}.{}", "trpc", config.app, config.server, "Greeter");
    TRPC_FMT_INFO("service name:{}", service_name);

    RegisterService(service_name, std::make_shared<GreeterServiceImpl>());

    return 0;
  }

  void Destroy() override {}

};

}  // ssz

int main(int argc, char** argv) {
  ssz::SszWeiXinOpenServer server;
  server.Main(argc, argv);
  server.Wait();

  return 0;
}

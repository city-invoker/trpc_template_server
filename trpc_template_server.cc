// copyright skylanwei 2023-11-18

#include <string>

#include "trpc/common/trpc_app.h"
#include "trpc_template_service.h"

namespace trpc {
namespace sample {

class TrpcTemplateServer : public ::trpc::TrpcApp {
 public:
  int Initialize() override {
    const auto& config = ::trpc::TrpcConfig::GetInstance()->GetServerConfig();
    // Set the service name, which must be the same as the value of the `/server/service/name` configuration item
    // in the configuration file, otherwise the framework cannot receive requests normally.
    std::string service_name = fmt::format("{}.{}.{}.{}", "trpc", config.app, config.server, "TrpcTemplateService");
    TRPC_FMT_INFO("service name:{}", service_name);
    RegisterService(service_name, std::make_shared<TrpcTemplateServiceImpl>());

    return 0;
  }

  void Destroy() override {}

};

}  // sample 
}  // trpc 

int main(int argc, char** argv) {
  ::trpc::sample::TrpcTemplateServer server;
  server.Main(argc, argv);
  server.Wait();

  return 0;
}

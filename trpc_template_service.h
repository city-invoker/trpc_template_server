// copyright skylanwei 2023-11-18

#ifndef TRPC_SAMPLE_SERVICE_H_
#define TRPC_SAMPLE_SERVICE_H_

#include "protos/trpc_template_server.trpc.pb.h"
#include "trpc/config/trpc_conf.h"
#include "trpc/config/default/default_config.h"

namespace trpc {
namespace sample {

class TrpcTemplateServiceImpl : public ::trpc::sample::TrpcTemplateService {
public:

  TrpcTemplateServiceImpl() {

    app_busi_conf = trpc::config::Load("../conf/app_busi_conf.yaml", 
                        trpc::config::WithCodec("yaml"),
                        trpc::config::WithProvider("app_busi_conf"));
    app_db_conf = trpc::config::Load("../conf/app_db_conf.yaml", 
                        trpc::config::WithCodec("yaml"),
                        trpc::config::WithProvider("app_db_conf"));
  }


  ::trpc::Status TrpcTemplateHandler(::trpc::ServerContextPtr context,
                               const ::trpc::sample::TrpcTemplateReq* req,
                               ::trpc::sample::TrpcTemplateRsp* rsp) override;

  ::trpc::Status TrpcQueryUserHandler(::trpc::ServerContextPtr context,
                               const ::trpc::sample::TrpcQueryUserReq* req,
                               ::trpc::sample::TrpcQueryUserRsp* rsp) override;

public:
  ::trpc::config::DefaultConfigPtr app_busi_conf;
  ::trpc::config::DefaultConfigPtr app_db_conf;

};

} // namespace sample
} // namespace trpc

#endif // TRPC_SAMPLE_SERVICE_H_

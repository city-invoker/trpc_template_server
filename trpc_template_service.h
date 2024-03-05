// copyright skylanwei 2023-11-18

#ifndef TRPC_SAMPLE_SERVICE_H_
#define TRPC_SAMPLE_SERVICE_H_

#include "protos/trpc_template_server.trpc.pb.h"

namespace trpc {
namespace sample {

class TrpcTemplateServiceImpl : public ::trpc::sample::TrpcTemplateService {
 public:
  ::trpc::Status TrpcTemplateHandler(::trpc::ServerContextPtr context,
                               const ::trpc::sample::TrpcTemplateReq* req,
                               ::trpc::sample::TrpcTemplateRsp* rsp) override;

  ::trpc::Status TrpcQueryUserHandler(::trpc::ServerContextPtr context,
                               const ::trpc::sample::TrpcQueryUserReq* req,
                               ::trpc::sample::TrpcQueryUserRsp* rsp) override;

};

} // namespace sample
} // namespace trpc

#endif // TRPC_SAMPLE_SERVICE_H_

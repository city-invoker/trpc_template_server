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
//

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
};

} // namespace sample
} // namespace trpc

#endif // TRPC_SAMPLE_SERVICE_H_

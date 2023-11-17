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

#ifndef TRPC_TEMPLATE_SERVICE_H_
#define TRPC_TEMPLATE_SERVICE_H_

#include "ptoros/trpc_template_server.trpc.pb.h"

namespace trpc {

class TrpcTemplateServiceImpl : public ::trpc::TrpcTemplateService {
 public:
  ::trpc::Status TrpcTemplateHandler(::trpc::ServerContextPtr context,
                               const ::trpc::TrpcTemplateReq* req,
                               ::trpc::TrpcTemplateRsp* rsp) override;
};

}  // namespace trpc
#endif // TRPC_TEMPLATE_SERVICE_H_

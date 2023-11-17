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

#include "trpc_template_service.h"

#include <string>

#include "trpc/common/status.h"
#include "trpc/log/trpc_log.h"

namespace trpc {

::trpc::Status TrpcTemplateServiceImpl::TrpcTemplateHandler(::trpc::ServerContextPtr context,
    const ::trpc::TrpcTemplateReq* req, ::trpc::TrpcTemplateRsp* rsp) {
  TRPC_FMT_INFO("start handler");                               
  TRPC_FMT_INFO("end handler");                               

  return ::trpc::kSuccStatus;

}


}  // trpc 

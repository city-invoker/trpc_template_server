// copyright skylanwei 2023-11-18

#include "trpc_template_service.h"

#include <string>

#include "trpc/common/status.h"
#include "trpc/log/trpc_log.h"

namespace trpc {
namespace sample {

::trpc::Status TrpcTemplateServiceImpl::TrpcTemplateHandler(::trpc::ServerContextPtr context,
                             const ::trpc::sample::TrpcTemplateReq* req,
                             ::trpc::sample::TrpcTemplateRsp* rsp) {

  TRPC_FMT_INFO("process start");
  TRPC_FMT_DEBUG("test debug log info");
  TRPC_FMT_ERROR("error, something goes wrong");

  rsp->set_uuid("085815c18507a3eec90559d63042298a");
  rsp->set_spid("e90d02d68103c2d966751ed7d45e1015e3d8de5d");
  rsp->set_msg("the devil is inside the detail");
    
  std::string x = "asdfsksfjsa";
  TRPC_FMT_INFO("%s", x.c_str());
  TRPC_FMT_INFO("process end");
  return ::trpc::kSuccStatus;
}

::trpc::Status TrpcTemplateServiceImpl::TrpcQueryUserHandler(::trpc::ServerContextPtr context,
                             const ::trpc::sample::TrpcQueryUserReq* req,
                             ::trpc::sample::TrpcQueryUserRsp* rsp) {

  TRPC_FMT_INFO("process start");
  TRPC_FMT_DEBUG("test debug log info");
  TRPC_FMT_ERROR("error, something goes wrong");

  rsp->set_uid("085815c18507a3eec90559d63042298a");
  rsp->set_seesion_id("e90d02d68103c2d966751ed7d45e1015e3d8de5d");
  rsp->set_msg("the devil is inside the detail");
    
  TRPC_FMT_INFO("process end");
  return ::trpc::kSuccStatus;
}
}  // sample 
}  // trpc 

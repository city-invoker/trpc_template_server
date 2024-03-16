// copyright skylanwei 2024-03-15

#ifndef TOOL_TRPC_CLI_PACK_UTIL_H_
#define TOOL_TRPC_CLI_PACK_UTIL_H_

#include "trpc/util/buffer/noncontiguous_buffer.h"

#include "trpc/serialization/trpc_serialization.h"
#include "trpc/codec/codec_manager.h"


namespace trpc {
namespace tool {

class PackUtil {
  public:

    PackUtil() {
      codec::Init();
      serialization::Init();
    }

    virtual ~PackUtil() {
      codec::Destroy();
      serialization::Destroy();
    }

    std::string FlattenToString(const trpc::NoncontiguousBuffer& nb) ;
    //std::string PackTrpcPb(void* busi_req);
    std::string PackTrpcPb(void* busi_req, const std::string& service, const std::string& func);

};

}
}

#endif // TOOL_TRPC_CLI_PACK_UTIL_H_

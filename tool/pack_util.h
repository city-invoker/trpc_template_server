// copyright skylanwei 2024-03-15

#ifndef TOOL_TRPC_CLI_PACK_UTIL_H_
#define TOOL_TRPC_CLI_PACK_UTIL_H_

#include "trpc/util/buffer/noncontiguous_buffer.h"

namespace trpc {
namespace tool {
  class PackUtil {
    public:

      std::string PackUtil::FlattenToString(const NoncontiguousBuffer& nb) ;
      std::string PackTrpcPb(void* busi_req);




}
}

#endif // TOOL_TRPC_CLI_PACK_UTIL_H_

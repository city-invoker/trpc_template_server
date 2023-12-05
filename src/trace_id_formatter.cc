
#include "req_id_flag_formatter.h"

void ReqIdFlagFormatter::format(const spdlog::details::log_msg &, const std::tm &, spdlog::memory_buf_t &dest) {

  //TODO get req_id from thread local
  //TODO add req_id to dest

}

std::unique_ptr<custom_flag_formatter> ReqIdFlagFormatter::clone() const {

    return spdlog::details::make_unique<ReqIdFlagFormatter>();
}


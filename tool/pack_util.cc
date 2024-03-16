#include "pack_util.h"


namespace trpc {
namespace tool {

std::string PackUtil::FlattenToString(const NoncontiguousBuffer& nb) {
  std::size_t max_bytes = nb.ByteSize();
  std::string rc;
  std::size_t left = max_bytes;
  rc.reserve(max_bytes);
  for (auto iter = nb.begin(); iter != nb.end() && left; ++iter) {
    auto len = std::min(left, iter->size());
    rc.append(iter->data(), len);
    left -= len;
  }
  return rc;
}

std::string PackUtil::PackTrpcPb(void* busi_req) {
  //trpc::sample::TrpcQueryUserReq busi_req;
  //busi_req.set_uid("skylanweixasdfkkllasdfas");
  //busi_req.set_session_id("wtf is thereasdlfwwalsfjasdsja");

  trpc::TrpcRequestProtocolPtr req_ptr = std::make_shared<TrpcRequestProtocol>();
  req_ptr->req_header.set_version(0);
  req_ptr->req_header.set_call_type(trpc::serialization::kPbMessage);
  req_ptr->req_header.set_request_id(999);
  req_ptr->req_header.set_timeout(5*1000);
  req_ptr->req_header.set_caller("trpc.ssz.trpc_template_server.trpc_cli");
  req_ptr->req_header.set_callee("trpc.ssz.trpc_template_server.TrpcTemplateService");
  req_ptr->req_header.set_func("/trpc.sample.TrpcTemplateService/TrpcQueryUserHandler");
  req_ptr->req_header.set_message_type(TrpcMessageType::TRPC_DEFAULT);
  //req_ptr->req_header.set_trans_info();
  req_ptr->req_header.set_content_type(trpc::serialization::kPbMessage);
  req_ptr->req_header.set_content_encoding(compressor::kNone);
  uint32_t att_size = 0;
  req_ptr->req_header.set_attachment_size(att_size);

  trpc::serialization::SerializationType serialization_type = req_ptr->req_header.content_type();
  trpc::serialization::SerializationFactory* serialization_factory = trpc::serialization::SerializationFactory::GetInstance();

  trpc::detail::NoncontiguousBuffer body;
  bool encode_ret = serialization_factory->Get(serialization_type)->Serialize(trpc::serialization::kPbMessage, static_cast<void *>(&busi_req), &body);
  req_ptr->SetNonContiguousProtocolBody(std::move(body));

  trpc::detail::NoncontiguousBuffer bin_data;
  req_ptr->ZeroCopyEncode(bin_data);
  std::string rsp_str = FlattenToString(bin_data);
  return rsp_str;
}



}
}

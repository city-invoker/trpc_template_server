#include <iostream>
#include <fstream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <google/protobuf/message.h>
#include <google/protobuf/util/json_util.h>
#include <google/protobuf/dynamic_message.h>
#include <google/protobuf/descriptor.h>
#include "gtest/gtest.h"


#include "../protos/trpc_template_server.pb.h"
#include "../protos/trpc_template_server.trpc.pb.h"

#include "trpc/codec/protocol.h"
#include "trpc/codec/trpc/trpc_protocol.h"
#include "trpc/codec/trpc/trpc_client_codec.h"
//#include "trpc/codec/trpc/trpc_client_codec.h"
#include "trpc/util/ref_ptr.h"
#include "trpc/codec/trpc/testing/trpc_protocol_testing.h"
#include "trpc/transport/server/testing/server_transport_testing.h"
#include "trpc/server/testing/server_context_testing.h"
#include "trpc/server/rpc/rpc_method_handler.h"
#include "trpc/serialization/serialization_type.h"
#include "trpc/serialization/trpc_serialization.h"
#include "trpc/codec/codec_manager.h"

using namespace trpc;
using namespace trpc::sample;
using namespace trpc::testing;
//using namespace std;

//bool PackTrpcRequest(const DummyTrpcProtocol& protocol, void* in, NoncontiguousBuffer& bin_data) {
//  serialization::SerializationType serialization_type = protocol.content_type;
//  serialization::SerializationFactory* serializationfactory = serialization::SerializationFactory::GetInstance();
//
//  std::cout << "pack trpc request" << std::endl;
//  NoncontiguousBuffer body;
//  bool encode_ret = serializationfactory->Get(serialization_type)->Serialize(protocol.data_type, in, &body);
//  if (!encode_ret) {
//    return false;
//  }
//
//  std::cout << "pack trpc request ok" << std::endl;
//
//  TrpcRequestProtocol req;
//
//  req.req_header.set_version(0);
//  req.req_header.set_call_type(protocol.call_type);
//  req.req_header.set_request_id(protocol.request_id);
//  req.req_header.set_timeout(protocol.timeout);
//  req.req_header.set_caller(protocol.caller);
//  req.req_header.set_callee(protocol.callee);
//  req.req_header.set_func(protocol.func);
//  req.req_header.set_message_type(protocol.message_type);
//  req.req_header.set_content_type(protocol.content_type);
//  req.req_header.set_content_encoding(protocol.content_encoding);
//
//  auto req_trans_info = req.req_header.mutable_trans_info();
//  (*req_trans_info)["testkey1"] = "testvalue1";
//  (*req_trans_info)["testkey2"] = "testvalue2";
//
//  req.req_header.set_content_encoding(TrpcCompressType::TRPC_DEFAULT_COMPRESS);
//
//  req.SetNonContiguousProtocolBody(std::move(body));
//
//  std::cout << "pack trpc request end" << std::endl;
//
//  return req.ZeroCopyEncode(bin_data);
//}




void pack(NoncontiguousBuffer& bin_data) {

  std::cout << "log1" << std::endl;
  trpc::sample::TrpcQueryUserReq busi_req;
  busi_req.set_uid("skylanweixasdfkkllasdfas");
  busi_req.set_session_id("wtf is thereasdlfwwalsfjasdsja");

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

  std::cout << "log2" << std::endl;

  trpc::serialization::SerializationType serialization_type = req_ptr->req_header.content_type();
  trpc::serialization::SerializationFactory* serialization_factory = trpc::serialization::SerializationFactory::GetInstance();

  NoncontiguousBuffer body;
  bool encode_ret = serialization_factory->Get(serialization_type)->Serialize(trpc::serialization::kPbMessage, static_cast<void *>(&busi_req), &body);
  req_ptr->SetNonContiguousProtocolBody(std::move(body));
  req_ptr->ZeroCopyEncode(bin_data);

  std::cout << "logx:=" << bin_data.ByteSize() << std::endl;
  return;
}

std::string FlattenSlowX(const NoncontiguousBuffer& nb) {
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

// Function to send protocol buffer message to server and receive response
std::string send_message_to_server(const std::string& host, int port, const google::protobuf::Message& message) {
    // Serialize the message
    std::string serialized_message;
    if (!message.SerializeToString(&serialized_message)) {
        std::cerr << "Error: Failed to serialize message" << std::endl;
        return "";
    }

    // Create socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        std::cerr << "Error: Failed to create socket" << std::endl;
        return "";
    }

    // Server address
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(host.c_str());

    // Connect to server
    if (connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Error: Connection failed" << std::endl;
        close(sockfd);
        return "";
    }

    //size_t bsize = 100;
    //char* sbuf = new char[bsize];
    
    NoncontiguousBuffer bin_data;
    pack(bin_data);

    std::cout << "logt:=" << bin_data.ByteSize() << std::endl;
    char* sbuf = new char[bin_data.ByteSize()];

    //std::string FlattenSlow(const NoncontiguousBuffer& nb, std::size_t max_bytes = std::numeric_limits<std::size_t>::max());
    //detail::FlattenToSlow(bin_data, sbuf, bin_data.ByteSize());
    std::string sb = FlattenSlowX(bin_data);
    std::cout << "logb:=" << sb << std::endl;
    std::cout << "logb:=" << sb.size() << std::endl;
    if (send(sockfd, sb.c_str(), sb.size(), 0) < 0) {
        std::cerr << "Error: Failed to send message" << std::endl;
        close(sockfd);
        return "";
    }

    // Receive response from server
    char buffer[1024];
    std::string response;
    ssize_t bytes_received;
    while ((bytes_received = recv(sockfd, buffer, sizeof(buffer), 0)) > 0) {
        response.append(buffer, bytes_received);
    }
    if (bytes_received < 0) {
        std::cerr << "Error: Failed to receive response" << std::endl;
        close(sockfd);
        return "";
    }

    // Close socket
    close(sockfd);

    return response;
}


int main(int argc, char** argv) {
    // Parse command-line arguments
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <host> <port> <request_json_file>" << std::endl;
        return 1;
    }
    codec::Init();
    serialization::Init();

    // Parse host and port from command line
    std::string host = argv[1];
    int port = std::stoi(argv[2]);

    // Read request JSON from file
    std::string json_file_path = argv[3];
    std::ifstream json_file(json_file_path);
    if (!json_file) {
        std::cerr << "Error: Failed to open JSON file" << std::endl;
        return 1;
    }
    std::string json_string((std::istreambuf_iterator<char>(json_file)),
                             std::istreambuf_iterator<char>());

    // Parse JSON string and create dynamic message
    google::protobuf::DynamicMessageFactory factory;
    const google::protobuf::Descriptor* descriptor = TrpcQueryUserReq::GetDescriptor(); /* Replace with your message descriptor */
    std::unique_ptr<google::protobuf::Message> request(factory.GetPrototype(descriptor)->New());
    {
        google::protobuf::util::JsonParseOptions options;
        options.ignore_unknown_fields = true;
        google::protobuf::util::JsonStringToMessage(json_string, request.get(), options);
    }

    // Send protocol buffer message to server and receive response
    std::string response = send_message_to_server(host, port, *request);

    // Print response
    std::cout << "Response from server:" << std::endl;
    std::cout << response << std::endl;

    return 0;
}


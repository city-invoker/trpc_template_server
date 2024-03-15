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

trpc::ProtocolPtr pack() {
  trpc::TrpcClientCodec* tcc_ptr = new trpc::TrpcClientCodec();
  trpc::ProtocolPtr req_protocol = tcc_ptr->CreateRequestPtr();
  trpc::ClientContextPtr context = MakeRefCounted<ClientContext>();
  context->SetRequest(req_protocol);
  //context->SetReqCompressType(compressor::kZlib);
  trpc::sample::TrpcQueryUserReq query_user_req;
  query_user_req.set_uid("skylanwei");
  tcc_ptr->FillRequest(context, req_protocol, &query_user_req);
  return req_protocol;
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
    //trpc::ProtocolPtr ptr = pack();
    trpc::TrpcClientCodec* tcc_ptr = new trpc::TrpcClientCodec();
    trpc::ProtocolPtr ptr = tcc_ptr->CreateRequestPtr();

    trpc::ClientContextPtr context = MakeRefCounted<ClientContext>();
    context->SetRequest(ptr);
    context->SetCallType(trpc::serialization::kPbMessage);
    context->SetRequestId(1022);
    context->SetTimeout(5*1000);
    context->SetCallerName("trpc_cli");
    context->SetCalleeName("trpc_server");
    context->SetFuncName("/trpc.sample.TrpcTemplateService/TrpcQueryUserHandler");
    //context->SetMessageType(TrpcMessageType::TRPC_DEFAULT);
    context->SetReqEncodeType(trpc::serialization::kPbMessage);
    context->SetReqCompressType(compressor::kZlib);

    trpc::sample::TrpcQueryUserReq query_user_req;
    query_user_req.set_uid("skylanweixasdfkkllasdfas");
    query_user_req.set_session_id("wtf is thereasdlfwwalsfjasdsja");

    tcc_ptr->FillRequest(context, ptr, &query_user_req);

    trpc::NoncontiguousBuffer req_bin_data;
    tcc_ptr->ZeroCopyEncode(context, ptr, req_bin_data);

    std::cout << "track" << req_bin_data.ByteSize() << std::endl;
    std::size_t bsize = req_bin_data.ByteSize();
    std::cout << "track" << bsize << std::endl;
    char* sbuf = new char[bsize];
    trpc::detail::FlattenToSlowSlow(req_bin_data, sbuf, bsize);

    if (send(sockfd, sbuf, bsize, 0) < 0) {
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


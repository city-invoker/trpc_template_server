#include <iostream>

//#include <fstream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>

#include "pack_util.h"
#include "../protos/trpc_template_server.pb.h"

using namespace trpc;
using namespace trpc::sample;
using namespace trpc::tool;

// Function to send protocol buffer message to server and receive response
std::string send_message_to_server(const std::string& host, int port, const std::string& send_data) {
    // Create socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        std::cerr << "Error: Failed to create socket" << std::endl;
        return "";
    }

    //int flags = fcntl(sockfd, F_GETFL, 0);
    //fcntl(sockfd, F_SETFL, flags | O_NONBLOCK);
    struct timeval timeout;
    timeout.tv_sec = 5;
    timeout.tv_usec = 0;
    setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
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


    if (send(sockfd, send_data.c_str(), send_data.size(), 0) < 0) {
        std::cerr << "Error: Failed to send message" << std::endl;
        close(sockfd);
        return "";
    }

    // Receive response from server
    char buffer[10*1024];
    std::string response;
    ssize_t bytes_received;
    ssize_t bc = recv(sockfd, buffer, sizeof(buffer), 0);
    if (bc > 0) {
        response.append(buffer, bc);
    }
    close(sockfd);
    return response;
}

int main(int argc, char** argv) {
    // Parse command-line arguments
    //if (argc != 4) {
    //    std::cerr << "Usage: " << argv[0] << " <host> <port>" << std::endl;
    //    return 1;
    //}
    //codec::Init();
    //serialization::Init();

    //// Parse host and port from command line
    //std::string host = argv[1];
    //int port = std::stoi(argv[2]);

    std::shared_ptr<PackUtil> pu_ptr =  std::make_shared<PackUtil>();
    trpc::sample::TrpcQueryUserReq busi_req;
    busi_req.set_uid("bbfb00765d29233677cf0bcf503c3401");
    busi_req.set_session_id("BiZTFiMTVhMWVjNTk1MDExYjE2M2Q3MmY2MWFlMjAxYzU3ZDQ0NjBlNDM4ZmQ4Y2M2MmY5Y2E5OWY4MGM1ZCAgLQo=");
    std::string service("trpc.ssz.trpc_template_server.TrpcTemplateService");
    std::string func("/trpc.sample.TrpcTemplateService/TrpcQueryUserHandler");

    std::string send_data = pu_ptr->PackTrpcPb(static_cast<void *>(&busi_req), service, func);
    std::string host("127.0.0.1");
    uint32_t port = 8088; 
    std::string response = send_message_to_server(host, port, send_data);

    // Print response
    std::cout << "Response from server:" << std::endl;
    std::cout << response << std::endl;

    return 0;
}


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

#include "../protos/trpc_template_server.pb.h"
//#include "../protos/trpc_template_server.trpc.pb.h"


using namespace trpc::sample;

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

    // Send message to server
    if (send(sockfd, serialized_message.c_str(), serialized_message.size(), 0) < 0) {
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


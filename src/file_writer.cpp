//
// Created by fernando on 09/03/2022.
//

#include "file_writer.hpp"

namespace log_helper {
    /**
     * Only local file writing
     */
    LocalFile::LocalFile(std::string file_path) {
        this->file_path = std::move(file_path);
        std::ofstream output(this->file_path, std::ios::app);
        if (output.fail()) {
            EXCEPTION_MESSAGE("[ERROR in create_log_file(char *)] Unable to open file " + this->file_path);
        }
        output.close();
    }

    bool LocalFile::write(const std::string &buffer) {
        std::ofstream output(this->file_path, std::ios::app);
        if (output.good()) {
            output << buffer;
            output.close();
            return true;
        }
        EXCEPTION_MESSAGE("[ERROR Unable to open the file " + this->file_path + "]");
        return false;
    }

    std::string LocalFile::get_file_path() {
        return this->file_path;
    }


    /**
     * Networking file writing
     */
    UDPFile::UDPFile(std::string server_ip, const int32_t port)
            : server_ip(std::move(server_ip)), port(port), server_address({}) {
        //  Prepare our context and socket
        // Filling server information
        this->client_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
        this->server_address.sin_family = AF_INET;
        this->server_address.sin_port = htons(this->port);
        inet_pton(AF_INET, this->server_ip.c_str(), &(this->server_address.sin_addr.s_addr));
        if (this->client_socket < -1) {
            EXCEPTION_MESSAGE("[ERROR Unable to create a socket]");
        }
    }

    bool UDPFile::write(const std::string &buffer) {
        auto error = sendto(this->client_socket, buffer.data(), buffer.size(),
                            MSG_CONFIRM, (const struct sockaddr *) &this->server_address,
                            sizeof(this->server_address));

        if (error < 0) {
            EXCEPTION_MESSAGE("[ERROR Unable to send the message " + buffer + "]");
            return false;
        }
        return true;
    }

    std::string UDPFile::get_file_path() {
        return this->server_ip;
    }


    /**
     * To use both methods TODO: NOT TESTED
     */
    LocalAndUDPFile::LocalAndUDPFile(const std::string &file_path, const std::string &server_ip, const int32_t port)
            : LocalFile(file_path), UDPFile(server_ip, port) {}

    bool LocalAndUDPFile::write(const std::string &buffer) {
        return LocalFile::write(buffer) && UDPFile::write(buffer);
    }

    std::string LocalAndUDPFile::get_file_path() {
        return "LOCAL:" + this->file_path + " IP:" + this->server_ip;
    }

} /*END NAMESPACE LOG_HELPER*/
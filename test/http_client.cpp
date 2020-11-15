//
// Created by liember on 11/15/20.
//

#include "gtest/gtest.h"
#include "http/server.hpp"

char *request = (char *)"GET / HTTP/1.1\r\n\r\n";

TEST(http_client, init) {
    ASSERT_NO_THROW(http::client c("192.168.0.1"));
}

TEST(http_client, send) {
    http::client c("192.168.0.1");
    ASSERT_NO_THROW(c.sendData(request));
}

TEST(http_client, recv) {
    http::client c("192.168.0.1");
    c.sendData(request);
    char *res = c.recvData();
    std::string_view str(res, 4);
    ASSERT_GT(str.size(), 0);
}
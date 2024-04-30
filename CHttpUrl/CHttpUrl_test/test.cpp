#include "pch.h"
#include <gtest/gtest.h>
#include "../../CHttpUrl/CHttpUrl/CHttpUrl.cpp"
#include "../../CHttpUrl/CHttpUrl/CUrlParsingError.cpp"


// Test constructor with a URL string
TEST(CHttpUrlTest, ConstructorWithStringURL) {
    CHttpUrl url("https://example.com:8080/path");

    EXPECT_EQ(url.GetDomain(), "example.com");
    EXPECT_EQ(url.GetDocument(), "/path");
    EXPECT_EQ(url.GetProtocol(), Protocol::HTTPS);
    EXPECT_EQ(url.GetPort(), 8080);
}

// Test constructor with domain, document, and protocol
TEST(CHttpUrlTest, ConstructorWithComponents) {
    CHttpUrl url("example.com", "/path", Protocol::HTTPS, 8080);

    EXPECT_EQ(url.GetDomain(), "example.com");
    EXPECT_EQ(url.GetDocument(), "/path");
    EXPECT_EQ(url.GetProtocol(), Protocol::HTTPS);
    EXPECT_EQ(url.GetPort(), 8080);
}

// Test constructor with default port based on protocol
TEST(CHttpUrlTest, ConstructorWithDefaultPort) {
    CHttpUrl urlHttp("example.com", "/path", Protocol::HTTP);
    EXPECT_EQ(urlHttp.GetPort(), 80);

    CHttpUrl urlHttps("example.com", "/path", Protocol::HTTPS);
    EXPECT_EQ(urlHttps.GetPort(), 443);
}

// Test that invalid URL strings throw an exception
TEST(CHttpUrlTest, ConstructorWithInvalidURL) {
    EXPECT_THROW({
        CHttpUrl url("invalid://example.com");
        }, CUrlParsingError);

    EXPECT_THROW({
        CHttpUrl url("http://:80/");
        }, CUrlParsingError);
}

// Test GetURL method
TEST(CHttpUrlTest, GetURL) {
    CHttpUrl url1("example.com", "/path", Protocol::HTTPS, 8080);
    EXPECT_EQ(url1.GetURL(), "https://example.com:8080/path");

    CHttpUrl url2("example.com", "/path", Protocol::HTTPS);
    EXPECT_EQ(url2.GetURL(), "https://example.com/path");
}

// Test CUrlParsingError exception
TEST(CUrlParsingErrorTest, Exception) {
    try {
        throw CUrlParsingError("Parsing error occurred");
    }
    catch (const CUrlParsingError& e) {
        EXPECT_STREQ(e.what(), "Parsing error occurred");
    }
}


#ifndef CHTTPURL_H
#define CHTTPURL_H

#include <string>
#include "CUrlParsingError.h" 

enum class Protocol
{
    HTTP,
    HTTPS
};

class CHttpUrl
{
public:
    CHttpUrl(const std::string& url);
    CHttpUrl(
        const std::string& domain, 
        const std::string& document, 
        Protocol protocol = Protocol::HTTP);
    CHttpUrl(
        const std::string& domain, 
        const std::string& document,
        Protocol protocol, 
        unsigned short port);

    std::string GetURL() const;
    std::string GetDomain() const;
    std::string GetDocument() const;
    Protocol GetProtocol() const;
    unsigned short GetPort() const;

private:
    void ParseURL(const std::string& url);
    unsigned short GetDefaultPort(Protocol protocol) const;

    std::string m_domain;
    std::string m_document;
    Protocol m_protocol;
    unsigned short m_port;
};

#endif
#include "CHttpUrl.h"
#include <regex>

CHttpUrl::CHttpUrl(const std::string& url)
{
    ParseURL(url);
}

CHttpUrl::CHttpUrl(
    const std::string& domain,
    const std::string& document, 
    Protocol protocol)
    : m_domain(domain), m_document(document), m_protocol(protocol)
{
    m_port = GetDefaultPort(m_protocol);

    if (m_domain.empty() || m_document.empty())
    {
        throw std::invalid_argument("Domain and document cannot be empty");
    }

    if (m_document[0] != '/')
    {
        m_document = "/" + m_document;
    }
}

CHttpUrl::CHttpUrl(
    const std::string& domain, 
    const std::string& document, 
    Protocol protocol, 
    unsigned short port)
    : m_domain(domain), m_document(document), m_protocol(protocol), m_port(port)
{
    if (m_domain.empty() || m_document.empty())
    {
        throw std::invalid_argument("Domain and document cannot be empty");
    }

    if (m_document[0] != '/')
    {
        m_document = "/" + m_document;
    }

    if (port <= 0 || port > 65535)
    {
        throw std::invalid_argument("Invalid port number");
    }
}

std::string CHttpUrl::GetURL() const
{
    std::string url;
    if (m_protocol == Protocol::HTTP)
    {
        url = "http://";
        if (m_port != 80)
        {
            url += m_domain + ":" + std::to_string(m_port) + m_document;
        }
        else
        {
            url += m_domain + m_document;
        }
    }
    else
    {
        url = "https://";
        if (m_port != 443)
        {
            url += m_domain + ":" + std::to_string(m_port) + m_document;
        }
        else
        {
            url += m_domain + m_document;
        }
    }
    return url;
}

std::string CHttpUrl::GetDomain() const
{
    return m_domain;
}

std::string CHttpUrl::GetDocument() const
{
    return m_document;
}

Protocol CHttpUrl::GetProtocol() const
{
    return m_protocol;
}

unsigned short CHttpUrl::GetPort() const
{
    return m_port;
}

void CHttpUrl::ParseURL(const std::string& url)
{
    std::regex urlPattern(R"(^((http|https)://)?([a-zA-Z0-9.-]+)(:(\d+))?(/.*)?$)");
    std::smatch matches;

    if (!std::regex_match(url, matches, urlPattern))
    {
        throw CUrlParsingError("Invalid URL");
    }

    if (matches[2] == "http")
    {
        m_protocol = Protocol::HTTP;
        m_port = GetDefaultPort(m_protocol);
    }
    else if (matches[2] == "https")
    {
        m_protocol = Protocol::HTTPS;
        m_port = GetDefaultPort(m_protocol);
    }
    else
    {
        throw CUrlParsingError("Unknown protocol");
    }

    m_domain = matches[3];

    if (matches[5].matched)
    {
        m_port = static_cast<unsigned short>(std::stoi(matches[5].str()));
    }

    if (matches[6].matched)
    {
        m_document = matches[6].str();
    }
    else
    {
        m_document = "/";
    }
}

unsigned short CHttpUrl::GetDefaultPort(Protocol protocol) const
{
    if (protocol == Protocol::HTTP)
    {
        return 80;
    }
    else
    {
        return 443;
    }
}

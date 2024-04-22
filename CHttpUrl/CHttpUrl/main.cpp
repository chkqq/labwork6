#include <iostream>
#include "CHttpUrl.h"

int main()
{
    std::string url;

    while (std::getline(std::cin, url))
    {
        try
        {
            CHttpUrl httpUrl(url);

            std::cout << "URL: " << httpUrl.GetURL() << std::endl;
            std::cout << "Domain: " << httpUrl.GetDomain() << std::endl;
            std::cout << "Document: " << httpUrl.GetDocument() << std::endl;
            std::cout << "Protocol: " << (httpUrl.GetProtocol() == Protocol::HTTP ? "HTTP" : "HTTPS") << std::endl;
            std::cout << "Port: " << httpUrl.GetPort() << std::endl;
        }
        catch (const CUrlParsingError& e)
        {
            std::cout << "Error parsing URL: " << e.what() << std::endl;
        }
        catch (const std::invalid_argument& e)
        {
            std::cout << "Invalid argument error: " << e.what() << std::endl;
        }
    }

    return 0;
}

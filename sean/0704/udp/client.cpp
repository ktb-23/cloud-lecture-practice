#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{
  int sock = 0;
  struct sockaddr_in serv_addr;
  char buffer[1024] = {0};

  if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
  {
    std::cerr << "Socket creation error" << std::endl;
    return -1;
  }

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(8080);

  if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
  {
    std::cerr << "Invalid address/ Address not supported" << std::endl;
    return -1;
  }

  std::string input;
  while (true)
  {
    std::cout << "서버로 보낼 메시지: ";
    std::getline(std::cin, input);

    if (input == "exit")
    {
      break;
    }

    sendto(sock, input.c_str(), input.length(), 0, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    socklen_t len = sizeof(serv_addr);
    int valread = recvfrom(sock, buffer, 1024, 0, (struct sockaddr *)&serv_addr, &len);
    if (valread > 0)
    {
      buffer[valread] = '\0';
      std::cout << "서버에서 온 응답: " << buffer << std::endl;
    }

    memset(buffer, 0, sizeof(buffer));
  }

  close(sock);
  return 0;
}
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>


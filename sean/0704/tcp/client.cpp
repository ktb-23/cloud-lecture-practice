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

  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
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

  if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
  {
    std::cerr << "Connection Failed" << std::endl;
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

    send(sock, input.c_str(), input.length(), 0);

    int valread = read(sock, buffer, 1024);
    if (valread > 0)
    {
      buffer[valread] = '\0';
      std::cout << "서버에서 온 응답: " << buffer << std::endl;
    }
    else
    {
      std::cerr << "Server disconnected or error occurred" << std::endl;
      break;
    }

    memset(buffer, 0, sizeof(buffer));
  }

  close(sock);
  return 0;
}

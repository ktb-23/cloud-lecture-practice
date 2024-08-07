#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

std::string printAddress(sockaddr_in &socket_address)
{
  char ip[INET_ADDRSTRLEN];
  if (inet_ntop(AF_INET, &socket_address.sin_addr, ip, INET_ADDRSTRLEN) == nullptr)
  {
    perror("inet_ntop");
    exit(EXIT_FAILURE);
  }
  __uint16_t port = ntohs(socket_address.sin_port);
  return std::string(ip) + ":" + std::to_string(port);
}

void handle_client(int server_socket, sockaddr_in &client_addr)
{
  char buffer[1024] = {0};
  int valread;
  socklen_t len = sizeof(client_addr);
  while ((valread = recvfrom(server_socket, buffer, 1024, 0, (struct sockaddr *)&client_addr, &len)) > 0)
  {
    std::cout << "받은 데이터: " << buffer << std::endl;
    const char *response = "안녕하세요, 클라이언트!";
    sendto(server_socket, response, strlen(response), 0, (struct sockaddr *)&client_addr, len);
    memset(buffer, 0, sizeof(buffer));
  }
  std::cout << "클라이언트 " << printAddress(client_addr) << "연결이 종료되었습니다.\n";

  close(server_socket);
}

int main()
{
  int server_fd;
  struct sockaddr_in address, client_addr;
  int opt = 1;

  // 소켓 파일 디스크립터 생성
  if ((server_fd = socket(AF_INET, SOCK_DGRAM, 0)) == 0)
  {
    perror("socket failed");
    exit(EXIT_FAILURE);
  }

  // 8080 포트를 다중 할당 가능하게 설정
  if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)))
  {
    perror("setsockopt");
    exit(EXIT_FAILURE);
  }

  address.sin_family = AF_INET;
  // 모든 IP 주소에서 연결 수락
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(8080);

  // 소켓을 포트에 바인딩
  if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
  {
    perror("bind failed");
    exit(EXIT_FAILURE);
  }

  std::cout << "UDP 서버가 시작되었습니다. 클라이언트를 기다리는 중...\n";

  while (true)
  {
    handle_client(server_fd, client_addr);
  }

  close(server_fd);
  return 0;
}

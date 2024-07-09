# 컴파일러 설정
CXX = clang++
CXXFLAGS = -Wall -std=c++11

# 타겟 파일들
TARGETS = client server

# 기본 타겟
all: $(TARGETS)

# client 타겟
client: client.o
	$(CXX) $(CXXFLAGS) -o client client.o

# server 타겟
server: server.o
	$(CXX) $(CXXFLAGS) -o server server.o

# 개별 소스 파일들
client.o: client.cpp
	$(CXX) $(CXXFLAGS) -c client.cpp

server.o: server.cpp
	$(CXX) $(CXXFLAGS) -c server.cpp

# clean 타겟 - 빌드 결과물 제거
clean:
	rm -f $(TARGETS) *.o

.PHONY: all clean
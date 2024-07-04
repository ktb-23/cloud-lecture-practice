import socket

def tcp_server():
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind(('localhost', 12345))
    server_socket.listen(1)

    print("TCP 서버가 시작되었습니다. 클라이언트를 기다리는 중...")

    while True:
        conn, addr = server_socket.accept()
        print(f"클라이언트 {addr}에 연결되었습니다.")

        data = conn.recv(1024)
        if not data:
            break
        print(f"받은 데이터: {data.decode()}")

        conn.send('안녕하세요, 클라이언트!'.encode('utf-8'))
        conn.close()
        print(f"클라이언트 {addr} 연결이 종료되었습니다.")

if __name__ == "__main__":
    tcp_server()

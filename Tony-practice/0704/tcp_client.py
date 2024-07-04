import socket

def tcp_client():
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client_socket.connect(('localhost', 12345))

    client_socket.send('안녕하세요, 서버!'.encode('utf-8'))
    data = client_socket.recv(1024)
    print(f"받은 데이터: {data.decode()}")



if __name__ == "__main__":
    tcp_client()

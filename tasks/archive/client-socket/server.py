import socket
import sys
import time

def main():
    HOST = sys.argv[1]  # Хост
    PORT = int(sys.argv[2])  # Порт
    MESSAGE_TO_CLIENT = sys.argv[3]

    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    s.bind((HOST, PORT))
    s.listen(1)

    conn, addr = s.accept()

    data = conn.recv(8096)
    message_from_client = data.decode('utf-8')
    conn.sendall((MESSAGE_TO_CLIENT + message_from_client).encode('utf-8'))

    conn.close()

if __name__ == '__main__':
    main()
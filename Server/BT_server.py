import socket
import json
import numpy as np
from stable_baselines3 import PPO

model = PPO.load("attack_model.zip")

HOST= '127.0.0.1'
PORT=9999

server_socket=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
server_socket.bind((HOST, PORT))
server_socket.listen()

print(f"[server] execute...(port: {PORT})")

while True:
    client_socket, addr=server_socket.accept()
    print(f"[connect]{addr}to connect")
    data=client_socket.recv(1024)
    if not data:
        break

    # Unreal에서 보낸 JSON 데이터 파싱
    state_dict=json.loads(data.decode())

    state = np.array([
        state_dict["skill_type"],
        state_dict["is_hit"],
        state_dict["hit_count"],
        state_dict["skill_active"]
    ], dtype=np.float32)
    # 행동 예측
    action,_=model.predict(state)

    # 결과 전송
    client_socket.send(str(int(action)).encode())
    client_socket.close()
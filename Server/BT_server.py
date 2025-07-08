import socket
import json
import numpy as np
from stable_baselines3 import PPO

model = PPO.load("attack_model")

HOST= '127.0.0.1'
PORT=9999

server_socket=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
server_socket.bind((HOST, PORT))
server_socket.listen()

print(f"[server] execute...(port: {PORT})")
while True:
    client_socket, addr = server_socket.accept()
    print(f"[connect]{addr} to connect")
    data = client_socket.recv(1024)
    if not data:
        break

    # Unreal에서 보낸 JSON 데이터 파싱
    state_dict = json.loads(data.decode())
    
    # 디버깅용 출력
    print("Received JSON:", json.dumps(state_dict, indent=2))

    # skills 배열에서 첫 번째 스킬 사용
    if "skills" in state_dict and len(state_dict["skills"]) > 0:
        skill = state_dict["skills"][0]

        state = np.array([
            skill["skill_type"],
            skill["is_hit"],
            skill["hit_count"],
            skill["skill_active"]
        ], dtype=np.float32)

        # 행동 예측
        action, _ = model.predict(state)

        # 결과 전송
        client_socket.send(str(int(action)).encode())
    else:
        print("[error] 'skills'가 없거나 비어 있음")
        client_socket.send(b"-1")  # 에러 응답

    client_socket.close()

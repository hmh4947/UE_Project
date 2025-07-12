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
    try:
        data = client_socket.recv(2048)
        if not data:
            client_socket.close()
            continue

    # Unreal에서 보낸 JSON 데이터 파싱
        state_dict = json.loads(data.decode())
    
    # 디버깅용 출력
        print("Received JSON:", json.dumps(state_dict, indent=2))

    # skills 배열에서 첫 번째 스킬 사용
        skills = state_dict.get("skills", [])
        if not skills:
            print("[error] 'skills' 배열이 비어 있습니다.")
            client_socket.send(b"-1")
            client_socket.close()
            continue

        # 유동적인 상태 벡터 생성
        state = []
        for skill in skills:
            state.extend([
                skill.get("skill_type", 0),
                skill.get("is_hit", 0),
                skill.get("hit_count", 0),
                skill.get("skill_active", 0)
            ])
        state = np.array(state, dtype=np.float32).reshape(1, -1)  # (1, N)

    # 모델 예측
        action, _ = model.predict(state)
        action_index = int(action)

        print(f"Predicted Action Index: {action_index}")
        client_socket.send(str(action_index).encode())

    except Exception as e:
        print("[exception]", e)
        client_socket.send(b"-1")

    client_socket.close()

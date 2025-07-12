from stable_baselines3 import PPO
from stable_baselines3.common.vec_env import DummyVecEnv
import gym
import numpy as np
from math import log
# === 1. 커스텀 환경 정의 ===
class AttackEnv(gym.Env):
    def __init__(self):
        super(AttackEnv, self).__init__()
         # 상태 공간 정의: [  skill_type,is_hit, hit_count, skill_active]
        #self.observation_space = gym.spaces.Box(
        #    low=np.array([0, 0, 0, 0], dtype=np.float32),
        #    high=np.array([1, 1, 100, 1], dtype=np.float32),
        #    dtype=np.float32
        #)
        self.num_skills = 3
        self.observation_space = gym.spaces.Box(
            low=np.zeros(4 * self.num_skills, dtype=np.float32),
            high=np.array([1, 1, 100, 1] * self.num_skills, dtype=np.float32),
            dtype=np.float32
            )

        self.action_space = gym.spaces.Discrete(self.num_skills)  # 0, 1 (근거리, 원거리)

    # 환경 초기화: 상태를 랜덤하게 설정하고 반환
    def reset(self):
        self.skills = []
        for _ in range(self.num_skills):
            skill_type = np.random.randint(0, 2)      # 근거리 or 원거리
            is_hit = np.random.randint(0, 2)          # 적중 여부
            hit_count = 0
            skill_active = np.random.randint(0, 2)    # 사용 가능 여부
            self.skills.extend([skill_type, is_hit, hit_count, skill_active])
        self.state = np.array(self.skills, dtype=np.float32)
        return self.state
    
   # 하나의 행동을 수행 → 다음 상태, 보상, 종료 여부, 기타 정보 반환
    def step(self, action): #external_state=파이썬에서 리스트로 정리
        reward = 0
        done = True

        base_idx = action * 4
        skill_type = int(self.state[base_idx])
        is_hit = int(self.state[base_idx + 1])
        hit_count = int(self.state[base_idx + 2])
        skill_active = int(self.state[base_idx + 3])

    # 보상 설계 예시: 스킬 적절성 평가

        if not skill_active:    #스킬 쿨타임 중
            reward -= 1.0
        elif action == skill_type:  #스킬을 맞게 선택
            if skill_type == 0:   #0:근거리 1:원거리
                reward += 0.7
            else:
                reward += 0.5


            if is_hit:       #히트에 성공했다면
                 hit_count += 1 #카운트 증가
                 reward += np.log(hit_count + 1) #많이 누적시 보상을 점점 덜 증가하도록
            else:
                reward -= 0.5
        else:
            reward -= 1.0

        done = True  # 1 step짜리 환경
        return self.state, reward, done, {}

# === 2. 환경 래핑 ===
env = DummyVecEnv([lambda: AttackEnv()])

# === 3. 모델 학습 ===
model = PPO("MlpPolicy", env, verbose=1)
model.learn(total_timesteps=10000)  # 학습량은 조절 가능

# === 4. 저장 ===
model.save("attack_model")
print("attack_model.zip 생성 완료!")

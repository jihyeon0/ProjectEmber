# 🔥 MEMORIK
2nd Team 3 Final Project – Unreal Engine 5 Healing Adventure Game  

![Unreal Engine 5](https://img.shields.io/badge/Engine-Unreal%20Engine%205-blue?logo=unrealengine)  
![Status](https://img.shields.io/badge/Status-In%20Development-important)  
![License](https://img.shields.io/badge/License-MIT-green)

## 🎮 프로젝트 개요

**MEMORIK**는 UE5 기반의 3인칭 서바이벌 어드벤처 게임입니다.  
플레이어는 폐허가 된 세계에서 살아남기 위해 자원을 수집하고, 야생 동물을 상대하며, 잃어버린 '메모리'를 찾아나섭니다.  
판타지와 SF가 뒤섞인 세계관 속에서 탐험, 성장, 전략이 결합된 몰입형 게임 경험을 제공합니다.

## 🛠️ 핵심 기능

- ✅ 오픈 월드 기반 야생 탐험 시스템
- ✅ 동물 AI (지각, 먹이/수면, 공격/반격, 무리 행동, 경계 시스템 포함)
- ✅ 동물 스포너 시스템 (거리 기반, 큐 분산 처리, 상태 메시지 연동)
- ✅ 세이브/로드 기능 (Easy Multi Save 연동)
- ✅ 시간/날씨 변화 (BP_StylizedSky 기반)
- ✅ 플레이어 전투 시스템 및 능력 기반 스킬 사용
- ✅ UI: HP/스태미나 바, 몽타주 기반 애니메이션 HUD, 동물 HUD

## 🧠 사용 기술 및 구조

| 항목 | 내용 |
|------|------|
| Engine | Unreal Engine 5.3 |
| Language | C++, Blueprint |
| Version Control | Git + Git LFS |
| Save System | Easy Multi Save (EMS) Plugin |
| AI 시스템 | Behavior Tree, Blackboard, Gameplay Tags, Perception, FSM 구조 |
| 스폰 시스템 | `AAnimalSpawner` 클래스 기반 거리-큐 시스템 |
| 팀 협업 | GitHub 기반 브랜치 전략 및 이슈 관리 |

## 👨‍👩‍👧‍👦 팀원 소개

| 이름 | 역할 | 주요 담당 |
|------|------|-----------|
| 김태완 | 팀장 | 캐릭터, 전투시스템, 프로젝트 구조 설계|
| 전지현 | 부팀 | AI Animal, 스폰 시스템, 토큰 레이드 시스템 |
| 윤현중 | 프로그래머 | 미니맵, 던전 생성 알고리즘 |
| 서원호 | 프로그래머 | 아이템 시스템, 인벤토리 시스템 |
| 문정수 | 프로그래머 | 건축 시스템 |
| 고건호 | 프로그래머 | 환경설정, 메인메뉴 시스템 |
| 김현우 | 프로그래머 | 메인 시나리오, 퀘스트 시스템, 튜토리얼 |
| 송정훈 | 프로그래머 | 레벨 디자인, 상호작용 엑터 |

## 🗓️ 개발 기간

- **2025.05.07 ~ 2025.07.02** (총 8주)

## ☑️문제 발생 및 해결

1. 죽음 이후 상태 갱신 처리
- 문제 상황
캐릭터 사망 처리는 GAS 기반의 DeathAbility로 구현했습니다.
해당 어빌리티 내에서 사망 몽타주를 재생합니다. 몽타주가 끝난 시점에 파밍 대기시간을 위한 타이머가 설정되며, 타이머 종료 후 어빌리티가 종료됩니다.
하지만 스포너는 어빌리티의 종료 시점을 인식하지 못해 객체의 상태 갱신이 누락되었고, 이로 인해 후처리가 정상적으로 이루어지지 않는 문제가 발생했습니다.
- 해결 방법
모듈 간 강결합을 피하기 위해 모듈 간 중개 역할을 하는 메시지 버스 모듈을 활용했습니다.
어빌리티 종료 시점에 메시지 버스를 통해 스포너에게 상태 변경 이벤트를 전달함으로써, 객체를 적절한 배열로 이동시키고 후처리를 정확히 수행할 수 있도록 개선했습니다.
1. CDO 관련 초기화 오류
- 문제 상황
같은 베이스 클래스를 상속받은 블루프린트 클래스임에도 일부 클래스에서 AttributeSet이 nullptr로 초기화되는 문제가 발생했습니다. 코드 및 블루프린트 구조는 정상 동작하는 클래스와 동일했으며, 명확한 차이를 발견하기 어려웠습니다.
- 해결 방법
저장/불러오기를 위한 EMS 플러그인을 사용하여 포인터 변수를 직렬화하면서 CDO(Cached Default Object) 관련 문제가 발생했을 가능성이 있다고 생각했습니다.
포인터 변수에 EMS 플러그인 사용을 위한 UPROPERTY(SaveGame) 키워드를 제거하고 UPROPERTY(Transient)로 선언하여 직렬화 대상에서 제외한 결과, 문제가 발생하지 않았습니다. 이후 코드에서 설정한 값이 정상적으로 유지되며, 어트리뷰트셋이 올바르게 초기화되었습니다.

## 📷 플레이 영상
[![데모 영상](https://img.youtube.com/vi/1qO8luD1DK0/0.jpg)](https://youtu.be/1qO8luD1DK0)


## 📃 라이선스

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.



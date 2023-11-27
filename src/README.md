# README

## 폴더 구조

### stargazer

이 프로젝트의 메인 프로젝트입니다. 다음 주어진 기능을 수행합니다.

- 온도, 습도, 토양 습도 측정
- Wi-Fi CSI 신경망 추론

### coprocessor

stargazer 프로젝트의 보조 모듈 프로젝트로서, 다음 주어진 기능을 수행합니다.

- 카메라 촬영 및 사진 전송
- Face recognition 신경망 추론

### backend

stargazer와 coprocessor에서 발신한 데이터를 받아 처리하는 서버입니다. 이 폴더는 다음과 같이 구성됩니다.

- Home assistant
- 데모 시연을 위한 간단한 웹 서버

### WiFi-CSI

CSI 신경망 학습을 위한 폴더입니다. 이 폴더는 [SenseFi: A Benchmark for WiFi CSI Sensing](https://github.com/xyanchen/WiFi-CSI-Sensing-Benchmark)를 기반으로 [AutoFi: Towards Wifi Sensing via Geometric Self-Supervised Learning](https://arxiv.org/pdf/2205.01629.pdf)을 구현하고, 양자화 및 컴파일을 수행합니다.

## 통신

이 프로젝트는 Wi-Fi에서 MQTT5를 기반으로 통신합니다. MQTT5에서 사용되는 topic은 다음과 같습니다.

- `sensor`
  - `sensor/temperature` | 온도 데이터
  - `sensor/humidity` | 습도 데이터
  - `sensor/soil-humidity` | 토양 습도 데이터
  - `sensor/picture` | 사진 데이터
- `misc`
  - `misc/take-a-picture` | 사진 촬영 트리거
  - `misc/csi-raw-data` | csi raw value

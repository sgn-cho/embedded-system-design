# Wi-Fi

esp32 마이크로컨트롤러의 Wi-Fi 통신을 담당하는 모듈

## Configuration

- `WIFI_SSID` | 연결할 Wi-Fi의 SSID
- `WIFI_PASSWORD` | 연결할 Wi-Fi의 비밀번호
- `WIFI_MAXIUM_ENTRY` | 최대 연결 재시도 횟수

## Files

### `init.c`

Wi-Fi station 모드를 초기화하고 연결을 시도하는 파일입니다.

### `handler.c`

Wi-Fi station 모드 초기화 시 callback 핸들러를 정의한 파일입니다.

### `csi.c`

CSI (Channel State Information) 관련 데이터를 처리하기 위한 파일입니다.

## CSI (Channel State Information) 구조

현재 CSI 데이터를 주고받기 위해 고려할 수 있는 선택지는 다음과 같습니다.

1. 라우터의 CSI를 받아오는 방법
2. 2개 이상의 ESP를 이용하여, ESP-NOW를 통해 통신하는 방법
3. 라우터를 거쳐 ping replay

ESP 내부 CSI 포맷은 [esp-idf documentation](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-guides/wifi.html#wi-fi-channel-state-information)에서 정의되어 있습니다.

# MQTT5 Client

stargazer에서 사용하는 mqtt5 통신을 담당하는 component

## Prequisites

`idf.py menuconfig` 등을 이용하여 다음과 같이 값을 설정하여야 합니다. 해당 설정값은 `sdkconfig.defaults`에서도 확인하실 수 있습니다.드

- `CONFIG_MQTT_PROTOCOL_311=n`
- `CONFIG_MQTT_PROTOCOL_5=y`

## Files

- `init.c` | MQTT5 client 최초 초기화 관련 코드
- `handler.c` | MQTT5 event handler 코드
- `pub.c` | MQTT5 message publish 코드

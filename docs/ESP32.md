# ESP32

ESP32는 Espressif에서 개발한 마이크로프로세서로 구체적인 모델은 [나무위키](https://namu.wiki/w/ESP32)를 가볍게 참조하시기 바랍니다. ESP32-H2의 경우 Matter와 함께 발표된 Thread 프로토콜을 지원하며, 대다수의 모델은 Wi-Fi와 Bluetooth를 기본적으로 지원합니다.

## IoT Development Framework

다음 [repo](https://github.com/espressif/esp-idf)를 참조해주시기 바랍니다. ESP-IDF는 RTOS를 내장하고 있습니다.

## Deep learning Resource

ESP32 모델 중 일부의 경우 Espressif에서 Deep learning 가속을 위한 [SDK](https://github.com/espressif/esp-dl)를 제공하고 있습니다. 공식 문서에서 발췌한 각 인공지능 모델에 따른 Latency는 다음과 같습니다.

### [Face Recognition](https://github.com/espressif/esp-dl/blob/master/examples/face_recognition/README.md)

| SoC | 8-bit | 16-bit |
|:---:| ----:| ----:|
| ESP32 | 13,301 ms | 5,041 ms |
| ESP32-S3 | 287 ms | 554 ms |

### [Face Detection](https://github.com/espressif/esp-dl/tree/master/examples/human_face_detect)

`TWO_STAGE` 가 `true` 일 때 face landmark 인식 과정을 거쳐 인식률이 향상되지만 Latency가 증가합니다.

|SoC|`TWO_STAGE` = 1|`TWO_STAGE` = 0|
|:-:|--:|--:|
|ESP32|415,246 us|154,687 us|
|ESP32-S2|1,052,363 us|309,159 us|
|ESP32-S3|56,303 us|16,614 us|

## Matter

Espressif는 matter protocol을 쉽게 구현할 수 있게 [SDK](https://github.com/espressif/esp-matter)를 제공합니다.

[![Video Label](http://img.youtube.com/vi/i2doZomr9V0/0.jpg)](https://www.youtube.com/watch?v=i2doZomr9V0)


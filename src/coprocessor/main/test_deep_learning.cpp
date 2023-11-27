#include <stdio.h>
#include <human_face_detect_mnp01.hpp>
#include <human_face_detect_msr01.hpp>
#include <esp_log.h>

extern "C" void test_deep_learning(uint8_t **pixels) {

    HumanFaceDetectMSR01 s1(0.3F, 0.5F, 10, 0.2F);

    ESP_LOGI("test_deep_learning", "inference start");

    std::list<dl::detect::result_t> &results
        = s1.infer((uint8_t *)(*pixels), {768, 1024, 3});
    int i = 0;

    ESP_LOGI("test_deep_learning", "inference end");
    ESP_LOGI("test_deep_learning", "results.size() = %d", results.size());
    for (std::list<dl::detect::result_t>::iterator prediction = results.begin(); prediction != results.end(); prediction++, i++)
    {

        printf("[%d] score: %f, box: [%d, %d, %d, %d]\n", i, prediction->score, prediction->box[0], prediction->box[1], prediction->box[2], prediction->box[3]);
    }
}
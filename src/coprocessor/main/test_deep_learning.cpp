#include <stdio.h>
#include <human_face_detect_mnp01.hpp>
#include <human_face_detect_msr01.hpp>

extern "C" void test_deep_learning(uint8_t **pixels) {

    HumanFaceDetectMSR01 s1(0.1F, 0.5F, 10, 0.2F);
    HumanFaceDetectMNP01 s2(0.5F, 0.3F, 5);

    std::list<dl::detect::result_t> &candidates
        = s1.infer((uint8_t *)(*pixels), {320, 240, 3});
    std::list<dl::detect::result_t> &results
        = s2.infer((uint8_t *)(*pixels), {320, 240, 3}, candidates);

    int i = 0;
    for (std::list<dl::detect::result_t>::iterator prediction = results.begin(); prediction != results.end(); prediction++, i++)
    {
        printf("[%d] score: %f, box: [%d, %d, %d, %d]\n", i, prediction->score, prediction->box[0], prediction->box[1], prediction->box[2], prediction->box[3]);
        printf("    left eye: (%3d, %3d), ", prediction->keypoint[0], prediction->keypoint[1]);
        printf("right eye: (%3d, %3d)\n", prediction->keypoint[6], prediction->keypoint[7]);
        printf("    nose: (%3d, %3d)\n", prediction->keypoint[4], prediction->keypoint[5]);
        printf("    mouth left: (%3d, %3d), ", prediction->keypoint[2], prediction->keypoint[3]);
        printf("mouth right: (%3d, %3d)\n\n", prediction->keypoint[8], prediction->keypoint[9]);
    }
}
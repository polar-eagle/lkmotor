//
// Created by 82653 on 25-4-20.
//

#ifndef LKMOTOR_H
#define LKMOTOR_H
#include "gcan.h"
#include <array>
#include <cstring>
#include "command.h"

class lkmotor {

public:
    unsigned char mla[8];
    gcan can;
    lkmotor();
    ~lkmotor();
    void tx_can(int id, const unsigned char * data);
    int8_t rx_can(P_CAN_OBJ vco);
    void closeMotor(int id);
    void openMotor(int id);
    void stopMotor(int id);
    void clearError(int id);
    int16_t state2(CAN_OBJ rec); // power
    double multiLoopAngle(CAN_OBJ rec);
    void speedControl(int id, int32_t speed);
    void positionControl(int id, double pos, uint16_t speed);
    void positionControl(int id, double pos);
    void powerControl(int id, int16_t power);
    void setPower(int id, int16_t power);
    void setZero(int id);
};

#endif //LKMOTOR_H

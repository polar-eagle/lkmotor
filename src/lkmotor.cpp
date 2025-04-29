//
// Created by 82653 on 25-4-20.
//

#include "lkmotor.h"
using namespace std;

lkmotor::lkmotor() {
    can.init_can(1000);
}

lkmotor::~lkmotor() {
    can.CloseDevice();
}

void lkmotor::tx_can(int id, const unsigned char * data) {
    CAN_OBJ send;
    send.ID = command::ID_st + id;
    send.SendType = 0;
    send.RemoteFlag = 0;
    send.ExternFlag = 0;
    send.DataLen = 8;
    for (int i = 0; i < 8; ++i) send.Data[i] = data[i];
    DWORD t;
    cout << "sending" << endl;
    t = can.Transmit(&send, 1);
    if (t == STATUS_ERR) cout << "send error" << endl;
    else cout << "send success" << endl;
}

int8_t lkmotor::rx_can(P_CAN_OBJ rec) {
    return can.Receive(rec, 1, 0);
}

void lkmotor::closeMotor(int id) {
    tx_can(id, command::closeMotor);
}

void lkmotor::openMotor(int id) {
    tx_can(id, command::openMotor);
}

void lkmotor::stopMotor(int id) {
    tx_can(id, command::stopMotor);
}

void lkmotor::clearError(int id) {
    tx_can(id, command::clearError);
}

int16_t lkmotor::state2(CAN_OBJ rec) {
    int16_t power = 0;
    power |= int16_t(rec.Data[2]);
    power |= int16_t(rec.Data[3]) << 8;
    return power;
}

double lkmotor::multiLoopAngle(CAN_OBJ rec) {
    int64_t angle=0;
    for (int j=1;j<8;j++)
        angle |= int64_t(rec.Data[j])<<(8*j-8);
    angle |= int64_t(rec.Data[7])<<56;
    double angle_d=double(angle)/100.0;
    return angle_d;
}

void lkmotor::speedControl(int id, int32_t speed) {
    unsigned char data[8];
    speed*=100;
    memcpy(data,command::speedControl,sizeof(command::speedControl));
    for (int i=4;i<8;++i) {
        data[i] = speed & 0xFF;
        speed >>= 8;
    }
    tx_can(id, data);
}

void lkmotor::positionControl(int id, double pos, uint16_t speed) {
    unsigned char data[8];
    memcpy(data,command::posControl2,sizeof(command::posControl1));
    data[2] = speed & 0xFF;
    data[3] = (speed >> 8) & 0xFF;
    int32_t angleControl = int32_t(pos * 100.0);
    for (int i=4;i<8;++i) {
        data[i] = angleControl & 0xFF;
        angleControl >>= 8;
    }
    tx_can(id, data);
}

void lkmotor::positionControl(int id, double pos) {
    unsigned char data[8];
    memcpy(data,command::posControl1,sizeof(command::posControl1));
    int32_t angleControl = int32_t(pos * 100.0);
    for (int i=4;i<8;++i) {
        data[i] = angleControl & 0xFF;
        angleControl >>= 8;
    }
    tx_can(id, data);
}

void lkmotor::powerControl(int id, int16_t power) {
    unsigned char data[8];
    memcpy(data,command::powerControl,sizeof(command::powerControl));
    data[4] = power & 0xFF;
    data[5] = (power >> 8) & 0xFF;
    tx_can(id, data);
}

void lkmotor::setPower(int id, int16_t power) {
    unsigned char data[8];
    memcpy(data,command::setPower,sizeof(command::setPower));
    data[4] = power & 0xFF;
    data[5] = (power >> 8) & 0xFF;
    tx_can(id, data);
}

void lkmotor::setZero(int id) {
    tx_can(id, command::setZero);
}


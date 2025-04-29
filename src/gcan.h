//
// Created by 82653 on 25-4-15.
//

#ifndef GCAN_H
#define GCAN_H
#include <thread>
#include <atomic>
#include <iostream>
#include <ECanVci64.h>


class gcan{
public:
    // 设备操作函数
    DWORD OpenDevice();
    DWORD ResetCAN();
    DWORD CloseDevice();

    // CAN初始化与控制
    DWORD InitCAN(P_INIT_CONFIG pInitConfig);
    DWORD StartCAN();

    // 数据收发函数
    ULONG Transmit(P_CAN_OBJ pSend, ULONG Len);
    ULONG Receive(P_CAN_OBJ pReceive, ULONG Len, INT WaitTime = -1);

    // 状态与信息读取
    ULONG GetReceiveNum();
    DWORD ClearBuffer();
    DWORD ReadErrInfo(P_ERR_INFO pErrInfo);
    DWORD ReadCANStatus(P_CAN_STATUS pCANStatus);

    // 配置与板卡信息
    DWORD SetReference(DWORD RefType, PVOID pData);
    DWORD ReadBoardInfo(P_BOARD_INFO pInfo);

    int devtype=USBCAN1;//设备类型号//
    int devind=0; //设备索引号
    int res;    //保留参数，通常为0
    int canind=0; //第几路can
    int reftype;//参数类型
    bool musbcanstart; //是否打开设备

    void init_can(int baud);

};
#endif //LKMOTOR_H

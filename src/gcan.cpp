//
// Created by 82653 on 25-4-16.
//
#include "gcan.h"
using namespace std;

DWORD gcan::OpenDevice() {
    return ::OpenDevice(devtype, devind, res);
}
DWORD gcan::ResetCAN() {
    return ::ResetCAN(devtype, devind, canind);
}
DWORD gcan::CloseDevice() {
    return ::CloseDevice(devtype, devind);
}
DWORD gcan::InitCAN(P_INIT_CONFIG pInitConfig) {
    return ::InitCAN(devtype, devind, canind, pInitConfig);
}
DWORD gcan::StartCAN() {
    return ::StartCAN(devtype, devind, canind);
}
ULONG gcan::Transmit(P_CAN_OBJ pSend, ULONG Len) {
    // cout<<"transmitting"<<endl;
    return ::Transmit(devtype, devind, canind, pSend, Len);
}
ULONG gcan::Receive(P_CAN_OBJ pReceive, ULONG Len, INT WaitTime) {
    return ::Receive(devtype, devind, canind, pReceive, Len, WaitTime);
}
ULONG gcan::GetReceiveNum() {
    return ::GetReceiveNum(devtype, devind, canind);
}
DWORD gcan::ClearBuffer() {
    return ::ClearBuffer(devtype, devind, canind);
}
DWORD gcan::ReadErrInfo(P_ERR_INFO pErrInfo) {
    return ::ReadErrInfo(devtype, devind, canind, pErrInfo);
}
DWORD gcan::ReadCANStatus(P_CAN_STATUS pCANStatus) {
    return ::ReadCANStatus(devtype, devind, canind, pCANStatus);
}
DWORD gcan::SetReference(DWORD RefType, PVOID pData) {
    return ::SetReference(devtype, devind, canind, RefType, pData);
}
DWORD gcan::ReadBoardInfo(P_BOARD_INFO pInfo) {
    return ::ReadBoardInfo(devtype, devind, pInfo);
}

void gcan::init_can(int baud) {
    bool ok;
    ERR_INFO vei;
    CAN_OBJ preceive[100];
//    CAN_OBJ psend;
//    int baud=0x10000000;//参数有关数据缓冲区地址首指针
//      int pdata=0x00;//参数有关数据缓冲区地址首指针
   //打开设备
    musbcanstart=false;
    if(OpenDevice()==STATUS_ERR )//为1表示操作成功，0表示操作失败。
    {
        this_thread::sleep_for(chrono::milliseconds(100));
        if(ReadErrInfo(&vei)!=STATUS_ERR)
            cout<<"open failed"<<hex<<vei.ErrCode<<endl;
        return;
    }
    else cout<<"open success"<<endl;

    //初始化
    INIT_CONFIG init_config;//INIT_CONFIG
    //init_config.Mode=0;//0正常模式//1为只听模式//2为自发自收模式//
    init_config.Filter=0;//滤波方式，单滤波
    switch(baud)
    {
        case 1000:
            init_config.Timing0 = 0;
            init_config.Timing1 =0x14;
            break;
        case 800:
            init_config.Timing0 = 0;
            init_config.Timing1 = 0x16;
            break;
        case 666:
            init_config.Timing0 = 0x80;
            init_config.Timing1 = 0xb6;
            break;
        case 500:
            init_config.Timing0 = 0;
            init_config.Timing1 = 0x1c;
            break;
        case 400:
            init_config.Timing0 = 0x80;
            init_config.Timing1 = 0xfa;
            break;
        case 250:
            init_config.Timing0 = 0x01;
            init_config.Timing1 = 0x1c;
            break;
        case 200:
            init_config.Timing0 = 0x81;
            init_config.Timing1 = 0xfa;
            break;
        case 125:
            init_config.Timing0 = 0x03;
            init_config.Timing1 = 0x1c;
            break;
        case 100:
            init_config.Timing0 = 0x04;
            init_config.Timing1 = 0x1c;
            break;
        case 80:
            init_config.Timing0 = 0x83;
            init_config.Timing1 = 0xff;
            break;
        case 50:
            init_config.Timing0 = 0x09;
            init_config.Timing1 = 0x1c;
            break;
    }

    init_config.AccCode=0x000000;//验收码
    init_config.AccMask=0xFFFFFF;//屏蔽码
    this_thread::sleep_for(chrono::milliseconds(100));
    if(InitCAN(&init_config)==STATUS_ERR)
    {
        cout<<"Init Error"<<endl;
        CloseDevice();
        return;
    }
    else cout<<"Init success"<<endl;


    if(StartCAN()==STATUS_ERR){
        cout<<"start fail";
        CloseDevice();
        return;
    }
    else{
        cout<<"start success"<<endl;
        musbcanstart=true;
        ClearBuffer();
    }
    this_thread::sleep_for(chrono::milliseconds(100));
}

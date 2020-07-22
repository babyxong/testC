/**
 * Copyright (C), 2020, Sugon Information Industry Co., Ltd.
 *
 * @file    simSCSI.h
 * @author  徐宏
 * @date    2020.07.21
 * @brief    SCSI命令处理头文件
 * @note     新增文件
 */ 
#ifndef __SIM_SCSI_H__
#define __SIM_SCSI_H__

#include "simSCSIpub.h"

#define SCSI_CMD_BUFF_SIZE 16

///< SCSI SENSE DATA异常sense配置关键值
typedef struct SimScsiSense {
   U8 key;   ///< sense key
   U8 asc;   ///< sense asc
   U8 ascq;  ///< sense ascq
} SimScsiSense_t;

///< SCSI数据传输方向
typedef enum SimScsiXferMode {
    SCSI_XFER_NOEXCHANGE,         ///< 无数据交换，例:TEST_UNIT_READY …
    SCSI_XFER_FROM_DEV,     ///< 数据从盘获取，例:READ、INQUIRY、MODE_SENSE…
    SCSI_XFER_TO_DEV,       ///< 数据转入盘，例:WRITE、MODE_SELECT…
} SimScsiXferMode_t;

///< SCSI命令数据结构，CDB解析的内容放到下面的关键值内
typedef struct SimScsiCmd {
    U8      cmdBuf[SCSI_CMD_BUFF_SIZE];  ///< SCSI的CDB命令实例
    U32     cmdLen;      ///< CDB buff长度
    size_t  xferLen;     ///< 数据传输长度
    U64     lba;         ///< LBA
    SimScsiXferMode_t xferMode; ///< 数据传输方向
} SimScsiCmd_t;

///< SCSI 数据缓存
typedef struct IOvector {
    void *iovBase; ///< 数据缓冲区基地址
    size_t iovLen; ///< 数据缓冲区长度
}IOvector_t;

typedef struct SimScsiReqOps SimScsiReqOps_t;

///< SCSI请求数据结构
typedef struct SimScsiRequest {
    SimSCSIBus_t *pBus; ///< SCSI BUS结构体
    struct DeviceAccessRequest *pDar; ///< 保存DAR结构指针
    /** 保存ScsiDevice结构指针，预期通过
     *  DAR channelID，targetDeviceID，LUN ID(0)找到对应的device
     */
    struct SimSCSIDevice *pDev;
    const SimScsiReqOps_t *ops; ///< CDB命令对应的处理函数回调组
    U32 refCount;       ///< req引用计数
    U32 lun;            ///< 逻辑单元数(模拟盘为0)
    U32 status;         ///< CDB命令返回处理结构，结束时回调到DAR的 scsiStatus
    size_t dataLen;     ///< 传输数据长度，queue中使用的是resid
    SimScsiCmd_t cmd;   ///< SCSI命令结构体
    ///< CDB命令请求处理中存储的Sense_data结果，请求处理完成时回填到DAR中
    U8   sense[SCSI_SENSE_BUF_SIZE]; 
    U32  senseLen;      ///< Sense_data数据长度
    bool enqueued;      ///< 请求是否入段标志
    bool ioCanceled;    ///< 请求已经取消标志
    bool retry;         ///< IO错误操作重试标志
    bool dmaStarted;    ///< DMA传输开始标志
    BlockAIOCB *aiocb;  ///< AIO刷盘的回调函数
    //QTAILQ_ENTRY(SimScsiRequest_t) next;  ///< 数据链表
    SimDiskReq_t diskReq;            ///< 模拟盘请求数据结构
    IOvector_t iov;     ///< 数据IOV结构
}SimScsiRequest_t;

///< SCSI消息处理回调函数组定义
typedef struct SimScsiReqOps {
    void (*freeReqIov)(SimScsiRequest_t *req);   ///< 释放命令申请的数据缓存空间
    S32  (*sendCmd)(SimScsiRequest_t *req);      ///< 模拟SCSI CDB命令处理流程
    void (*readData)(SimScsiRequest_t *req);     ///< SCSI 数据读
    void (*writeData)(SimScsiRequest_t *req);    ///< SCSI 数据写
    U8  *(*getReqIov)(SimScsiRequest_t *req);    ///< 获取命令的ioBase地址
};

S32 simScsiCdbParse(SimSCSIDevice *pDev, SimScsiCmd_t *pCmd, U8 *pDarCdb);



#endif ///<__SIM_SCSI_H__

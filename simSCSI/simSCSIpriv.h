/**
 * Copyright (C), 2020, Sugon Information Industry Co., Ltd.
 *
 * @file    simSCSIpriv.h
 * @author  徐宏
 * @date    2020.07.21
 * @brief    SCSI命令处理私有头文件
 * @note     新增文件
 */
#ifndef __SIM_SCSI_PRIV_H__
#define __SIM_SCSI_PRIV_H__
#include "simSCSIpriv.c"


#define SCSI_SENSE_LEN 18

///< 根据CDB OPCODE分组
#define SCSI_OPCODE_GRP(opcode) (opcode >> 5)

#define SCSI_OPCODE_GRP_6B      0x00
#define SCSI_OPCODE_GRP_10B1    0x01
#define SCSI_OPCODE_GRP_10B2    0x02
#define SCSI_OPCODE_GRP_12B     0x05
#define SCSI_OPCODE_GRP_16B     0x04

///< CDB命令长度
#define SCSI_CDB_LEN6   6       
#define SCSI_CDB_LEN10  10
#define SCSI_CDB_LEN12  12
#define SCSI_CDB_LEN16  16

#define  simSCSICheckPtr(ptr) \
    if (!ptr) {  \
        printf("ptr is Nul !\n"); \
        log();  \//TODO : 增加打印
    }


/**
 * @brief   SCSI解析CDB长度
 * @param   cmbBuf [i], CDB命令buff
 * @return   >0:解析CDB长度， <0:解析CDB长度错误
 */
U32 simScsiCdbLenParse(U8 *cmbBuf);


#endif ///< __SIM_SCSI_PRIV_H__


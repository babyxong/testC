/**
 * Copyright (C), 2020, Sugon Information Industry Co., Ltd.
 *
 * @file    simSCSIpriv.c
 * @author  徐宏
 * @date    2020.07.21
 * @brief    SCSI命令处理私有部分
 * @note     新增文件
 */

#include "simSCSIpriv.h"
#include "simSCSIpub.h"

///<  No sense data available 
const struct SimScsiSense_t sense_code_NO_SENSE = {
    .key = NO_SENSE , .asc = 0x00 , .ascq = 0x00
};

///<  LUN not ready, Manual intervention required 
const struct SimScsiSense_t sense_code_LUN_NOT_READY = {
    .key = NOT_READY, .asc = 0x04, .ascq = 0x03
};

///<  LUN not ready, Medium not present 
const struct SimScsiSense_t sense_code_NO_MEDIUM = {
    .key = NOT_READY, .asc = 0x3a, .ascq = 0x00
};

///<  LUN not ready, medium removal prevented 
const struct SimScsiSense_t sense_code_NOT_READY_REMOVAL_PREVENTED = {
    .key = NOT_READY, .asc = 0x53, .ascq = 0x02
};

///<  Hardware error, internal target failure 
const struct SimScsiSense_t sense_code_TARGET_FAILURE = {
    .key = HARDWARE_ERROR, .asc = 0x44, .ascq = 0x00
};

///<  Illegal request, invalid command operation code 
const struct SimScsiSense_t sense_code_INVALID_OPCODE = {
    .key = ILLEGAL_REQUEST, .asc = 0x20, .ascq = 0x00
};

///<  Illegal request, LBA out of range 
const struct SimScsiSense_t sense_code_LBA_OUT_OF_RANGE = {
    .key = ILLEGAL_REQUEST, .asc = 0x21, .ascq = 0x00
};

///<  Illegal request, Invalid field in CDB 
const struct SimScsiSense_t sense_code_INVALID_FIELD = {
    .key = ILLEGAL_REQUEST, .asc = 0x24, .ascq = 0x00
};

///<  Illegal request, Invalid field in parameter list 
const struct SimScsiSense_t sense_code_INVALID_PARAM = {
    .key = ILLEGAL_REQUEST, .asc = 0x26, .ascq = 0x00
};

///<  Illegal request, Parameter list length error 
const struct SimScsiSense_t sense_code_INVALID_PARAM_LEN = {
    .key = ILLEGAL_REQUEST, .asc = 0x1a, .ascq = 0x00
};

///<  Illegal request, LUN not supported 
const struct SimScsiSense_t sense_code_LUN_NOT_SUPPORTED = {
    .key = ILLEGAL_REQUEST, .asc = 0x25, .ascq = 0x00
};

///<  Illegal request, Saving parameters not supported 
const struct SimScsiSense_t sense_code_SAVING_PARAMS_NOT_SUPPORTED = {
    .key = ILLEGAL_REQUEST, .asc = 0x39, .ascq = 0x00
};

///<  Illegal request, Incompatible medium installed 
const struct SimScsiSense_t sense_code_INCOMPATIBLE_FORMAT = {
    .key = ILLEGAL_REQUEST, .asc = 0x30, .ascq = 0x00
};

///<  Illegal request, medium removal prevented 
const struct SimScsiSense_t sense_code_ILLEGAL_REQ_REMOVAL_PREVENTED = {
    .key = ILLEGAL_REQUEST, .asc = 0x53, .ascq = 0x02
};

///<  Illegal request, Invalid Transfer Tag 
const struct SimScsiSense_t sense_code_INVALID_TAG = {
    .key = ILLEGAL_REQUEST, .asc = 0x4b, .ascq = 0x01
};

///<  Command aborted, I/O process terminated 
const struct SimScsiSense_t sense_code_IO_ERROR = {
    .key = ABORTED_COMMAND, .asc = 0x00, .ascq = 0x06
};

///<  Command aborted, I_T Nexus loss occurred 
const struct SimScsiSense_t sense_code_I_T_NEXUS_LOSS = {
    .key = ABORTED_COMMAND, .asc = 0x29, .ascq = 0x07
};

///<  Command aborted, Logical Unit failure 
const struct SimScsiSense_t sense_code_LUN_FAILURE = {
    .key = ABORTED_COMMAND, .asc = 0x3e, .ascq = 0x01
};

///<  Command aborted, Overlapped Commands Attempted 
const struct SimScsiSense_t sense_code_OVERLAPPED_COMMANDS = {
    .key = ABORTED_COMMAND, .asc = 0x4e, .ascq = 0x00
};

///<  Command aborted, LUN Communication Failure 
const struct SimScsiSense_t sense_code_LUN_COMM_FAILURE = {
    .key = ABORTED_COMMAND, .asc = 0x08, .ascq = 0x00
};

///<  Medium Error, Unrecovered read error 
const struct SimScsiSense_t sense_code_READ_ERROR = {
    .key = MEDIUM_ERROR, .asc = 0x11, .ascq = 0x00
};

///<  Not ready, Cause not reportable 
const struct SimScsiSense_t sense_code_NOT_READY = {
    .key = NOT_READY, .asc = 0x04, .ascq = 0x00
};

///<  Unit attention, Capacity data has changed 
const struct SimScsiSense_t sense_code_CAPACITY_CHANGED = {
    .key = UNIT_ATTENTION, .asc = 0x2a, .ascq = 0x09
};

///<  Unit attention, Power on, reset or bus device reset occurred 
const struct SimScsiSense_t sense_code_RESET = {
    .key = UNIT_ATTENTION, .asc = 0x29, .ascq = 0x00
};

///<  Unit attention, SCSI bus reset 
const struct SimScsiSense_t sense_code_SCSI_BUS_RESET = {
    .key = UNIT_ATTENTION, .asc = 0x29, .ascq = 0x02
};

///<  Unit attention, No medium 
const struct SimScsiSense_t sense_code_UNIT_ATTENTION_NO_MEDIUM = {
    .key = UNIT_ATTENTION, .asc = 0x3a, .ascq = 0x00
};

///<  Unit attention, Medium may have changed 
const struct SimScsiSense_t sense_code_MEDIUM_CHANGED = {
    .key = UNIT_ATTENTION, .asc = 0x28, .ascq = 0x00
};

///<  Unit attention, Reported LUNs data has changed 
const struct SimScsiSense_t sense_code_REPORTED_LUNS_CHANGED = {
    .key = UNIT_ATTENTION, .asc = 0x3f, .ascq = 0x0e
};

///<  Unit attention, Device internal reset 
const struct SimScsiSense_t sense_code_DEVICE_INTERNAL_RESET = {
    .key = UNIT_ATTENTION, .asc = 0x29, .ascq = 0x04
};

///<  Data Protection, Write Protected 
const struct SimScsiSense_t sense_code_WRITE_PROTECTED = {
    .key = DATA_PROTECT, .asc = 0x27, .ascq = 0x00
};

///<  Data Protection, Space Allocation Failed Write Protect 
const struct SimScsiSense_t sense_code_SPACE_ALLOC_FAILED = {
    .key = DATA_PROTECT, .asc = 0x27, .ascq = 0x07
};


/**
 * @brief   SCSI解析CDB长度
 * @param   cmbBuf [i], CDB命令buff
 * @return   >0:解析CDB长度， <0:解析CDB长度错误
 */
S32 simScsiCdbLenParse(U8 *cmdBuf)
{
    S32 cmdLen;
    switch (SCSI_OPCODE_GRP(cmdBuf[0])) {
        case SCSI_OPCODE_GRP_6B:
            cmdLen = SCSI_CDB_LEN6;
            break;
        case SCSI_OPCODE_GRP_10B1:
        case SCSI_OPCODE_GRP_10B2:
            cmdLen = SCSI_CDB_LEN10;
            break;
        case SCSI_OPCODE_GRP_16B:
            cmdLen = SCSI_CDB_LEN16;
            break;
        case SCSI_OPCODE_GRP_12B:
            cmdLen = SCSI_CDB_LEN12;
            break;
        default:
            log();
            cmdLen = -1;
            break;
    }

   return cmdLen;
}

/**
 * @brief   SCSI解析数据传输xfer长度
 * @param   cmbBuf [i], CDB命令buff
 * @return   >0:解析CDB长度， <0:解析CDB长度错误
 */
S32 simScsiCdbXferLenParse(U8 *cmdBuf, U32 *pXferLen)
{  
    S32  ret = 0;
    
    switch (SCSI_OPCODE_GRP(cmdBuf[0])) {
        case SCSI_OPCODE_GRP_6B:
            *pXferLen = cmdBuf[4] & 0xFF;
            break;
        case SCSI_OPCODE_GRP_10B1:
        case SCSI_OPCODE_GRP_10B2:
            *pXferLen = SWAP16_BIG2LITTLE(cmdBuf + 7);
            
            break;
        case  SCSI_OPCODE_GRP_12B:
            *pXferLen = SWAP32_BIG2LITTLE(cmdBuf + 6);
            break;
        case SCSI_OPCODE_GRP_16B:
            *pXferLen = SWAP32_BIG2LITTLE(cmdBuf + 10);
            break;
        default:
            ret = -1;
            log();
            *pXferLen = -1;
            break;
    }

    return ret
}


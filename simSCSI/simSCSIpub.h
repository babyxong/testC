/**
 * Copyright (C), 2020, Sugon Information Industry Co., Ltd.
 *
 * @file    simSCSIpub.h
 * @author  徐宏
 * @date    2020.07.21
 * @brief    SCSI命令处理共同头文件
 * @note     新增文件
 */ 
 
#ifndef __SIM_SCSI_PUB_H__
#define __SIM_SCSI_PUB_H__

///< SCSI CDB OP_CODE
#define TEST_UNIT_READY       0x00
#define REWIND                0x01
#define REQUEST_SENSE         0x03
#define FORMAT_UNIT           0x04
#define READ_BLOCK_LIMITS     0x05
#define INITIALIZE_ELEMENT_STATUS 0x07
#define REASSIGN_BLOCKS       0x07
#define READ_6                0x08
#define WRITE_6               0x0a
#define SET_CAPACITY          0x0b
#define READ_REVERSE          0x0f
#define WRITE_FILEMARKS       0x10
#define SPACE                 0x11
#define INQUIRY               0x12
#define RECOVER_BUFFERED_DATA 0x14
#define MODE_SELECT           0x15
#define RESERVE               0x16
#define RELEASE               0x17
#define COPY                  0x18
#define ERASE                 0x19
#define MODE_SENSE            0x1a
#define LOAD_UNLOAD           0x1b
#define SCAN                  0x1b
#define START_STOP            0x1b
#define RECEIVE_DIAGNOSTIC    0x1c
#define SEND_DIAGNOSTIC       0x1d
#define ALLOW_MEDIUM_REMOVAL  0x1e
#define SET_WINDOW            0x24
#define READ_CAPACITY_10      0x25
#define GET_WINDOW            0x25
#define READ_10               0x28
#define WRITE_10              0x2a
#define SEND                  0x2a
#define SEEK_10               0x2b
#define LOCATE_10             0x2b
#define POSITION_TO_ELEMENT   0x2b
#define WRITE_VERIFY_10       0x2e
#define VERIFY_10             0x2f
#define SEARCH_HIGH           0x30
#define SEARCH_EQUAL          0x31
#define OBJECT_POSITION       0x31
#define SEARCH_LOW            0x32
#define SET_LIMITS            0x33
#define PRE_FETCH             0x34
#define READ_POSITION         0x34
#define GET_DATA_BUFFER_STATUS 0x34
#define SYNCHRONIZE_CACHE     0x35
#define LOCK_UNLOCK_CACHE     0x36
#define INITIALIZE_ELEMENT_STATUS_WITH_RANGE 0x37
#define READ_DEFECT_DATA      0x37
#define MEDIUM_SCAN           0x38
#define COMPARE               0x39
#define COPY_VERIFY           0x3a
#define WRITE_BUFFER          0x3b
#define READ_BUFFER           0x3c
#define UPDATE_BLOCK          0x3d
#define READ_LONG_10          0x3e
#define WRITE_LONG_10         0x3f
#define CHANGE_DEFINITION     0x40
#define WRITE_SAME_10         0x41
#define UNMAP                 0x42
#define READ_TOC              0x43
#define REPORT_DENSITY_SUPPORT 0x44
#define GET_CONFIGURATION     0x46
#define SANITIZE              0x48
#define GET_EVENT_STATUS_NOTIFICATION 0x4a
#define LOG_SELECT            0x4c
#define LOG_SENSE             0x4d
#define READ_DISC_INFORMATION 0x51
#define RESERVE_TRACK         0x53
#define MODE_SELECT_10        0x55
#define RESERVE_10            0x56
#define RELEASE_10            0x57
#define MODE_SENSE_10         0x5a
#define SEND_CUE_SHEET        0x5d
#define PERSISTENT_RESERVE_IN 0x5e
#define PERSISTENT_RESERVE_OUT 0x5f
#define VARLENGTH_CDB         0x7f
#define WRITE_FILEMARKS_16    0x80
#define READ_REVERSE_16       0x81
#define ALLOW_OVERWRITE       0x82
#define EXTENDED_COPY         0x83
#define ATA_PASSTHROUGH_16    0x85
#define ACCESS_CONTROL_IN     0x86
#define ACCESS_CONTROL_OUT    0x87
#define READ_16               0x88
#define COMPARE_AND_WRITE     0x89
#define WRITE_16              0x8a
#define WRITE_VERIFY_16       0x8e
#define VERIFY_16             0x8f
#define PRE_FETCH_16          0x90
#define SPACE_16              0x91
#define SYNCHRONIZE_CACHE_16  0x91
#define LOCATE_16             0x92
#define WRITE_SAME_16         0x93
#define ERASE_16              0x93
#define SERVICE_ACTION_IN_16  0x9e
#define WRITE_LONG_16         0x9f
#define REPORT_LUNS           0xa0
#define ATA_PASSTHROUGH_12    0xa1
#define MAINTENANCE_IN        0xa3
#define MAINTENANCE_OUT       0xa4
#define MOVE_MEDIUM           0xa5
#define EXCHANGE_MEDIUM       0xa6
#define SET_READ_AHEAD        0xa7
#define READ_12               0xa8
#define WRITE_12              0xaa
#define SERVICE_ACTION_IN_12  0xab
#define ERASE_12              0xac
#define READ_DVD_STRUCTURE    0xad
#define WRITE_VERIFY_12       0xae
#define VERIFY_12             0xaf
#define SEARCH_HIGH_12        0xb0
#define SEARCH_EQUAL_12       0xb1
#define SEARCH_LOW_12         0xb2
#define READ_ELEMENT_STATUS   0xb8
#define SEND_VOLUME_TAG       0xb6
#define READ_DEFECT_DATA_12   0xb7
#define SET_CD_SPEED          0xbb
#define MECHANISM_STATUS      0xbd
#define READ_CD               0xbe
#define SEND_DVD_STRUCTURE    0xbf

///< Status codes
#define GOOD                 0x00
#define CHECK_CONDITION      0x02
#define CONDITION_GOOD       0x04
#define BUSY                 0x08
#define INTERMEDIATE_GOOD    0x10
#define INTERMEDIATE_C_GOOD  0x14
#define RESERVATION_CONFLICT 0x18
#define COMMAND_TERMINATED   0x22
#define TASK_SET_FULL        0x28
#define ACA_ACTIVE           0x30
#define TASK_ABORTED         0x40

#define STATUS_MASK          0x3e

///<SENSE KEYS
#define NO_SENSE            0x00
#define RECOVERED_ERROR     0x01
#define NOT_READY           0x02
#define MEDIUM_ERROR        0x03
#define HARDWARE_ERROR      0x04
#define ILLEGAL_REQUEST     0x05
#define UNIT_ATTENTION      0x06
#define DATA_PROTECT        0x07
#define BLANK_CHECK         0x08
#define COPY_ABORTED        0x0a
#define ABORTED_COMMAND     0x0b
#define VOLUME_OVERFLOW     0x0d
#define MISCOMPARE          0x0e

///< DEVICE TYPES 模拟平台只有一种设备类型
#define TYPE_DISK           0x00

///< SCSI SENSE DATA异常sense配置关键值
typedef struct SimScsiSense {
   U8 key;   ///< sense key
   U8 asc;   ///< sense asc
   U8 ascq;  ///< sense ascq
} SimScsiSense_t;

///< No sense data available 
extern const struct SimScsiSense_t sense_code_NO_SENSE;
///<  LUN not ready, Manual intervention required
extern const struct SimScsiSense_t sense_code_LUN_NOT_READY;
///<  LUN not ready, Medium not present 
extern const struct SimScsiSense_t sense_code_NO_MEDIUM;
///<  LUN not ready, medium removal prevented
extern const struct SimScsiSense_t sense_code_NOT_READY_REMOVAL_PREVENTED;
///<  Hardware error, internal target failure 
extern const struct SimScsiSense_t sense_code_TARGET_FAILURE;
///<  Illegal request, invalid command operation code
extern const struct SimScsiSense_t sense_code_INVALID_OPCODE;
///<  Illegal request, LBA out of range 
extern const struct SimScsiSense_t sense_code_LBA_OUT_OF_RANGE;
///<  Illegal request, Invalid field in CDB 
extern const struct SimScsiSense_t sense_code_INVALID_FIELD;
///<  Illegal request, Invalid field in parameter list 
extern const struct SimScsiSense_t sense_code_INVALID_PARAM;
///<  Illegal request, Parameter list length error 
extern const struct SimScsiSense_t sense_code_INVALID_PARAM_LEN;
///<  Illegal request, LUN not supported 
extern const struct SimScsiSense_t sense_code_LUN_NOT_SUPPORTED;
///<  Illegal request, Saving parameters not supported 
extern const struct SimScsiSense_t sense_code_SAVING_PARAMS_NOT_SUPPORTED;
///<  Illegal request, Incompatible format 
extern const struct SimScsiSense_t sense_code_INCOMPATIBLE_FORMAT;
///<  Illegal request, medium removal prevented 
extern const struct SimScsiSense_t sense_code_ILLEGAL_REQ_REMOVAL_PREVENTED;
///<  Illegal request, Invalid Transfer Tag 
extern const struct SimScsiSense_t sense_code_INVALID_TAG;
///<  Command aborted, I/O process terminated 
extern const struct SimScsiSense_t sense_code_IO_ERROR;
///<  Command aborted, I_T Nexus loss occurred 
extern const struct SimScsiSense_t sense_code_I_T_NEXUS_LOSS;
///<  Command aborted, Logical Unit failure 
extern const struct SimScsiSense_t sense_code_LUN_FAILURE;
///<  Command aborted, LUN Communication failure 
extern const struct SimScsiSense_t sense_code_LUN_COMM_FAILURE;
///<  Command aborted, Overlapped Commands Attempted 
extern const struct SimScsiSense_t sense_code_OVERLAPPED_COMMANDS;
///<  Medium error, Unrecovered read error 
extern const struct SimScsiSense_t sense_code_READ_ERROR;
///<  LUN not ready, Cause not reportable 
extern const struct SimScsiSense_t sense_code_NOT_READY;
///<  Unit attention, Capacity data has changed 
extern const struct SimScsiSense_t sense_code_CAPACITY_CHANGED;
///<  Unit attention, SCSI bus reset 
extern const struct SimScsiSense_t sense_code_SCSI_BUS_RESET;
///<  LUN not ready, Medium not present 
extern const struct SimScsiSense_t sense_code_UNIT_ATTENTION_NO_MEDIUM;
///<  Unit attention, Power on, reset or bus device reset occurred 
extern const struct SimScsiSense_t sense_code_RESET;
///<  Unit attention, Medium may have changed
extern const struct SimScsiSense_t sense_code_MEDIUM_CHANGED;
///<  Unit attention, Reported LUNs data has changed 
extern const struct SimScsiSense_t sense_code_REPORTED_LUNS_CHANGED;
///<  Unit attention, Device internal reset 
extern const struct SimScsiSense_t sense_code_DEVICE_INTERNAL_RESET;
///<  Data Protection, Write Protected 
extern const struct SimScsiSense_t sense_code_WRITE_PROTECTED;
///<  Data Protection, Space Allocation Failed Write Protect 
extern const struct SimScsiSense_t sense_code_SPACE_ALLOC_FAILED;

#define SENSE_CODE(x) sense_code_ ## x

/**
 * @brief   大小端转换
 * @param   pSrcData  [in], 转换的源数据
 * @param   pDestData [out], 目标数据
 * @param   srcSize [in], 源数据长度
 * @param   dstSize [in], 目标数据长度
 * @return   =>0:成功， <0:失败
 */
static inline S32 simBigLittleSwap(const U8 *pSrcData, U8 *pDestData, 
        U32 srcSize, U32 dstSize)
{
    U32 i;
    S32 ret;

    if (NULL == pSrcData || NULL == pDestData) {
        printf(" 需要打印日志 ");
        log();
        ret = -1;
    }

    for (i = 0; i < (srcSize+1)/2; i++) {
        *(pDestData + srcSize -i -1) = *(pSrcData+i);
        *(pDestData+i) = *(pSrcData + srcSize -i -1);
    }

    for (i = srcSize; i < dstSize; i++) {
        *(pDestData + i) &= 0;
    }

    ret = 0;
end:
    return ret;
}

#endif ///< __SIM_SCSI_PUB_H__


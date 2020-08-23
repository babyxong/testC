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


#define SCSI_SENSE_FIX_LEN 18
#define SCSI_SENSE_STD_LEN 8

///< 根据CDB OPCODE分组
#define SCSI_OPCODE_GRP(opcode) (opcode >> 5)

#define SCSI_OPCODE_GRP_6B      0x00
#define SCSI_OPCODE_GRP_10B1    0x01
#define SCSI_OPCODE_GRP_10B2    0x02
#define SCSI_OPCODE_GRP_12B     0x05
#define SCSI_OPCODE_GRP_16B     0x04

///< CDB命令长度
#define SCSI_CDB_LEN6   
#define SCSI_CDB_LEN10  10
#define SCSI_CDB_LEN12  12
#define SCSI_CDB_LEN16  16


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

#define STATUS_INIT          (-1)
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

///< 16位大小端转换
#define SWAP16_BIGXLITTLE(px) \
    ((*(U16 *)px & 0xFF) << 8 |\
     (*(U16 *)px & 0xFF00) >> 8)

#define SWAP32_BIGXLITTLE(px) \
    (((*(U32 *)px & (0xFF <<  0)) << 24) |\
     ((*(U32 *)px & (0xFF <<  8)) << 8 ) |\
     ((*(U32 *)px & (0xFF << 16)) >> 8 ) |\
     ((*(U32 *)px & (0xFF << 24)) >> 24))

#define SWAP64_BIGXLITTLE(px) \
    (((*(U64 *)px & ((U64)0xFF <<  0)) << 56) |\
     ((*(U64 *)px & ((U64)0xFF <<  8)) << 40) |\
     ((*(U64 *)px & ((U64)0xFF << 16)) << 24) |\
     ((*(U64 *)px & ((U64)0xFF << 24)) << 8)  |\
     ((*(U64 *)px & ((U64)0xFF << 32)) >> 8)  |\
     ((*(U64 *)px & ((U64)0xFF << 40)) >> 24) |\
     ((*(U64 *)px & ((U64)0xFF << 48)) >> 40) |\
     ((*(U64 *)px & ((U64)0xFF << 56)) >> 56))

#define SWAP16_BIG2LITTLE(pX)   SWAP16_BIGXLITTLE(pX)
#define SWAP16_LITTLE2BIG(pX)   SWAP16_BIGXLITTLE(pX)
#define SWAP32_BIG2LITTLE(pX)   SWAP32_BIGXLITTLE(pX)
#define SWAP32_LITTLE2BIG(pX)   SWAP32_BIGXLITTLE(pX)
#define SWAP64_BIG2LITTLE(pX)   SWAP64_BIGXLITTLE(pX)
#define SWAP64_LITTLE2BIG(pX)   SWAP64_BIGXLITTLE(pX)

/**
 * @brief   模拟平台二期支持的CDB命令
 * @param   Opcode [in],
 * @return  0:支持， <0:不支持
 */
static inline Bool_t simScsiOpcodeIsSupport(U8 Opcode)
{
    Bool_t ret;
    switch (Opcode) {
        case TEST_UNIT_READY:
        case INQUIRY:
        case MODE_SENSE:
        case MODE_SENSE_10:
        case MODE_SELECT:
        case MODE_SELECT_10;
        case START_STOP:
        case READ_CAPACITY_10:
        case REQUEST_SENSE:
///<        case SYNCHRONIZE_CACHE:
///<        case SEEK_10:
        case UNMAP:
        case WRITE_SAME_10:
        case WRITE_SAME_16:
        case VERIFY_10:
        case VERIFY_12:
        case VERIFY_16:
        case READ_6:
        case READ_10:
        case READ_12:
        case READ_16:
        case WRITE_6:
        case WRITE_10:
        case WRITE_12:
        case WRITE_16:
        case WRITE_VERIFY_10:
        case WRITE_VERIFY_12:
        case WRITE_VERIFY_16:
        case REPORT_LUNS:
            ret = 0;
            break;
        default:
            ret = -1;
            break;
    }
    
    return ret;
}

#define SIM_CHECK_PTR(ptr, ret, errMsg)\
            if (NULL == ptr) { \
                log(errMsg);\
                return ret;
            }
            
#define SIM_CHECK_PTR_NORET(ptr, errMsg)\
            if (NULL == ptr) { \
                log(errMsg);\
                return;
            }




/**
 * @brief   SCSI解析xfer长度 
 * @param   pDev [i], C
 * @param   pCmd [i], CDB命令内部结构
 * @param   cmbBuf [i], CDB命令buff
 * @return   >0:解析CDB长度， <0:解析CDB长度错误
 */
S32 simScsiXferLenParse(SimSCSIDevice_t *pDev, SimSCSICmd_t *pCmd, U8 *cmdBuf);

/**
 * @brief   SCSI解析CDB长度
 * @param   cmbBuf [i], CDB命令buff
 * @return   >0:解析CDB长度， <0:解析CDB长度错误
 */
S32 simScsiCdbLenParse(U32 *pCmdLen, U8 *cmdBuf);

/**
 * @brief   SCSI解析数据传输模式解析
 * @param   cmbBuf [i], CDB命令buff
 @param   cmbBuf [i], CDB命令buff
 * @return   >=0:解析CDB长度， <0:解析CDB长度错误
 */
SimSCSIXferMode_t simScsiXferModeParse(SimSCSICmd_t *pCmd, U8 *cmdBuf);


#endif ///< __SIM_SCSI_PRIV_H__


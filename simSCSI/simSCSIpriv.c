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

#ifndef MIN
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif
#ifndef MAX
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#endif


///<  No sense data available 
const struct SimSCSISense_t sense_code_NO_SENSE = {
    .key = NO_SENSE , .asc = 0x00 , .ascq = 0x00
};

///<  LUN not ready, Manual intervention required 
const struct SimSCSISense_t sense_code_LUN_NOT_READY = {
    .key = NOT_READY, .asc = 0x04, .ascq = 0x03
};

///<  LUN not ready, Medium not present 
const struct SimSCSISense_t sense_code_NO_MEDIUM = {
    .key = NOT_READY, .asc = 0x3a, .ascq = 0x00
};

///<  LUN not ready, medium removal prevented 
const struct SimSCSISense_t sense_code_NOT_READY_REMOVAL_PREVENTED = {
    .key = NOT_READY, .asc = 0x53, .ascq = 0x02
};

///<  Hardware error, internal target failure 
const struct SimSCSISense_t sense_code_TARGET_FAILURE = {
    .key = HARDWARE_ERROR, .asc = 0x44, .ascq = 0x00
};

///<  Illegal request, invalid command operation code 
const struct SimSCSISense_t sense_code_INVALID_OPCODE = {
    .key = ILLEGAL_REQUEST, .asc = 0x20, .ascq = 0x00
};

///<  Illegal request, LBA out of range 
const struct SimSCSISense_t sense_code_LBA_OUT_OF_RANGE = {
    .key = ILLEGAL_REQUEST, .asc = 0x21, .ascq = 0x00
};

///<  Illegal request, Invalid field in CDB 
const struct SimSCSISense_t sense_code_INVALID_FIELD = {
    .key = ILLEGAL_REQUEST, .asc = 0x24, .ascq = 0x00
};

///<  Illegal request, Invalid field in parameter list 
const struct SimSCSISense_t sense_code_INVALID_PARAM = {
    .key = ILLEGAL_REQUEST, .asc = 0x26, .ascq = 0x00
};

///<  Illegal request, Parameter list length error 
const struct SimSCSISense_t sense_code_INVALID_PARAM_LEN = {
    .key = ILLEGAL_REQUEST, .asc = 0x1a, .ascq = 0x00
};

///<  Illegal request, LUN not supported 
const struct SimSCSISense_t sense_code_LUN_NOT_SUPPORTED = {
    .key = ILLEGAL_REQUEST, .asc = 0x25, .ascq = 0x00
};

///<  Illegal request, Saving parameters not supported 
const struct SimSCSISense_t sense_code_SAVING_PARAMS_NOT_SUPPORTED = {
    .key = ILLEGAL_REQUEST, .asc = 0x39, .ascq = 0x00
};

///<  Illegal request, Incompatible medium installed 
const struct SimSCSISense_t sense_code_INCOMPATIBLE_FORMAT = {
    .key = ILLEGAL_REQUEST, .asc = 0x30, .ascq = 0x00
};

///<  Illegal request, medium removal prevented 
const struct SimSCSISense_t sense_code_ILLEGAL_REQ_REMOVAL_PREVENTED = {
    .key = ILLEGAL_REQUEST, .asc = 0x53, .ascq = 0x02
};

///<  Illegal request, Invalid Transfer Tag 
const struct SimSCSISense_t sense_code_INVALID_TAG = {
    .key = ILLEGAL_REQUEST, .asc = 0x4b, .ascq = 0x01
};

///<  Command aborted, I/O process terminated 
const struct SimSCSISense_t sense_code_IO_ERROR = {
    .key = ABORTED_COMMAND, .asc = 0x00, .ascq = 0x06
};

///<  Command aborted, I_T Nexus loss occurred 
const struct SimSCSISense_t sense_code_I_T_NEXUS_LOSS = {
    .key = ABORTED_COMMAND, .asc = 0x29, .ascq = 0x07
};

///<  Command aborted, Logical Unit failure 
const struct SimSCSISense_t sense_code_LUN_FAILURE = {
    .key = ABORTED_COMMAND, .asc = 0x3e, .ascq = 0x01
};

///<  Command aborted, Overlapped Commands Attempted 
const struct SimSCSISense_t sense_code_OVERLAPPED_COMMANDS = {
    .key = ABORTED_COMMAND, .asc = 0x4e, .ascq = 0x00
};

///<  Command aborted, LUN Communication Failure 
const struct SimSCSISense_t sense_code_LUN_COMM_FAILURE = {
    .key = ABORTED_COMMAND, .asc = 0x08, .ascq = 0x00
};

///<  Medium Error, Unrecovered read error 
const struct SimSCSISense_t sense_code_READ_ERROR = {
    .key = MEDIUM_ERROR, .asc = 0x11, .ascq = 0x00
};

///<  Not ready, Cause not reportable 
const struct SimSCSISense_t sense_code_NOT_READY = {
    .key = NOT_READY, .asc = 0x04, .ascq = 0x00
};

///<  Unit attention, Capacity data has changed 
const struct SimSCSISense_t sense_code_CAPACITY_CHANGED = {
    .key = UNIT_ATTENTION, .asc = 0x2a, .ascq = 0x09
};

///<  Unit attention, Power on, reset or bus device reset occurred 
const struct SimSCSISense_t sense_code_RESET = {
    .key = UNIT_ATTENTION, .asc = 0x29, .ascq = 0x00
};

///<  Unit attention, SCSI bus reset 
const struct SimSCSISense_t sense_code_SCSI_BUS_RESET = {
    .key = UNIT_ATTENTION, .asc = 0x29, .ascq = 0x02
};

///<  Unit attention, No medium 
const struct SimSCSISense_t sense_code_UNIT_ATTENTION_NO_MEDIUM = {
    .key = UNIT_ATTENTION, .asc = 0x3a, .ascq = 0x00
};

///<  Unit attention, Medium may have changed 
const struct SimSCSISense_t sense_code_MEDIUM_CHANGED = {
    .key = UNIT_ATTENTION, .asc = 0x28, .ascq = 0x00
};

///<  Unit attention, Reported LUNs data has changed 
const struct SimSCSISense_t sense_code_REPORTED_LUNS_CHANGED = {
    .key = UNIT_ATTENTION, .asc = 0x3f, .ascq = 0x0e
};

///<  Unit attention, Device internal reset 
const struct SimSCSISense_t sense_code_DEVICE_INTERNAL_RESET = {
    .key = UNIT_ATTENTION, .asc = 0x29, .ascq = 0x04
};

///<  Data Protection, Write Protected 
const struct SimSCSISense_t sense_code_WRITE_PROTECTED = {
    .key = DATA_PROTECT, .asc = 0x27, .ascq = 0x00
};

///<  Data Protection, Space Allocation Failed Write Protect 
const struct SimSCSISense_t sense_code_SPACE_ALLOC_FAILED = {
    .key = DATA_PROTECT, .asc = 0x27, .ascq = 0x07
};

static const SimSCSIReqOps_t  gReqInvaildOpcodeOps = {
    .sendCmd = NULL;
};

static const SimSCSIReqOps_t gReqInvalidFieldOps = {
    .sendCmd = NULL:
};

static const SimSCSIReqOps_t gReqUnitAttentionOps = {
    .sendCmd = NULL:
};


static void simScsiCheckCondition(SimSCSIRequest_t *pReq, SimSCSISense_t sense)
{
    log("",pReq->lun, sense.key, sense.asc, sense.ascq);

    simScsiReqSenseBuild(pReq, sense, SIM_TURE);
    simScsiReqComplete(pReq, CHECK_CONDITION);
}


static void simScsiReqIovFree(SimSCSIRequest_t *pReq)
{   
    SIM_CHECK_PTR_NORET(pReq, "   ");
    SIM_CHECK_PTR_NORET(pReq->iov.iov_base, "   ");

    SIM_MEM_ZFREE(&pReq->iov.iov_base);
    pReq->iov.iov_base = NULL;
    
    return ;
}


static const S32 simScisDiskEmuSendCmd(SimSCSIRequest_t *pReq)
{   
    U8 outbuf;
    U64 sectorNum;
    int dateBuflen;
    U8 opcode = pReq->cmd.cmdBuf[0];
    
    
    switch (opcode) {
        ///< 普通管理查询控制命令不涉及盘数据
        case INQUIRY:
        case MODE_SENSE:
        case MODE_SENSE_10:
        case RESERVE:
        case RESERVE_10:
        case RELEASE:
        case RELEASE_10:
        case START_STOP:
        case ALLOW_MEDIUM_REMOVAL:
        case GET_CONFIGURATION:
        case GET_EVENT_STATUS_NOTIFICATION:
        case MECHANISM_STATUS:
        case REQUEST_SENSE:
            break;
            
        default:         
            if (!blk_is_available(s->qdev.conf.blk)) { ///< gouxiaofei 提供接口
                scsi_check_condition(r, SENSE_CODE(NO_MEDIUM));
            }
            xferlen =0;
            goto end;          
    }

    if (pReq->cmd.xferLen > 0xFFFF) {
        goto illegalRequest;
    }

    dateBuflen = MAX(4096, pReq->cmd.xferLen);

    if (NULL == pReq->iov.base) {
        pReq->iov.base = 
    }
    


end:
    return xferlen;
    
illegalRequest:    
    simScsiCheckCondition(pReq,SENSE_CODE(INVALID_FIELD));
    xferlen = 0;
    goto end;    
}


static const SimSCSIReqOps_t gSimScsiEmuReqOps = {
    .freeReqIov = simScsiReqIovFree,
    .sendCmd    = simScsiDiskEmuSendCmd,
    .readData   = simScsiDiskEmuRead,
    .writeData  = simScsiDiskEmuWrite,
    .getReqIov  = simScsiReqIovGet,
}
static const SimSCSIReqOps_t gSimScsiDmaReqOps = {
    .freeReqIov = simScsiReqIovFree,
    .sendCmd    = simScsiDiskDmaSendCmd,

    .getReqIov = simScsiReqIovGet,
}


static const SimSCSIReqOps_t *const gScsiReqOpsTable[256] = {
    [TEST_UNIT_READY]                 = &gSimScsiEmuReqOps,
    [INQUIRY]                         = &gSimScsiEmuReqOps,
    [MODE_SENSE]                      = &gSimScsiEmuReqOps,
    [MODE_SENSE_10]                   = &gSimScsiEmuReqOps,
    [START_STOP]                      = &gSimScsiEmuReqOps,
    [READ_CAPACITY_10]                = &gSimScsiEmuReqOps,   
    [REQUEST_SENSE]                   = &gSimScsiEmuReqOps,
    [SYNCHRONIZE_CACHE]               = &gSimScsiEmuReqOps,
    [SEEK_10]                         = &gSimScsiEmuReqOps,
    [MODE_SELECT]                     = &gSimScsiEmuReqOps,
    [MODE_SELECT_10]                  = &gSimScsiEmuReqOps,
    [UNMAP]                           = &gSimScsiEmuReqOps,
    [WRITE_SAME_10]                   = &gSimScsiEmuReqOps,
    [WRITE_SAME_16]                   = &gSimScsiEmuReqOps,
    [VERIFY_10]                       = &gSimScsiEmuReqOps,
    [VERIFY_12]                       = &gSimScsiEmuReqOps,
    [VERIFY_16]                       = &gSimScsiEmuReqOps,
    [REPORT_LUNS]                     = &gSimScsiEmuReqOps,

    [READ_6]                          = &gSimScsiDmaReqOps,
    [READ_10]                         = &gSimScsiDmaReqOps,
    [READ_12]                         = &gSimScsiDmaReqOps,
    [READ_16]                         = &gSimScsiDmaReqOps,
    [WRITE_6]                         = &gSimScsiDmaReqOps,
    [WRITE_10]                        = &gSimScsiDmaReqOps,
    [WRITE_12]                        = &gSimScsiDmaReqOps,
    [WRITE_16]                        = &gSimScsiDmaReqOps,
    [WRITE_VERIFY_10]                 = &gSimScsiDmaReqOps,
    [WRITE_VERIFY_12]                 = &gSimScsiDmaReqOps,
    [WRITE_VERIFY_16]                 = &gSimScsiDmaReqOps,
};



SimSCSIReqOps_t *simScsiReqOpsUaGet(void)
{
    return &gReqUnitAttentionOps;
}

SimSCSIReqOps_t *simScsiReqOpsErrFieldGet(void)
{
    return &gReqInvalidFieldOps;
}

SimSCSIReqOps_t *simScsiReqOpsErrOpcodeGet(void)
{
    return &gReqInvaildOpcodeOps;
}

SimSCSIReqOps_t *simScsiReqOpsMatch(U8 opcode)
{
    S32 ret = 0;
    SimSCSIReqOps_t *pOps = NULL;
    
    ret = simScsiOpcodeIsSupport(opcode);
    if (SIM_FALSE == ret) {
        pOps = &gReqInvaildOpcodeOps;
        goto end;
    }

    pOps = &gScsiReqOpsTable[opcode];
    
end:
    return pOps;
}




/**
 * @brief   SCSI解析CDB长度
 * @param   cmbBuf [i], CDB命令buff
 * @return   >=0:成功， <0:失败
 */
S32 simScsiCdbLenParse(U32 *pCmdLen, U8 *cmdBuf)
{
    S32 ret = 0;

    switch (SCSI_OPCODE_GRP(cmdBuf[0])) {
        case SCSI_OPCODE_GRP_6B:
            *pCmdLen = SCSI_CDB_LEN6;
            break;
        case SCSI_OPCODE_GRP_10B1:
        case SCSI_OPCODE_GRP_10B2:
            *pCmdLen = SCSI_CDB_LEN10;
            break;
        case SCSI_OPCODE_GRP_16B:
            *pCmdLen = SCSI_CDB_LEN16;
            break;
        case SCSI_OPCODE_GRP_12B:
            *pCmdLen = SCSI_CDB_LEN12;
            break;
        default:
            log();
            *pCmdLen = -1;
            ret = -1；
            break;
    }
    
    return ret;
}

/**
 * @brief   SCSI解析数据传输xfer长度
 * @param   cmbBuf [i], CDB命令buff
 * @return   >=0:解析CDB长度， <0:解析CDB长度错误
 */
static S32 simScsiCdbXferLenParse(U8 *cmdBuf, U64 *pXferLen)
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

    return ret;
}

/**
 * @brief   SCSI解析xfer长度 
 * @param   cmbBuf [i], CDB命令buff
 * @return   >0:解析CDB长度， <0:解析CDB长度错误
 */
S32 simScsiXferLenParse(SimSCSIDevice_t *pDev, U64 *pXferLen, U8 *cmdBuf)
{
    S32 ret = 0;
    
    ret = simScsiCdbXferLenParse(cmdBuf, pXferLen);
    if (0 > ret) {
        log();
        goto end;
    }
    
    switch (cmdBuf[0]) {
        case TEST_UNIT_READY:
        case START_STOP:
            *pXferLen = 0;
            break;
        case VERIFY_10:
        case VERIFY_12:
        case VERIFY_16:
             if ((cmdBuf[1] & 2) == 0) {
                    *pXferLen = 0;
                } else if ((cmdBuf[1] & 4) != 0) {
                    *pXferLen = 1;
                }
            *pXferLen *= pDev->blocksize;
            break;
        case WRITE_SAME_10:
        case WRITE_SAME_16:
            *pXferLen = (cmdBuf[1] & 1) ? 0 : pDev->blocksize;
            break;
        case READ_CAPACITY_10:
            *pXferLen = 8;
            break;
        case WRITE_6:
            ///< 根据协议 WRITE_6 TRANSFER LENGTH  等于0表示256个块
            if (*pXferLen == 0) {
                *pXferLen = 256;
            }
        case WRITE_10:
        case WRITE_VERIFY_10:
        case WRITE_12:
        case WRITE_VERIFY_12:
        case WRITE_16:
        case WRITE_VERIFY_16:
            *pXferLen *= pDev->blocksize;
            break;
        case READ_6:
            ///< 根据协议 READ_6 TRANSFER LENGTH  等于0表示256个块
            if (*pXferLen == 0) {
                *pXferLen = 256;
            }        
        case READ_10:
        case READ_12:
        case READ_16:
            *pXferLen *= pDev->blocksize;
            break;
        case INQUIRY:
            *pXferLen = SWAP16_BIG2LITTLE(cmdBuf + 3);
            break;
            
        default:
            log();
            ret = -1;
            *pXferLen = -1;
            break; 
   }
   
end:
   return ret;
}

/**
 * @brief   SCSI解析数据传输模式
 * @param   cmbBuf [i], CDB命令buff
 * @return   >=0:解析CDB长度， <0:解析CDB长度错误
 */
SimSCSIXferMode_t simScsiXferModeParse(SimSCSICmd_t *pCmd, U8 *cmdBuf)
{
    SimSCSIXferMode_t xferMode;

    if (0 == pCmd->xfer) {
        xferMode = SCSI_XFER_NOEXCHANGE;
        goto end;
    }
    
    switch (cmdBuf[0]) {
        case WRITE_6:
        case WRITE_10:
        case WRITE_VERIFY_10:
        case WRITE_12:
        case WRITE_VERIFY_12:
        case WRITE_16:
        case WRITE_VERIFY_16:
        case VERIFY_10:
        case VERIFY_12:
        case VERIFY_16:
        case COPY:
        case COPY_VERIFY:
        case COMPARE:
        case CHANGE_DEFINITION:
        case LOG_SELECT:
        case MODE_SELECT:
        case MODE_SELECT_10:
        case SEND_DIAGNOSTIC:
        case WRITE_BUFFER:
        case FORMAT_UNIT:
        case REASSIGN_BLOCKS:
        case SEARCH_EQUAL:
        case SEARCH_HIGH:
        case SEARCH_LOW:
        case UPDATE_BLOCK:
        case WRITE_LONG_10:
        case WRITE_SAME_10:
        case WRITE_SAME_16:
        case UNMAP:
        case SEARCH_HIGH_12:
        case SEARCH_EQUAL_12:
        case SEARCH_LOW_12:
        case MEDIUM_SCAN:
        case SEND_VOLUME_TAG:
        case SEND_CUE_SHEET:
        case SEND_DVD_STRUCTURE:
        case PERSISTENT_RESERVE_OUT:
        case MAINTENANCE_OUT:
        case SET_WINDOW:
        case SCAN:
            /* SCAN conflicts with START_STOP.  START_STOP has cmd->xfer set to 0 for
             * non-scanner devices, so we only get here for SCAN and not for START_STOP.
             */
            xferMode = SCSI_XFER_TO_DEV;
            break;
        case ATA_PASSTHROUGH_12:
        case ATA_PASSTHROUGH_16:
            /* T_DIR */
            xferMode = (pCmd->buf[2] & 0x8) ?
                       SCSI_XFER_FROM_DEV : SCSI_XFER_TO_DEV;
            break;
        default:
            xferMode = SCSI_XFER_FROM_DEV;
            break;
    }
    
end:
    return xferMode;   
}

/**
 * @brief   SCSI解析LBA(LOGICAL BLOCK ADDRESS)长度
 * @param   cmbBuf [i], CDB命令buff
 * @return   >=0:解析CDB长度， <0:解析CDB长度错误
 */
U64 simScsiLbaParse(U8 *cmdBuf)
{
    U64 lba;

    switch (SCSI_OPCODE_GRP(cmdBuf[0])) {        
        case SCSI_OPCODE_GRP_6B:
            ///< SCSI协议描述6字节的CDB可能包含21bit的LBA字段, 即CDB2后5bit
            lba = SWAP32_BIG2LITTLE(cmdBuf) & 0x1FFFFF;
            break;
        case SCSI_OPCODE_GRP_10B1:
        case SCSI_OPCODE_GRP_10B2:
        case  SCSI_OPCODE_GRP_12B:
            lba = SWAP32_BIG2LITTLE(cmdBuf + 2) & 0xFFFFFFFFULL;
            break;
        case SCSI_OPCODE_GRP_16B:
            lba = SWAP64_BIG2LITTLE(cmdBuf + 2);
            break;
        default:          
            log();
            lba = -1;
            break;
    }
    return lba;
}






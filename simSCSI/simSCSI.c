/**
 * Copyright (C), 2020, Sugon Information Industry Co., Ltd.
 *
 * @file    simSCSI.c
 * @author  徐宏
 * @date    2020.07.21
 * @brief    SCSI命令处理
 * @note     新增文件
 */ 
#include <stdint.h>
#include "simSCSI.h"
#include "simSCSIpriv.h"

/**
 * @brief   SCSI构建SENSE DATA数据
 * @param   pReq [in/out], SCSI request请求对象
 * @param   sense [in], sense定义
 * @return   =>0:成功， <0:失败
 */
S32 simScsiReqSenseBuild(SimScsiRequest *pReq, SimSCSISense_t sense, Bool 
        isFixed)
{
    S32 ret;
    U8  buf[SCSI_SENSE_LEN] = {0};
    U8 *pOutBuf = pReq->sense;
    S32 len;
    
    if (0 != simSCSICheckPtr(pReq)) {
        ret = -1;
        goto end;
    }

    if (SIM_TURE == isFixed) {
        buf[0] = 0x70;
        buf[2] = sense.key;
        buf[7] = 10;
        buf[12] = sense.asc;
        buf[13] = sense.ascq;
        len = SCSI_SENSE_FIX_LEN;
    } else {
        buf[0] = 0x72;
        buf[1] = sense.key;
        buf[2] = sense.asc;
        buf[3] = sense.ascq;
        len = SCSI_SENSE_STD_LEN;
    }
    
    memcpy(pOutBuf, buf, len);
    ret = 0;
end:
    return ret;
}

/**
 * @brief   SCSI CDB(Command Descriptor Block)命令解析
 * @param   pDev [in], 模拟盘对象
 * @param   pCmd [out], 解析后的SCSI命令
 * @param   pDarCdb [in], DAL下发的DAR参数
 * @return   =>0:成功， <0:失败
 */
S32 simScsiCdbParse(SimSCSIDevice *pDev, SimSCSICmd_t *pCmd, U8 *pDarCdb)
{
    S32 ret = 0;

    if (0 != SIM_CHECK_PTR(pDev) || 0 != simSCSICheckPtr(pCmd) ||
        0 != SIM_CHECK_PTR(pDarCdb)) {
         ret = -1;
         goto end;
    }
    
    ret = simScsiOpcodeIsSupport(pDarCdb[0]);
    if (0 > ret) {
        log();
        goto end;
    }
    
    ret = simScsiCdbLenParse(&pCmd->cmdLen, pDarCdb);
    if (0 > ret) {
        log();
        goto end;
    }

    ret = simScsiXferLenParse(pDev, &pCmd->xferLen, pDarCdb);
    if (0 > ret) {
        log();
        goto end;
    }

    pCmd->xferMode = simScsiXferModeParse(pCmd, pDarCdb);

    pCmd->lba = simScsiLbaParse(pDarCdb);

    memcpy(pCmd->cmdBuf, pDarCdb, pCmd->cmdLen);

    log("pCmd param: cmdLen:%u, xferLen:%u, xferMode:%u, pCmd->lba:%llu", 
            pCmd->cmdLen, pCmd->xferLen, pCmd->xferMode, pCmd->lba);

end:
    return ret;
}


static S32 simScsiReqCheckRef(U32 reqRefCount)
{
    S32 ret = 0;
    if (0 >= reqRefCount) {
       ret = -1;
    }
    return ret;
}

/**
 * @brief   SCSI命令处理引用计数加
 * @param   pReq [in/out], [in/out ]SCSI request请求对象
 * @return   =>0:成功， <0:失败simSCSICheckPtr
 */
S32 simScsiReqRef(SimScsiRequest *pReq)
{
    S32 ret = 0;
    
    simSCSICheckPtr(pReq);   

    if (0 != simScsiReqCheckRef(pReq->refCount)) {
        log();
        ret = -1;
        goto end;
    }
    
    pReq->refCount++;
    ret = 0;
end:
    return ret;
}

/**
 * @brief   SCSI命令处理引用计数减
 * @param   pReq [in/out], SCSI request请求对象
 * @return   =>0:成功， <0:失败
 */
S32 simScsiReqUnref(SimScsiRequest *pReq)
{
    S32 ret = 0;
    
    simSCSICheckPtr(pReq); 
    
    if (0 != simScsiReqCheckRef(pReq->refCount)) {
        log();
        ret = -1;
        goto end;
    }

    if (0 == (--pReq->refCount)) {

        if (NULL != pReq->ops->freeReqIov) {
           pReq->ops->freeReqIov(pReq);
        } else {
            log();
        }
        SIM_MEM_ZFREE(pReq)
    }
    
end:
    return ret;
}

/**
 * @brief   SCSI命令入队
 * @param   pReq [in/out], SCSI request请求对象
 * @return   =>0:成功， <0:失败
 */
S32 simScsiReqEnqueue(SimScsiRequest *pReq)
{
    S32 ret = 0;
 
    ///< qemu scsi_req_enqueue_internal by xuhong
    ret = simScsiReqRef(pReq);  ///计数- 对应出队
    if (0 > ret) {
        log();
        goto end;
    }
    
    if (pReq->bus->info->get_sg_list) {
        pReq->sgl = pReq->bus->info->get_sg_list(req);
    } else {
        pReq->sgl = NULL;
    }
    pReq->enqueued = SIM_TRUE;

    // QTAILQ_INSERT_TAIL(&pReq->dev->requests, req, next); 加链
    ///<  scsi_req_enqueue_internal by xuhong 

    simScsiReqRef(pReq);
    if (NULL ==  pReq->ops->sendCmd) {
        log();
        ret = -1;
        goto end;
    }
    ret = pReq->ops->sendCmd();
    simScsiReqUnref(pReq);
    
end:
    return ret;
}

/**
 * @brief   SCSI命令出
 * @param   pReq [in/out], SCSI request请求对象
 * @return   =>0:成功， <0:失败
 */
S32 simScsiReqDequeue(SimScsiRequest *pReq)
{
    S32 ret = 0;
    if (SIM_TURE == pReq->enqueued) {
         //    QTAILQ_REMOVE(&req->dev->requests, req, next); 摘链
         pReq->enqueued = SIM_FALSE;
         simScsiReqUnref(pReq);
         ret = 0;
    } else {
        log();
        ret = -1;        
    }
end:     
    return ret;
}

/**
 * @brief   SCSI命令取消IO
 * @param   pReq [in/out], [in/out ]SCSI request请求对象
 * @return   =>0:成功， <0:失败
 */
S32 simScsiReqCancel(SimScsiRequest *pReq)
{
    S32 ret;
    
    if (!pReq->enqueued) {
        return;
    }
    
    if(SIM_FALSE!=req->ioCanceled) {
        
        printf();
        BUG_ON();
    }

    simScsiReqRef(pReq);
    simScsiReqDequeue(pReq);
    pReq->ioCanceled = SIM_TURE;
    
    if(NULL == pReq->aiocb) {

      
    }  else {
        
    
    }

end:     
    return ret;
}

/**
 * @brief   SCSI命令处理结束
 * @param   pReq [in/out], SCSI request请求对象
 * @param   status [in/out], SCSI 命令处理上报status
 * @return   =>0:成功， <0:失败
 */
S32 simScsiReqComplete(SimScsiRequest *pReq, S32 status)
{
    S32 ret;

    if (STATUS_INIT == pReq->status) {
        log();
        ret = -1;
        goto end;
    }        
    pReq->status = status;
    
    if (pReq->senseLen > sizeof(pReq->sense)) {
        log();
        ret = -1;
        goto end;
    }
    
    if (GOOD == status) {
        pReq->sense_len = 0；
        pReq->pDev->sense_len = 0;
        pReq->pDev->sense_is_ua = SIM_FALSE;
    } else {
        simMemCpy(pReq->pDev->sense, pReq->sense, pReq->senseLen);
        pReq->pDev->sense_len = pReq->senseLen;
        pReq->pDev->sense_is_ua = (pReq->ops == &reqops_unit_attention); ///< UA回调
    }

    simScsiClearUA(pReq);  ///< 清除UA
    
    simScsiReqRef(pReq);
    simScsiReqDequeue(pReq);
    if (NULL ==  pReq->pBus-busOps->comlete) {
        log();
        ret =-1;
        goto end;
    }    
    pReq->pBus->busOps->comlete(pReq, pReq->status, pReq->dataLen);
    simScsiReqUnref(pReq);
    
end: 
    return ret;
}

/**
 * @brief   SCSI命令请求分配对象
 * @param   ops [in], 分配req的函数对象
 * @param   pDev [in], 模拟盘对象
 * @param   pDarCdb [in], DAL下发的DAR参数
 * @return   !=NULL:成功， NULL:失败
 */
static SimScsiRequest *simScsiReqAlloc(const SimSCSIReqOps_t *ops, 
        SimSCSIDevice_t *pDev, U8 *pDarCdb)
{
    SimScsiRequest *pReq;
    SimSCSIBus *pBus = find_bus(pDev);  ///<

    pReq = SIM_MEM_ZALLOC(sizeof(SimScsiRequest));
    if (NULL == pReq) {
        log()；
        goto end;
    }

    pReq->refcount  = 1;
    pReq->pBus      = pBus;
    pReq->pDev      = pDev;
    pReq->ops       = ops;
    pReq->lun       = pDev->lun;
    pReq->status    = -1;  
    
end:
    return pReq;
}

/**
 * @brief   SCSI命令请求资源申请
 * @param   pDev [in], 模拟盘对象
 * @param   pDarCdb [in], DAL下分的DAR参数
 * @return   !=NULL:成功， NULL:失败
 */
SimScsiRequest *simScsiReqNew(SimSCSIDevice_t *pDev, U8 *pDarCdb)
{   
    SimScsiRequest *pReq = NULL;
    SimSCSIBus_t   *pBus = NULL;    
    SimSCSICmd_t    cmd  = {0};
    const SimSCSIBusOps_t   *ops = NULL;
    S32 ret;
    
    SIM_CHECK_PTR(pDev, NULL, "   ");
    SIM_CHECK_PTR(pDarCdb, NULL, "   ");
    
    if ((pDev->unit_attention.key == UNIT_ATTENTION ||
         pBus->unit_attention.key == UNIT_ATTENTION) &&
        (pDarCdb[0] != INQUIRY &&
         pDarCdb[0] != REPORT_LUNS &&
         pDarCdb[0] != GET_CONFIGURATION &&
         pDarCdb[0] != GET_EVENT_STATUS_NOTIFICATION &&
         !(pDarCdb[0] == REQUEST_SENSE && pDev->sense_is_ua))) {
         
        ops = simScsiReqOpsUaGet();
    } else {
        ops = NULL;
    }    

    ret = simScsiCdbParse(pDev, &cmd, pDarCdb);
    if (0 > ret) {
        log();
        ops = simScsiReqOpsErrOpcodeGet();
    } else {
        if (UINT32_MAX < cmd.xferLen) {
            ops = simScsiReqOpsErrFieldGet();
        } else if (NULL == ops) {
           ops = simScsiReqOpsMatch(pDarCdb[0]);      
        } else {
           pReq = NULL;
           log();
           goto end;
        } 
    }

    pReq = simScsiReqAlloc(ops, pDev, pDarCdb);   
    SIM_CHECK_PTR(pReq, NULL, "   ");
    
    simMemCpy(pReq->cmd, cmd, sizeof(pReq->cmd));
    pReq->dataLen = pReq->cmd.xferLen;
    pReq->pDev = pDev; 

    
end:    
    return pReq;
}

/**
 * @brief   SCSI 命令数据处理
 * @param   pReq [in/out], SCSI request请求对象
 * @return   =>0:成功， <0:失败
 */
S32 simScsiReqDataProc(SimScsiRequest *pReq)
{
    S32 ret = 0;
    SIM_CHECK_PTR(pReq, -1, "   ");
    SIM_CHECK_PTR(pReq->ops,-1," ");
    SIM_CHECK_PTR(pReq->ops->readData,-1," ");
    SIM_CHECK_PTR(pReq->ops->writeData,-1," ");

    if (SIM_TRUE == pReq->ioCanceled) {
        log();
        ret = -1;
        goto end;
    }
    
    if (SCSI_XFER_TO_DEV == pReq->cmd.xferMode) {        
        pReq->ops->writeData(pReq);
    } else if (SCSI_XFER_FROM_DEV == pReq->cmd.xferMode) {
        pReq->ops->readData(pReq);
    } else {
        log();
        ret = -1;
        goto end;
    }

end:     
    return ret;
}


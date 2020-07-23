/**
 * Copyright (C), 2020, Sugon Information Industry Co., Ltd.
 *
 * @file    simSCSI.c
 * @author  徐宏
 * @date    2020.07.21
 * @brief    SCSI命令处理
 * @note     新增文件
 */ 

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
    
    ret = simSCSIOpcodeIsSupport(pDarCdb[0]);
    if (0 > ret)
    {
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

end:
    return ret;
}

/**
 * @brief   SCSI命令处理引用计数加
 * @param   pReq [in/out], [in/out ]SCSI request请求对象
 * @return   =>0:成功， <0:失败simSCSICheckPtr
 */
S32 simScsiReqRef(SimScsiRequest *pReq)
{
    S32 ret;
    
    simSCSICheckPtr(pReq);


   
    
    pReq->refCount++;

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
    S32 ret;

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
    S32 ret;

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
    S32 ret;

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
S32 simScsiReqComplete(SimScsiRequest *pReq， S32 status)
{
    S32 ret;
    /*
        回调bus的结束分支
    */
    
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
SimScsiRequest *simScsiReqAlloc(const SimSCSIReqOps_t ops, SimSCSIDevice *pDev,
        U8 *pDarCdb);
{
    SimScsiRequest *pReq;
    
    return NULL；
    return pReq;
}

/**
 * @brief   SCSI命令请求资源申请
 * @param   pDev [in], 模拟盘对象
 * @param   pDarCdb [in], DAL下分的DAR参数
 * @return   !=NULL:成功， NULL:失败
 */
SimScsiRequest *simScsiReqNew(SimSCSIDevice *pDev, U8 *pDarCdb)
{
    SimScsiRequest *pReq;
    
    return pReq;
}

/**
 * @brief   SCSI 命令数据处理
 * @param   pReq [in/out], SCSI request请求对象
 * @return   =>0:成功， <0:失败
 */
S32 simScsiReqDataProc(SimScsiRequest *pReq)
{
    S32 ret;
    
   
end:     
    return ret;
}


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



#endif ///< __SIM_SCSI_PUB_H__


/** @file
  Definition of the MMC Host Protocol

  Copyright (c) 2011-2014, ARM Limited. All rights reserved.

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#ifndef __MMC_HOST_H__
#define __MMC_HOST_H__

///
/// Global ID for the MMC Host Protocol
///
#define EFI_MMC_HOST_PROTOCOL_GUID \
  { 0x3e591c00, 0x9e4a, 0x11df, {0x92, 0x44, 0x00, 0x02, 0xA5, 0xD5, 0xC5, 0x1B } }

#define MMC_RESPONSE_TYPE_R1        0
#define MMC_RESPONSE_TYPE_R1b       0
#define MMC_RESPONSE_TYPE_R2        1
#define MMC_RESPONSE_TYPE_R3        0
#define MMC_RESPONSE_TYPE_R6        0
#define MMC_RESPONSE_TYPE_R7        0
#define MMC_RESPONSE_TYPE_OCR       0
#define MMC_RESPONSE_TYPE_CID       1
#define MMC_RESPONSE_TYPE_CSD       1
#define MMC_RESPONSE_TYPE_RCA       0

typedef UINT32  MMC_RESPONSE_TYPE;

typedef UINT32 MMC_CMD;

#define MMC_CMD_WAIT_RESPONSE      (1 << 16)
#define MMC_CMD_LONG_RESPONSE      (1 << 17)
#define MMC_CMD_NO_CRC_RESPONSE    (1 << 18)

#define MMC_INDX(Index)       ((Index) & 0xFFFF)
#define MMC_GET_INDX(MmcCmd)  ((MmcCmd) & 0xFFFF)

#define MMC_CMD0              (MMC_INDX(0) | MMC_CMD_NO_CRC_RESPONSE)
#define MMC_CMD1              (MMC_INDX(1) | MMC_CMD_WAIT_RESPONSE | MMC_CMD_NO_CRC_RESPONSE)
#define MMC_CMD2              (MMC_INDX(2) | MMC_CMD_WAIT_RESPONSE | MMC_CMD_LONG_RESPONSE)
#define MMC_CMD3              (MMC_INDX(3) | MMC_CMD_WAIT_RESPONSE)
#define MMC_CMD5              (MMC_INDX(5) | MMC_CMD_WAIT_RESPONSE | MMC_CMD_NO_CRC_RESPONSE)
#define MMC_CMD7              (MMC_INDX(7) | MMC_CMD_WAIT_RESPONSE)
#define MMC_CMD8              (MMC_INDX(8) | MMC_CMD_WAIT_RESPONSE)
#define MMC_CMD9              (MMC_INDX(9) | MMC_CMD_WAIT_RESPONSE | MMC_CMD_LONG_RESPONSE)
#define MMC_CMD11             (MMC_INDX(11) | MMC_CMD_WAIT_RESPONSE)
#define MMC_CMD12             (MMC_INDX(12) | MMC_CMD_WAIT_RESPONSE)
#define MMC_CMD13             (MMC_INDX(13) | MMC_CMD_WAIT_RESPONSE)
#define MMC_CMD16             (MMC_INDX(16) | MMC_CMD_WAIT_RESPONSE)
#define MMC_CMD17             (MMC_INDX(17) | MMC_CMD_WAIT_RESPONSE)
#define MMC_CMD18             (MMC_INDX(18) | MMC_CMD_WAIT_RESPONSE)
#define MMC_CMD20             (MMC_INDX(20) | MMC_CMD_WAIT_RESPONSE)
#define MMC_CMD23             (MMC_INDX(23) | MMC_CMD_WAIT_RESPONSE)
#define MMC_CMD24             (MMC_INDX(24) | MMC_CMD_WAIT_RESPONSE)
#define MMC_CMD55             (MMC_INDX(55) | MMC_CMD_WAIT_RESPONSE)
#define MMC_ACMD41            (MMC_INDX(41) | MMC_CMD_WAIT_RESPONSE | MMC_CMD_NO_CRC_RESPONSE)

// Valid responses for CMD1 in eMMC
#define EMMC_CMD1_CAPACITY_LESS_THAN_2GB 0x00FF8080 // Capacity <= 2GB, byte addressing used
#define EMMC_CMD1_CAPACITY_GREATER_THAN_2GB 0x40FF8080 // Capacity > 2GB, 512-byte sector addressing used

typedef enum _MMC_STATE {
    MmcInvalidState = 0,
    MmcHwInitializationState,
    MmcIdleState,
    MmcReadyState,
    MmcIdentificationState,
    MmcStandByState,
    MmcTransferState,
    MmcSendingDataState,
    MmcReceiveDataState,
    MmcProgrammingState,
    MmcDisconnectState,
} MMC_STATE;

///
/// Forward declaration for EFI_MMC_HOST_PROTOCOL
///
typedef struct _EFI_MMC_HOST_PROTOCOL  EFI_MMC_HOST_PROTOCOL;

typedef BOOLEAN (EFIAPI *MMC_ISCARDPRESENT) (
  IN  EFI_MMC_HOST_PROTOCOL   *This
  );

typedef BOOLEAN (EFIAPI *MMC_ISREADONLY) (
  IN  EFI_MMC_HOST_PROTOCOL   *This
  );

typedef EFI_STATUS (EFIAPI *MMC_BUILDDEVICEPATH) (
  IN  EFI_MMC_HOST_PROTOCOL     *This,
  OUT EFI_DEVICE_PATH_PROTOCOL  **DevicePath
  );

typedef EFI_STATUS (EFIAPI *MMC_NOTIFYSTATE) (
  IN  EFI_MMC_HOST_PROTOCOL     *This,
  IN  MMC_STATE                 State
  );

typedef EFI_STATUS (EFIAPI *MMC_SENDCOMMAND) (
  IN  EFI_MMC_HOST_PROTOCOL     *This,
  IN  MMC_CMD                   Cmd,
  IN  UINT32                    Argument
  );

typedef EFI_STATUS (EFIAPI *MMC_RECEIVERESPONSE) (
  IN  EFI_MMC_HOST_PROTOCOL     *This,
  IN  MMC_RESPONSE_TYPE         Type,
  IN  UINT32                    *Buffer
  );

typedef EFI_STATUS (EFIAPI *MMC_READBLOCKDATA) (
  IN  EFI_MMC_HOST_PROTOCOL     *This,
  IN  EFI_LBA                   Lba,
  IN  UINTN                     Length,
  OUT UINT32                    *Buffer
  );

typedef EFI_STATUS (EFIAPI *MMC_WRITEBLOCKDATA) (
  IN  EFI_MMC_HOST_PROTOCOL     *This,
  IN  EFI_LBA                   Lba,
  IN  UINTN                     Length,
  IN  UINT32                    *Buffer
  );


struct _EFI_MMC_HOST_PROTOCOL {

  UINT32                  Revision;
  MMC_ISCARDPRESENT       IsCardPresent;
  MMC_ISREADONLY          IsReadOnly;
  MMC_BUILDDEVICEPATH     BuildDevicePath;

  MMC_NOTIFYSTATE         NotifyState;

  MMC_SENDCOMMAND         SendCommand;
  MMC_RECEIVERESPONSE     ReceiveResponse;

  MMC_READBLOCKDATA       ReadBlockData;
  MMC_WRITEBLOCKDATA      WriteBlockData;

};

#define MMC_HOST_PROTOCOL_REVISION    0x00010001    // 1.1

extern EFI_GUID gEfiMmcHostProtocolGuid;

#endif


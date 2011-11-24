/*
 * Copyright (c) 2010, Code Aurora Forum. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   * Neither the name of Code Aurora Forum, Inc. nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef MMCUTILS_H_
#define MMCUTILS_H_

/* Some useful define used to access the MBR/EBR table */
#define BLOCK_SIZE                0x200
#define TABLE_ENTRY_0             0x1BE
#define TABLE_ENTRY_1             0x1CE
#define TABLE_ENTRY_2             0x1DE
#define TABLE_ENTRY_3             0x1EE
#define TABLE_SIGNATURE           0x1FE
#define TABLE_ENTRY_SIZE          0x010

#define OFFSET_STATUS             0x00
#define OFFSET_TYPE               0x04
#define OFFSET_FIRST_SEC          0x08
#define OFFSET_SIZE               0x0C
#define COPYBUFF_SIZE             (1024 * 16)
#define BINARY_IN_TABLE_SIZE      (16 * 512)
#define MAX_FILE_ENTRIES          20

#define MMC_BOOT_TYPE 0x48
#define MMC_SYSTEM_TYPE 0x82
#define MMC_USERDATA_TYPE 0x83
#define MMC_RECOVERY_TYPE 0x71
#define MMC_MISC_TYPE 0x76

/* HTC VIVOW dtypes:
#define MMC_HBOOT_TYPE 0x47
#define MMC_SBL1_TYPE  0x4D
#define MMC_SBL2_TYPE  0x51
#define MMC_SBL3_TYPE  0x45
*/

/* These are CAF LK partitions
#define MMC_MODEM_TYPE                 0x06
#define MMC_MODEM_TYPE2                0x0C
#define MMC_SBL1_TYPE                  0x4D
#define MMC_SBL2_TYPE                  0x51
#define MMC_SBL3_TYPE                  0x45
#define MMC_RPM_TYPE                   0x47
#define MMC_TZ_TYPE                    0x46

#define MMC_ABOOT_TYPE                 0x4C
#define MMC_BOOT_TYPE                  0x48
#define MMC_SYSTEM_TYPE                0x82
#define MMC_USERDATA_TYPE              0x83
#define MMC_RECOVERY_TYPE	       0x60
*/

#define MMC_RCA 2

#define MAX_PARTITIONS 64

#define GET_LWORD_FROM_BYTE(x)    ((unsigned)*(x) | \
        ((unsigned)*((x)+1) << 8) | \
        ((unsigned)*((x)+2) << 16) | \
        ((unsigned)*((x)+3) << 24))

#define PUT_LWORD_TO_BYTE(x, y)   do{*(x) = (y) & 0xff;     \
    *((x)+1) = ((y) >> 8) & 0xff;     \
    *((x)+2) = ((y) >> 16) & 0xff;     \
    *((x)+3) = ((y) >> 24) & 0xff; }while(0)

#define GET_PAR_NUM_FROM_POS(x) ((((x) & 0x0000FF00) >> 8) + ((x) & 0x000000FF))

#define MMC_BOOT_TYPE 0x48
#define MMC_EXT3_TYPE 0x83
#define MMC_VFAT_TYPE 0xC

//typedef struct MmcPartition MmcPartition;

typedef struct {
	char *device_index;
	char *filesystem;
	char *name;
	unsigned dstatus;
	unsigned dtype ;
	unsigned dfirstsec;
	unsigned dsize;
} MmcPartition;

/* Functions */
int mmc_scan_partitions();
const MmcPartition *mmc_find_partition_by_name(const char *name);
const MmcPartition *mmc_find_partition_by_device_index(const char *device_index);
int mmc_format_ext3 (const MmcPartition *partition);
int mmc_format_ext4 (const MmcPartition *partition);
int mmc_upgrade_ext3 (const MmcPartition *partition);
int mmc_mount_partition(const MmcPartition *partition, const char *mount_point, \
                        int read_only);
int mmc_raw_copy (const MmcPartition *partition, char *in_file);

#endif  // MMCUTILS_H_


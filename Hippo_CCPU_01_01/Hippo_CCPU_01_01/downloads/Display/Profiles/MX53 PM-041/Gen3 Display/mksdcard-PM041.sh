#!/bin/sh

# Set partition sizes below
# partition sizes in MB
BOOT_PARTITION_SIZE=11
PERSISTENT_PARTITION_SIZE=1
ROOTFS_PARTITION_SIZE=300
APPS_PARTITION_SIZE=300

### DO NOT MODIFY BELOW THIS LINE ###

BOOT_PARTITION_START=1
PERSISTENT_PARTITION_START=$(expr ${BOOT_PARTITION_START} + ${BOOT_PARTITION_SIZE})
ROOTFS1_PARTITION_START=$(expr ${PERSISTENT_PARTITION_START} + ${PERSISTENT_PARTITION_SIZE})
ROOTFS2_PARTITION_START=$(expr ${ROOTFS1_PARTITION_START} + ${ROOTFS_PARTITION_SIZE})
APPS_PARTITION_START=$(expr ${ROOTFS2_PARTITION_START} + ${ROOTFS_PARTITION_SIZE})
DATA_PARTITION_START=$(expr ${APPS_PARTITION_START} + ${APPS_PARTITION_SIZE})


# call sfdisk to create partition table

# destroy the partition table
node=$1
dd if=/dev/zero of=${node} bs=512 count=34
dd if=/dev/zero of=${node} bs=512 count=34 seek=$(expr $(cat /sys/block/mmcblk0/size) - 34)

#sfdisk --force -uM ${node} << EOF
#1,20,83
#21,300,83
#321,300,83
#621,,85
#621,300,83
#921,,83;
#EOF

# Create GPT partition table
parted /dev/mmcblk0 mklabel gpt << EOF
y
EOF

#Create boot files partition
parted /dev/mmcblk0 mkpart primary fat32 ${BOOT_PARTITION_START}MB ${PERSISTENT_PARTITION_START}MB
#Create persistent data partition
parted /dev/mmcblk0 mkpart primary ext2 ${PERSISTENT_PARTITION_START}MB ${ROOTFS1_PARTITION_START}MB
#Create first rootfs partition
parted /dev/mmcblk0 mkpart primary ext4 ${ROOTFS1_PARTITION_START}MB ${ROOTFS2_PARTITION_START}MB
#Create second rootfs partition
parted /dev/mmcblk0 mkpart primary ext4 ${ROOTFS2_PARTITION_START}MB ${APPS_PARTITION_START}MB
#Create apps partition
parted /dev/mmcblk0 mkpart primary ext4 ${APPS_PARTITION_START}MB ${DATA_PARTITION_START}MB
#Create data partition
parted /dev/mmcblk0 mkpart primary ext4 ${DATA_PARTITION_START}MB 100%
#Print partition layout
parted /dev/mmcblk0 print

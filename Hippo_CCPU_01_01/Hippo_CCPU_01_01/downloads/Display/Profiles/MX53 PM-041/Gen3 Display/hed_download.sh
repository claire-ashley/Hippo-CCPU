#!/bin/bash

RELEASE_DIR="${1}"
SSH_KEY_PATH="$(realpath ${RELEASE_DIR})/id_rsa"
DOWNLOAD_TMP_DIR="/tmp/hed_download"
uname | grep -i cygwin > /dev/null
if [ $? -eq 0 ]; then
	IMX_USB_CMD="imx_usb"
else
	if [ -f $(dirname ${0})/../../mfgtool-build/host/usr/bin/imx_usb ]; then
		IMX_USB_CMD="sudo $(dirname ${0})/../../mfgtool-build/host/usr/bin/imx_usb"
	else
		IMX_USB_CMD="sudo imx_usb"
	fi
fi

IMX_USB_CONF="${DOWNLOAD_TMP_DIR}/imx_usb.conf"
IMX_USB_MODULE_CONF="${DOWNLOAD_TMP_DIR}/pm-041.conf"
IMX_USB_OUTPUT="${DOWNLOAD_TMP_DIR}/imx_usb.output"

REMOTE_IP=10.1.2.11
SSH_CMD="ssh -oStrictHostKeyChecking=no -i ${SSH_KEY_PATH} root@${REMOTE_IP}"
SCP_CMD="scp -oStrictHostKeyChecking=no -i ${SSH_KEY_PATH} root@${REMOTE_IP}"

PARTITION_SCRIPT=mksdcard-PM041.sh
EMMC_DEV=mmcblk0
START_DIR=$(pwd)
DOWNLOAD=0
REPARTITION=0
WIPE_DATA=0
WIPE_PERSISTENT=0
READ_FUSES=0
WRITE_FUSES=0
BOARD_TEST=0
TOUCH_CALIBRATE=0
TOUCH_VERIFY=0
PROGRESS=0
# Disable block discard during format operations by default since it takes a very long time
DISCARD_BLOCKS="-E nodiscard"

DOWNLOAD_STATUS_LED_PATH="/sys/class/leds/Heartbeat"

SPLASH_FIFO=/tmp/splash.fifo

usage() {
	echo "Usage:"
	echo "   hed_download.sh RELEASE_DIR [DOWNLOAD] [REPARTITION] [WIPE_DATA] [WIPE_PERSISTENT] [LOAD_PERSISTENT /PATH/TO/persistent.tar.bz2] [READ_FUSES] [WRITE_FUSES] [DISCARD_BLOCKS] [BOOT] [BOARD_TEST] [TOUCH_CALIBRATE] [TOUCH_VERIFY]"
}

send_cmd() {
	if [ -n "${1}" ]; then
		check_connection
		if [ -n "${2}" ] && [ -f "${2}" ]; then
			cat ${2} | ${SSH_CMD} "${1}"
		else
			${SSH_CMD} "${1}"
		fi
	fi
}

check_connection() {
	local TIMEOUT_MAX=30
	local TIMEOUT=0
	uname | grep -i cygwin > /dev/null
	if [ $? -eq 0 ]; then
		# Running in Windows
		until ipconfig | grep "$(echo ${REMOTE_IP} | cut -d '.' -f 1-3)" > /dev/null || [ ${TIMEOUT} -ge ${TIMEOUT_MAX} ]; do
			echo -n "."
			sleep 1
			((TIMEOUT++))
		done
	else
		# Running in Linux
		until /sbin/ifconfig | grep "$(echo ${REMOTE_IP} | cut -d '.' -f 1-3)" > /dev/null || [ ${TIMEOUT} -ge ${TIMEOUT_MAX} ]; do
			for interface in $(ls /sys/class/net/); do
				/sbin/udevadm info --query=all --path=/sys/class/net/$interface | grep rndis > /dev/null
				if [ $? -eq 0 ]; then
					echo ""
					sudo /sbin/dhclient -v -r -pf /var/run/dhclient-hed-download.pid
					sleep 1
					sudo /sbin/dhclient -v -pf /var/run/dhclient-hed-download.pid "${interface}"
					if [ $? -eq 0 ]; then
						break
					fi
				fi
				echo -n "."
			done
			sleep 1
			((TIMEOUT++))
		done
	fi
	if [ ${TIMEOUT} -ge ${TIMEOUT_MAX} ]; then
		echo "ERROR: Timeout trying to connect to device.  Check your USB connection."
		exit 1
	fi
}

run_imx_usb() {
	rm -rfv "${DOWNLOAD_TMP_DIR}"
	mkdir -pv "${DOWNLOAD_TMP_DIR}"
	# Create device config file
	UBOOT_MFGTOOL_BIN="${RELEASE_DIR}/u-boot.imx-mfgtool"
	KERNEL_MFGTOOL_BIN="${RELEASE_DIR}/zImage-mfgtool"
	echo "mx53" > "${IMX_USB_MODULE_CONF}"
	echo "bulk,512,0xfbf06000,0x70000000,512M,0xf8006000,0x20000" >> "${IMX_USB_MODULE_CONF}"
	echo "${UBOOT_MFGTOOL_BIN}:dcd" >> "${IMX_USB_MODULE_CONF}"
	echo "${KERNEL_MFGTOOL_BIN}:load 0x70800000" >> "${IMX_USB_MODULE_CONF}"
	echo "${RELEASE_DIR}/cl-712.dtb:load 0x71FE0000" >> "${IMX_USB_MODULE_CONF}"
	echo "${RELEASE_DIR}/cl-711.dtb:load 0x71FF0000" >> "${IMX_USB_MODULE_CONF}"
	echo "${RELEASE_DIR}/rootfs.img:load 0x70B00000" >> "${IMX_USB_MODULE_CONF}"
	echo "${UBOOT_MFGTOOL_BIN}:load,plug,jump header" >> "${IMX_USB_MODULE_CONF}"
	sync
	# Create imx_usb.conf config file
	echo "0x15a2:0x004e, pm-041.conf" > "${IMX_USB_CONF}"
	sync

	# Run imx_usb
	${IMX_USB_CMD} --help > /dev/null
	${IMX_USB_CMD} -c "${DOWNLOAD_TMP_DIR}/" 2>&1 | tee "${IMX_USB_OUTPUT}"
	if [ $? -ne 0 ]; then
		echo "ERROR: Failed to run imx_usb to boot module"
		exit 1
	fi

	# Check for for no USB device found (but imx_usb still returns 0)
	grep "no matching USB device found" "${IMX_USB_OUTPUT}"
	if [ $? -eq 0 ]; then
		echo "ERROR:  Please connect the module through USB"
		exit 1
	fi
}

fail_exit() {
	send_cmd "echo 0 > ${DOWNLOAD_STATUS_LED_PATH}/brightness"
	rm -rfv "${DOWNLOAD_TMP_DIR}"
	echo ""
	echo "ERROR:  Download Oeperations Failed!"
	send_cmd "/etc/init.d/S19splash stop && sync && sleep 1 && fbv -f -c -s 1 -e /root/Download_Fail.png"
	exit 1
}

update_progress() {
	PROGRESS=$((${PROGRESS} + 1))
	send_cmd "echo $(((${PROGRESS} * 100) / ${TOTAL_STEPS})) > ${SPLASH_FIFO}"
}

download() {
	UBOOT_BIN="${DOWNLOAD_DIR}/u-boot.imx"
	if [ -f "${UBOOT_BIN}" ]; then
		echo ""
		echo "*** Downloading $(basename ${UBOOT_BIN}) ***"
		send_cmd "echo 0 > /sys/block/${EMMC_DEV}boot0/force_ro && dd if=/dev/zero of=/dev/${EMMC_DEV}boot0 bs=1024 count=1022 seek=1 && sync && cat | dd of=/dev/${EMMC_DEV}boot0 bs=1024 seek=1 && sync && echo 1 > /sys/block/${EMMC_DEV}boot0/force_ro && sleep 1 && sync" "${UBOOT_BIN}"
		if [ $? -ne 0 ]; then
			echo "ERROR: Failed to write u-boot.imx to flash"
			fail_exit
		fi
		update_progress
		send_cmd "echo 0 > /sys/block/${EMMC_DEV}boot1/force_ro && dd if=/dev/zero of=/dev/${EMMC_DEV}boot1 bs=1024 count=1022 seek=1 && sync && cat | dd of=/dev/${EMMC_DEV}boot1 bs=1024 seek=1 && sync && echo 1 > /sys/block/${EMMC_DEV}boot1/force_ro && sleep 1 && sync" "${UBOOT_BIN}"
		if [ $? -ne 0 ]; then
			echo "ERROR: Failed to write u-boot.imx to flash"
			fail_exit
		fi
		send_cmd "mmc bootpart enable 1 1 /dev/${EMMC_DEV}"
		if [ $? -ne 0 ]; then
			echo "ERROR: Failed to enable booting from eMMC boot partition"
			fail_exit
		fi
	else
		update_progress
	fi
	update_progress

	if [ -f "${DOWNLOAD_DIR}/boot.tar.bz2" ]; then
		echo ""
		echo "*** Downloading boot.tar.bz2 ***"
		send_cmd "/sbin/mkfs.vfat -n boot /dev/${EMMC_DEV}p1 && mkdir -pv /mnt/storage && mount /dev/${EMMC_DEV}p1 /mnt/storage && mkdir -pv /mnt/storage/a /mnt/storage/b && echo 'bootpath=a' > /mnt/storage/bootpath.txt && echo 'rootpartition=3' >> /mnt/storage/bootpath.txt && cd /mnt/storage/a && cat | BZIP2=--small /bin/tar -xvj && sync && cd && cp -afv /mnt/storage/a/* /mnt/storage/b/ && sync && umount /mnt/storage" "${DOWNLOAD_DIR}/boot.tar.bz2"
		if [ $? -ne 0 ]; then
			echo "ERROR: Failed to write boot.tar.bz2 to flash"
			fail_exit
		fi
		update_progress
		if [ -f "${DOWNLOAD_DIR}/boot.md5" ]; then
			echo ""
			echo "*** Verifying boot.tar.bz2 Checksum ***"
			send_cmd "mkdir -pv /mnt/storage && mount -o ro /dev/${EMMC_DEV}p1 /mnt/storage && cd /mnt/storage/a && cat | md5sum -c && cd && umount /mnt/storage" "${DOWNLOAD_DIR}/boot.md5"
			if [ $? -eq 0 ]; then
				send_cmd "mkdir -pv /mnt/storage && mount -o ro /dev/${EMMC_DEV}p1 /mnt/storage && cd /mnt/storage/b && cat | md5sum -c && cd && umount /mnt/storage" "${DOWNLOAD_DIR}/boot.md5"
				if [ $? -ne 0 ]; then
					echo "ERROR: boot checksum failed"
					fail_exit
				fi
			else
				echo "ERROR: boot checksum failed"
				fail_exit
			fi
		else
			echo "INFO: No boot.md5 file found.  Skipping boot checksum verification."
		fi
	else
		update_progress
	fi
	update_progress

	if [ -f "${DOWNLOAD_DIR}/splash" ]; then
		echo ""
		echo "*** Downloading splash ***"
		send_cmd "cat > /tmp/splash && sync" "${DOWNLOAD_DIR}/splash"
		if [ $? -ne 0 ]; then
			echo "ERROR: Failed to write splash to flash"
			fail_exit
		fi
		update_progress
		if [ -f "${DOWNLOAD_DIR}/splash.md5" ]; then
			echo ""
			echo "*** Verifying splash Checksum ***"
			send_cmd "cd /tmp && cat | md5sum -c" "${DOWNLOAD_DIR}/splash.md5"
			if [ $? -ne 0 ]; then
				echo "ERROR: splash checksum failed"
				fail_exit
			fi
		fi
		echo ""
		echo "*** Installing splash image ***"
		send_cmd "mkdir -pv /mnt/storage && mount /dev/${EMMC_DEV}p1 /mnt/storage && convert -verbose /tmp/splash ppm:/mnt/storage/splash && sync && umount /mnt/storage"
		if [ $? -ne 0 ]; then
			echo "ERROR: Failed to install splash flash image"
			fail_exit
		fi
	else
		update_progress
	fi
	update_progress

	if [ -f "${DOWNLOAD_DIR}/persistent.tar.bz2" ]; then
		echo ""
		echo "*** Downloading persistent.tar.bz2 ***"
		send_cmd "/usr/sbin/mkfs.ext2 -L persistent /dev/${EMMC_DEV}p2 && mkdir -pv /mnt/storage && mount /dev/${EMMC_DEV}p2 /mnt/storage && cd /mnt/storage && cat | BZIP2=--small /bin/tar -xvj && sync && cd && umount /mnt/storage" "${DOWNLOAD_DIR}/persistent.tar.bz2"
		if [ $? -ne 0 ]; then
			echo "ERROR: Failed to write persistent.tar.bz2 to flash"
			fail_exit
		fi
		update_progress
		if [ -f "${DOWNLOAD_DIR}/persistent.md5" ]; then
			echo ""
			echo "*** Verifying persistent.tar.bz2 Checksum ***"
			send_cmd "mkdir -pv /mnt/storage && mount -o ro /dev/${EMMC_DEV}p2 /mnt/storage && cd /mnt/storage && cat | md5sum -c && cd && umount /mnt/storage" "${DOWNLOAD_DIR}/persistent.md5"
			if [ $? -ne 0 ]; then
				echo "ERROR: persistent checksum failed"
				fail_exit
			fi
		else
			echo "INFO: No persistent.md5 file found.  Skipping persistent checksum verification."
		fi
	else
		update_progress
	fi
	update_progress

	if [ -f "${DOWNLOAD_DIR}/rootfs.tar.bz2" ]; then
		echo ""
		echo "*** Downloading rootfs.tar.bz2 ***"
		send_cmd "/usr/sbin/mkfs.ext4 ${DISCARD_BLOCKS} -L rootfs1 /dev/${EMMC_DEV}p3 && mkdir -pv /mnt/storage && mount /dev/${EMMC_DEV}p3 /mnt/storage && cd /mnt/storage && cat | BZIP2=--small /bin/tar -xvj && sync && cd && umount /mnt/storage" "${DOWNLOAD_DIR}/rootfs.tar.bz2"
		if [ $? -ne 0 ]; then
			echo "ERROR: Failed to write rootfs.tar.bz2 to flash"
			fail_exit
		fi
		update_progress
		if [ -f "${DOWNLOAD_DIR}/rootfs.md5" ]; then
			echo ""
			echo "*** Verifying rootfs.tar.bz2 Checksum ***"
			send_cmd "mkdir -pv /mnt/storage && mount -o ro /dev/${EMMC_DEV}p3 /mnt/storage && cd /mnt/storage && cat | md5sum -c && cd && umount /mnt/storage" "${DOWNLOAD_DIR}/rootfs.md5"
			if [ $? -eq 0 ]; then
				send_cmd "/usr/sbin/mkfs.ext4 ${DISCARD_BLOCKS} -L rootfs2 /dev/${EMMC_DEV}p4 && sync"
				if [ $? -ne 0 ]; then
					echo "ERROR: Failed to format rootfs2 partition"
				fi
			else
				echo "ERROR: rootfs checksum failed"
				fail_exit
			fi
		else
			echo "INFO: No rootfs.md5 file found.  Skipping rootfs checksum verification."
		fi
	else
		update_progress
	fi
	update_progress

	if [ -f "${DOWNLOAD_DIR}/apps.tar.bz2" ]; then
		echo ""
		echo "*** Downloading apps.tar.bz2 ***"
		send_cmd "/usr/sbin/mkfs.ext4 ${DISCARD_BLOCKS} -L apps /dev/${EMMC_DEV}p5 && mkdir -pv /mnt/storage && mount /dev/${EMMC_DEV}p5 /mnt/storage && mkdir -pv /mnt/storage/apps1 /mnt/storage/apps2 && cd /mnt/storage && ln -sf apps1 apps && cd /mnt/storage/apps && cat | BZIP2=--small /bin/tar -xvj && sync && cd && umount /mnt/storage" "${DOWNLOAD_DIR}/apps.tar.bz2"
		if [ $? -ne 0 ]; then
			echo "ERROR: Failed to write apps.tar.bz2 to flash"
			fail_exit
		fi
		update_progress
		if [ -f "${DOWNLOAD_DIR}/apps.md5" ]; then
			echo ""
			echo "*** Verifying apps.tar.bz2 Checksum ***"
			send_cmd "mkdir -pv /mnt/storage && mount -o ro /dev/${EMMC_DEV}p5 /mnt/storage && cd /mnt/storage/apps && cat | md5sum -c && cd && umount /mnt/storage" "${DOWNLOAD_DIR}/apps.md5"
			if [ $? -ne 0 ]; then
				echo "ERROR: apps checksum failed"
				fail_exit
			fi
		else
			echo "INFO: No apps.md5 file found.  Skipping apps checksum verification."
		fi
	else
		update_progress
	fi
	update_progress

	if [ -f "${DOWNLOAD_DIR}/data.tar.bz2" ]; then
		echo ""
		echo "*** Downloading data.tar.bz2 ***"
		send_cmd "/usr/sbin/mkfs.ext4 ${DISCARD_BLOCKS} -L data /dev/${EMMC_DEV}p6 && mkdir -pv /mnt/storage && mount /dev/${EMMC_DEV}p6 /mnt/storage && cd /mnt/storage && cat | BZIP2=--small /bin/tar -xvj && sync && cd && umount /mnt/storage" "${DOWNLOAD_DIR}/data.tar.bz2"
		if [ $? -ne 0 ]; then
			echo "ERROR: Failed to write data.tar.bz2 to flash"
			fail_exit
		fi
		update_progress
		if [ -f "${DOWNLOAD_DIR}/data.md5" ]; then
			echo ""
			echo "*** Verifying data.tar.bz2 Checksum ***"
			send_cmd "mkdir -pv /mnt/storage && mount -o ro /dev/${EMMC_DEV}p6 /mnt/storage && cd /mnt/storage && cat | md5sum -c && cd && umount /mnt/storage" "${DOWNLOAD_DIR}/data.md5"
			if [ $? -ne 0 ]; then
				echo "ERROR: data checksum failed"
				fail_exit
			fi
		else
			echo "INFO: No data.md5 file found.  Skipping data checksum verification."
		fi
	else
		update_progress
	fi
	update_progress

	if [ -f "${DOWNLOAD_DIR}/xml.tar.bz2" ]; then
		echo ""
		echo "*** Downloading xml.tar.bz2 ***"
		send_cmd "mkdir -pv /mnt/storage && mount /dev/${EMMC_DEV}p6 /mnt/storage && mkdir -pv /mnt/storage/Arranger/xml && cd /mnt/storage/Arranger/xml && cat | BZIP2=--small /bin/tar -xvj && sync && cd && umount /mnt/storage" "${DOWNLOAD_DIR}/xml.tar.bz2"
		if [ $? -ne 0 ]; then
			echo "ERROR: Failed to write xml.tar.bz2 to flash"
			fail_exit
		fi
		update_progress
		if [ -f "${DOWNLOAD_DIR}/xml.md5" ]; then
			echo ""
			echo "*** Verifying xml.tar.bz2 Checksum ***"
			send_cmd "mkdir -pv /mnt/storage && mount -o ro /dev/${EMMC_DEV}p6 /mnt/storage && cd /mnt/storage/Arranger/xml && cat | md5sum -c && cd && umount /mnt/storage" "${DOWNLOAD_DIR}/xml.md5"
			if [ $? -ne 0 ]; then
				echo "ERROR: xml checksum failed"
				fail_exit
			fi
		else
			echo "INFO: No xml.md5 file found.  Skipping XML checksum verification."
		fi
	else
		update_progress
	fi
	update_progress

	if [ -f "${DOWNLOAD_DIR}/images.tar.bz2" ]; then
		echo ""
		echo "*** Downloading images.tar.bz2 ***"
		send_cmd "mkdir -pv /mnt/storage && mount /dev/${EMMC_DEV}p6 /mnt/storage && mkdir -pv /mnt/storage/Arranger/images && cd /mnt/storage/Arranger/images && cat | BZIP2=--small /bin/tar -xvj && sync && cd && umount /mnt/storage" "${DOWNLOAD_DIR}/images.tar.bz2"
		if [ $? -ne 0 ]; then
			echo "ERROR: Failed to write images.tar.bz2 to flash"
			fail_exit
		fi
		update_progress
		if [ -f "${DOWNLOAD_DIR}/images.md5" ]; then
			echo ""
			echo "*** Verifying images.tar.bz2 Checksum ***"
			send_cmd "mkdir -pv /mnt/storage && mount -o ro /dev/${EMMC_DEV}p6 /mnt/storage && cd /mnt/storage/Arranger/images && cat | md5sum -c && cd && umount /mnt/storage" "${DOWNLOAD_DIR}/images.md5"
			if [ $? -ne 0 ]; then
				echo "ERROR: images checksum failed"
				fail_exit
			fi
		else
			echo "INFO: No images.md5 file found.  Skipping images checksum verification."
		fi
	else
		update_progress
	fi
	update_progress

	if [ -f "${DOWNLOAD_DIR}/fonts.tar.bz2" ]; then
		echo ""
		echo "*** Downloading fonts.tar.bz2 ***"
		send_cmd "mkdir -pv /mnt/storage && mount /dev/${EMMC_DEV}p6 /mnt/storage && mkdir -pv /mnt/storage/Arranger/fonts && cd /mnt/storage/Arranger/fonts && cat | BZIP2=--small /bin/tar -xvj && sync && cd && umount /mnt/storage" "${DOWNLOAD_DIR}/fonts.tar.bz2"
		if [ $? -ne 0 ]; then
			echo "ERROR: Failed to write fonts.tar.bz2 to flash"
			fail_exit
		fi
		update_progress
		if [ -f "${DOWNLOAD_DIR}/fonts.md5" ]; then
			echo ""
			echo "*** Verifying fonts.tar.bz2 Checksum ***"
			send_cmd "mkdir -pv /mnt/storage && mount -o ro /dev/${EMMC_DEV}p6 /mnt/storage && cd /mnt/storage/Arranger/fonts && cat | md5sum -c && cd && umount /mnt/storage" cat "${DOWNLOAD_DIR}/fonts.md5"
			if [ $? -ne 0 ]; then
				echo "ERROR: fonts checksum failed"
				fail_exit
			fi
		else
			echo "INFO: No fonts.md5 file found.  Skipping fonts checksum verification."
		fi
	else
		update_progress
	fi
	update_progress
}

repartition() {
	echo ""
	echo "*** Repartitioning Flash ***"
	send_cmd "cat > /tmp/${PARTITION_SCRIPT} && sh /tmp/${PARTITION_SCRIPT} /dev/${EMMC_DEV} && sync && /sbin/mdev -s && sync" "${RELEASE_DIR}/${PARTITION_SCRIPT}"
	if [ $? -ne 0 ]; then
		echo "ERROR: Failed to repartition the module flash"
		fail_exit
	fi
	update_progress
	wipe_persistent
	wipe_data
}

wipe_data() {
	echo ""
	echo "*** Wiping Data Partition ***"
	send_cmd "/usr/sbin/mkfs.ext4 ${DISCARD_BLOCKS} -L data /dev/${EMMC_DEV}p6"
	if [ $? -ne 0 ]; then
		echo "ERROR: Failed to wipe the data partition"
		fail_exit
	fi
	update_progress
}

wipe_persistent() {
	echo ""
	echo "*** Wiping Persistent Partition ***"
	send_cmd "/usr/sbin/mkfs.ext2 -L persistent /dev/${EMMC_DEV}p2"
	if [ $? -ne 0 ]; then
		echo "ERROR: Failed to wipe the persistent partition data"
		fail_exit
	fi
	update_progress
}

load_persistent() {
	echo ""
	echo "*** Downloading Persistent Partition ***"
	send_cmd "/usr/sbin/mkfs.ext2 -L persistent /dev/${EMMC_DEV}p2 && mkdir -pv /mnt/storage && mount /dev/${EMMC_DEV}p2 /mnt/storage && cd /mnt/storage && cat | BZIP2=--small /bin/tar -xvj && sync && cd && umount /mnt/storage" "${DOWNLOAD_DIR}/${PERSISTENT_TAR}"
	if [ $? -ne 0 ]; then
		echo "ERROR: Failed to load the persistent partition data"
		fail_exit
	fi
	update_progress
}

fuse_read() {
	send_cmd "dd if=/dev/mxc_iim of=/dev/console bs=1 skip=${1} count=1 2>/dev/null && tail -1 /var/log/messages | cut -d ':' -f 5-10" #Read eFuse
	if [ $? -ne 0 ]; then
		printf "ERROR: Failed to read the fuses at address 0x%04X\n" ${1}
		fail_exit
	fi
}

read_fuses() {
	echo ""
	echo "*** Reading eFuses ***"
	echo "*** Value of eFuse address 0x0800-0x0814 (Boot Configuration) ***"
	fuse_read 2048 #Read eFuse 0x0800
	fuse_read 2052 #Read eFuse 0x0804
	fuse_read 2060 #Read eFuse 0x080C
	fuse_read 2064 #Read eFuse 0x0810
	fuse_read 2068 #Read eFuse 0x0814
	fuse_read 2072 #Read eFuse 0x0818
	fuse_read 2076 #Read eFuse 0x081C
	echo "Value of eFuse address 0x0820-0x083C (SJC Challenge/Unique ID)"
	fuse_read 2080 #Read eFuse 0x0820
	fuse_read 2084 #Read eFuse 0x0824
	fuse_read 2088 #Read eFuse 0x0828
	fuse_read 2092 #Read eFuse 0x082C
	fuse_read 2096 #Read eFuse 0x0830
	fuse_read 2100 #Read eFuse 0x0834
	fuse_read 2104 #Read eFuse 0x0838
	fuse_read 2108 #Read eFuse 0x083C
	fuse_read 2112 #Read eFuse 0x0840
	fuse_read 2116 #Read eFuse 0x0844
	echo "Value of eFuse address 0x0860-0x087C (General Purpose)"
	fuse_read 2144 #Read eFuse 0x0860
	fuse_read 2148 #Read eFuse 0x0864
	fuse_read 2152 #Read eFuse 0x0868
	fuse_read 2156 #Read eFuse 0x086C
	fuse_read 2160 #Read eFuse 0x0870
	fuse_read 2164 #Read eFuse 0x0874
	fuse_read 2168 #Read eFuse 0x0878
	fuse_read 2172 #Read eFuse 0x087C
	echo "Value of eFuse address 0x0C00-0x0C20 (SJC Response)"
	fuse_read 3072 #Read eFuse 0x0C00
	fuse_read 3076 #Read eFuse 0x0C04
	fuse_read 3080 #Read eFuse 0x0C08
	fuse_read 3084 #Read eFuse 0x0C0C
	fuse_read 3088 #Read eFuse 0x0C10
	fuse_read 3092 #Read eFuse 0x0C14
	fuse_read 3096 #Read eFuse 0x0C18
	fuse_read 3100 #Read eFuse 0x0C1C
	fuse_read 3104 #Read eFuse 0x0C20
	echo "Value of eFuse address 0x0C24-0x0C38 (MAC Address)"
	fuse_read 3108 #Read eFuse 0x0C24
	fuse_read 3112 #Read eFuse 0x0C28
	fuse_read 3116 #Read eFuse 0x0C2C
	fuse_read 3120 #Read eFuse 0x0C30
	fuse_read 3124 #Read eFuse 0x0C34
	fuse_read 3128 #Read eFuse 0x0C38
	echo "Value of eFuse address 0x1400-0x147C (SRK Hash)"
	fuse_read 5120 #Read eFuse 0x1400
	fuse_read 5124 #Read eFuse 0x1404
	fuse_read 5128 #Read eFuse 0x1408
	fuse_read 5132 #Read eFuse 0x140C
	fuse_read 5136 #Read eFuse 0x1410
	fuse_read 5140 #Read eFuse 0x1414
	fuse_read 5144 #Read eFuse 0x1418
	fuse_read 5148 #Read eFuse 0x141C
	fuse_read 5152 #Read eFuse 0x1420
	fuse_read 5156 #Read eFuse 0x1424
	fuse_read 5160 #Read eFuse 0x1428
	fuse_read 5164 #Read eFuse 0x142C
	fuse_read 5168 #Read eFuse 0x1430
	fuse_read 5172 #Read eFuse 0x1434
	fuse_read 5176 #Read eFuse 0x1438
	fuse_read 5180 #Read eFuse 0x143C
	fuse_read 5184 #Read eFuse 0x1440
	fuse_read 5188 #Read eFuse 0x1444
	fuse_read 5192 #Read eFuse 0x1448
	fuse_read 5196 #Read eFuse 0x144C
	fuse_read 5200 #Read eFuse 0x1450
	fuse_read 5204 #Read eFuse 0x1454
	fuse_read 5208 #Read eFuse 0x1458
	fuse_read 5212 #Read eFuse 0x145C
	fuse_read 5216 #Read eFuse 0x1460
	fuse_read 5220 #Read eFuse 0x1464
	fuse_read 5224 #Read eFuse 0x1468
	fuse_read 5228 #Read eFuse 0x146C
	fuse_read 5232 #Read eFuse 0x1470
	fuse_read 5236 #Read eFuse 0x1474
	fuse_read 5240 #Read eFuse 0x1478
	fuse_read 5244 #Read eFuse 0x147C
	echo "Value of eFuse address 0x1808-0x1810 (Misc Config)"
	fuse_read 6152 #Read eFuse 0x1808
	fuse_read 6156 #Read eFuse 0x180C
	fuse_read 6160 #Read eFuse 0x1810
	echo "Value of eFuse address 0x1814-0x181C (General Purpose)"
	fuse_read 6164 #Read eFuse 0x1814
	fuse_read 6168 #Read eFuse 0x1818
	fuse_read 6172 #Read eFuse 0x181C
	update_progress
}

write_fuses() {
	echo ""
	echo "*** Writing eFuses ***"
	send_cmd "echo \"0x804 0x10\" > /dev/mxc_iim"	# Set eFuse 0x804
	CUR_FUSE_VAL=$(${SSH_CMD} "dd if=/dev/mxc_iim of=/dev/console bs=1 skip=2052 count=1 2>/dev/null && tail -1 /var/log/messages | awk '{print \$NF}'")
	if [ 0x$(printf "%02X" $((${CUR_FUSE_VAL} & 0x10))) != "0x10" ]; then
		echo "ERROR: Failed to write 0x10 to fuse 0x804, current value is ${CUR_FUSE_VAL}"
		fail_exit
	else
		send_cmd "dd if=/dev/mxc_iim of=/dev/console bs=1 skip=2052 count=1 2>/dev/null && tail -1 /var/log/messages | cut -d ':' -f 5-10" #Read eFuse 0x804
	fi
	send_cmd "echo \"0x80c 0x70\" > /dev/mxc_iim"	# Set eFuse 0x80c
	CUR_FUSE_VAL=$(${SSH_CMD} "dd if=/dev/mxc_iim of=/dev/console bs=1 skip=2060 count=1 2>/dev/null && tail -1 /var/log/messages | awk '{print \$NF}'")
	if [ 0x$(printf "%02X" $((${CUR_FUSE_VAL} & 0xFA))) != "0x70" ]; then
		echo "ERROR: Failed to write 0x70 to fuse 0x80C, current value is ${CUR_FUSE_VAL}"
		fail_exit
	else
		send_cmd "dd if=/dev/mxc_iim of=/dev/console bs=1 skip=2060 count=1 2>/dev/null && tail -1 /var/log/messages | cut -d ':' -f 5-10" #Read eFuse 0x80C
	fi
	send_cmd "echo \"0x810 0x41\" > /dev/mxc_iim"	# Set eFuse 0x810
	CUR_FUSE_VAL=$(${SSH_CMD} "dd if=/dev/mxc_iim of=/dev/console bs=1 skip=2064 count=1 2>/dev/null && tail -1 /var/log/messages | awk '{print \$NF}'")
	if [ 0x$(printf "%02X" $((${CUR_FUSE_VAL} & 0xF1))) != "0x41" ]; then
		echo "ERROR: Failed to write 0x41 to fuse 0x810, current value is ${CUR_FUSE_VAL}"
		fail_exit
	else
		send_cmd "dd if=/dev/mxc_iim of=/dev/console bs=1 skip=2064 count=1 2>/dev/null && tail -1 /var/log/messages | cut -d ':' -f 5-10" #Read eFuse 0x810
	fi
	send_cmd "echo \"0x814 0x20\" > /dev/mxc_iim"	# Set eFuse 0x814
	CUR_FUSE_VAL=$(${SSH_CMD} "dd if=/dev/mxc_iim of=/dev/console bs=1 skip=2068 count=1 2>/dev/null && tail -1 /var/log/messages | awk '{print \$NF}'")
	if [ 0x$(printf "%02X" $((${CUR_FUSE_VAL} & 0x3C))) != "0x20" ]; then
		echo "ERROR: Failed to write 0x20 to fuse 0x814, current value is ${CUR_FUSE_VAL}"
		fail_exit
	else
		send_cmd "dd if=/dev/mxc_iim of=/dev/console bs=1 skip=2068 count=1 2>/dev/null && tail -1 /var/log/messages | cut -d ':' -f 5-10" #Read eFuse 0x814
	fi
	# Use the USB 120MHz clock with the SATA PHY to use the temperature sensor that is part of the SATA PHY
	send_cmd "echo \"0x180c 0x04\" > /dev/mxc_iim" # Set eFuse 0x180C
	CUR_FUSE_VAL=$(${SSH_CMD} "dd if=/dev/mxc_iim of=/dev/console bs=1 skip=6156 count=1 2>/dev/null && tail -1 /var/log/messages | awk '{print \$NF}'")
	if [ 0x$(printf "%02X" $((${CUR_FUSE_VAL} & 0x06))) != "0x04" ]; then
		echo "ERROR: Failed to write 0x04 to fuse 0x180C, current value is ${CUR_FUSE_VAL}"
		fail_exit
	else
		send_cmd "dd if=/dev/mxc_iim of=/dev/console bs=1 skip=6156 count=1 2>/dev/null && tail -1 /var/log/messages | cut -d ':' -f 5-10" #Read eFuse 0x180C
	fi

	update_progress
}

boot_emmc() {
	rm -rfv "${DOWNLOAD_TMP_DIR}"
	mkdir -pv "${DOWNLOAD_TMP_DIR}"
	# Create device config file
	echo "mx53" > "${IMX_USB_MODULE_CONF}"
	echo "bulk,512,0xfbf06000,0x70000000,512M,0xf8006000,0x12000" >> "${IMX_USB_MODULE_CONF}"
	echo "${RELEASE_DIR}/download/u-boot.imx:dcd" >> "${IMX_USB_MODULE_CONF}"
	echo "${RELEASE_DIR}/download/u-boot.imx:load,plug,jump header" >> "${IMX_USB_MODULE_CONF}"
	sync
	# Create imx_usb.conf config file
	echo "0x15a2:0x004e, pm-041.conf" > "${IMX_USB_CONF}"
	sync
	# Run imx_usb
	echo $(pwd)
	${IMX_USB_CMD} -c "${DOWNLOAD_TMP_DIR}/"
	if [ $? -ne 0 ]; then
		echo "ERROR: Failed to run imx_usb to boot module"
		exit 1
	fi

	exit 0
}

board_test() {
	if [ ! -f "${RELEASE_DIR}/apps-mfgtool.tar.bz2" ]; then
		echo "ERROR: The board test file apps-mfgtool.tar.bz2 is missing from the release directory"
		return 1
	fi

	send_cmd "mkdir -pv /test && cat | BZIP2=--small /bin/tar -xjv -C /test && sync && mkdir -pv /mnt/persistent && /test/linux-board-test/linux-board-test -a -d" "${RELEASE_DIR}/apps-mfgtool.tar.bz2"
	if [ $? -ne 0 ]; then
		echo "ERROR: Failed to run the board test application"
		return 1
	fi
}

touch_calibrate() {
	send_cmd "mkdir -pv /mnt/persistent && mount -o ro /dev/mmcblk0p2 /mnt/persistent && /etc/init.d/input-sx865x calibrate"
	if [ $? -ne 0 ]; then
		echo "ERROR: Failed to run the touchscreen calibration"
		return 1
	fi
}

touch_verify() {
	send_cmd "mkdir -pv /mnt/persistent && mount -o ro /dev/mmcblk0p2 /mnt/persistent && /etc/init.d/input-sx865x verify"
	if [ $? -ne 0 ]; then
		echo "ERROR: Failed to run the touchscreen calibration"
		return 1
	fi
}


if [ ! $# -ge 1 ]; then
	usage
fi

# Clean out old known hosts of previous download
ssh-keygen -f "${HOME}/.ssh/known_hosts" -R ${REMOTE_IP}

if [ ! -d "${RELEASE_DIR}" ]; then
	echo "ERROR: ${RELEASE_DIR} is not a release directory"
	usage
	exit 1
fi
shift

TOTAL_STEPS=0
while [ $# -gt 0 ]; do
	case "$1" in
	DOWNLOAD)
		TOTAL_STEPS=$((${TOTAL_STEPS} + 20))
		DOWNLOAD=1
		DOWNLOAD_DIR="${RELEASE_DIR}/download"
		if [ ! -d "${DOWNLOAD_DIR}" ]; then
			echo "ERROR: "Download directory ${DOWNLOAD_DIR}" does not exist"
			usage
			exit 1
		fi
		;;
	REPARTITION)
		TOTAL_STEPS=$((${TOTAL_STEPS} + 3))
		REPARTITION=1
		;;
	WIPE_DATA)
		TOTAL_STEPS=$((${TOTAL_STEPS} + 1))
		WIPE_DATA=1
		;;
	WIPE_PERSISTENT)
		TOTAL_STEPS=$((${TOTAL_STEPS} + 1))
		WIPE_PERSISTENT=1
		;;
	LOAD_PERSISTENT)
		TOTAL_STEPS=$((${TOTAL_STEPS} + 1))
		shift
		if [ ! -f "${1}" ]; then
			echo "ERROR: "${1}" is not a regular file"
			usage
			exit 1
		fi
		PERSISTENT_TAR="${1}"
		;;
	READ_FUSES)
		TOTAL_STEPS=$((${TOTAL_STEPS} + 1))
		READ_FUSES=1
		;;
	WRITE_FUSES)
		TOTAL_STEPS=$((${TOTAL_STEPS} + 1))
		WRITE_FUSES=1
		;;
	DISCARD_BLOCKS)
		# Enabling discarding of blocks on partition format
		DISCARD_BLOCKS=""
		;;
	BOOT)
		boot_emmc
		;;
	BOARD_TEST)
		BOARD_TEST=1
		;;
	TOUCH_CALIBRATE)
		TOUCH_CALIBRATE=1
		;;
	TOUCH_VERIFY)
		TOUCH_VERIFY=1
		;;
	*)
		echo "ERROR: Unknown argument ${1}"
		usage
		exit 1
		;;
	esac
	shift
done

echo "RELEASE_DIR = ${RELEASE_DIR}"
echo "DOWNLOAD = ${DOWNLOAD}"
echo "DOWNLOAD_DIR = ${DOWNLOAD_DIR}"
echo "REPARTITION = ${REPARTITION}"
echo "WIPE_DATA = ${WIPE_DATA}"
echo "WIPE_PERSISTENT = ${WIPE_PERSISTENT}"
echo "PERSISTENT_TAR = ${PERSISTENT_TAR}"
echo "READ_FUSES = ${READ_FUSES}"
echo "WRITE_FUSES = ${WRITE_FUSES}"
echo "TOUCH_CALIBRATE = ${TOUCH_CALIBRATE}"
echo "TOUCH_VERIFY = ${TOUCH_VERIFY}"
echo "BOARD_TEST = ${BOARD_TEST}"


run_imx_usb
chmod 600 ${SSH_KEY_PATH}
sleep 1
echo ""
echo "Waiting for module to boot and USB networking to initialize."
check_connection
echo ""
sleep 1

send_cmd "echo heartbeat > ${DOWNLOAD_STATUS_LED_PATH}/trigger && echo 255 > ${DOWNLOAD_STATUS_LED_PATH}/brightness"
send_cmd "/bin/umount /mnt/storage > /dev/null 2>&1"
send_cmd "/sbin/mdev -s"
send_cmd "echo 0 > ${SPLASH_FIFO}"

if [ ${BOARD_TEST} -ne 0 ]; then
	board_test
	exit $?
fi

if [ ${REPARTITION} -ne 0 ] && [ -n "${RELEASE_DIR}" ]; then
	repartition
fi

if [ ${WIPE_DATA} -ne 0 ]; then
	wipe_data
fi

if [ ${WIPE_PERSISTENT} -ne 0 ]; then
	wipe_persistent
fi

if [ -n "${PERSISTENT_TAR}" ]; then
	load_persistent
fi

if [ ${DOWNLOAD} -ne 0 ] && [ -n "${RELEASE_DIR}" ] && [ -n "${DOWNLOAD_DIR}" ]; then
	download
fi

if [ ${TOUCH_CALIBRATE} -ne 0 ]; then
	touch_calibrate
fi

if [ ${TOUCH_VERIFY} -ne 0 ]; then
	touch_verify
fi

if [ ${READ_FUSES} -ne 0 ]; then
	read_fuses
fi

if [ ${WRITE_FUSES} -ne 0 ]; then
	write_fuses
fi

echo ""
echo "Download Operations Complete"
send_cmd "echo none > ${DOWNLOAD_STATUS_LED_PATH}/trigger && echo 255 > ${DOWNLOAD_STATUS_LED_PATH}/brightness"
send_cmd "fbv -f -c -s 1 -e /root/Download_Complete.png > /dev/null"

exit 0


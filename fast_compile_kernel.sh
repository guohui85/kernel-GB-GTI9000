#/bin/sh
. ./setenv.sh
chmod 4755 ../initramfs-GB-GT-I9000/root/sbin/su
make -j4
find . -name *.ko | while read MODULE; do cp $MODULE ../initramfs-GB-GT-I9000/root/lib/modules/ ; done
make -j4


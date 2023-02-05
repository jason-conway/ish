#!/bin/sh

mkdir -p /etc/udhcpc/
echo 'RESOLV_CONF=no' > /etc/udhcpc/udhcpc.conf
echo 'nameserver 8.8.8.8' > /etc/resolv.conf
echo 'nameserver 8.8.4.4' >> /etc/resolv.conf
echo -e 'iSH+Linux\n' > /etc/motd

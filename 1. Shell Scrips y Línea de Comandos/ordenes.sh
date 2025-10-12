# !/bin/bash

DATE=`date`
echo $DATE
USERS=`who | wc -l`
echo $USERS
UP=`date ; uptime`
echo $UP
grep `id -un` /etc/passwd
#!/bin/bash

echo "change sources and update system"
sudo mv /etc/apt/sources.list /etc/apt/sources.list.bak
sudo echo "deb http://mirrors.aliyun.com/ubuntu/ bionic main restricted universe multiverse
deb http://mirrors.aliyun.com/ubuntu/ bionic-security main restricted universe multiverse
deb http://mirrors.aliyun.com/ubuntu/ bionic-updates main restricted universe multiverse
deb http://mirrors.aliyun.com/ubuntu/ bionic-proposed main restricted universe multiverse
deb http://mirrors.aliyun.com/ubuntu/ bionic-backports main restricted universe multiverse
deb-src http://mirrors.aliyun.com/ubuntu/ bionic main restricted universe multiverse
deb-src http://mirrors.aliyun.com/ubuntu/ bionic-security main restricted universe multiverse
deb-src http://mirrors.aliyun.com/ubuntu/ bionic-updates main restricted universe multiverse
deb-src http://mirrors.aliyun.com/ubuntu/ bionic-proposed main restricted universe multiverse
deb-src http://mirrors.aliyun.com/ubuntu/ bionic-backports main restricted universe multiverse

deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ bionic main restricted universe multiverse
deb-src https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ bionic main restricted universe multiverse
deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ bionic-updates main restricted universe multiverse
deb-src https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ bionic-updates main restricted universe multiverse
deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ bionic-backports main restricted universe multiverse
deb-src https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ bionic-backports main restricted universe multiverse
deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ bionic-security main restricted universe multiverse
deb-src https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ bionic-security main restricted universe multiverse
deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ bionic-proposed main restricted universe multiverse
deb-src https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ bionic-proposed main restricted universe multiverse

deb Index of /ubuntu/ bionic main restricted universe multiverse
deb Index of /ubuntu/ bionic-security main restricted universe multiverse
deb Index of /ubuntu/ bionic-updates main restricted universe multiverse
deb Index of /ubuntu/ bionic-proposed main restricted universe multiverse
deb Index of /ubuntu/ bionic-backports main restricted universe multiverse
deb-src Index of /ubuntu/ bionic main restricted universe multiverse
deb-src Index of /ubuntu/ bionic-security main restricted universe multiverse
deb-src Index of /ubuntu/ bionic-updates main restricted universe multiverse
deb-src Index of /ubuntu/ bionic-proposed main restricted universe multiverse
deb-src Index of /ubuntu/ bionic-backports main restricted universe multiverse
" > /etc/apt/sources.list.d

echo "update system"
sudo apt-get update -y
sudo apt-get upgrade -y
cd /etc/apt/sources.list.d
sudo rm -y ./*
echo "finished"

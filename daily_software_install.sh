#!/bin/bash

# install software using apt
sudo apt install python3 -y
sudo apt install  python3-pip -y
sudo apt install python-dev python3-dev build-essential python-pip python3-pip python3-setuptools -y
sudo apt install node npm -y
sudo pip3 install setuptools -y
sudo apt install nodejs -y
sudo apt install npm -y
sudo apt install curl shadowsocks-libev -y
sudo apt install gnome-tweak-tool -y
sudo apt install gnome-shell-extensions -y
sudo apt install chrome-gnome-shell -y
sudo apt install neofetch
sudo apt install git vim curl unzip unrar jd xclip -y
sudo apt-get install maven -y
sudo add-apt-repository ppa:noobslab/icons -y
sudo apt-get update -y
sudo apt-get install flat-remix-icons -y
sudo apt autoremove -y

# install dock dash
cd ~/Downloads
git clone https://github.com/micheleg/dash-to-dock.git
cd dash-to-dock
make && make install

# install nodejs
curl -sL https://deb.nodesource.com/setup_6.x | sudo -E bash -
sudo apt-get install -y nodejs
sudo apt-get install -y build-essential

# install docker and some containers
sudo apt-get install -y docker.io
sudo docker pull  nginx
sudo docker pull tomcat
sudo docker pull mysql

# configure java
sudo echo "export JAVA_HOME=/usr/java/jdk1.8" >> /etc/profile
sudo echo "export JRE_HOME=\${JAVA_HOME}/jre" >> /etc/profile
sudo echo "export CLASSPATH=.:\${JAVA_HOME}/lib:\${JRE_HOME}/lib" >> /etc/profile
sudo echo "export PATH=\${JAVA_HOME}/bin:\$PATH" >> /etc/profile
source /etc/profile

# change npm sources
yarn config set registry https://registry.npm.taobao.org --global
yarn config set disturl https://npm.taobao.org/dist --global

# configure pip
mkdir ~/.pip
touch ~/.pip/pip.conf
echo "[global]
index-url=https://pypi.tuna.tsinghua.edu.cn/simple" > ~/.pip/pip.conf

# install windows manager
sudo apt-get install xmonad
sudo apt-get install xmobar dmenu

# remove ibus and install fcitx pinyin
sudo apt-get remove ibus
sudo apt-get purge ibus
sudo  apt-get remove indicator-keyboard
sudo apt install fcitx-table-wbpy fcitx-config-gtk
im-config -n fcitx

# clean apt cache
sudo apt-get clean
sudo rm -rf /var/lib/apt/lists/*
sudo apt update

# modify gnome
gsettings set org.gnome.desktop.peripherals.touchpad send-events enabled # 启动touch pad
gsettings set org.gnome.desktop.peripherals.touchpad tap-to-click true # 启动单击
gsettings set org.gnome.desktop.peripherals.touchpad natural-scroll true ## 修改滑动方向

mkdir ~/Downloads
mkdir ~/Documents
# Downloads dir must not exists!
ln -s ~/下载 ~/Downloads
ln -s ~/文档 ~/Documents
ln -s ~/桌面 ~/Desktop

# install Albert
sudo sh -c "echo 'deb http://download.opensuse.org/repositories/home:/manuelschneid3r/xUbuntu_18.04/ /' > /etc/apt/sources.list.d/home:manuelschneid3r.list"
sudo apt-get update
sudo apt-get install albert

# install uget
sudo add-apt-repository ppa:plushuang-tw/uget-stable
sudo apt update
sudo apt install uget
sudo apt install aria2
sudo apt-get install redshift-gtk

# install sublime3
wget https://link.juejin.im/?target=https%3A%2F%2Fdownload.sublimetext.com%2Fsublime_text_3_build_3143_x64.tar.bz2
wget -qO - https://download.sublimetext.com/sublimehq-pub.gpg | sudo apt-key add -
sudo apt-get install apt-transport-https
echo "deb https://download.sublimetext.com/ apt/stable/" | sudo tee /etc/apt/sources.list.d/sublime-text.list
sudo apt-get update
sudo apt-get install sublime-text

# install fcitx and sogou pinyin
sudo apt update #  /home/lithium/.xinputrc 
sudo apt install fcitx fcitx-frontend-all fcitx-table*
wget http://cdn2.ime.sogou.com/dl/index/1524572264/sogoupinyin_2.2.0.0108_amd64.deb?st=Y_fcaAfZ4m3o35bKV3R0_A&e=1566625578&fn=sogoupinyin_2.2.0.0108_amd64.deb && sudo dpkg -i sougou*.deb
sudo apt -f install 
sudo apt-get --fix-broken install

# install wine and TIM, baidupan, thunderspeed
git clone https://gitee.com/wszqkzqk/deepin-wine-for-ubuntu.git
wget https://mirrors.aliyun.com/deepin/pool/non-free/d/deepin.com.qq.office/deepin.com.qq.office_2.0.0deepin4_i386.deb &&
wget https://mirrors.aliyun.com/deepin/pool/non-free/d/deepin.com.baidu.pan/deepin.com.baidu.pan_5.7.3deepin0_i386.deb &&
wget https://mirrors.aliyun.com/deepin/pool/non-free/d/deepin.com.thunderspeed/deepin.com.thunderspeed_7.10.35.366deepin18_i386.deb
sudo dpkg -i *.deb

# install wps and fix problems
wget https://wdl1.cache.wps.cn/wps/download/ep/Linux2019/8722/wps-office_11.1.0.8722_amd64.deb
wget http://kr.archive.ubuntu.com/ubuntu/pool/main/libp/libpng/libpng12-0_1.2.54-1ubuntu1_amd64.deb
sudo dpkg -i libpng12-0_1.2.54-1ubuntu1_amd64.deb
sudo dpkg -i wps-office*.deb
cd /tmp && git clone https://github.com/iamdh4/ttf-wps-fonts.git
cd ttf-wps-fonts/
sudo mkdir /usr/share/fonts/wps-fonts
sudo mv ttf-wps-fonts/* /usr/share/fonts/wps-fonts
sudo chmod 644 /usr/share/fonts/wps-fonts/*
sudo mkfontscale
sudo mkfontdir
sudo fc-cache


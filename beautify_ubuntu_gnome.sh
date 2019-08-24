#!/bin/bash

#install software
sudo apt-get update
sudo apt-get upgrade
sudo add-apt-repository ppa:noobslab/themes
sudo add-apt-repository ppa:noobslab/icons
sudo apt-get update
sudo apt-get install arc-theme ultra-flat-icons
sudo apt install git
sudo apt-get install redshift-gtk
sudo apt install zsh

# install oh-my-zsh
wget https://github.com/robbyrussell/oh-my-zsh/raw/master/tools/install.sh -O - | sh
chsh -s /usr/bin/zsh
#chsh -s /usr/local/zsh
sed -i 's/ZSH_THEME="agnoster"/ZSH_THEME="agnoster"/g' ~/.zshrc
#~/.oh-my-zsh/themes/
export DEFAULT_USER="username"

#admin ALL=(ALL) ALL
echo "admin ALL=(ALL) NOPASSWD: ALL" >> /etc/sudoers

#change grub theme
sudo mkdir -p /boot/grub/themes
echo 'GRUB_THEME="/boot/grub/themes/Vimix/theme.txt"' >> /etc/default/grub
sudo update-grub

#install powerline fonts
git clone https://github.com/powerline/fonts.git  --depth=1
#sudo apt-get install fonts-powerline
cd fonts
./install.sh


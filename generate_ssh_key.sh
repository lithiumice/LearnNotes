#!/bin/bash

github_mail="2729020028@qq.com"
github_name="lithiumice"
git config --global user.name "${github_name}"
git config --global user.email "${github_mail}"
git config --lis

cd ~/.ssh
ssh-keygen -t rsa -b 4096 -C ${github_mail}
#eval "$(ssh-agent -s)"
ssh-add ~/.ssh/id_rsa
sudo apt-get install xclip -y
xclip -sel clip < ~/.ssh/id_rsa.pub
cat ~/.ssh/id_rsa > ~/desktop/github_ssh_key.txt
#xclip -selection c  id_rsa.pub

#!/bin/bash

sudo apt install shadowsockt
sudo apt install vim 
echo "{
"server":"ip",
"server_port":port,
"local_port":1080,
"password":"password",
"timeout":600,
"method":"method"
}" > /etc/shadowsocks.json

sslocal -c /etc/shadowsocks.json

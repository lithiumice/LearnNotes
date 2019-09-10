#!/bin/bash

sudo pacman -S mariadb-server mariadb-client
sudo pacman -S nginx
pip install uwsgi
conda install uwsgi django 

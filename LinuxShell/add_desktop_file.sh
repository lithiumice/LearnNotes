#!/bin/bash


# name="minecraft"
# exec="java -jar /home/lithium/Downloads/Minecraft.jar %u"
# cate="game"
# icon=${name}


name="YouDaoNote"
exec="/usr/bin/YouDaoNote"
cate="tools"
icon="YouDaoNote"

echo "
[Desktop Entry]
Name=$name
Exec=$exec
Terminal=false
X-MultipleArgs=false
Type=Application
Icon=$icon
Categories=$cate;
StartupNotify=true
" > sudo tee /usr/share/applications/${name}

sudo tee /usr/share/applications/${name} <<-'EOF'
[Desktop Entry]
Name=$name
Exec=$exec
Terminal=false
X-MultipleArgs=false
Type=Application
Icon=$icon
Categories=$cate;
StartupNotify=true
EOF
echo "finished."

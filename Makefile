BLOCKSDS	?= /opt/blocksds/core

NAME			:= luna_os
GAME_TITLE		:= luna_os

GAME_SUBTITLE 	:= luna_os
GAME_AUTHOR		:= maksasj
# GAME_ICON	?= $(BLOCKSDS)/sys/icon.bmp

SOURCEDIRS		:= src/core src/dsi 3dparty/lua
INCLUDEDIRS		:= 3dparty 3dparty/lua 

include $(BLOCKSDS)/sys/default_makefiles/rom_arm9/Makefile
# Vars
PROJECT = main.cpp main.h window.cpp window.h gameobject.cpp gameobject.h player.cpp player.h bullet.cpp bullet.h enemy.cpp enemy.h text.cpp text.h playersettings.cpp playersettings.h timer.cpp timer.h
LINKER = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
OUT = -o ShootEmUp

ShootEmUp:
	g++ $(PROJECT) $(LINKER) $(OUT)
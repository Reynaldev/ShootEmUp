# Vars
install:
	rm -rf build
	
	cmake -S . -B build
	cmake --build build/ 

	cp -r src/assets build/bin/

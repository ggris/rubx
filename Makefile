rubix: build cmk mk run

fast: mk run

cmk:
	cd build && cmake ../

mk:
	cd build && make rubx

run:
	cd build/bin && ./rubx

build:
	mkdir build

gdb:
	cd build/bin && gdb ./rubx

clean:
	rm -r build

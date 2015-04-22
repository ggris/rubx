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

clean:
	rm -r build

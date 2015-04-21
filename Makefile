rubix: build compile run

compile:
	cd build && cmake ../
	cd build && make rubx

run:
	cd build/bin && ./rubx

build:
	mkdir build

clean:
	rm -r build

rubix: build configure compile run

fast: compile run

configure:
	cd build && cmake ../

compile:
	cd build && make rubx

run:
	cd build/bin && ./rubx

build:
	mkdir build

clean:
	rm -r build

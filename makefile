all: clean
	mkdir -p build
	cd build && cmake .. -GNinja && ninja

clean:
	rm -rf build

deps:
	python3 -m pip install --force-reinstall -v "cmake==4.1" --break-system-packages
.PHONY: all clean grade-3 grade-4 grade-5

all: grade-3 grade-4 grade-5

grade-3:
	$(MAKE) -C grade-3

grade-4:
	cmake -S grade-4 -B grade-4/build
	cmake --build grade-4/build

grade-5:
	cmake -S grade-5 -B grade-5/build
	cmake --build grade-5/build

clean:
	$(MAKE) -C grade-3 clean
	rm -rf grade-4/build grade-5/build

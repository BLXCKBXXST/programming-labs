.PHONY: all clean grade-3 grade-4 grade-5 grade-star benchmark

all: grade-3 grade-4 grade-5 grade-star

grade-3:
	$(MAKE) -C grade-3

grade-4:
	$(MAKE) -C grade-4

grade-5:
	$(MAKE) -C grade-5

grade-star:
	$(MAKE) -C grade-star

benchmark:
	$(MAKE) -C grade-4 benchmark

clean:
	$(MAKE) -C grade-3 clean
	$(MAKE) -C grade-4 clean
	$(MAKE) -C grade-5 clean
	$(MAKE) -C grade-star clean

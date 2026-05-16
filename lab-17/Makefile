.PHONY: all test clean grade-3 grade-4 grade-5

# Дефолтная цель — полный CMake-билд (он соберёт ВСЕ три grade и
# зарегистрирует их в ctest).
all: grade-5

# grade-3 и grade-4 имеют свои Makefile-ы и собираются автономно.
grade-3:
	$(MAKE) -C grade-3

grade-4:
	$(MAKE) -C grade-4

# grade-5 — через корневой CMakeLists.txt (он же подтянет grade-3 и grade-4).
grade-5:
	cmake -S . -B build
	cmake --build build

# Запуск всех тестов через ctest. Этот таргет используется в README
# (картинка ctest.png снята именно с такого запуска).
test: grade-5
	cd build && ctest --output-on-failure

clean:
	$(MAKE) -C grade-3 clean
	$(MAKE) -C grade-4 clean
	rm -rf build

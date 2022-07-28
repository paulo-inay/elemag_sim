CPPLIST = src/Heatmap.cpp src/Mesh.cpp
LIBS = -lpng -lstdc++fs
HEADER_DIR1 = src/include
HEADER_DIR2 = src
BUILD_DIR = build

yee11x11 : test/yee11x11.cpp
	$(shell [ ! -d $(BUILD_DIR) ] && mkdir -p $(BUILD_DIR))
	$(shell [ ! -d $(BUILD_DIR)/11x11 ] && mkdir -p $(BUILD_DIR)/11x11) 
	g++ $(CPPLIST) -g test/yee11x11.cpp -I$(HEADER_DIR1) -I$(HEADER_DIR2) $(LIBS) \
	  -o $(BUILD_DIR)/11x11/yee11x11
	cd build/11x11; \
	./yee11x11 > results.txt

yee101x101 : test/yee101x101.cpp
	$(shell [ ! -d $(BUILD_DIR) ] && mkdir -p $(BUILD_DIR))
	$(shell [ ! -d $(BUILD_DIR)/101x101 ] && mkdir -p $(BUILD_DIR)/101x101)
	g++ $(CPPLIST) -g test/yee101x101.cpp -I$(HEADER_DIR1) -I$(HEADER_DIR2) $(LIBS) \
	  -o $(BUILD_DIR)/101x101/yee101x101
	cd build/101x101; \
	./yee101x101 

twosources : test/twosources.cpp
	$(shell [ ! -d $(BUILD_DIR) ] && mkdir -p $(BUILD_DIR))
	$(shell [ ! -d $(BUILD_DIR)/twosources ] && mkdir -p $(BUILD_DIR)/twosources)
	g++ $(CPPLIST) -g test/twosources.cpp -I$(HEADER_DIR1) -I$(HEADER_DIR2) $(LIBS) \
		-o $(BUILD_DIR)/twosources/twosources
	cd build/twosources; \
	./twosources 
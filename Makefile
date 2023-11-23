# clear && python3 generate_raw_measurements.py && cat raw_measurements.csv && gcc src/*.c OpenAHRS_9DOF.c -o build/OpenAHRS_9DOF -lm && ./build/OpenAHRS_9DOF
# clear && python3 generate_raw_measurements.py && cat build/raw_measurements.csv && gcc src/*.c -o build/OpenAHRS_9DOF -lm && cd build/ && ./OpenAHRS_9DOF && cd ..
# clear && make clean && make && python3 generate_raw_measurements.py && cat build/raw_measurements.csv && cd build/ && ./OpenAHRS_9DOF && cd ..
# clear && git clone https://OpenRTVC:ghp_FHTpGuD4s695Mzz8xVy3jOCfgafc5t08E81r@github.com/OpenRTVC/OpenAHRS.git && cd OpenAHRS && git add 'filename' && git commit -m "Add 'filename' file." && git push origin main
# clear && make clean && make && python3 generate_raw_measurements.py && cat build/raw_measurements.csv && cd build/ && ./OpenAHRS_9DOF && cd .. && find * -type f -exec md5sum {} + | while read sum file; do md5sum_dest=$(md5sum "/home/titoune/github/OpenAHRS/$file" 2>/dev/null | awk '{print $1}'); [ "$sum" != "$md5sum_dest" ] && echo "Copie : $file" && cp "$file" "/home/titoune/github/OpenAHRS/$file"; done
# clear && git checkout main && git add --all && git commit -m "Automatic update - $(date)" && git push origin main

CC = gcc
CFLAGS = -Wall -I./includes
#CFLAGS = -Wall -I./includes -Wunused-variable -Wno-unused-variable
LDFLAGS = -lm
SRC_DIR = ./src
BUILD_DIR = ./build
EXE = OpenAHRS_9DOF

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))

all: $(BUILD_DIR)/$(EXE)

$(BUILD_DIR)/$(EXE): $(OBJS)
	$(CC) $^ $(CFLAGS) $(LDFLAGS) -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean

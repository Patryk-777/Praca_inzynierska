# Project Name
TARGET = MyProj

# Source Files
CPP_SOURCES = \
    src/main.cpp \
    src/FuzzEffect.cpp \
    src/OnePoleLPF.cpp \
    src/ShelfFilter.cpp \
    src/AnalogFuzz.cpp \
    src/EffectBypass.cpp   # <-- DODANE

# Library Locations
LIBDAISY_DIR = ../../libDaisy
DAISYSP_DIR  = ../../DaisySP

# Include directories
INCLUDE_DIRS = \
    $(LIBDAISY_DIR) \
    $(LIBDAISY_DIR)/Drivers \
    $(LIBDAISY_DIR)/src \
    $(DAISYSP_DIR)/Source \
    src

# Core location and Makefile include
SYSTEM_FILES_DIR = $(LIBDAISY_DIR)/core
include $(SYSTEM_FILES_DIR)/Makefile

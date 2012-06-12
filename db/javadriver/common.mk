AM_CFLAGS = # -Wall -Wextra 
AM_CPPFLAGS = # -Wall -Wextra 
AM_CXXFLAGS = #-fpic

if DEBUG
AM_CPPFLAGS += -g3 -O3
AM_CXXFLAGS += -g3 -O3
endif

if PROFILE
AM_CPPFLAGS += -pg
AM_CXXFLAGS += -pg
endif


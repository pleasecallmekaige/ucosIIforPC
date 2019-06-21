# Project: uCOSII

BuildPath = ./build
MinGWPath = D:/App/MinGW

CPP      = g++.exe -D__DEBUG__
CC       = gcc.exe -D__DEBUG__
WINDRES  = windres.exe
OBJ      = ${BuildPath}/main.o ${BuildPath}/Source/os_dbg_r.o ${BuildPath}/Source/ucos_ii.o ${BuildPath}/Ports/WIN32/os_cpu_c.o ${BuildPath}/Ports/WIN32/os_trace.o
LINKOBJ  = ${BuildPath}/main.o ${BuildPath}/Source/os_dbg_r.o ${BuildPath}/Source/ucos_ii.o ${BuildPath}/Ports/WIN32/os_cpu_c.o ${BuildPath}/Ports/WIN32/os_trace.o
LIBS     = -L"${MinGWPath}/mingw64/lib" \
           -L"${MinGWPath}/mingw64/x86_64-w64-mingw32/lib" \
		   -static-libgcc -lWinMM -lkernel32 -luser32 -lgdi32 -lwinspool -lcomdlg32 -ladvapi32 -lshell32 -lole32 -loleaut32 -luuid -lodbc32 -lodbccp32 -lkernel32 -luser32 -lgdi32 -lwinspool -lcomdlg32 -ladvapi32 -lshell32 -lole32 -loleaut32 -luuid -lodbc32 -lodbccp32
INCS     = -I"${MinGWPath}/mingw64/include" \
           -I"${MinGWPath}/mingw64/x86_64-w64-mingw32/include" \
		   -I"${MinGWPath}/mingw64/lib/gcc/x86_64-w64-mingw32/4.9.2/include" \
		   -I".//" \
		   -I"./Source//" \
		   -I"./Ports/Win32//"
CXXINCS  = -I"${MinGWPath}/mingw64/include" \
           -I"${MinGWPath}/mingw64/x86_64-w64-mingw32/include" \
		   -I"${MinGWPath}/mingw64/lib/gcc/x86_64-w64-mingw32/4.9.2/include" \
		   -I"${MinGWPath}/mingw64/lib/gcc/x86_64-w64-mingw32/4.9.2/include/c++" \
		   -I".//" \
		   -I"./Source//" \
		   -I"./Ports/Win32//"
BIN      = uCOSII.exe
CXXFLAGS = $(CXXINCS) -g3 -D__GNUWIN32__ -W -fexceptions -DWIN32 -D_DEBUG -D_CONSOLE -D_MBCS
CFLAGS   = $(INCS) -g3 -D__GNUWIN32__ -W -fexceptions -DWIN32 -D_DEBUG -D_CONSOLE -D_MBCS
RM       = rm.exe -f


.PHONY: all all-before all-after clean clean-custom

all: all-before $(BIN) all-after

clean: clean-custom
	${RM} $(OBJ) $(BIN)
	${RM} -r ${BuildPath}

$(BIN): $(OBJ)
	$(CPP) $(LINKOBJ) -o $(BIN) $(LIBS)

${BuildPath}/main.o: main.c
	if [ ! -d ${BuildPath} ]; then mkdir ${BuildPath}; fi;\
	$(CC) -c main.c -o ${BuildPath}/main.o $(CFLAGS)

${BuildPath}/Source/os_dbg_r.o: Source/os_dbg_r.c
	if [ ! -d ${BuildPath}/Source ]; then mkdir -p ${BuildPath}/Source; fi;\
	$(CC) -c Source/os_dbg_r.c -o ${BuildPath}/Source/os_dbg_r.o $(CFLAGS)

${BuildPath}/Source/ucos_ii.o: Source/ucos_ii.c
	if [ ! -d ${BuildPath}/Source ]; then mkdir -p ${BuildPath}/Source; fi;\
	$(CC) -c Source/ucos_ii.c -o ${BuildPath}/Source/ucos_ii.o $(CFLAGS)

${BuildPath}/Ports/WIN32/os_cpu_c.o: Ports/WIN32/os_cpu_c.c
	if [ ! -d ${BuildPath}/Ports/WIN32 ]; then mkdir -p ${BuildPath}/Ports/WIN32; fi;\
	$(CC) -c Ports/WIN32/os_cpu_c.c -o ${BuildPath}/Ports/WIN32/os_cpu_c.o $(CFLAGS)

${BuildPath}/Ports/WIN32/os_trace.o: Ports/WIN32/os_trace.c
	if [ ! -d ${BuildPath}/Ports/WIN32 ]; then mkdir -p ${BuildPath}/Ports/WIN32; fi;\
	$(CC) -c Ports/WIN32/os_trace.c -o ${BuildPath}/Ports/WIN32/os_trace.o $(CFLAGS)

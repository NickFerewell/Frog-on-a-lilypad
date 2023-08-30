CC := g++# Compiler name
ProgramName := UnluckyFrog
debugFlags := -g
releaseFlags := -O2
buildMode ?= RELEASE#  DEBUG -g, RELEASE -O2
compFlags := -Wall# Если собираешся дебагить, то добавляй "-g". А если релизить, то "-O2". "-Wall" включает многие оповещения компилятора об ошибках.
srcDir := src
objDir := obj
binDir := bin
depDir := dep
includeDir := libs/include# directory with libraries
sources := $(wildcard $(srcDir)/*.cpp)
headers := $(wildcard $(srcDir)/*.h)
objects := $(patsubst %.cpp,%.o,$(sources))
objects := $(patsubst $(srcDir)%,$(objDir)%,$(objects))

ifeq ($(buildMode),RELEASE)
    compFlags += $(releaseFlags)
else
	compFlags += $(debugFlags)
endif

VPATH := src:obj
 
all: sayBuilding checkFolders build sayCompleted run

onlyBuild: sayBuilding checkFolders build sayCompleted

sayBuilding:
	@echo Building $(ProgramName) in $(buildMode) mode...
	@echo ...

sayCompleted:
	@echo Building completed!
	@echo ...

checkFolders:
	@echo Checking folders
	-mkdir $(objDir)
	-mkdir $(binDir)
	-mkdir $(depDir)
	@echo ...

build: $(objects)
	@echo Linking $^
	$(CC) -o $(binDir)/$(ProgramName) $(objects) -L libs/src -l sfml-graphics -l sfml-window -l sfml-system -l libbox2d
	@echo ...

run:
	@echo Running...
	$(binDir)/$(ProgramName).exe
	@echo App closed
	@echo ...
#.cpp.o:
#	$(CC) -c $< -o $@ -I $(includeDir)

#Собачка(@) говорит, что эту строку не надо печатать в консоль
#notdir берёт только название и расширение файла, но не путь к нему
clean:
	@echo Cleaning...
	
	-cd $(objDir) && rm $(notdir $(wildcard $(objDir)/*.o))
	-cd $(depDir) && rm $(notdir $(wildcard $(depDir)/*.d))
	-cd $(binDir) && rm $(ProgramName).exe
	
	@echo Cleaning completed!
# or use del on windows?

cleanAll:
	@echo Cleaning ALL...
	
	# if exist $(objDir) (rmdir /s/q $(objDir))
	# if exist $(depDir) (rmdir /s/q $(depDir))
	# rmdir $(objDir) $(depDir)

	test -d $(objDir) && rm -r $(objDir)
	test -d $(depDir) && rm -r $(depDir)

	-cd $(binDir) && rm $(ProgramName).exe
	
	@echo Cleaning ALL completed!

-include $(objects:$(objDir)/%.o=$(depDir)/%.d)

$(objDir)/%.o: $(srcDir)/%.cpp
	@echo Compiling $@ from $<
	$(CC) $(compFlags) -c $< -o $@ -I $(includeDir)
	$(CC) -MM -MT $(objDir)/$*.o -MP $(compFlags) $< > $(depDir)/$*.d
	@echo ...
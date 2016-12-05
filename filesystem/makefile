sSOURCES=$(wildcard ./*.cpp ./parse/*.cpp ./parse/parser/*.cpp ./parse/sql/*.cpp )
HEADERS=$(wildcard  ./indexmanager/*.h ./parse/*.h ./parse/parser/*.h ./parse/sql/*.h ./bufmaneger/*.h ./recordmaneger/*.h ./utils/*.h ./systemManager/*.h)
sOBJECTS=$(sSOURCES:%.cpp=%.o)
TARGET=test

all: $(TARGET)
$(TARGET): $(sOBJECTS) $(HEADERS)
	@echo "Now Generating $(TARGET) ..."
	g++ $(sOBJECTS) -o $(TARGET)
%.o: %.cpp $(HEADERS)
	@echo "Now Compiling $< ..."
	g++ -g -I. -std=c++11 -c $< -o $@
clean:
	del *.o *.exe *.bak
explain:
	@echo "Headers: $(HEADERS)"
	@echo "User Sources: $(sSOURCES)"
	@echo "User Objects: $(sOBJECTS)"
	@echo "Target: $(TARGET)"

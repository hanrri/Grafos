# Compilador e flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -Iinclude

# Nome do executável final
TARGET = programa

SRCS = src/main.cpp src/grafo.cpp
OBJS = $(SRCS:.cpp=.o)

# Regra principal
all: $(TARGET)

# Como construir o executável
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regra para limpar os arquivos gerados (útil antes de subir pro GitHub)
clean:
	rm -f $(OBJS) $(TARGET)
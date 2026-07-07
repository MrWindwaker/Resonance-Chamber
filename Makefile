# ---- Project config ----
NAME       := hexmerge
SRC        := src/main.c src/hex_grid.c src/tile.c
DIST_WEB   := dist/web
DIST_NATIVE:= dist/native

RAYLIB_WEB_DIR    := lib/raylib/web
RAYLIB_NATIVE_DIR := lib/raylib/native

# ---- Web (emscripten) build ----
EMCC_FLAGS := -DPLATFORM_WEB -Os \
              -s USE_GLFW=3 \
              -s ASYNCIFY \
              -s TOTAL_MEMORY=67108864

web: $(DIST_WEB)/index.html

$(DIST_WEB)/index.html: $(SRC)
	mkdir -p $(DIST_WEB)
	emcc $(SRC) -o $(DIST_WEB)/index.html \
		-I$(RAYLIB_WEB_DIR) -L$(RAYLIB_WEB_DIR) -lraylib \
		$(EMCC_FLAGS)

serve: web
	cd $(DIST_WEB) && python3 -m http.server 8000

# ---- Native build (fast local iteration, no browser needed) ----
CC := gcc
CFLAGS := -Wall -std=c99
LDFLAGS_NATIVE := -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

native: $(DIST_NATIVE)/$(NAME)

$(DIST_NATIVE)/$(NAME): $(SRC)
	mkdir -p $(DIST_NATIVE)
	$(CC) $(SRC) -o $(DIST_NATIVE)/$(NAME) \
		-I$(RAYLIB_NATIVE_DIR) -L$(RAYLIB_NATIVE_DIR) \
		$(CFLAGS) $(LDFLAGS_NATIVE)

run: native
	./$(DIST_NATIVE)/$(NAME)

# ---- Housekeeping ----
clean:
	rm -rf $(DIST_WEB) $(DIST_NATIVE)

.PHONY: web serve native run clean
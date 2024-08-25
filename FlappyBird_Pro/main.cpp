#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int PIPE_WIDTH = 80;
const int PIPE_HEIGHT = 400;
const int BIRD_WIDTH = 50;
const int BIRD_HEIGHT = 50;
const int GRAVITY = 1;
const int JUMP_STRENGTH = 10;
const int PIPE_SPEED = 3;

enum GameState { MENU, PLAY, PAUSE, GAMEOVER, HELP, HIGHSCORE, CREDITS };

struct Pipe {
    int x, y;
    bool passed;
};

class FlappyBird {
public:
    FlappyBird();
    ~FlappyBird();
    bool init();
    void run();
private:
    void handleEvents(bool& quit);
    void update();
    void render();
    void close();
    void reset();
    bool checkCollision();
    void renderText(const std::string& text, int x, int y, SDL_Color color);
    void loadHighScore();
    void saveHighScore();
    void renderMenu();
    void renderHighScore();
    void renderGameOver();
    void renderCredits();
    void renderPause();
    void renderHelp();  // Thêm hàm để hiển thị hướng dẫn

    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* birdTexture;
    SDL_Texture* pipeTexture;
    SDL_Texture* backgroundTexture;
    Mix_Chunk* hitSound;
    Mix_Chunk* pointSound;
    Mix_Chunk* flapSound;
    TTF_Font* font;

    int birdX, birdY, birdVelocity;
    std::vector<Pipe> pipes;
    int score;
    int highScore;
    bool gameOver;
    GameState gameState;
};

FlappyBird::FlappyBird() : window(nullptr), renderer(nullptr), birdTexture(nullptr), pipeTexture(nullptr), backgroundTexture(nullptr), hitSound(nullptr), pointSound(nullptr), flapSound(nullptr), font(nullptr), birdX(100), birdY(SCREEN_HEIGHT / 2), birdVelocity(0), score(0), highScore(0), gameOver(false), gameState(MENU) {}

FlappyBird::~FlappyBird() {
    close();
}

bool FlappyBird::init() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow("Flappy Bird", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        std::cerr << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
        return false;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
        return false;
    }

    if (TTF_Init() == -1) {
        std::cerr << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << std::endl;
        return false;
    }

    birdTexture = IMG_LoadTexture(renderer, "assets/bird.png");
    pipeTexture = IMG_LoadTexture(renderer, "assets/pipe.png");
    backgroundTexture = IMG_LoadTexture(renderer, "assets/background.png");
    hitSound = Mix_LoadWAV("assets/hit.wav");
    pointSound = Mix_LoadWAV("assets/point.wav");
    flapSound = Mix_LoadWAV("assets/flap.wav");
    font = TTF_OpenFont("assets/font.ttf", 28);

    if (!birdTexture || !pipeTexture || !backgroundTexture || !hitSound || !pointSound || !flapSound || !font) {
        std::cerr << "Failed to load assets! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    loadHighScore();

    srand(static_cast<unsigned int>(time(0)));
    return true;
}

void FlappyBird::run() {
    bool quit = false;
    SDL_Event e;

    while (!quit) {
        handleEvents(quit);
        update();
        render();

        SDL_Delay(16);

        if (gameOver && gameState == GAMEOVER) {
            SDL_WaitEvent(&e);
            if (e.type == SDL_QUIT) {
                quit = true;
            } else if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_SPACE) {
                    reset();
                    gameState = MENU;
                } else if (e.key.keysym.sym == SDLK_q) {
                    quit = true;
                }
            }
        }
    }
}

void FlappyBird::handleEvents(bool& quit) {
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            quit = true;
        } else if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym) {
                case SDLK_SPACE:
                    if (gameState == PLAY) {
                        birdVelocity = -JUMP_STRENGTH;
                        Mix_PlayChannel(-1, flapSound, 0);
                    } else if (gameState == MENU) {
                        gameState = PLAY;
                    } else if (gameState == GAMEOVER) {
                        reset();
                        gameState = MENU;
                    }
                    break;
                case SDLK_p:
                    if (gameState == PLAY) {
                        gameState = PAUSE;
                    }
                    break;
                case SDLK_r:
                    if (gameState == PAUSE) {
                        gameState = PLAY;
                    }
                    break;
                case SDLK_h:
                    if (gameState == MENU) {
                        gameState = HELP;
                    }
                    break;
                case SDLK_m:
                    if (gameState == HELP || gameState == HIGHSCORE || gameState == CREDITS || gameState == PAUSE) {
                        gameState = MENU;
                    }
                    break;
                case SDLK_s:
                    if (gameState == MENU) {
                        gameState = HIGHSCORE;
                    }
                    break;
                case SDLK_c:
                    if (gameState == MENU) {
                        gameState = CREDITS;
                    }
                    break;
                case SDLK_q:
                    if (gameState == MENU || gameState == GAMEOVER) {
                        quit = true;  // Thoát game khi nhấn Q
                    }
                    break;
            }
        }
    }
}

void FlappyBird::update() {
    if (gameState == PLAY) {
        birdY += birdVelocity;
        birdVelocity += GRAVITY;

        if (birdY < 0) {
            birdY = 0;
        } else if (birdY + BIRD_HEIGHT > SCREEN_HEIGHT) {
            birdY = SCREEN_HEIGHT - BIRD_HEIGHT;
            gameOver = true;
            gameState = GAMEOVER;
            Mix_PlayChannel(-1, hitSound, 0);
            saveHighScore();
        }

        for (auto& pipe : pipes) {
            pipe.x -= PIPE_SPEED;

            if (!pipe.passed && pipe.x + PIPE_WIDTH < birdX) {
                pipe.passed = true;
                score++;
                Mix_PlayChannel(-1, pointSound, 0);
            }

            if (pipe.x + PIPE_WIDTH < 0) {
                pipes.erase(pipes.begin());
            }
        }

        if (pipes.empty() || pipes.back().x < SCREEN_WIDTH - 300) {
            Pipe newPipe;
            newPipe.x = SCREEN_WIDTH;
            newPipe.y = rand() % (SCREEN_HEIGHT - PIPE_HEIGHT - 100) + 50;
            newPipe.passed = false;
            pipes.push_back(newPipe);
        }

        if (checkCollision()) {
            gameOver = true;
            gameState = GAMEOVER;
            Mix_PlayChannel(-1, hitSound, 0);
            saveHighScore();
        }
    }
}

void FlappyBird::render() {
    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);

    if (gameState == MENU) {
        renderMenu();
    } else if (gameState == PLAY) {
        for (const auto& pipe : pipes) {
            SDL_Rect topPipeRect = {pipe.x, pipe.y - PIPE_HEIGHT, PIPE_WIDTH, PIPE_HEIGHT};
            SDL_Rect bottomPipeRect = {pipe.x, pipe.y + 150, PIPE_WIDTH, PIPE_HEIGHT};
            SDL_RenderCopy(renderer, pipeTexture, NULL, &topPipeRect);
            SDL_RenderCopyEx(renderer, pipeTexture, NULL, &bottomPipeRect, 0, NULL, SDL_FLIP_VERTICAL);
        }

        SDL_Rect birdRect = {birdX, birdY, BIRD_WIDTH, BIRD_HEIGHT};
        SDL_RenderCopy(renderer, birdTexture, NULL, &birdRect);

        renderText("Score: " + std::to_string(score), 10, 10, {64, 64, 64}); // Màu xám đậm
    } else if (gameState == PAUSE) {
        renderPause();
    } else if (gameState == GAMEOVER) {
        renderGameOver();
    } else if (gameState == HELP) {
        renderHelp();  // Gọi hàm renderHelp để hiển thị hướng dẫn
    } else if (gameState == HIGHSCORE) {
        renderHighScore();
    } else if (gameState == CREDITS) {
        renderCredits();
    }

    SDL_RenderPresent(renderer);
}

void FlappyBird::renderMenu() {
    renderText("Flappy Bird", SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 100, {64, 64, 64}); // Màu xám đậm
    renderText("Press SPACE to Start", SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 - 50, {64, 64, 64}); // Màu xám đậm
    renderText("Press H for Help", SCREEN_WIDTH / 2 - 120, SCREEN_HEIGHT / 2, {64, 64, 64}); // Màu xám đậm
    renderText("Press S to View High Scores", SCREEN_WIDTH / 2 - 200, SCREEN_HEIGHT / 2 + 50, {64, 64, 64}); // Màu xám đậm
    renderText("Press C for Credits", SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 + 100, {64, 64, 64}); // Màu xám đậm
    renderText("Press Q to Quit", SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 + 150, {64, 64, 64}); // Màu xám đậm
}

void FlappyBird::renderPause() {
    renderText("Paused", SCREEN_WIDTH / 2 - 60, SCREEN_HEIGHT / 2 - 100, {64, 64, 64}); // Màu xám đậm
    renderText("Press R to Resume", SCREEN_WIDTH / 2 - 120, SCREEN_HEIGHT / 2, {64, 64, 64}); // Màu xám đậm
    renderText("Press M to go to Menu", SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 + 50, {64, 64, 64}); // Màu xám đậm
}

void FlappyBird::renderHelp() {
    renderText("Help:", SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2 - 150, {64, 64, 64}); // Màu xám đậm
    renderText("Press SPACE to Flap", SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 - 100, {64, 64, 64}); // Màu xám đậm
    renderText("Avoid the Pipes!", SCREEN_WIDTH / 2 - 120, SCREEN_HEIGHT / 2 - 50, {64, 64, 64}); // Màu xám đậm
    renderText("Press P to Pause the game", SCREEN_WIDTH / 2 - 180, SCREEN_HEIGHT / 2, {64, 64, 64}); // Màu xám đậm
    renderText("Press R to Resume", SCREEN_WIDTH / 2 - 120, SCREEN_HEIGHT / 2 + 50, {64, 64, 64}); // Màu xám đậm
    renderText("Press M to go to Menu", SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 + 100, {64, 64, 64}); // Màu xám đậm
}

void FlappyBird::renderHighScore() {
    renderText("High Scores", SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 100, {64, 64, 64}); // Màu xám đậm
    renderText("Highest Score: " + std::to_string(highScore), SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 - 50, {64, 64, 64}); // Màu xám đậm
    renderText("Press M to go to Menu", SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2, {64, 64, 64}); // Màu xám đậm
}

void FlappyBird::renderCredits() {
    renderText("Credits", SCREEN_WIDTH / 2 - 60, SCREEN_HEIGHT / 2 - 100, {64, 64, 64}); // Màu xám đậm
    renderText("Created by: quocanh27", SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 - 50, {64, 64, 64}); // Màu xám đậm
    renderText("Version: 2.0", SCREEN_WIDTH / 2 - 80, SCREEN_HEIGHT / 2, {64, 64, 64}); // Màu xám đậm
    renderText("Press M to go to Menu", SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 + 50, {64, 64, 64}); // Màu xám đậm
}

void FlappyBird::renderGameOver() {
    renderText("Game Over!", SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 50, {255, 0, 0}); // Màu đỏ
    renderText("High Score: " + std::to_string(highScore), SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2, {64, 64, 64}); // Màu xám đậm
    renderText("Press SPACE to Restart", SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 + 50, {64, 64, 64}); // Màu xám đậm
    renderText("Press Q to Quit", SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 + 100, {64, 64, 64}); // Màu xám đậm
}

void FlappyBird::close() {
    SDL_DestroyTexture(birdTexture);
    SDL_DestroyTexture(pipeTexture);
    SDL_DestroyTexture(backgroundTexture);
    Mix_FreeChunk(hitSound);
    Mix_FreeChunk(pointSound);
    Mix_FreeChunk(flapSound);
    TTF_CloseFont(font);

    birdTexture = nullptr;
    pipeTexture = nullptr;
    backgroundTexture = nullptr;
    hitSound = nullptr;
    pointSound = nullptr;
    flapSound = nullptr;
    font = nullptr;

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    renderer = nullptr;
    window = nullptr;

    Mix_Quit();
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}

void FlappyBird::reset() {
    birdX = 100;
    birdY = SCREEN_HEIGHT / 2;
    birdVelocity = 0;
    pipes.clear();
    score = 0;
    gameOver = false;
}

bool FlappyBird::checkCollision() {
    for (const auto& pipe : pipes) {
        SDL_Rect birdRect = {birdX, birdY, BIRD_WIDTH, BIRD_HEIGHT};
        SDL_Rect topPipeRect = {pipe.x, pipe.y - PIPE_HEIGHT, PIPE_WIDTH, PIPE_HEIGHT};
        SDL_Rect bottomPipeRect = {pipe.x, pipe.y + 150, PIPE_WIDTH, PIPE_HEIGHT};

        if (SDL_HasIntersection(&birdRect, &topPipeRect) || SDL_HasIntersection(&birdRect, &bottomPipeRect)) {
            return true;
        }
    }
    return false;
}

void FlappyBird::renderText(const std::string& text, int x, int y, SDL_Color color) {
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), color);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    SDL_Rect renderQuad = { x, y, textSurface->w, textSurface->h };
    SDL_RenderCopy(renderer, textTexture, NULL, &renderQuad);

    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}

void FlappyBird::loadHighScore() {
    std::ifstream file("highscore.txt");
    if (file.is_open()) {
        file >> highScore;
        file.close();
    } else {
        highScore = 0;
    }
}

void FlappyBird::saveHighScore() {
    if (score > highScore) {
        highScore = score;
        std::ofstream file("highscore.txt");
        if (file.is_open()) {
            file << highScore;
            file.close();
        }
    }
}

int main(int argc, char* args[]) {
    FlappyBird game;
    if (game.init()) {
        game.run();
    }

    return 0;
}

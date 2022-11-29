#ifndef SCREENS_H
#define SCREENS_H

typedef enum GameScreen { UNKNOWN = -1, GAMEPLAY = 0} GameScreen;

const int screenWidth = 800;
const int screenHeight = 450;
extern GameScreen currentScreen;
extern Font font;
extern Music music; 

extern "C" {

void InitGameplayScreen(void);
void UpdateGameplayScreen(void);
void DrawGameplayScreen(void);
void UnloadGameplayScreen(void);

}

#endif // SCREENS_H
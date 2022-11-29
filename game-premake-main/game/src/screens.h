#ifndef SCREENS_H
#define SCREENS_H

typedef enum GameScreen { UNKNOWN = -1, LOGO = 0, GAMEPLAY } GameScreen;

//can ignore
extern GameScreen currentScreen;
extern Font font;
extern Music music;

#ifdef __cplusplus
extern "C" {            // Prevents name mangling of functions
#endif

void InitLogoScreen(void);
void UpdateLogoScreen(void);
void DrawLogoScreen(void);
void UnloadLogoScreen(void);
int FinishLogoScreen(void);


void InitGameplayScreen(void);
void UpdateGameplayScreen(void);
void DrawGameplayScreen(void);
void UnloadGameplayScreen(void);
int FinishGameplayScreen(void);

#ifdef __cplusplus
}
#endif

#endif // SCREENS_H
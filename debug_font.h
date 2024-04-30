
#ifndef DEBUG_FONT_H_
#define DEBUG_FONT_H_


void DebugFont_Initialize(void);

void DebugFont_Finalize(void);


void DebugFont_Draw(int x, int y, const char* pFormat, ...);


#endif // DEBUG_FONT_H_
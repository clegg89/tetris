/**
 * @file GameIO.cpp
 * 
 * @author C. Smith
 * @date Dec 6, 2015
 */

#include <cstdio>

#include "GameIO.h"

GameIO GameIO::pSelf;

GameIO::GameIO() : pWindowHeight( 640 ), pWindowWidth( 480 )
{
    this->pImpl = new GameIOImpl();

    this->UnregisterKeyCBs();
}

GameIO::~GameIO()
{
    this->UnregisterKeyCBs();

    delete this->pImpl;
}

bool GameIO::Init(const int windowHeight, const int windowWidth)
{
    this->pWindowHeight = windowHeight;
    this->pWindowWidth = windowWidth;

    this->UnregisterKeyCBs();

    return this->pImpl->Init(this->pWindowHeight, this->pWindowWidth, Color(0x00, 0x00, 0x00, 0xFF));
}

void GameIO::Close()
{
    this->pImpl->Close();

    this->UnregisterKeyCBs();

    this->pWindowHeight = 0;
    this->pWindowWidth = 0;
}

static bool validateKeycode(eKeyCode keycode)
{
    if (keycode >= NUM_KEYCODES)
    {
        return false;
    }

    return true;
}

void GameIO::UnregisterKeyCBs(void)
{
    for (int i = 0; i < NUM_KEYCODES; ++i)
    {
        this->pKeyCallbacks[i].callback = NULL;
        this->pKeyCallbacks[i].context = NULL;
    }
}
void GameIO::RegisterKeyCB(tKeyCB callback, void* context, eKeyCode keycode)
{
    if (!validateKeycode(keycode))
        return;

    this->pKeyCallbacks[keycode].callback = callback;
    this->pKeyCallbacks[keycode].context = context;
}

void GameIO::ClearScreen(const Color bgColor)
{
    this->pImpl->ClearScreen(bgColor);
}

void GameIO::DrawRect(const int x, const int y, const int w, const int h, const Color color)
{
    this->pImpl->DrawRect(x, y, w, h, color);
}

void GameIO::DrawBorder(const Color borderColor, const Color bgColor)
{
    int x, y, w, h;

    x = 0;
    y = 0;
    w = ( BORDER_SIZE_PIXELS * 2 ) + ( BLOCK_SIZE_PIXELS * BOARD_WIDTH );
    h = ( BLOCK_SIZE_PIXELS * BOARD_HEIGHT );

    this->pImpl->DrawRect(x, y, w, h, borderColor);

    x += BORDER_SIZE_PIXELS;
    w = ( BLOCK_SIZE_PIXELS * BOARD_WIDTH );
    h = ( BLOCK_SIZE_PIXELS * BOARD_HEIGHT );

    this->pImpl->DrawRect(x, y, w, h, bgColor);
}

void GameIO::DrawBoard(Board* board)
{
    for (int i = 0; i < BOARD_WIDTH; ++i)
    {
        for (int j = 0; j < BOARD_HEIGHT; ++j)
        {
            if (board->IsFilled(i, j))
            {
                this->internalDrawBlock(*(board->GetBlockColor(i, j)), i, j);
            }
        }
    }
}

void GameIO::DrawTetromino(Tetromino* tetro)
{
    this->internalDrawTetro(tetro, tetro->GetX(), tetro->GetY(), false);
}

void GameIO::DrawNextTetromino(Tetromino* tetro)
{
    this->internalDrawTetro(tetro, NEXT_TETROMINO_X, NEXT_TETROMINO_Y, true);
}

void GameIO::PrintLevel(int level)
{
    static char levelStr[20];
    Color color_white(0xFF, 0xFF, 0xFF, 0xFF);

    sprintf(levelStr, "Level: %d", level);

    this->pImpl->PrintText(levelStr, this->pWindowWidth, 0, HALIGN_RIGHT, VALIGN_TOP, color_white);
}

void GameIO::PrintScore(int score)
{
    static char scoreStr[20];
    int x = ( BORDER_SIZE_PIXELS * 2 ) + ( BLOCK_SIZE_PIXELS * BOARD_WIDTH );
    Color color_white(0xFF, 0xFF, 0xFF, 0xFF);

    sprintf(scoreStr, "Score: %d", score);

    this->pImpl->PrintText(scoreStr, x, 0, HALIGN_LEFT, VALIGN_TOP, color_white);
}

void GameIO::Print(const char* text, const int x, const int y, const hAlignment hAlign, vAlignment vAlign, const Color color)
{
    this->pImpl->PrintText(text, x, y, hAlign, vAlign, color);
}

void GameIO::internalDrawTetro(Tetromino* tetro, int x, int y, bool isBase)
{
    for (int i = 0; i < TETROMINO_BLOCKS; ++i)
    {
    	for (int j = 0; j < TETROMINO_BLOCKS; ++j)
    	{
    		if (tetro->IsBlockFilled(i, j, isBase))
    		{
    		    this->internalDrawBlock(*(tetro->GetColor()), (i + x), (j + y));
    		}
		}
	}
}

void GameIO::internalDrawBlock(Color color, int x, int y)
{
    int block_x, block_y, w, h;

    w = BLOCK_SIZE_PIXELS;
    h = BLOCK_SIZE_PIXELS;
    block_x = BORDER_SIZE_PIXELS + ( x * BLOCK_SIZE_PIXELS );
    block_y = ( y * BLOCK_SIZE_PIXELS );

    this->pImpl->DrawTexture(block_x, block_y, w, h, color);
}

void GameIO::Present()
{
    this->pImpl->Present();
}

void GameIO::LoadFontFromFile(const char * filename, int size)
{
    this->pImpl->LoadFontFromFile(filename, size);
}

void GameIO::LoadBgMusicFromFile(const char * filename)
{
    this->pImpl->LoadBgMusicFromFile(filename);
}

void GameIO::PlayBgMusic()
{
    this->pImpl->PlayBgMusic();
}

void GameIO::PauseBgMusic()
{
    this->pImpl->PauseBgMusic();
}

void GameIO::callKeyCallback(eKeyCode keycode, eKeyDirection direction)
{
    if (this->pKeyCallbacks[keycode].callback != NULL)
    {
        this->pKeyCallbacks[keycode].callback(this->pKeyCallbacks[keycode].context, direction);
    }
}

bool GameIO::PollInputs()
{
    return this->pImpl->PollInputs(this->pKeyCallbacks);
}

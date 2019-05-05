#include <PlayState.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <PlayLevel.h>
#include <Player.h>
#include <LevelInfo.h>
#include <experimental/filesystem>
#include <StateReturnValue.h>
#include <DeadScreen.h>
#include <WinScreen.h>
#include <assert.h>

PlayState::PlayState(SDL_Window *window, Player *player, Mix_Music *music) : GameState(window) {
	m_music = music;
	m_player = player;
	m_quit = false;
	m_playing = false;
	m_currentLevel = nullptr;
	m_order = "";
	m_mouseX = -1;
	m_mouseY = -1;
	m_background = IMG_LoadTexture(m_renderer, "data/img/lacity2.png");
	if(m_background == NULL) {
		std::cerr << "Could not load image lacity.png" << std::endl;
		std::cerr << IMG_GetError() << std::endl;
		assert(m_background != NULL);
	}
	m_menuButton = new Button(m_renderer, "Go back");
	for(auto& fileName: std::experimental::filesystem::directory_iterator("data/map")) {
		LevelInfo *levelInfo = new LevelInfo(m_renderer, fileName.path());
		if(levelInfo == nullptr) {
			std::cerr << "Couldn't load informations about " << fileName.path() << std::endl;
			assert(levelInfo != nullptr);
		}
		m_levels.push_back(levelInfo);
	}
}

PlayState::~PlayState() {
	SDL_DestroyTexture(m_background);
	delete m_menuButton;
	for(const LevelInfo *elem : m_levels) {
		delete elem;
	}
}

void PlayState::render() {
	SDL_SetRenderDrawColor(m_renderer, 255, 128, 128, 255);
	SDL_RenderClear(m_renderer);
	// Get the renderer's size
	int width, height, count;
	SDL_GetRendererOutputSize(m_renderer, &width, &height);
	// Get the background width and height
	int BGW, BGH;
	SDL_QueryTexture(m_background, NULL, NULL, &BGW, &BGH);
	// Calculate the src rectangle of the background
	SDL_Rect backgroundRect = { (BGW - BGH*width/height)/2, 0, BGH*width/height, BGH };
	// Copy the texture to the renderer
	SDL_RenderCopy(m_renderer, m_background, &backgroundRect, NULL);
	int x, y, w, h;
	x = 10;
	y = 10;
	w = width / 4 - 20;
	h = height /5-20;
	SDL_Rect rect = { x, y, w, h };
	SDL_RenderCopy(m_renderer, m_menuButton->getTexture(), NULL, &rect);
	if(m_mouseX > x && m_mouseX < x + w && m_mouseY > y && m_mouseY < y + h) {
		m_mouseX = -1;
		m_mouseY = -1;
		m_order = "Menu";		
	}
	std::vector<LevelInfo*>::iterator i;
	for(i = m_levels.begin(), count = 0; count < 8 && i != m_levels.end(); count++, i++) {
		x = (count%4)*width/4 + 10;
		y = ((int)(count/4)*2+1) * height/5 + 10;
		w = width/4 - 20;
		h = 2*height/5 - 20;
		if(m_mouseX > x && m_mouseX < x + w && m_mouseY > y && m_mouseY < y + h) {
			m_mouseX = -1;
			m_mouseY = -1;
			m_order = (*i)->getPath();		
		}
		rect = { x, y, w, h };
		SDL_RenderCopy(m_renderer, (*i)->getTexture(), NULL, &rect);
		y += height/5 + 5;
		h /= 2;
		rect = { x, y, w, h };
		SDL_RenderCopy(m_renderer, (*i)->getTitle(), NULL, &rect);
	}
	SDL_RenderPresent(m_renderer);
}

void PlayState::input() {
	SDL_Event e;
	while(SDL_PollEvent(&e)) {
		if(e.type == SDL_QUIT) {
			m_quit = true;
		}
		else if(e.type == SDL_MOUSEBUTTONDOWN) {
			SDL_GetMouseState(&m_mouseX, &m_mouseY);	
		}
	}
}

StateReturnValue PlayState::update() {
	if(m_quit) {
		return RETURN_QUIT;
	}
	else if(m_order == "Menu") {
		return RETURN_MENU;
	}
	else if(m_order == "") {
		return RETURN_NOTHING;
	}
	else if(m_order != "") {
		std::vector<LevelInfo*>::iterator i;
		for(i = m_levels.begin(); i != m_levels.end(); i++) {
			if((*i)->getPath() == m_order) {
				m_playing = true;
				m_currentLevel = new PlayLevel(m_renderer, (*i)->getPath(), m_player);
				m_currentLevel->m_background = m_background;
				if(m_currentLevel == nullptr) {
					std::cerr << "Couldn't allocate new memory on the heap." << std::endl;
				}
				break;
			}
		}
	}
	if(m_playing) {
		// We created a new PlayLevel object, ready to use !
		// We take its return code in order to treat it properly depending on what happened
		StateReturnValue result = m_currentLevel->run();
		m_playing = false;
		delete m_currentLevel;
		if(result == RETURN_DEAD) {
			Mix_Chunk *tmp = Mix_LoadWAV("data/music/gameDead.wav");
			Mix_PlayChannel(-1, tmp, 0);
			DeadScreen ds(m_renderer);
			m_player->setLife(3);
		}
		else if(result == RETURN_WIN) {
			WinScreen ws(m_renderer);
			Mix_Chunk *tmp = Mix_LoadWAV("data/music/gameWin.wav");
			Mix_PlayChannel(-1, tmp, 0);
			ws.show();
			SDL_Delay(3000);

		}
		else if(result != RETURN_BACK && result != RETURN_PLAY) {
			return result;
		}
		Mix_PlayMusic(m_music, -1);
	}
	m_order = "";
	return RETURN_NOTHING;
}


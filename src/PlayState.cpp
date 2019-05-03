#include <PlayState.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <PlayLevel.h>
#include <Player.h>
#include <LevelInfo.h>
#include <experimental/filesystem>
#include <StateReturnValue.h>
#include <DeadScreen.h>
#include <WinScreen.h>

PlayState::PlayState(SDL_Window *window, Player *player) : GameState(window) {
	m_player = player;
	m_quit = false;
	m_playing = false;
	m_currentLevel = nullptr;
	m_order = "";
	m_mouseX = -1;
	m_mouseY = -1;
	m_background = IMG_LoadTexture(m_renderer, "data/img/lacity.png");
	if(m_background == NULL) {
		std::cerr << "Could not load image lacity.png" << std::endl;
		std::cerr << IMG_GetError() << std::endl;
	}
	m_menuButton = new Button(m_renderer, "Go back");
	for(auto& fileName: std::experimental::filesystem::directory_iterator("data/map")) {
		LevelInfo *levelInfo = new LevelInfo(m_renderer, fileName.path());
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

//	SDL_RenderCopy(m_renderer, m_background, NULL, NULL);
	int width, height, count;
	SDL_GetRendererOutputSize(m_renderer, &width, &height);
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
					std::cerr << "Something weird is happening" << std::endl;
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
			DeadScreen ds(m_renderer);
			m_player->setLife(3);
		}
		else if(result == RETURN_WIN) {
			WinScreen ws(m_renderer);
			ws.show();
			SDL_Delay(3000);

		}
		else if(result != RETURN_BACK && result != RETURN_PLAY) {
			return result;
		}
	}
	m_order = "";
	return RETURN_NOTHING;
}


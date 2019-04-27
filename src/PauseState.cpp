#include <PauseState.h>
#include <SDL2/SDL.h>
#include <StateReturnValue.h>
#include <Button.h>
#include <string>
#include <vector>

PauseState::PauseState(SDL_Renderer *renderer) {
	m_renderer = renderer;
	m_returnValue = RETURN_NOTHING;
	m_buttonPressedText = "";
	m_mouseX = -1;
	m_mouseY = -1;
	Button *b = new Button(m_renderer, "Resume");
	m_buttons.push_back(b);
	b = new Button(m_renderer, "Change Level");
	m_buttons.push_back(b);
	b = new Button(m_renderer, "Back To Menu");
	m_buttons.push_back(b);
	b = new Button(m_renderer, "Quit");
	m_buttons.push_back(b);
}

PauseState::~PauseState() {
	std::vector<Button *>::iterator i;
	for(i = m_buttons.begin(); i != m_buttons.end(); i++) {
		delete *i;
	}
}

void PauseState::render() {
	SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
	SDL_RenderClear(m_renderer);
	int width;
	int height;
	int count;
	int x, y, w, h;
	SDL_Rect rectangle;
	SDL_GetRendererOutputSize(m_renderer, &width, &height);
	std::vector<Button *>::iterator i;
	for(i = m_buttons.begin(), count = 0; i != m_buttons.end(); i++, count++) {
		x = width/3;
		y = (count + 3) * height / 7 + 10;
		w = width/3;
		h = height / 7 - 20;
		if(m_mouseX > x && m_mouseX < x + w && m_mouseY > y && m_mouseY < y+h) {
			m_buttonPressedText = (*i)->getMessage();	
		}
		rectangle = { x, y, w, h };
		SDL_RenderCopy(m_renderer, (*i)->getTexture(), NULL, &rectangle);
	}
	SDL_RenderPresent(m_renderer);
}

StateReturnValue PauseState::update() {
	if(m_buttonPressedText == "Resume") {
		m_mouseX = -1;
		m_mouseY = -1;
		m_buttonPressedText = "";
		return RETURN_BACK;
	}
	else if(m_buttonPressedText == "Change Level") {
		m_mouseX = -1;
		m_mouseY = -1;
		m_buttonPressedText = "";
		return RETURN_PLAY;
	}
	else if(m_buttonPressedText ==  "Back To Menu") {
		m_mouseX = -1;
		m_mouseY = -1;
		m_buttonPressedText = "";
		return RETURN_MENU;
	}
	else if(m_buttonPressedText == "Quit") {
		m_mouseX = -1;
		m_mouseY = -1;
		m_buttonPressedText = "";
		return RETURN_QUIT;
	}
	else {
		return m_returnValue;		
	}
}

void PauseState::handleInput() {
	SDL_Event e;
	while(SDL_PollEvent(&e) > 0) {
		if(e.type == SDL_QUIT) {
			m_returnValue = RETURN_QUIT;
			break;
		}
		if(e.type == SDL_MOUSEBUTTONDOWN) {
			SDL_GetMouseState(&m_mouseX, &m_mouseY);
		}
	}
}

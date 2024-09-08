#include <__MiniNebula/App.h>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <chrono>
#include <thread>

bool App::init(int argc, char *argv[]) {
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
        SDL_Log("Failed to initialize SDL -> %s",  SDL_GetError());
        return false;
    }

    if (!IMG_Init(IMG_INIT_PNG )) {
        SDL_Log("Failed to initialize SDL_image -> %s", SDL_GetError());
        return false;
    }

    if (!Mix_Init(MIX_INIT_OGG | MIX_INIT_MP3)) {
        SDL_Log("Failed to initialize SDL_mixer -> %s", SDL_GetError());
        return false;
    }
    SDL_AudioDeviceID deviceId = SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK;

    auto *spec = new SDL_AudioSpec();
    spec->channels = 2;
    spec->freq = 44100;
    spec->format = SDL_AUDIO_S16LE;
    if (!Mix_OpenAudio(deviceId, spec)) {
        SDL_Log("Failed to open audio -> %s", SDL_GetError());
        return false;
    }


    // Set Window Properties
    SDL_PropertiesID props = SDL_CreateProperties();
    SDL_SetStringProperty(props, SDL_PROP_WINDOW_CREATE_TITLE_STRING, title.c_str());
    SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_WIDTH_NUMBER, _window_size.x);
    SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_HEIGHT_NUMBER, _window_size.y);
//    SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_BORDERLESS_BOOLEAN, true); // Borderless
    SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_HIGH_PIXEL_DENSITY_BOOLEAN, true); // HDPI
    // Init Window
    window = SDL_CreateWindowWithProperties(props);
    SDL_DestroyProperties(props);
    // Init Renderer
    renderer = SDL_CreateRenderer(window, nullptr);
    if (!renderer)
    {
        SDL_Log("Error creating SDL_Renderer -> %s", SDL_GetError());
        return -1;
    }
    // Set Viewport Scale
    SDL_SetRenderScale(renderer, _window_scale.x, _window_scale.y); // SDL_SetRenderScale(renderer, 3.0f, 3.0f);

    // Init Resource Manager
    rm_i = ResourceManager::getInstance();
    rm_i->init(renderer);
    rm_i->load();

    // Init Map Manager
    mp_i = MapManager::getInstance();
    mp_i->load();


    // Init Music

    _running = SDL_TRUE;
    return true;
}

bool App::run() {
    while (_running) {
        // Event
        _event();
        // Update
        _update();
        // Clear Renderer
        SDL_RenderClear(renderer);
        // Render
        _render();
        // Present Renderer
        SDL_RenderPresent(renderer);
        // Calculate Frame Duration
        FrameDurationCalc();
    }
    return true;
}

void App::_render() {
//    SDL_SetRenderDrawColor( renderer, 55, 148, 110, 255 );
    cm_i->debugRender(renderer);
    SDL_SetRenderDrawColor( renderer, 16, 0, 16, 255 );
    for (auto& tile : mp_i->getMap(0)->Layer4) {
        tile.render(renderer);
    }
    for (auto& tile : mp_i->getMap(0)->Layer3) {
        tile.render(renderer);
    }
    for (auto& tile : mp_i->getMap(0)->Layer2) {
        tile.render(renderer);
    }
    for (auto& tile : mp_i->getMap(0)->Layer1) {
        tile.render(renderer);
    }
    for (auto& tile : mp_i->getMap(0)->Layer0) {
        tile.render(renderer);
    }
}

void App::_update() {

    SDL_UpdateWindowSurface(window);
}

void App::_event() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            _running = false;
        }
        if (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_SPACE) {
            Mix_PlayMusic( rm_i->getMusic("mfx.theme"), 1 );
            Mix_VolumeMusic(10);
        }
        if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN && event.button.button == SDL_BUTTON_LEFT) {
            Vec2<float> mouse_pos = {event.button.x, event.button.y};
            mp_i->getML_instance()->at(0).Layer0.push_back(MapTile({static_cast<int>(mouse_pos.x / _window_scale.x), static_cast<int>(mouse_pos.y / _window_scale.y)}, rm_i->getAtlasTexture("gfx.alligator.forklift.empty"), {Sprite::Type::Atlas, 4}));
        }
        if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN && event.button.button == SDL_BUTTON_RIGHT) {
            Vec2<float> mouse_pos = {event.button.x, event.button.y};
            mp_i->getML_instance()->at(0).Layer0.push_back(MapTile({static_cast<int>(mouse_pos.x / _window_scale.x), static_cast<int>(mouse_pos.y / _window_scale.y)}, rm_i->getAtlasTexture("gfx.alligator.forklift.full"), {Sprite::Type::Atlas, 4}));
        }
    }
}

bool App::quit() {
    rm_i->freeAllMusic();
    Mix_CloseAudio();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
    return true;
}

SDL_Texture* App::_load_texture(const char* path) {
    SDL_Surface* surface = IMG_Load(path);
    if (!surface) {
        SDL_Log("Failed to load texture -> %s", SDL_GetError());
        return nullptr;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        SDL_Log("Failed to create texture -> %s", SDL_GetError());
        SDL_DestroySurface(surface);
        return nullptr;
    }
    SDL_DestroySurface(surface);
    return texture;
}

void App::FrameDurationCalc() {
    // ManageFrameRate
    auto TimeStampA = std::chrono::system_clock::now();
    std::chrono::duration<double, std::milli> work_time = TimeStampA - TimeStampB;

    if (work_time.count() < dt) {
        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<long long>(dt - work_time.count())));
    }

    TimeStampB = std::chrono::system_clock::now();
}

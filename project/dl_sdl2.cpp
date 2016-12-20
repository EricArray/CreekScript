#include <creek/creek.hpp>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

struct SDLException : public creek::Exception {
    SDLException() : Exception(SDL_GetError()) { }
};

int wrap_SDL_SetError(const char* m) {
    return SDL_SetError(m);
}

// Basics
CREEK_FUNC(init,            &SDL_Init);
CREEK_FUNC(quit,            &SDL_Quit);
CREEK_FUNC(get_error,       &SDL_GetError);
CREEK_FUNC(set_error,       &wrap_SDL_SetError);
CREEK_FUNC(was_init,        &SDL_WasInit);
CREEK_FUNC(delay,           &SDL_Delay);

CREEK_VAR(INIT_EVERYTHING,  SDL_INIT_EVERYTHING);

// image
CREEK_FUNC(img_init,        &IMG_Init);
CREEK_FUNC(img_quit,        &IMG_Quit);

CREEK_VAR(INIT_JPG,         IMG_INIT_JPG);
CREEK_VAR(INIT_PNG,         IMG_INIT_PNG);
CREEK_VAR(INIT_TIF,         IMG_INIT_TIF);
CREEK_VAR(INIT_WEBP,        IMG_INIT_WEBP);


// - Point
SDL_Point wrap_SDL_Point_new(int x, int y) { return { x, y }; }
int wrap_SDL_Point_x(SDL_Point& r) { return r.x; }
int wrap_SDL_Point_y(SDL_Point& r) { return r.y; }
int wrap_SDL_Point_set_x(SDL_Point& r, int x) { return r.x = x; }
int wrap_SDL_Point_set_y(SDL_Point& r, int y) { return r.y = y; }
CREEK_CLASS(Point, SDL_Point) (
    CREEK_ATTR(x,         &SDL_Point::x),
    CREEK_ATTR(y,         &SDL_Point::y),
    CREEK_METHOD(new,     &wrap_SDL_Point_new),
    CREEK_METHOD(x,       &wrap_SDL_Point_x),
    CREEK_METHOD(y,       &wrap_SDL_Point_y),
    CREEK_METHOD(set_x,   &wrap_SDL_Point_set_x),
    CREEK_METHOD(set_y,   &wrap_SDL_Point_set_y)
);

// - Rect
SDL_Rect wrap_SDL_Rect_new(int x, int y, int w, int h) { return { x, y, w, h }; }
int wrap_SDL_Rect_x(SDL_Rect& r) { return r.x; }
int wrap_SDL_Rect_y(SDL_Rect& r) { return r.y; }
int wrap_SDL_Rect_w(SDL_Rect& r) { return r.w; }
int wrap_SDL_Rect_h(SDL_Rect& r) { return r.h; }
int wrap_SDL_Rect_set_x(SDL_Rect& r, int x) { return r.x = x; }
int wrap_SDL_Rect_set_y(SDL_Rect& r, int y) { return r.y = y; }
int wrap_SDL_Rect_set_w(SDL_Rect& r, int w) { return r.w = w; }
int wrap_SDL_Rect_set_h(SDL_Rect& r, int h) { return r.h = h; }
CREEK_CLASS(Rect, SDL_Rect) (
    CREEK_ATTR(x,         &SDL_Rect::x),
    CREEK_ATTR(y,         &SDL_Rect::y),
    CREEK_METHOD(new,     &wrap_SDL_Rect_new),
    CREEK_METHOD(x,       &wrap_SDL_Rect_x),
    CREEK_METHOD(y,       &wrap_SDL_Rect_y),
    CREEK_METHOD(w,       &wrap_SDL_Rect_w),
    CREEK_METHOD(h,       &wrap_SDL_Rect_h),
    CREEK_METHOD(set_x,   &wrap_SDL_Rect_set_x),
    CREEK_METHOD(set_y,   &wrap_SDL_Rect_set_y),
    CREEK_METHOD(set_w,   &wrap_SDL_Rect_set_w),
    CREEK_METHOD(set_h,   &wrap_SDL_Rect_set_h)
);


// Event
// - MouseButton
struct wrap_MouseButton { };
CREEK_CLASS(MouseButton, wrap_MouseButton) (
    CREEK_STATIC(LEFT,    SDL_BUTTON_LEFT),
    CREEK_STATIC(MIDDLE,  SDL_BUTTON_MIDDLE),
    CREEK_STATIC(RIGHT,   SDL_BUTTON_RIGHT),
    CREEK_STATIC(X1,      SDL_BUTTON_X1),
    CREEK_STATIC(X2,      SDL_BUTTON_X2)
);
// - MouseButtonEvent
CREEK_CLASS(MouseButtonEvent, SDL_MouseButtonEvent) (
    CREEK_ATTR(type,      &SDL_MouseButtonEvent::type),
    CREEK_ATTR(timestamp, &SDL_MouseButtonEvent::timestamp),
    CREEK_ATTR(window_id, &SDL_MouseButtonEvent::windowID),
    CREEK_ATTR(which,     &SDL_MouseButtonEvent::which),
    CREEK_ATTR(button,    &SDL_MouseButtonEvent::button),
    CREEK_ATTR(state,     &SDL_MouseButtonEvent::state),
    CREEK_ATTR(clicks,    &SDL_MouseButtonEvent::clicks),
    CREEK_ATTR(x,         &SDL_MouseButtonEvent::x),
    CREEK_ATTR(y,         &SDL_MouseButtonEvent::y)
);
// - MouseMotionEvent
CREEK_CLASS(MouseMotionEvent, SDL_MouseMotionEvent) (
    CREEK_ATTR(type,      &SDL_MouseMotionEvent::type),
    CREEK_ATTR(timestamp, &SDL_MouseMotionEvent::timestamp),
    CREEK_ATTR(window_id, &SDL_MouseMotionEvent::windowID),
    CREEK_ATTR(which,     &SDL_MouseMotionEvent::which),
    CREEK_ATTR(state,     &SDL_MouseMotionEvent::state),
    CREEK_ATTR(x,         &SDL_MouseMotionEvent::x),
    CREEK_ATTR(y,         &SDL_MouseMotionEvent::y),
    CREEK_ATTR(xrel,      &SDL_MouseMotionEvent::xrel),
    CREEK_ATTR(yrel,      &SDL_MouseMotionEvent::yrel)
);
// - Keymod
struct wrap_Keymod { };
CREEK_CLASS(Keymod, wrap_Keymod) (
    CREEK_STATIC(NONE,    KMOD_NONE),
    CREEK_STATIC(LSHIFT,  KMOD_LSHIFT),
    CREEK_STATIC(RSHIFT,  KMOD_RSHIFT),
    CREEK_STATIC(LCTRL,   KMOD_LCTRL),
    CREEK_STATIC(RCTRL,   KMOD_RCTRL),
    CREEK_STATIC(LALT,    KMOD_LALT),
    CREEK_STATIC(RALT,    KMOD_RALT),
    CREEK_STATIC(LGUI,    KMOD_LGUI),
    CREEK_STATIC(RGUI,    KMOD_RGUI),
    CREEK_STATIC(NUM,     KMOD_NUM),
    CREEK_STATIC(CAPS,    KMOD_CAPS),
    CREEK_STATIC(MODE,    KMOD_MODE),
    CREEK_STATIC(CTRL,    KMOD_CTRL),
    CREEK_STATIC(SHIFT,   KMOD_SHIFT),
    CREEK_STATIC(ALT,     KMOD_ALT),
    CREEK_STATIC(GUI,     KMOD_GUI)
);
// - Scancode
struct wrap_Scancode { };
CREEK_CLASS(Scancode, wrap_Scancode) (
    CREEK_METHOD(from_name,   &SDL_GetScancodeFromName)
);
// - Keysym
CREEK_CLASS(Keysym, SDL_Keysym) (
    CREEK_ATTR(scancode,  &SDL_Keysym::scancode),
    CREEK_ATTR(sym,       &SDL_Keysym::sym),
    CREEK_ATTR(mod,       &SDL_Keysym::mod)
);
// - KeyboardEvent
CREEK_CLASS(KeyboardEvent, SDL_KeyboardEvent) (
    CREEK_ATTR(type,      &SDL_KeyboardEvent::type),
    CREEK_ATTR(timestamp, &SDL_KeyboardEvent::timestamp),
    CREEK_ATTR(window_id, &SDL_KeyboardEvent::windowID),
    CREEK_ATTR(state,     &SDL_KeyboardEvent::state),
    CREEK_ATTR(repeat,    &SDL_KeyboardEvent::repeat),
    CREEK_ATTR(keysym,    &SDL_KeyboardEvent::keysym)
);
// - QuitEvent
CREEK_CLASS(QuitEvent, SDL_QuitEvent) (
    CREEK_ATTR(type,      &SDL_QuitEvent::type),
    CREEK_ATTR(timestamp, &SDL_QuitEvent::timestamp)
);
// - WindowEvent
CREEK_CLASS(WindowEvent, SDL_WindowEvent) (
    CREEK_ATTR(type,      &SDL_WindowEvent::type),
    CREEK_ATTR(timestamp, &SDL_WindowEvent::timestamp),
    CREEK_ATTR(window_id, &SDL_WindowEvent::windowID),
    CREEK_ATTR(event,     &SDL_WindowEvent::event),
    CREEK_ATTR(data1,     &SDL_WindowEvent::data1),
    CREEK_ATTR(data2,     &SDL_WindowEvent::data2)
);
// - Event
SDL_Event wrap_SDL_Event_new() {
    return SDL_Event();
}
CREEK_CLASS(Event,  SDL_Event) (
    CREEK_ATTR(type,      &SDL_Event::type),
    CREEK_ATTR(button,    &SDL_Event::button),
    CREEK_ATTR(motion,    &SDL_Event::motion),
    CREEK_ATTR(key,       &SDL_Event::key),
    CREEK_ATTR(quit,      &SDL_Event::quit),
    CREEK_ATTR(window,    &SDL_Event::window),
    CREEK_METHOD(new, &wrap_SDL_Event_new),
    CREEK_STATIC(AUDIODEVICEADDED,          SDL_AUDIODEVICEADDED),
    CREEK_STATIC(AUDIODEVICEREMOVED,        SDL_AUDIODEVICEREMOVED),
    CREEK_STATIC(CONTROLLERAXISMOTION,      SDL_CONTROLLERAXISMOTION),
    CREEK_STATIC(CONTROLLERBUTTONDOWN,      SDL_CONTROLLERBUTTONDOWN),
    CREEK_STATIC(CONTROLLERBUTTONUP,        SDL_CONTROLLERBUTTONUP),
    CREEK_STATIC(CONTROLLERDEVICEADDED,     SDL_CONTROLLERDEVICEADDED),
    CREEK_STATIC(CONTROLLERDEVICEREMOVED,   SDL_CONTROLLERDEVICEREMOVED),
    CREEK_STATIC(CONTROLLERDEVICEREMAPPED,  SDL_CONTROLLERDEVICEREMAPPED),
    CREEK_STATIC(DOLLARGESTURE,             SDL_DOLLARGESTURE),
    CREEK_STATIC(DOLLARRECORD,              SDL_DOLLARRECORD),
    CREEK_STATIC(DROPFILE,                  SDL_DROPFILE),
    CREEK_STATIC(FINGERMOTION,              SDL_FINGERMOTION),
    CREEK_STATIC(FINGERDOWN,                SDL_FINGERDOWN),
    CREEK_STATIC(FINGERUP,                  SDL_FINGERUP),
    CREEK_STATIC(KEYDOWN,                   SDL_KEYDOWN),
    CREEK_STATIC(KEYUP,                     SDL_KEYUP),
    CREEK_STATIC(JOYAXISMOTION,             SDL_JOYAXISMOTION),
    CREEK_STATIC(JOYBALLMOTION,             SDL_JOYBALLMOTION),
    CREEK_STATIC(JOYHATMOTION,              SDL_JOYHATMOTION),
    CREEK_STATIC(JOYBUTTONDOWN,             SDL_JOYBUTTONDOWN),
    CREEK_STATIC(JOYBUTTONUP,               SDL_JOYBUTTONUP),
    CREEK_STATIC(JOYDEVICEADDED,            SDL_JOYDEVICEADDED),
    CREEK_STATIC(JOYDEVICEREMOVED,          SDL_JOYDEVICEREMOVED),
    CREEK_STATIC(MOUSEMOTION,               SDL_MOUSEMOTION),
    CREEK_STATIC(MOUSEBUTTONDOWN,           SDL_MOUSEBUTTONDOWN),
    CREEK_STATIC(MOUSEBUTTONUP,             SDL_MOUSEBUTTONUP),
    CREEK_STATIC(MOUSEWHEEL,                SDL_MOUSEWHEEL),
    CREEK_STATIC(MULTIGESTURE,              SDL_MULTIGESTURE),
    CREEK_STATIC(QUIT,                      SDL_QUIT),
    CREEK_STATIC(SYSWMEVENT,                SDL_SYSWMEVENT),
    CREEK_STATIC(TEXTEDITING,               SDL_TEXTEDITING),
    CREEK_STATIC(TEXTINPUT,                 SDL_TEXTINPUT),
    CREEK_STATIC(USEREVENT,                 SDL_USEREVENT),
    CREEK_STATIC(WINDOWEVENT,               SDL_WINDOWEVENT)
);
CREEK_FUNC(poll_event,      &SDL_PollEvent);


// Video
CREEK_CLASS_HEADER(Window);
CREEK_CLASS_HEADER(Renderer);
CREEK_CLASS_HEADER(Surface);
CREEK_CLASS_HEADER(Texture);

CREEK_FUNC(show_simple_message_box, &SDL_ShowSimpleMessageBox);

// - Color
SDL_Color wrap_SDL_Color_new(Uint8 r, Uint8 g, Uint8 b, Uint8 a) { return {r, g, b, a}; }
CREEK_CLASS(Color, SDL_Color) (
    CREEK_ATTR(r,  &SDL_Color::r),
    CREEK_ATTR(g,  &SDL_Color::g),
    CREEK_ATTR(b,  &SDL_Color::b),
    CREEK_ATTR(a,  &SDL_Color::a),
    CREEK_METHOD(new, &wrap_SDL_Color_new)
);

// - Palette
CREEK_CLASS(Palette, SDL_Palette) (

);

// - BlendMode
struct wrap_SDL_BlendMode { };
CREEK_CLASS(BlendMode, wrap_SDL_BlendMode) (
    CREEK_STATIC(NONE,   SDL_BLENDMODE_NONE),
    CREEK_STATIC(BLEND,  SDL_BLENDMODE_BLEND),
    CREEK_STATIC(ADD,    SDL_BLENDMODE_ADD),
    CREEK_STATIC(MOD,    SDL_BLENDMODE_MOD)
);

// - PixelFormat
Uint32 wrap_SDL_MapRGBA(const SDL_PixelFormat* f, const SDL_Color& c) { return SDL_MapRGBA(f, c.r, c.g, c.b, c.a); }
SDL_Color wrap_SDL_GetRGB(const SDL_PixelFormat* f, Uint32 pixel) { SDL_Color c; SDL_GetRGB(pixel, f, &c.r, &c.g, &c.b); return c; }
SDL_Color wrap_SDL_GetRGBA(const SDL_PixelFormat* f, Uint32 pixel) { SDL_Color c; SDL_GetRGBA(pixel, f, &c.r, &c.g, &c.b, &c.a); return c; }
CREEK_CLASS(PixelFormat, SDL_PixelFormat) (
    CREEK_ATTR(format,            &SDL_PixelFormat::format),
    CREEK_ATTR(palette,           &SDL_PixelFormat::palette),
    CREEK_ATTR(bits_per_pixel,    &SDL_PixelFormat::BitsPerPixel),
    CREEK_ATTR(bytes_per_pixel,   &SDL_PixelFormat::BytesPerPixel),
    CREEK_ATTR(r_mask,            &SDL_PixelFormat::Rmask),
    CREEK_ATTR(g_mask,            &SDL_PixelFormat::Gmask),
    CREEK_ATTR(b_mask,            &SDL_PixelFormat::Bmask),
    CREEK_ATTR(a_mask,            &SDL_PixelFormat::Amask),
    CREEK_METHOD(map_color,   &wrap_SDL_MapRGBA),
    CREEK_METHOD(map_rgb,     &SDL_MapRGB),
    CREEK_METHOD(map_rgba,    &SDL_MapRGBA),
    CREEK_METHOD(get_rgb,     &wrap_SDL_GetRGB),
    CREEK_METHOD(get_rgba,    &wrap_SDL_GetRGBA)
);

// - Window
SDL_Point wrap_SDL_GetWindowPosition(SDL_Window* w) {
    SDL_Point p;
    SDL_GetWindowPosition(w, &p.x, &p.y);
    return p;
}
SDL_Point wrap_SDL_GetWindowSize(SDL_Window* w) {
    SDL_Point p;
    SDL_GetWindowSize(w, &p.x, &p.y);
    return p;
}
CREEK_CLASS_IMPL(Window, SDL_Window) (
    CREEK_METHOD(flags,           &SDL_GetWindowFlags),
    CREEK_METHOD(position,        &wrap_SDL_GetWindowPosition),
    CREEK_METHOD(size,            &wrap_SDL_GetWindowSize),
    CREEK_METHOD(surface,         &SDL_GetWindowSurface),
    CREEK_METHOD(title,           &SDL_GetWindowTitle),
    CREEK_METHOD(hide,            &SDL_HideWindow),
    CREEK_METHOD(maximize,        &SDL_MaximizeWindow),
    CREEK_METHOD(minimize,        &SDL_MinimizeWindow),
    CREEK_METHOD(raise,           &SDL_RaiseWindow),
    CREEK_METHOD(restore,         &SDL_RestoreWindow),
    CREEK_METHOD(set_position,    &SDL_SetWindowPosition),
    CREEK_METHOD(set_size,        &SDL_SetWindowSize),
    CREEK_METHOD(set_title,       &SDL_SetWindowTitle),
    CREEK_METHOD(show,            &SDL_ShowWindow),
    CREEK_METHOD(update_surface,  &SDL_UpdateWindowSurface),
    CREEK_STATIC(FULLSCREEN,         SDL_WINDOW_FULLSCREEN),
    CREEK_STATIC(FULLSCREEN_DESKTOP, SDL_WINDOW_FULLSCREEN_DESKTOP),
    CREEK_STATIC(OPENGL,             SDL_WINDOW_OPENGL),
    CREEK_STATIC(HIDDEN,             SDL_WINDOW_HIDDEN),
    CREEK_STATIC(BORDERLESS,         SDL_WINDOW_BORDERLESS),
    CREEK_STATIC(RESIZABLE,          SDL_WINDOW_RESIZABLE),
    CREEK_STATIC(MINIMIZED,          SDL_WINDOW_MINIMIZED),
    CREEK_STATIC(MAXIMIZED,          SDL_WINDOW_MAXIMIZED),
    CREEK_STATIC(INPUT_GRABBED,      SDL_WINDOW_INPUT_GRABBED),
    CREEK_STATIC(ALLOW_HIGHDPI,      SDL_WINDOW_ALLOW_HIGHDPI)
);
CREEK_FUNC(create_window,   &SDL_CreateWindow);
CREEK_FUNC(destroy_window,  &SDL_DestroyWindow);

// - Surface
SDL_Rect wrap_SDL_GetClipRect(SDL_Surface* s) { SDL_Rect r; SDL_GetClipRect(s, &r); return r; }
Uint32 wrap_SDL_GetColorKey(SDL_Surface* s) {
    Uint32 k;
    if (SDL_GetColorKey(s, &k) < 0) throw SDLException();
    return k;
}
Uint8 wrap_SDL_GetSurfaceAlphaMod(SDL_Surface* s) {
    Uint8 a;
    if (SDL_GetSurfaceAlphaMod(s, &a) < 0) throw SDLException();
    return a;
}
Uint8 wrap_SDL_GetSurfaceBlendMode(SDL_Surface* s) {
    SDL_BlendMode b;
    if (SDL_GetSurfaceBlendMode(s, &b) < 0) throw SDLException();
    return b;
}
SDL_Color wrap_SDL_GetSurfaceColorMod(SDL_Surface* s) {
    SDL_Color c;
    if (SDL_GetSurfaceColorMod(s, &c.r, &c.g, &c.b) < 0) throw SDLException();
    return c;
}
void wrap_SDL_SetSurfaceColorMod(SDL_Surface* s, const SDL_Color& c) {
    if (SDL_SetSurfaceColorMod(s, c.r, c.g, c.b) < 0) throw SDLException();
}
SDL_Surface* wrap_SDL_CreateRGBSurface(Uint32 flags, int w, int h, const SDL_PixelFormat* f) {
    auto s = SDL_CreateRGBSurface(flags, w, h, f->BitsPerPixel,
        f->Rmask, f->Gmask, f->Bmask, f->Amask);
    if (!s) throw SDLException();
    return s;
}
SDL_PixelFormat* wrap_SDL_Surface_format(SDL_Surface* s) {
    return s->format;
}
SDL_Surface* wrap_SDL_ConvertSurface(SDL_Surface* s, const SDL_PixelFormat* f) { return SDL_ConvertSurface(s, f, 0); }
CREEK_CLASS_IMPL(Surface, SDL_Surface) (
    CREEK_METHOD(blit_scaled,     &SDL_BlitScaled),
    CREEK_METHOD(blit_surface,    &SDL_BlitSurface),
    CREEK_METHOD(clip_rect,       &wrap_SDL_GetClipRect),
    CREEK_METHOD(color_key,       &wrap_SDL_GetColorKey),
    CREEK_METHOD(alpha_mod,       &wrap_SDL_GetSurfaceAlphaMod),
    CREEK_METHOD(blend_mode,      &wrap_SDL_GetSurfaceBlendMode),
    CREEK_METHOD(color_mod,       &wrap_SDL_GetSurfaceColorMod),
    CREEK_METHOD(load,            &IMG_Load),
    CREEK_METHOD(save,            &IMG_SavePNG),
    CREEK_METHOD(set_clip_rect,   &SDL_SetClipRect),
    CREEK_METHOD(set_color_key,   &SDL_SetColorKey),
    CREEK_METHOD(set_alpha_mod,   &SDL_SetSurfaceAlphaMod),
    CREEK_METHOD(set_blend_mode,  &SDL_SetSurfaceBlendMode),
    CREEK_METHOD(set_color_mod,   &wrap_SDL_SetSurfaceColorMod),
    CREEK_METHOD(fill_rect,       &SDL_FillRect),
    CREEK_METHOD(format,          &wrap_SDL_Surface_format),
    CREEK_METHOD(convert,         &wrap_SDL_ConvertSurface)
);
CREEK_FUNC(free_surface,    &SDL_FreeSurface);

// - Texture
SDL_BlendMode wrap_SDL_GetTextureBlendMode(SDL_Texture* texture) {
    SDL_BlendMode bm = SDL_BLENDMODE_NONE;
    if (SDL_GetTextureBlendMode(texture, &bm) < 0) throw SDLException();
    return bm;
}
SDL_Color wrap_SDL_GetTextureColorMod(SDL_Texture* texture) {
    SDL_Color c = {0, 0, 0, 0};
    if (SDL_GetTextureColorMod(texture, &c.r, &c.g, &c.b) < 0) throw SDLException();
    if (SDL_GetTextureAlphaMod(texture, &c.a) < 0) throw SDLException();
    return c;
}
void wrap_SDL_SetTextureBlendMode(SDL_Texture* texture, SDL_BlendMode bm) {
    if (SDL_SetTextureBlendMode(texture, bm) < 0) throw SDLException();
}
void wrap_SDL_SetTextureColorMod(SDL_Texture* texture, const SDL_Color& c) {
    if (SDL_SetTextureColorMod(texture, c.r, c.g, c.b) < 0) throw SDLException();
    if (SDL_SetTextureAlphaMod(texture, c.a) < 0) throw SDLException();
}
Uint32 wrap_SDL_QueryTexture_format(SDL_Texture* texture) {
    Uint32 format = 0;
    if (SDL_QueryTexture(texture, &format, nullptr, nullptr, nullptr) < 0) throw SDLException();
    return format;
}
int wrap_SDL_QueryTexture_access(SDL_Texture* texture) {
    int access = 0;
    if (SDL_QueryTexture(texture, nullptr, &access, nullptr, nullptr) < 0) throw SDLException();
    return access;
}
SDL_Point wrap_SDL_QueryTexture_size(SDL_Texture* texture) {
    SDL_Point size = {0, 0};
    if (SDL_QueryTexture(texture, nullptr, nullptr, &size.x, &size.y) < 0) throw SDLException();
    return size;
}
CREEK_CLASS(Texture, SDL_Texture) (
    CREEK_METHOD(blend_mode,      &wrap_SDL_GetTextureBlendMode),
    CREEK_METHOD(color_mod,       &wrap_SDL_GetTextureColorMod),
    CREEK_METHOD(set_blend_mode,  &wrap_SDL_SetTextureBlendMode),
    CREEK_METHOD(set_color_mod,   &wrap_SDL_SetTextureColorMod),
    CREEK_METHOD(format,          &wrap_SDL_QueryTexture_format),
    CREEK_METHOD(access,          &wrap_SDL_QueryTexture_access),
    CREEK_METHOD(size,            &wrap_SDL_QueryTexture_size)
);
CREEK_FUNC(destroy_texture,     &SDL_DestroyTexture);

// - Renderer
void wrap_SDL_SetRenderDrawColor(SDL_Renderer* renderer, const SDL_Color& c) {
    if (SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a) < 0) throw SDLException();
}
CREEK_CLASS(Renderer, SDL_Renderer) (
    CREEK_METHOD(clear,           &SDL_RenderClear),
    CREEK_METHOD(copy,            &SDL_RenderCopy),
    CREEK_METHOD(copy_ex,         &SDL_RenderCopyEx),
    CREEK_METHOD(draw_line,       &SDL_RenderDrawLine),
    CREEK_METHOD(draw_point,      &SDL_RenderDrawPoint),
    CREEK_METHOD(draw_rect,       &SDL_RenderDrawRect),
    CREEK_METHOD(fill_rect,       &SDL_RenderFillRect),
    CREEK_METHOD(set_draw_color,  &wrap_SDL_SetRenderDrawColor),
    CREEK_METHOD(set_draw_blend_mode, &SDL_SetRenderDrawBlendMode),
    CREEK_METHOD(present,         &SDL_RenderPresent),
    CREEK_METHOD(load_texture,    &IMG_LoadTexture),
    CREEK_STATIC(SOFTWARE,        SDL_RENDERER_SOFTWARE),
    CREEK_STATIC(ACCELERATED,     SDL_RENDERER_ACCELERATED),
    CREEK_STATIC(PRESENTVSYNC,    SDL_RENDERER_PRESENTVSYNC),
    CREEK_STATIC(TARGETTEXTURE,   SDL_RENDERER_TARGETTEXTURE),
    CREEK_STATIC(FLIP_NONE,       SDL_FLIP_NONE),
    CREEK_STATIC(FLIP_HORIZONTAL, SDL_FLIP_HORIZONTAL),
    CREEK_STATIC(FLIP_VERTICAL,   SDL_FLIP_VERTICAL)
);
CREEK_FUNC(create_renderer,     &SDL_CreateRenderer);
CREEK_FUNC(destroy_renderer,    &SDL_DestroyRenderer);

// // - MessageBox
// SDL_MessageBoxButtonData wrap_SDL_MessageBoxButtonData_new(Uint32 flags, int buttonid, const char* text) {
//     SDL_MessageBoxButtonData mbbd;
//     mbbd.flags = flags;
//     mbbd.buttonid = buttonid;
//     mbbd.text = text;
//     return mbbd;
// }
// CREEK_CLASS(MessageBoxButton, SDL_MessageBoxButtonData) {
//     CREEK_METHOD(new, &wrap_SDL_MessageBoxButtonData_new),
//     CREEK_ATTR(flags,     &SDL_MessageBoxButtonData::flags),
//     CREEK_ATTR(buttonid,  &SDL_MessageBoxButtonData::buttonid),
//     CREEK_ATTR(text,      &SDL_MessageBoxButtonData::text),
// };

// CREEK_CLASS(MessageBox, SDL_MessageBoxData) {

// };

#pragma once

// Setting macro name:
// BDE_<project>_<group>_<setting>
// e.g.: BDE_GLOBAL_DEBUG

// ----- Define build mode -----
#if defined(BUILD_DEBUG)
# define BDE_GLOBAL_BUILD_DEBUG
#elif defined(BUILD_RELEASE)
# define BDE_GLOBAL_BUILD_RELEASE
#elif defined(BUILD_DEMO)
# define BDE_GLOBAL_BUILD_DEMO
#endif


// ----- Setting  -----
// Global:
// - BDE_GLOBAL_ENABLE_EDITOR_FUNCTIONALITY  -> enable BL functionality that should be only availlable when there is editor.
// - BDE_GLOBAL_ENABLE_NICE_INIT             -> nicely initialize object members (useful for debug but should be omitted from demo)
// - BDE_GLOBAL_ENABLE_NICE_DESTROY          -> nicely release objects (the same)
// - BDE_GLOBAL_FRAME_LIMITER_FPS            -> sets frame limiter FPS (0 = disabled)
// 
// Assist:
// - BDE_ASSIST_DEFAULT_RANDOMIZER           -> default randomizer class to use
// 
// Audio:
// - BDE_AUDIO_DS_DEBUG                      -> enable DirectDound specific debugging
// 
// Render:
// - BDE_RENDER_DX_DEBUG                     -> enable DirectX specific debugging
// - BDE_RENDER_ENABLE_VSYNC                 -> enable vertical sync
// - BDE_RENDER_ENABLE_FULLSCREEN            -> enable fullscreen mode (should be enabled for demo only)

#if defined(BDE_GLOBAL_BUILD_DEBUG)
// ----- DEBUG settings -----
# define BDE_GLOBAL_ENABLE_EDITOR_FUNCTIONALITY  1
# define BDE_GLOBAL_ENABLE_NICE_INIT             1
# define BDE_GLOBAL_ENABLE_NICE_DESTROY          1
# define BDE_GLOBAL_FRAME_LIMITER_FPS            60
# define BDE_ASSIST_DEFAULT_RANDOMIZER           MTRandomizer
# define BDE_AUDIO_DS_DEBUG                      1
# define BDE_RENDER_DX_DEBUG                     1
# define BDE_RENDER_ENABLE_VSYNC                 0
# define BDE_RENDER_ENABLE_FULLSCREEN            0
# define BDE_RENDER_GET_ADAPTER_DATA             1

#elif defined(BDE_GLOBAL_BUILD_RELEASE)
// ----- RELEASE settings -----
# define BDE_GLOBAL_ENABLE_EDITOR_FUNCTIONALITY  1
# define BDE_GLOBAL_ENABLE_NICE_INIT             1
# define BDE_GLOBAL_ENABLE_NICE_DESTROY          1
# define BDE_GLOBAL_FRAME_LIMITER_FPS            60
# define BDE_ASSIST_DEFAULT_RANDOMIZER           MTRandomizer
# define BDE_AUDIO_DS_DEBUG                      0
# define BDE_RENDER_DX_DEBUG                     0
# define BDE_RENDER_ENABLE_VSYNC                 1
# define BDE_RENDER_ENABLE_FULLSCREEN            0
# define BDE_RENDER_GET_ADAPTER_DATA             0

#elif defined(BDE_GLOBAL_BUILD_DEMO)
// ----- DEMO settings -----
# define BDE_GLOBAL_ENABLE_EDITOR_FUNCTIONALITY  1
# define BDE_GLOBAL_ENABLE_NICE_INIT             0
# define BDE_GLOBAL_ENABLE_NICE_DESTROY          0
# define BDE_GLOBAL_FRAME_LIMITER_FPS            0
# define BDE_ASSIST_DEFAULT_RANDOMIZER           MTRandomizer
# define BDE_AUDIO_DS_DEBUG                      0
# define BDE_RENDER_DX_DEBUG                     0
# define BDE_RENDER_ENABLE_VSYNC                 0
# define BDE_RENDER_ENABLE_FULLSCREEN            0 
# define BDE_RENDER_GET_ADAPTER_DATA             0

#endif

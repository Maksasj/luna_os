require 'luna.libluna.ibm_bios_font'
require 'luna.libluna.c_pointer'

require 'luna.libluna.files'

local random = math.random

local function to_argb16(a, r, g, b)
    return ((a & 0xFFFF) << 15) | (r) | ((g & 0xFFFF) << 5) | ((b & 0xFFFF) << 10) & 0xFFFF
end

KEY_A = 0
KEY_B = 1
KEY_SELECT = 2
KEY_START = 3
KEY_RIGHT = 4
KEY_LEFT = 5
KEY_UP = 6
KEY_DOWN = 7
KEY_R = 8
KEY_L = 9
KEY_X = 10
KEY_Y = 11

libluna = {
    platform = {
        DSI = 0,
        DESKTOP = 1
    },
    gfx = {
        -- get_vram_pointer = get_vram_pointer,
        to_argb16 = to_argb16,

        colors = {
            WHITE = to_argb16(1, 31, 31, 31),
            BLACK = to_argb16(1, 0, 0, 0),
            RED = to_argb16(1, 31, 0, 0),
            GREEN = to_argb16(1, 0, 31, 0),
            BLUE = to_argb16(1, 0, 0, 31),
            YELLOW = to_argb16(1, 31, 31, 0),
            MAGENTA = to_argb16(1, 31, 0, 31),
            CYAN = to_argb16(1, 0, 31, 31)
        }
    },
    uuid = function()
        local template = "xxxxxxxx-xxxx-4xxx-yxxx-xxxxxxxxxxxx"
            return template:gsub("[xy]", function (c)
                local v = (c == 'x') and random(0, 0xf) or random(8, 0xb)
                return string.format('%x', v)
        end)
    end,
    types = {
        char      = { size = 1, mask = 0xFF },
        short     = { size = 2, mask = 0xFFFF },
        int       = { size = 4, mask = 0xFFFFFFFF },
        long_long = { size = 8, mask = 0xFFFFFFFFFFFFFFFF }
    },
    io = {
        keycodes = {
            KEY_A = KEY_A,
            KEY_B = KEY_B,
            KEY_SELECT = KEY_SELECT,
            KEY_START = KEY_START,
            KEY_RIGHT = KEY_RIGHT,
            KEY_LEFT = KEY_LEFT,
            KEY_UP = KEY_UP,
            KEY_DOWN = KEY_DOWN,
            KEY_R = KEY_R,
            KEY_L = KEY_L,
            KEY_X = KEY_X,
            KEY_Y = KEY_Y
        },
        opendir = _opendir,
        is_dir = _is_dir,
        is_file = _is_file,
        file_exist = _file_exist
    }
}

kernel.lua.require("packages/luna/ibm_bios_font.lua")
kernel.lua.require("packages/luna/c_pointer.lua")

local function get_vram_pointer()
    local pointer = kernel.gfx.get_raw_vram_pointer()
    return LibLunaPointer:new(pointer)
end

local function to_argb16(a, r, g, b)
    return ((a) << 15) | (r) | ((g) << 5) | ((b) << 10) & 0xFFFF
end

libluna = {
    gfx = {
        get_vram_pointer = get_vram_pointer,
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
    types = {
        char      = { size = 1, mask = 0xFF },
        short     = { size = 2, mask = 0xFFFF },
        int       = { size = 4, mask = 0xFFFFFFFF },
        long_long = { size = 8, mask = 0xFFFFFFFFFFFFFFFF }
    }
}

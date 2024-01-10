kernel.lua.require("packages/bush/ibm_bios_font.lua")

LibLunaPointer = {}
LibLunaPointer.__index = LibLunaPointer

function LibLunaPointer:new(rawPointer)
   local pointer = {}             -- our new object
   setmetatable(pointer, LibLunaPointer)  -- make Account handle lookup
   pointer.value = rawPointer      -- initialize our object
   return pointer
end

function LibLunaPointer.der_u16(self, value)
   kernel.lua._dereference_pointer_u16_left(self.value, value)
end

libluna = {
    gfx = {
        get_vram_pointer = function()
            local pointer = kernel.gfx.get_raw_vram_pointer()
            return LibLunaPointer:new(pointer)
        end,

        to_argb16 = function(a, r, g, b)
            return ((a) << 15) | (r) | ((g) << 5) | ((b) << 10)
        end
    },
    c = {
        char = {
            size = 1
        },
        short = {
            size = 2
        },
        int = {
            size = 4
        },
        long_long = {
            size = 8
        }
    }
}

table.insert(kernel.gfx, get_vram_pointer)

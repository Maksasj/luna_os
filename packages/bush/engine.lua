BushEngine = {}
BushEngine.__index = BushEngine

function BushEngine.new()
    local engine = {}
    
    setmetatable(engine, BushEngine)

    engine.lines = {}
    engine.vram = 0

    return engine
end

-- putc is platform dependent
function BushEngine:putc(str, xPos, yPos)
    self._putc(self.vram, str, xPos, yPos)
end

function BushEngine:put_line(str, xPos, yPos)
    -- This prints line character by character
    for i = 1, #str do
        local char = str:sub(i, i)
        BushEngine:putc(char, xPos + (i - 1), yPos)
    end

    -- This clears all other characters in line
    for i = 31, #str, -1 do
        BushEngine:putc(" ", i, yPos)
    end
end

function BushEngine:draw_lines()
    local linesDrawn = 0

    for index = #self.lines, 1, -1 do
        local line = self.lines[index]

        BushEngine:put_line(line, 0, 22 - linesDrawn)

        linesDrawn = linesDrawn + 1
        if linesDrawn == 23 then return end
    end
end

function BushEngine:print_line(line)
    local index = #self.lines
    self.lines[index + 1] = line
end



function BG_TILE_RAM(base)
    return ((base) * 0x4000) + 0x06000000
end

function BG_MAP_RAM(base)
    return ((base) * 0x800) + 0x06000000
end

-- MAP_BASE_SHIFT 8
-- TILE_BASE_SHIFT 2
-- BG_TILE_BASE(base)  
-- BG_MAP_BASE(base)   ((base) << MAP_BASE_SHIFT)
function BG_TILE_BASE(base)
    return ((base) << 2)
end

function BG_MAP_BASE(base)
    return ((base) << 8)
end

function BG_PRIORITY(n)
    return (n)
end

BgSize_T_256x256 = (0 << 14) | (1 << 16)
BG_COLOR_256 = 0x80

-- BgSize_T_256x256 (0 << 14) | (1 << 16)

-- REG_BG3CNT 0x400000E

-- REG_BG3PA 0x4000030
-- REG_BG3PB 0x4000032
-- REG_BG3PC 0x4000034
-- REG_BG3PD 0x4000036

-- REG_BG3X 0x4000038
-- REG_BG3Y 0x400003C

-- REG_DISPCNT 0x04000000 32 bit
-- DISPLAY_ENABLE_SHIFT 8

function BushEngine:setup()
    if kernel._platform() == libluna.platform.DSI then -- DSI PLATFORM
        -- Setup background
        kernel._dereference_pointer_u16_left(0x400000E, BgSize_T_256x256 | BG_TILE_BASE(1) |  BG_MAP_BASE(0) | BG_PRIORITY(3) | BG_COLOR_256);

        -- Set the affine matrix
        kernel._dereference_pointer_u16_left(0x4000030, 1 << 8)
        kernel._dereference_pointer_u16_left(0x4000032, 0)
        kernel._dereference_pointer_u16_left(0x4000034, 0)
        kernel._dereference_pointer_u16_left(0x4000036, 1 << 8)
        
        -- Set background at 0, 0
        kernel._dereference_pointer_u16_left(0x4000038, 0)
        kernel._dereference_pointer_u16_left(0x400003C, 0)

        -- Enable background layer
        local reg_dispcnt = kernel._dereference_pointer_u32_right(0x04000000)
        kernel._dereference_pointer_u32_left(0x04000000, reg_dispcnt | (1 << (8 + 3)))

        local tilePtr = BG_TILE_RAM(1)
        local mapPtr = BG_MAP_RAM(0)

        -- Setup platform dependent fields
        BushEngine.vram = mapPtr
        BushEngine._putc = function(vram, str, xPos, yPos)
            local c = string.byte(str)
            
            local pointer = LibLunaPointer:new(vram)
            pointer.value = pointer.value + 2 * (xPos + (yPos * 32))
            pointer:der_u16_l(c)
        end

        -- Load tile data and palette
        local vram_ptr = LibLunaPointer:new(tilePtr)
        for character = 0, 255 do
            for index = 1, 64 do
                local value = ibm_bios_font[character][index]
                
                vram_ptr:der_u8_l(value)

                vram_ptr.value = vram_ptr.value + 1
            end
        end

        local palette_ptr = LibLunaPointer:new(0x0000000005000000) -- BG_PALETTE
        palette_ptr:der_u16_l(libluna.gfx.colors.BLACK)
        palette_ptr.value = palette_ptr.value + 2
        palette_ptr:der_u16_l(libluna.gfx.colors.WHITE)

    else -- DESKTOP PLATFORM
        BushEngine.vram = kernel._get_raw_vram_pointer()
    
        BushEngine._putc = function(vram, str, xPos, yPos)
            local c = string.byte(str)
    
            for index = 1, 64 do
                local value = ibm_bios_font[c][index]
    
                local x = (index - 1) % 8 + xPos * 8
                local y = (index - 1) // 8 + yPos * 8
                    
                local pointer = LibLunaPointer:new(vram)
                pointer.value = pointer.value + libluna.types.short.size * (x + (y << 8))
    
                if value == 1 then
                    pointer:der_u16_l(libluna.gfx.colors.WHITE)
                else
                    pointer:der_u16_l(0)
                end
            end
        end
    end
end

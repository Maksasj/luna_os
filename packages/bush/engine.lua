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
        self:putc(char, xPos + (i - 1), yPos)
    end

    -- This clears all other characters in line
    for i = 31, #str, -1 do
        self:putc(" ", i, yPos)
    end
end

function BushEngine:draw_lines(yOffset)
    local linesDrawn = 0

    for index = #self.lines, 1, -1 do
        local line = self.lines[index]

        self:put_line(line, 0, (yOffset - 1) - linesDrawn)

        linesDrawn = linesDrawn + 1
        if linesDrawn == yOffset then return end
    end
end

function BushEngine:flush_lines()
    for k,v in pairs(self.lines) do
        self.lines[k] = nil
    end
end

function BushEngine:clear()
    for x = 0, 32 do
        for y = 0, 24 do
            self:putc(" ", x, y)
        end
    end
end

function BushEngine:print_line(line)
    local index = #self.lines
    self.lines[index + 1] = line
end

function BushEngine:print_lines(lines)
    for index = 1, #lines do
        self:print_line(lines[index])
    end
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


function BG_TILE_RAM_SUB(base)
    return ((base) * 0x4000) + 0x06200000
end

function BG_MAP_RAM_SUB(base)
    return ((base) * 0x800) + 0x06200000
end


function get_tile_base(base)
    return (base >> 2) & 15
end

function get_map_base(base)
    return (base >> 8) & 31
end




-- REG_BG3CNT_SUB 0x400100E

-- REG_BG3PA_SUB 0x4001030
-- REG_BG3PB_SUB 0x4001032
-- REG_BG3PC_SUB 0x4001034
-- REG_BG3PD_SUB 0x4001036

-- REG_BG3X_SUB 0x4001038
-- REG_BG3Y_SUB 0x400103C

-- REG_DISPCNT_SUB 0x04001000
-- DISPLAY_ENABLE_SHIFT 8

surfacec = {
    MAIN_SCREEN = {
        CNT = 0x400000E,
    
        PA = 0x4000030,
        PB = 0x4000032,
        PC = 0x4000034,
        PD = 0x4000036,
    
        X = 0x4000038,
        Y = 0x400003C,
    
        DISPCNT = 0x04000000,
    
        vram = BG_TILE_RAM(1),
        vmap = BG_MAP_RAM(0),

        BG_PALETTE = 0x0000000005000000
    },
    BOTTOM_SCREEN = {
        CNT = 0x400100E,
    
        PA = 0x4001030,
        PB = 0x4001032,
        PC = 0x4001034,
        PD = 0x4001036,
    
        X = 0x4001038,
        Y = 0x400103C,
    
        DISPCNT = 0x04001000,
    
        vram = BG_TILE_RAM_SUB(get_tile_base(1 + 4)),
        vmap = BG_MAP_RAM_SUB(get_map_base(0 + 4)),

        BG_PALETTE = 0x0000000005000400
    }
}

function BushEngine:setup(surface)
    if kernel._platform() == libluna.platform.DSI then -- DSI PLATFORM
        -- Setup background 
        kernel._dereference_pointer_u16_left(surface.CNT, BgSize_T_256x256 | BG_TILE_BASE(1) |  BG_MAP_BASE(0) | BG_PRIORITY(3) | BG_COLOR_256);
        -- Set the affine matrix
        kernel._dereference_pointer_u16_left(surface.PA, 1 << 8)
        kernel._dereference_pointer_u16_left(surface.PB, 0)
        kernel._dereference_pointer_u16_left(surface.PC, 0)
        kernel._dereference_pointer_u16_left(surface.PD, 1 << 8)
        -- Set background at 0, 0
        kernel._dereference_pointer_u16_left(surface.X, 0)
        kernel._dereference_pointer_u16_left(surface.Y, 0)
        -- Enable background layer
        local reg_dispcnt = kernel._dereference_pointer_u32_right(surface.DISPCNT)
        kernel._dereference_pointer_u32_left(surface.DISPCNT, reg_dispcnt | (1 << (8 + 3)))
-- 
        tilePtr = surface.vram -- BG_TILE_RAM_SUB(get_tile_base(1 + 4))
        mapPtr = surface.vmap -- BG_MAP_RAM_SUB(get_map_base(0 + 4)) 
            
            -- kernel._get_raw_vmap_pointer() -- BG_MAP_RAM_SUB(0 + 4)
            -- local tilePtr = kernel._get_raw_vram_pointer() -- BG_TILE_RAM_SUB(1 + 4)

        -- Setup platform dependent fields
        self.vram = mapPtr
        self._putc = function(vram, str, xPos, yPos)
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

        -- #define BG_PALETTE          ((u16 *)0x5000000) ///< Background palette memory
        -- #define BG_PALETTE_SUB      ((u16 *)0x5000400) ///< Background palette memory (sub engine)

        local palette_ptr = LibLunaPointer:new(surface.BG_PALETTE) -- BG_PALETTE
        palette_ptr:der_u16_l(libluna.gfx.colors.BLACK)
        palette_ptr.value = palette_ptr.value + 2
        palette_ptr:der_u16_l(libluna.gfx.colors.WHITE)

    else -- DESKTOP PLATFORM
        self.vram = kernel._get_raw_vram_pointer()
        self._putc = function(vram, str, xPos, yPos)
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

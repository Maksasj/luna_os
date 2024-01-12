BushEngine = {}

BushEngine.lines = {}

if kernel._platform() == libluna.platform.DSI then
    BushEngine._putc = function(str, xPos, yPos)
        local c = string.byte(str)
        
        local pointer = LibLunaPointer:new(kernel._get_raw_vmap_pointer())
        pointer.value = pointer.value + 2 * (xPos + (yPos * 32))
        pointer:der_u16_l(c)
    end
else 
    BushEngine._putc = function(str, xPos, yPos)
        local c = string.byte(str)

        for index = 1, 64 do
            local value = ibm_bios_font[c][index]

            local x = (index - 1) % 8 + xPos * 8
            local y = (index - 1) // 8 + yPos * 8

            local pointer = libluna.gfx.get_vram_pointer()
            pointer.value = pointer.value + libluna.types.short.size * (x + (y << 8))

            if value == 1 then
                pointer:der_u16_l(libluna.gfx.colors.WHITE)
            else
                pointer:der_u16_l(0)
            end
        end
    end
end
BushEngine.__index = BushEngine

function BushEngine:new()
    local engine = {}
    setmetatable(engine, BushEngine)

    return engine
end

-- putc is platform dependent
function BushEngine:putc(str, xPos, yPos)
    self._putc(str, xPos, yPos)
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

function BushEngine:print_line(line)
    local index = #self.lines
    self.lines[index + 1] = line
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

function BushEngine:setup()
    if kernel._platform() == libluna.platform.DSI then
        local vram1_ptr = LibLunaPointer:new(kernel._get_raw_vram1_pointer())
        for character = 0, 255 do
            for index = 1, 64 do
                local value = ibm_bios_font[character][index]
                
                vram1_ptr:der_u8_l(value)

                vram1_ptr.value = vram1_ptr.value + 1
            end
        end

        local palette_ptr = LibLunaPointer:new(0x0000000005000000) -- BG_PALETTE
        palette_ptr:der_u16_l(libluna.gfx.colors.BLACK)
        palette_ptr.value = palette_ptr.value + 2
        palette_ptr:der_u16_l(libluna.gfx.colors.WHITE)
    end
end

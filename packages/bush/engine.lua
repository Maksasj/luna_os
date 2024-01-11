BushEngine = {}
BushEngine.__index = BushEngine

function BushEngine:new()
   local engine = {}
   setmetatable(engine, BushEngine)
   engine.lines = {}
   return engine
end

function BushEngine.putc(str, xPos, yPos, color)
    local c = string.byte(str)

    for index = 1, 64 do
        local value = ibm_bios_font[c][index]

        local x = (index - 1) % 8 + xPos * 8
        local y = (index - 1) // 8 + yPos * 8

         local pointer = libluna.gfx.get_vram_pointer()
        pointer.value = pointer.value + libluna.types.short.size * (x + (y << 8))

        if value == 1 then
            pointer:der_u16_l(color)
        else
            pointer:der_u16_l(0)
        end
    end
end

function BushEngine.put_line(str, xPos, yPos, color)
    -- This prints line character by character
    for i = 1, #str do
        local char = str:sub(i, i)
        BushEngine.putc(char, xPos + (i - 1), yPos, color)
    end

    -- This clears all other characters in line
    for i = 31, #str, -1 do
        BushEngine.putc(" ", i, yPos, color)
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

        BushEngine.put_line(line, 0, 22 - linesDrawn, libluna.gfx.colors.WHITE)

        linesDrawn = linesDrawn + 1
        if linesDrawn == 23 then return end
    end
end

-- 0x04000130

-- A 0x0001
-- B 0x0002
-- Select 0x0004
-- Start 0x0008
-- Right 0x0010
-- Left 0x0020
-- Up 0x0040
-- Down 0x0080
-- R 0x0100
-- L 0x0200
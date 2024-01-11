BushEngine = {}
BushEngine.__index = BushEngine

function BushEngine:new()
   local engine = {}
   setmetatable(engine, BushEngine)
   -- pointer.value = rawPointer
   return engine
end

function BushEngine.putc(str, xPos, yPos, color)
    local c = string.byte(str)

    for index = 1, 64 do
        local value = ibm_bios_font[c][index]

        local x = (index - 1) % 8 + xPos * 8
        local y = (index - 1) // 8 + yPos * 8

        if value == 1 then
            local pointer = libluna.gfx.get_vram_pointer()
            pointer.value = pointer.value + libluna.types.short.size * (x + (y << 8))
            pointer:der_u16_l(65535)
        end
    end
end

function BushEngine.put_line(str, xPos, yPos, color)
    for i = 1, #str do
        local char = str:sub(i, i)
        BushEngine.putc(char, xPos + (i - 1), yPos, color)
    end
end
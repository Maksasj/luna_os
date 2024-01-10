kernel.lua.require("packages/bush/libluna.lua")

function print_ascii_values(str, lineOffset)
    local characterCount = 0

    for i = 1, #str do
        local c = string.byte(str:sub(i,i))

        for index = 1, 64 do
            local value = ibm_bios_font[c][index]

            local x = (index - 1) % 8 + characterCount * 8
            local y = (index - 1) // 8 + lineOffset

            if value == 1 then
                local pointer = libluna.gfx.get_vram_pointer()
                pointer.value = pointer.value + libluna.c.short.size * (x + (y << 8))
                pointer.der_u16(pointer, libluna.gfx.to_argb16(0, 31, 31, 31))
            end
        end

        characterCount = characterCount + 1
    end
end

function print_ascii_table(table)
    for key, value in pairs(table) do
        print_ascii_values(value, (key - 1) * 8)
    end
end

while true do
    print_ascii_table({
        "Hello world from luna os 0.0.1v"
    })

    kernel.gfx.wait_for_vblank()
end

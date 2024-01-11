kernel.lua.require("packages/luna/libluna.lua")

bush = {
    lines = {
        "poggers !"
    }
}

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
                pointer.value = pointer.value + libluna.types.short.size * (x + (y << 8))
                pointer:der_u16_l(libluna.gfx.colors.YELLOW)
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
    print_ascii_table(bush.lines)

    kernel.gfx.wait_for_vblank()
end

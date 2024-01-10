kernel.lua.require("packages/bush/ibm_bios_font.lua")

function print_ascii_values(str, lineOffset)
    characterCount = 0

    for i = 1, #str do
        c = string.byte(str:sub(i,i))

        for index = 1, 64 do
            value = ibm_bios_font[c][index]

            x = index % 8 + characterCount * 8
            y = index / 8 + lineOffset

            if value == 1 then
                kernel.gfx.test_gfx(x, y)
            end
        end

        characterCount = characterCount + 1
        ::continue::
    end
end

function print_ascii_table(table)
    for key, value in pairs(table) do
        print_ascii_values(value, (key - 1) * 8)
    end
end

function testFunction()
    while true do
        print_ascii_table({
            "Hello from luna os 0.0.1v"
        })

        kernel.gfx.wait_for_vblank()
    end
end

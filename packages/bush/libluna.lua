kernel.lua.require("packages/bush/ibm_bios_font.lua")

function print_ascii_values(str)
    characterCount = 0

    for i = 1, #str do
        c = string.byte(str:sub(i,i))

        for index = 1, 64 do
            value = ibm_bios_font[c][index]
    
            x = index % 8 + characterCount * 8
            y = index / 8
    
            if value == 1 then 
                kernel.gfx.test_gfx(x, y)
            end
        end

        characterCount = characterCount + 1
    end
end

function testFunction()
    while true do
        print_ascii_values("hello from luna os !")
    
        kernel.gfx.wait_for_vblank()
    end
end

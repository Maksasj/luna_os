kernel.lua.require("packages/bush/ibm_bios_font.lua")

function testFunction()
    while true do
        for x = 0, 256 do
            for y = 0, 192 do
                kernel.gfx.test_gfx(x, y)
            end
        end
    
        kernel.gfx.wait_for_vblank()
    end
end

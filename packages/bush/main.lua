kernel._require("packages/luna/libluna.lua")
kernel._require("packages/bush/engine.lua")

function main()
    bushEngine = BushEngine:new();

    bushEngine:setup()

    local dirp = kernel._opendir(".")
    if dirp == 0 then
        bushEngine:print_line("Failed to open directory")
    end

    while true do
        local cur = kernel._readdir(dirp)

        if cur == 0 then break end

        local name = kernel._dirent_get_name(cur)
        bushEngine:print_line(name)
    end

    kernel._closedir(dirp)

    function redraw()
        bushEngine:draw_lines()
        bushEngine:put_line("bush> ", 0, 23, libluna.gfx.colors.WHITE)
    end
    redraw()

    while true do
        if kernel._get_key(libluna.keycodes.KEY_B) ~= 0 then
            bushEngine:print_line("pressed key B")
            redraw()
        end

        if kernel._get_key(libluna.keycodes.KEY_A) ~= 0 then
            bushEngine:print_line("pressed key A")
            redraw()
        end

        kernel._wait_for_vblank()
    end
end


main()
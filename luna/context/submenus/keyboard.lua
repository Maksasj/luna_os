local submenu = {}

function submenu.create()
    return {
        title = "Virtual Keyboard",
        data = {},
        _enter = function(context, self)
            context.bushEngine:clear()
            context.bushEngine:flush_lines()

            context.bushEngine:print_lines({
                "�L back� Virtual Keyboard 0.1.0v",
                "��������                        ",
                "                                ",
                "                                ",
                "                                ",
                "                                ",
                "                                ",
                "                                ",
                "                                ",
                "                                ",
                "                                ",
                "                                ",
                "Selected 'A' key                ",
                "������������������������������Ŀ",
                "�~�1�2�3�4�5�6�7�8�9�0�+�'� <- �",
                "������������������������������Ĵ",
                "�tab�Q�W�E�R�T�Y�U�I�O�P�]�^�  �",
                "������������������������������Ĵ",
                "�Caps�A�S�D�F�G�H�J�K�L�\\ �[�* �",
                "������������������������������Ĵ",
                "�  �<�Z�X�C�V�B�N�M�,�.�-�     �",
                "������������������������������Ĵ",
                "�ctrl� �alt�       �a.gr� �ctrl�",
                "������ ������������������ ������"
            })
        end,
        _update = function(context, self)
            return false
        end,
        _draw = function(context, self)
            context.bushEngine:draw_lines(24)
        end
    }
end

return submenu
LibLunaPointer = {}
LibLunaPointer.__index = LibLunaPointer

function LibLunaPointer:new(rawPointer)
   local pointer = {}
   setmetatable(pointer, LibLunaPointer)
   pointer.value = rawPointer
   return pointer
end

-- Dereference pointer to as left value
function LibLunaPointer:der_u8_l(value)
   kernel.lua._dereference_pointer_u8_left(self.value, value)
end

function LibLunaPointer:der_u16_l(value)
   kernel.lua._dereference_pointer_u16_left(self.value, value)
end

function LibLunaPointer:der_u32_l(value)
   kernel.lua._dereference_pointer_u32_left(self.value, value)
end

function LibLunaPointer:der_u64_l(value)
   kernel.lua._dereference_pointer_u64_left(self.value, value)
end

-- Dereference pointer to as right value
function LibLunaPointer:der_u8_r()
   return kernel.lua._dereference_pointer_u8_right(self.value)
end

function LibLunaPointer:der_u16_r(value)
   return kernel.lua._dereference_pointer_u16_right(self.value)
end

function LibLunaPointer:der_u32_r(value)
   return kernel.lua._dereference_pointer_u32_right(self.value)
end

function LibLunaPointer:der_u64_r(value)
   return kernel.lua._dereference_pointer_u64_right(self.value)
end
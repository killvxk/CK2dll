#include "stdinc.h"
#include "byte_pattern.h"

namespace DecorativeLetterDialog
{
	/*-----------------------------------------------*/

	uintptr_t y_5;
	__declspec(naked) void y_8()
	{
		__asm {
			lea ecx, [ebp - 0x168];
			cmp dword ptr[ecx + 0x14], 0x10;
			jb y_8_;
			mov ecx, [ecx];

		y_8_:
			mov al, [ecx];

			cmp al, ESCAPE_SEQ_1;
			jz y_4;

			cmp al, ESCAPE_SEQ_2;
			jz y_4;

			cmp al, ESCAPE_SEQ_3;
			jz y_4;

			cmp al, ESCAPE_SEQ_4;
			jz y_4;

			jmp y_2;

		y_4:
			push 3;
			jmp y_3;

		y_2:
			push 1;

		y_3:
			push 0;
			lea eax, [ebp - 0xAA4];

			push y_5;
			ret;
		}
	}

	/*-----------------------------------------------*/

	errno_t func1_hook(CK2Version version) {
		std::string desc = "func1";

		switch (version) {
		case v2_8_X:
			byte_pattern::temp_instance().find_pattern("6A 01 6A 00 8D 85 5C F5 FF");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(0), y_8);
				y_5 = byte_pattern::temp_instance().get_first().address(10);
			}
			else return CK2ERROR1;
			return NOERROR;
		}
		return CK2ERROR1;
	}

	/*-----------------------------------------------*/

	uintptr_t z_6;
	__declspec(naked) void z_8()
	{
		__asm {
			lea ecx,[ebp - 0x168];
			cmp dword ptr[ecx + 0x14], 0x10;
			jb z_8_;
			mov ecx, [ecx];

		z_8_:
			mov al, [ecx];

			cmp al, ESCAPE_SEQ_1;
			jz z_2;

			cmp al, ESCAPE_SEQ_2;
			jz z_2;

			cmp al, ESCAPE_SEQ_3;
			jz z_2;

			cmp al, ESCAPE_SEQ_4;
			jz z_2;

			jmp z_3;

		z_2:
			push 3;
			jmp z_4;

		z_3:
			push 1;

		z_4:
			lea eax, [ebp - 0xAD4];

			lea ecx, [ebp - 0x168];

			push z_6;
			ret;
		}
	}

	/*-----------------------------------------------*/

	errno_t func2_hook(CK2Version version) {
		std::string desc = "func2";

		switch (version) {
		case v2_8_X:
			byte_pattern::temp_instance().find_pattern("8D 8D 98 FE FF FF 6A 01 8D");
			if (byte_pattern::temp_instance().has_size(1,desc)) {
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(0), z_8);
				z_6 = byte_pattern::temp_instance().get_first().address(14);
			}
			else return CK2ERROR1;
			return NOERROR;
		}
		return CK2ERROR1;
	}

	/*-----------------------------------------------*/

	errno_t init(CK2Version version) {
		errno_t result = NOERROR;

		byte_pattern::debug_output2("decorative letter dialog");

		// 1
		result |= func1_hook(version);
		// 2
		result |= func2_hook(version);

		return result;
	}
}
#include "editor.h"

extern mouse _mouse;
extern keyboard _keyboard;
extern uint system_tick;
extern bool debug_mode;
extern buffers memory;
extern buffers copy_data;
extern buffers sys_spritemap;

//static drawing     *draw;
static s_editor_code *e_code;
static drawing *draw;

editor::editor()
{
}
editor::~editor()
{
}

void editor::init(drawing &_draw, s_editor_code &_input) {
	draw = &_draw;
	e_code = &_input;
	
	e_code->text.push_back("--Hello World Example.");

	e_code->text.push_back("SW=256");
	e_code->text.push_back("SH=144");

	e_code->text.push_back("t=0");
	e_code->text.push_back("len=TEXT(0, 0, 'Hello Danas/Vc!')");
	e_code->text.push_back("function _MAIN()");
	e_code->text.push_back("   t=t+1");
	e_code->text.push_back("   CLS(0)");
	e_code->text.push_back("   TEXT(SW / 2 - 1 - len / 2, SH / 2 + 1, 'Hello Danas/Vc!', 9)");
	e_code->text.push_back("   TEXT(SW / 2     - len / 2, SH / 2,     'Hello Danas/Vc!', (t / 16) % 16)");
	e_code->text.push_back("end");

	//
	byte sys_sprdata[] = {
		40, 0, 11,  41, 0, 11,  42, 0, 11,  43, 0, 11,  44, 0, 11,  45, 0, 11,  46, 0, 11,  48, 0, 14,  49, 0, 14,  50, 0, 14,  51, 0, 14,  52, 0, 14,  53, 0, 14,  54, 0, 14,  56, 0, 15,  57, 0, 10,  62, 0, 10,  63, 0, 15,  96, 0, 10,  97, 0, 10,  98, 0, 15,  99, 0, 15,  100, 0, 15,  101, 0, 15,  102, 0, 15,  103, 0, 15,  1, 1, 5,
		2, 1, 5,  4, 1, 5,  5, 1, 5,  9, 1, 5,  10, 1, 5,  11, 1, 5,  12, 1, 5,  13, 1, 5,  14, 1, 5,  16, 1, 5,  18, 1, 5,  20, 1, 5,  22, 1, 5,  24, 1, 5,  25, 1, 5,  26, 1, 5,  34, 1, 5,  35, 1, 5,  36, 1, 5,  37, 1, 5,  38, 1, 5,  40, 1, 5,  41, 1, 5,  42, 1, 5,  43, 1, 5,  44, 1, 5,  45, 1, 5,  46, 1, 5,  48, 1, 11,  49, 1, 11,  50, 1, 11,  51, 1, 11,  52, 1, 11,  53, 1, 11,  54, 1, 11,  56, 1, 10,  57, 1, 11,  58, 1, 5,  59, 1, 5,  60, 1, 5,  61, 1, 5,  62, 1, 11,  63, 1, 10,  96, 1, 10,  97, 1, 5,  98, 1, 10,  99, 1, 15,  100, 1, 15,  101, 1, 15,  102, 1, 15,  103, 1, 15,  0, 2, 5,
		1, 2, 5,  5, 2, 5,  6, 2, 5,  8, 2, 5,  9, 2, 5,  10, 2, 5,  11, 2, 5,  12, 2, 5,  13, 2, 5,  14, 2, 5,  17, 2, 5,  19, 2, 5,  21, 2, 5,  24, 2, 5,  25, 2, 5,  26, 2, 5,  27, 2, 5,  28, 2, 5,  33, 2, 5,  34, 2, 5,  35, 2, 5,  36, 2, 5,  37, 2, 5,  38, 2, 5,  40, 2, 5,  41, 2, 5,  42, 2, 5,  43, 2, 5,  44, 2, 5,  45, 2, 5,  46, 2, 5,  48, 2, 11,  49, 2, 11,  50, 2, 11,  51, 2, 11,  52, 2, 11,  53, 2, 11,  54, 2, 11,  56, 2, 15,  58, 2, 5,  59, 2, 5,  60, 2, 5,  61, 2, 5,  63, 2, 15,  97, 2, 5,  98, 2, 5,  99, 2, 10,  100, 2, 15,  101, 2, 15,  102, 2, 15,  103, 2, 15,  0, 3, 5,
		1, 3, 5,  5, 3, 5,  6, 3, 5,  8, 3, 5,  16, 3, 5,  18, 3, 5,  20, 3, 5,  22, 3, 5,  24, 3, 5,  25, 3, 5,  26, 3, 5,  27, 3, 5,  28, 3, 5,  29, 3, 5,  30, 3, 5,  33, 3, 5,  38, 3, 5,  40, 3, 5,  41, 3, 5,  42, 3, 5,  43, 3, 5,  44, 3, 5,  45, 3, 5,  46, 3, 5,  48, 3, 11,  49, 3, 11,  50, 3, 11,  51, 3, 11,  52, 3, 11,  53, 3, 11,  54, 3, 11,  56, 3, 15,  57, 3, 15,  59, 3, 11,  60, 3, 11,  62, 3, 15,  63, 3, 15,  97, 3, 5,  98, 3, 5,  99, 3, 14,  100, 3, 10,  101, 3, 15,  102, 3, 15,  103, 3, 15,  0, 4, 5,
		1, 4, 5,  5, 4, 5,  6, 4, 5,  8, 4, 5,  9, 4, 5,  10, 4, 5,  11, 4, 5,  12, 4, 5,  17, 4, 5,  19, 4, 5,  21, 4, 5,  24, 4, 5,  25, 4, 5,  26, 4, 5,  27, 4, 5,  28, 4, 5,  29, 4, 5,  30, 4, 5,  33, 4, 5,  38, 4, 5,  40, 4, 5,  41, 4, 5,  42, 4, 5,  43, 4, 5,  44, 4, 5,  45, 4, 5,  46, 4, 5,  48, 4, 11,  49, 4, 11,  50, 4, 11,  51, 4, 11,  52, 4, 11,  53, 4, 11,  54, 4, 11,  56, 4, 15,  57, 4, 15,  58, 4, 15,  59, 4, 10,  60, 4, 10,  61, 4, 15,  62, 4, 15,  63, 4, 15,  97, 4, 11,  98, 4, 11,  101, 4, 15,  102, 4, 15,  103, 4, 15,  0, 5, 5,
		1, 5, 5,  5, 5, 5,  6, 5, 5,  11, 5, 5,  12, 5, 5,  16, 5, 5,  18, 5, 5,  20, 5, 5,  22, 5, 5,  24, 5, 5,  25, 5, 5,  26, 5, 5,  27, 5, 5,  28, 5, 5,  32, 5, 5,  33, 5, 5,  37, 5, 5,  38, 5, 5,  40, 5, 5,  41, 5, 5,  42, 5, 5,  43, 5, 5,  44, 5, 5,  45, 5, 5,  46, 5, 5,  48, 5, 11,  49, 5, 11,  50, 5, 11,  51, 5, 11,  52, 5, 11,  53, 5, 11,  54, 5, 11,  56, 5, 15,  57, 5, 15,  58, 5, 15,  59, 5, 15,  60, 5, 15,  61, 5, 15,  62, 5, 15,  63, 5, 15,  99, 5, 15,  100, 5, 15,  101, 5, 15,  102, 5, 15,  103, 5, 15,  1, 6, 5,
		2, 6, 5,  4, 6, 5,  5, 6, 5,  11, 6, 5,  12, 6, 5,  17, 6, 5,  19, 6, 5,  21, 6, 5,  24, 6, 5,  25, 6, 5,  26, 6, 5,  32, 6, 5,  33, 6, 5,  37, 6, 5,  38, 6, 5,  40, 6, 5,  41, 6, 5,  42, 6, 5,  43, 6, 5,  44, 6, 5,  45, 6, 5,  46, 6, 5,  48, 6, 11,  49, 6, 11,  50, 6, 11,  51, 6, 11,  52, 6, 11,  53, 6, 11,  54, 6, 11,  56, 6, 15,  57, 6, 15,  58, 6, 15,  59, 6, 15,  60, 6, 15,  61, 6, 15,  62, 6, 15,  63, 6, 15,  96, 6, 15,  97, 6, 15,  98, 6, 15,  99, 6, 15,  100, 6, 15,  101, 6, 15,  102, 6, 15,  103, 6, 15,  40, 7, 5,
		41, 7, 5,  42, 7, 5,  43, 7, 5,  44, 7, 5,  45, 7, 5,  46, 7, 5,  56, 7, 15,  57, 7, 15,  58, 7, 15,  59, 7, 15,  60, 7, 15,  61, 7, 15,  62, 7, 15,  63, 7, 15,  96, 7, 15,  97, 7, 15,  98, 7, 15,  99, 7, 15,  100, 7, 15,  101, 7, 15,  102, 7, 15,  103, 7, 15,  5, 8, 5,
		10, 8, 5,  11, 8, 5,  12, 8, 5,  13, 8, 5,  17, 8, 5,  19, 8, 5,  21, 8, 5,  23, 8, 5,  28, 8, 5,  4, 9, 5,
		5, 9, 5,  6, 9, 5,  10, 9, 5,  11, 9, 5,  12, 9, 5,  13, 9, 5,  16, 9, 5,  29, 9, 5,  3, 10, 5,
		4, 10, 5,  5, 10, 5,  6, 10, 5,  7, 10, 5,  10, 10, 5,  11, 10, 5,  12, 10, 5,  13, 10, 5,  23, 10, 5,  30, 10, 5,  2, 11, 5,
		3, 11, 5,  4, 11, 5,  5, 11, 5,  6, 11, 5,  10, 11, 5,  11, 11, 5,  12, 11, 5,  13, 11, 5,  16, 11, 5,  31, 11, 5,  1, 12, 5,
		2, 12, 5,  3, 12, 5,  4, 12, 5,  5, 12, 5,  10, 12, 5,  11, 12, 5,  12, 12, 5,  13, 12, 5,  23, 12, 5,  24, 12, 5,  25, 12, 5,  26, 12, 5,  27, 12, 5,  28, 12, 5,  29, 12, 5,  30, 12, 5,  0, 13, 5,
		2, 13, 5,  3, 13, 5,  4, 13, 5,  8, 13, 5,  9, 13, 5,  10, 13, 5,  11, 13, 5,  12, 13, 5,  13, 13, 5,  14, 13, 5,  15, 13, 5,  16, 13, 5,  24, 13, 5,  25, 13, 5,  26, 13, 5,  27, 13, 5,  28, 13, 5,  29, 13, 5,  0, 14, 5,
		3, 14, 5,  8, 14, 5,  15, 14, 5,  23, 14, 5,  24, 14, 5,  26, 14, 5,  27, 14, 5,  28, 14, 5,  0, 15, 5,
		1, 15, 5,  2, 15, 5,  8, 15, 5,  9, 15, 5,  10, 15, 5,  11, 15, 5,  12, 15, 5,  13, 15, 5,  14, 15, 5,  15, 15, 5,  16, 15, 5,  18, 15, 5,  20, 15, 5,  22, 15, 5,  24, 15, 5,  27, 15, 5,  8, 24, 5,
		16, 24, 5,  18, 24, 5,  25, 24, 5,  27, 24, 5,  34, 24, 5,  40, 24, 5,  43, 24, 5,  49, 24, 5,  50, 24, 5,  56, 24, 5,  65, 24, 5,  72, 24, 5,  124, 24, 5,  129, 24, 5,  130, 24, 5,  136, 24, 5,  137, 24, 5,  144, 24, 5,  145, 24, 5,  146, 24, 5,  152, 24, 5,  153, 24, 5,  154, 24, 5,  162, 24, 5,  168, 24, 5,  169, 24, 5,  170, 24, 5,  171, 24, 5,  177, 24, 5,  178, 24, 5,  184, 24, 5,  185, 24, 5,  186, 24, 5,  187, 24, 5,  8, 25, 5,
		16, 25, 5,  18, 25, 5,  24, 25, 5,  25, 25, 5,  26, 25, 5,  27, 25, 5,  28, 25, 5,  33, 25, 5,  34, 25, 5,  35, 25, 5,  43, 25, 5,  48, 25, 5,  56, 25, 5,  64, 25, 5,  73, 25, 5,  80, 25, 5,  82, 25, 5,  89, 25, 5,  123, 25, 5,  128, 25, 5,  131, 25, 5,  137, 25, 5,  147, 25, 5,  155, 25, 5,  161, 25, 5,  162, 25, 5,  168, 25, 5,  176, 25, 5,  187, 25, 5,  8, 26, 5,
		25, 26, 5,  27, 26, 5,  32, 26, 5,  33, 26, 5,  42, 26, 5,  49, 26, 5,  50, 26, 5,  52, 26, 5,  64, 26, 5,  73, 26, 5,  81, 26, 5,  88, 26, 5,  89, 26, 5,  90, 26, 5,  104, 26, 5,  105, 26, 5,  106, 26, 5,  122, 26, 5,  128, 26, 5,  131, 26, 5,  137, 26, 5,  145, 26, 5,  146, 26, 5,  153, 26, 5,  154, 26, 5,  160, 26, 5,  162, 26, 5,  168, 26, 5,  169, 26, 5,  170, 26, 5,  176, 26, 5,  177, 26, 5,  178, 26, 5,  186, 26, 5,  24, 27, 5,
		25, 27, 5,  26, 27, 5,  27, 27, 5,  28, 27, 5,  34, 27, 5,  35, 27, 5,  41, 27, 5,  48, 27, 5,  51, 27, 5,  64, 27, 5,  73, 27, 5,  80, 27, 5,  82, 27, 5,  89, 27, 5,  121, 27, 5,  128, 27, 5,  131, 27, 5,  137, 27, 5,  144, 27, 5,  155, 27, 5,  160, 27, 5,  161, 27, 5,  162, 27, 5,  163, 27, 5,  171, 27, 5,  176, 27, 5,  179, 27, 5,  185, 27, 5,  8, 28, 5,
		25, 28, 5,  27, 28, 5,  32, 28, 5,  33, 28, 5,  34, 28, 5,  41, 28, 5,  44, 28, 5,  49, 28, 5,  50, 28, 5,  52, 28, 5,  65, 28, 5,  72, 28, 5,  97, 28, 5,  112, 28, 5,  120, 28, 5,  129, 28, 5,  130, 28, 5,  137, 28, 5,  144, 28, 5,  145, 28, 5,  146, 28, 5,  147, 28, 5,  152, 28, 5,  153, 28, 5,  154, 28, 5,  162, 28, 5,  168, 28, 5,  169, 28, 5,  170, 28, 5,  177, 28, 5,  178, 28, 5,  185, 28, 5,  34, 29, 5,
		96, 29, 5,  1, 32, 5,
		2, 32, 5,  9, 32, 5,  10, 32, 5,  34, 32, 5,  48, 32, 5,  56, 32, 5,  57, 32, 5,  58, 32, 5,  65, 32, 5,  66, 32, 5,  73, 32, 5,  74, 32, 5,  80, 32, 5,  81, 32, 5,  82, 32, 5,  89, 32, 5,  90, 32, 5,  96, 32, 5,  97, 32, 5,  98, 32, 5,  104, 32, 5,  105, 32, 5,  106, 32, 5,  112, 32, 5,  113, 32, 5,  114, 32, 5,  121, 32, 5,  122, 32, 5,  123, 32, 5,  128, 32, 5,  131, 32, 5,  136, 32, 5,  137, 32, 5,  138, 32, 5,  146, 32, 5,  147, 32, 5,  152, 32, 5,  155, 32, 5,  160, 32, 5,  168, 32, 5,  172, 32, 5,  176, 32, 5,  179, 32, 5,  185, 32, 5,  186, 32, 5,  0, 33, 5,
		3, 33, 5,  8, 33, 5,  11, 33, 5,  16, 33, 5,  25, 33, 5,  33, 33, 5,  40, 33, 5,  41, 33, 5,  42, 33, 5,  49, 33, 5,  59, 33, 5,  64, 33, 5,  67, 33, 5,  72, 33, 5,  75, 33, 5,  80, 33, 5,  83, 33, 5,  88, 33, 5,  96, 33, 5,  99, 33, 5,  104, 33, 5,  112, 33, 5,  120, 33, 5,  128, 33, 5,  131, 33, 5,  137, 33, 5,  147, 33, 5,  152, 33, 5,  154, 33, 5,  160, 33, 5,  168, 33, 5,  169, 33, 5,  171, 33, 5,  172, 33, 5,  176, 33, 5,  177, 33, 5,  179, 33, 5,  184, 33, 5,  187, 33, 5,  1, 34, 5,
		2, 34, 5,  9, 34, 5,  10, 34, 5,  11, 34, 5,  32, 34, 5,  50, 34, 5,  57, 34, 5,  58, 34, 5,  64, 34, 5,  66, 34, 5,  67, 34, 5,  72, 34, 5,  75, 34, 5,  80, 34, 5,  81, 34, 5,  82, 34, 5,  88, 34, 5,  96, 34, 5,  99, 34, 5,  104, 34, 5,  105, 34, 5,  106, 34, 5,  112, 34, 5,  113, 34, 5,  114, 34, 5,  120, 34, 5,  122, 34, 5,  123, 34, 5,  128, 34, 5,  129, 34, 5,  130, 34, 5,  131, 34, 5,  137, 34, 5,  147, 34, 5,  152, 34, 5,  153, 34, 5,  160, 34, 5,  168, 34, 5,  170, 34, 5,  172, 34, 5,  176, 34, 5,  178, 34, 5,  179, 34, 5,  184, 34, 5,  187, 34, 5,  0, 35, 5,
		3, 35, 5,  11, 35, 5,  33, 35, 5,  40, 35, 5,  41, 35, 5,  42, 35, 5,  49, 35, 5,  64, 35, 5,  65, 35, 5,  67, 35, 5,  72, 35, 5,  73, 35, 5,  74, 35, 5,  75, 35, 5,  80, 35, 5,  83, 35, 5,  88, 35, 5,  96, 35, 5,  99, 35, 5,  104, 35, 5,  112, 35, 5,  120, 35, 5,  123, 35, 5,  128, 35, 5,  131, 35, 5,  137, 35, 5,  144, 35, 5,  147, 35, 5,  152, 35, 5,  154, 35, 5,  160, 35, 5,  168, 35, 5,  172, 35, 5,  176, 35, 5,  179, 35, 5,  184, 35, 5,  187, 35, 5,  1, 36, 5,
		2, 36, 5,  9, 36, 5,  10, 36, 5,  16, 36, 5,  25, 36, 5,  34, 36, 5,  48, 36, 5,  57, 36, 5,  65, 36, 5,  66, 36, 5,  72, 36, 5,  75, 36, 5,  80, 36, 5,  81, 36, 5,  82, 36, 5,  89, 36, 5,  90, 36, 5,  96, 36, 5,  97, 36, 5,  98, 36, 5,  104, 36, 5,  105, 36, 5,  106, 36, 5,  112, 36, 5,  121, 36, 5,  122, 36, 5,  123, 36, 5,  128, 36, 5,  131, 36, 5,  136, 36, 5,  137, 36, 5,  138, 36, 5,  145, 36, 5,  146, 36, 5,  152, 36, 5,  155, 36, 5,  160, 36, 5,  161, 36, 5,  162, 36, 5,  168, 36, 5,  172, 36, 5,  176, 36, 5,  179, 36, 5,  185, 36, 5,  186, 36, 5,  24, 37, 5,
		0, 40, 5,
		1, 40, 5,  2, 40, 5,  9, 40, 5,  10, 40, 5,  16, 40, 5,  17, 40, 5,  18, 40, 5,  25, 40, 5,  26, 40, 5,  27, 40, 5,  32, 40, 5,  33, 40, 5,  34, 40, 5,  40, 40, 5,  43, 40, 5,  48, 40, 5,  51, 40, 5,  56, 40, 5,  60, 40, 5,  64, 40, 5,  67, 40, 5,  72, 40, 5,  75, 40, 5,  80, 40, 5,  81, 40, 5,  82, 40, 5,  83, 40, 5,  88, 40, 5,  89, 40, 5,  96, 40, 5,  104, 40, 5,  105, 40, 5,  113, 40, 5,  128, 40, 5,  144, 40, 5,  163, 40, 5,  178, 40, 5,  0, 41, 5,
		3, 41, 5,  8, 41, 5,  11, 41, 5,  16, 41, 5,  19, 41, 5,  24, 41, 5,  33, 41, 5,  40, 41, 5,  43, 41, 5,  48, 41, 5,  51, 41, 5,  56, 41, 5,  60, 41, 5,  64, 41, 5,  67, 41, 5,  72, 41, 5,  75, 41, 5,  83, 41, 5,  88, 41, 5,  97, 41, 5,  105, 41, 5,  112, 41, 5,  114, 41, 5,  129, 41, 5,  137, 41, 5,  138, 41, 5,  139, 41, 5,  144, 41, 5,  145, 41, 5,  146, 41, 5,  153, 41, 5,  154, 41, 5,  161, 41, 5,  162, 41, 5,  163, 41, 5,  169, 41, 5,  170, 41, 5,  177, 41, 5,  185, 41, 5,  186, 41, 5,  187, 41, 5,  0, 42, 5,
		3, 42, 5,  8, 42, 5,  11, 42, 5,  16, 42, 5,  19, 42, 5,  25, 42, 5,  26, 42, 5,  33, 42, 5,  40, 42, 5,  43, 42, 5,  48, 42, 5,  50, 42, 5,  56, 42, 5,  58, 42, 5,  60, 42, 5,  65, 42, 5,  66, 42, 5,  73, 42, 5,  74, 42, 5,  75, 42, 5,  81, 42, 5,  82, 42, 5,  88, 42, 5,  98, 42, 5,  105, 42, 5,  136, 42, 5,  139, 42, 5,  144, 42, 5,  147, 42, 5,  152, 42, 5,  160, 42, 5,  163, 42, 5,  168, 42, 5,  170, 42, 5,  171, 42, 5,  176, 42, 5,  177, 42, 5,  178, 42, 5,  184, 42, 5,  187, 42, 5,  0, 43, 5,
		1, 43, 5,  2, 43, 5,  8, 43, 5,  11, 43, 5,  16, 43, 5,  17, 43, 5,  18, 43, 5,  27, 43, 5,  33, 43, 5,  40, 43, 5,  43, 43, 5,  48, 43, 5,  50, 43, 5,  56, 43, 5,  58, 43, 5,  60, 43, 5,  64, 43, 5,  67, 43, 5,  75, 43, 5,  80, 43, 5,  88, 43, 5,  99, 43, 5,  105, 43, 5,  136, 43, 5,  139, 43, 5,  144, 43, 5,  147, 43, 5,  152, 43, 5,  160, 43, 5,  163, 43, 5,  168, 43, 5,  169, 43, 5,  177, 43, 5,  184, 43, 5,  187, 43, 5,  0, 44, 5,
		9, 44, 5,  10, 44, 5,  16, 44, 5,  19, 44, 5,  24, 44, 5,  25, 44, 5,  26, 44, 5,  33, 44, 5,  41, 44, 5,  42, 44, 5,  49, 44, 5,  57, 44, 5,  59, 44, 5,  64, 44, 5,  67, 44, 5,  72, 44, 5,  73, 44, 5,  74, 44, 5,  80, 44, 5,  81, 44, 5,  82, 44, 5,  83, 44, 5,  88, 44, 5,  89, 44, 5,  100, 44, 5,  104, 44, 5,  105, 44, 5,  137, 44, 5,  138, 44, 5,  139, 44, 5,  144, 44, 5,  145, 44, 5,  146, 44, 5,  153, 44, 5,  154, 44, 5,  161, 44, 5,  162, 44, 5,  163, 44, 5,  169, 44, 5,  170, 44, 5,  177, 44, 5,  185, 44, 5,  186, 44, 5,  187, 44, 5,  11, 45, 5,
		120, 45, 5,  121, 45, 5,  122, 45, 5,  123, 45, 5,  187, 45, 5,  185, 46, 5,
		186, 46, 5,  0, 48, 5,
		24, 48, 5,  32, 48, 5,  97, 48, 5,  153, 48, 5,  154, 48, 5,  160, 48, 5,  168, 48, 5,  169, 48, 5,  177, 48, 5,  179, 48, 5,  0, 49, 5,
		8, 49, 5,  17, 49, 5,  24, 49, 5,  27, 49, 5,  32, 49, 5,  40, 49, 5,  41, 49, 5,  42, 49, 5,  43, 49, 5,  48, 49, 5,  49, 49, 5,  50, 49, 5,  57, 49, 5,  58, 49, 5,  64, 49, 5,  65, 49, 5,  66, 49, 5,  73, 49, 5,  74, 49, 5,  75, 49, 5,  80, 49, 5,  82, 49, 5,  89, 49, 5,  90, 49, 5,  91, 49, 5,  96, 49, 5,  97, 49, 5,  98, 49, 5,  104, 49, 5,  107, 49, 5,  112, 49, 5,  115, 49, 5,  120, 49, 5,  124, 49, 5,  128, 49, 5,  130, 49, 5,  136, 49, 5,  139, 49, 5,  144, 49, 5,  145, 49, 5,  146, 49, 5,  147, 49, 5,  153, 49, 5,  160, 49, 5,  169, 49, 5,  176, 49, 5,  178, 49, 5,  0, 50, 5,
		1, 50, 5,  2, 50, 5,  24, 50, 5,  26, 50, 5,  32, 50, 5,  40, 50, 5,  42, 50, 5,  44, 50, 5,  48, 50, 5,  51, 50, 5,  56, 50, 5,  59, 50, 5,  64, 50, 5,  67, 50, 5,  72, 50, 5,  75, 50, 5,  80, 50, 5,  81, 50, 5,  88, 50, 5,  89, 50, 5,  97, 50, 5,  104, 50, 5,  107, 50, 5,  112, 50, 5,  115, 50, 5,  120, 50, 5,  122, 50, 5,  124, 50, 5,  129, 50, 5,  136, 50, 5,  139, 50, 5,  146, 50, 5,  152, 50, 5,  153, 50, 5,  160, 50, 5,  169, 50, 5,  170, 50, 5,  0, 51, 5,
		3, 51, 5,  8, 51, 5,  17, 51, 5,  24, 51, 5,  25, 51, 5,  26, 51, 5,  32, 51, 5,  40, 51, 5,  42, 51, 5,  44, 51, 5,  48, 51, 5,  51, 51, 5,  56, 51, 5,  59, 51, 5,  64, 51, 5,  67, 51, 5,  72, 51, 5,  75, 51, 5,  80, 51, 5,  90, 51, 5,  91, 51, 5,  97, 51, 5,  104, 51, 5,  107, 51, 5,  112, 51, 5,  114, 51, 5,  121, 51, 5,  122, 51, 5,  123, 51, 5,  129, 51, 5,  136, 51, 5,  139, 51, 5,  145, 51, 5,  153, 51, 5,  160, 51, 5,  169, 51, 5,  0, 52, 5,
		3, 52, 5,  8, 52, 5,  17, 52, 5,  24, 52, 5,  27, 52, 5,  32, 52, 5,  40, 52, 5,  42, 52, 5,  44, 52, 5,  48, 52, 5,  51, 52, 5,  57, 52, 5,  58, 52, 5,  64, 52, 5,  65, 52, 5,  66, 52, 5,  73, 52, 5,  74, 52, 5,  75, 52, 5,  80, 52, 5,  88, 52, 5,  89, 52, 5,  90, 52, 5,  98, 52, 5,  105, 52, 5,  106, 52, 5,  107, 52, 5,  113, 52, 5,  121, 52, 5,  123, 52, 5,  128, 52, 5,  130, 52, 5,  137, 52, 5,  138, 52, 5,  139, 52, 5,  144, 52, 5,  145, 52, 5,  146, 52, 5,  147, 52, 5,  153, 52, 5,  154, 52, 5,  160, 52, 5,  168, 52, 5,  169, 52, 5,  17, 53, 5,
		64, 53, 5,  75, 53, 5,  139, 53, 5,  16, 54, 5,
		64, 54, 5,  75, 54, 5,  137, 54, 5,  138, 54, 5,  1, 88, 5,
		2, 88, 5,  3, 88, 5,  4, 88, 5,  9, 88, 5,  10, 88, 5,  11, 88, 5,  12, 88, 5,  17, 88, 5,  18, 88, 5,  19, 88, 5,  20, 88, 5,  25, 88, 5,  26, 88, 5,  27, 88, 5,  28, 88, 5,  33, 88, 5,  34, 88, 5,  35, 88, 5,  36, 88, 5,  41, 88, 5,  42, 88, 5,  43, 88, 5,  44, 88, 5,  0, 89, 5,
		3, 89, 5,  4, 89, 5,  5, 89, 5,  8, 89, 5,  9, 89, 5,  10, 89, 5,  13, 89, 5,  16, 89, 5,  17, 89, 5,  20, 89, 5,  21, 89, 5,  24, 89, 5,  29, 89, 5,  32, 89, 5,  34, 89, 5,  35, 89, 5,  37, 89, 5,  40, 89, 5,  41, 89, 5,  44, 89, 5,  45, 89, 5,  0, 90, 5,
		5, 90, 5,  8, 90, 5,  13, 90, 5,  16, 90, 5,  17, 90, 5,  20, 90, 5,  21, 90, 5,  24, 90, 5,  29, 90, 5,  32, 90, 5,  33, 90, 5,  36, 90, 5,  37, 90, 5,  40, 90, 5,  42, 90, 5,  43, 90, 5,  45, 90, 5,  0, 91, 5,
		5, 91, 5,  8, 91, 5,  13, 91, 5,  16, 91, 5,  21, 91, 5,  24, 91, 5,  25, 91, 5,  28, 91, 5,  29, 91, 5,  32, 91, 5,  33, 91, 5,  36, 91, 5,  37, 91, 5,  40, 91, 5,  42, 91, 5,  43, 91, 5,  45, 91, 5,  0, 92, 5,
		3, 92, 5,  4, 92, 5,  5, 92, 5,  8, 92, 5,  9, 92, 5,  10, 92, 5,  13, 92, 5,  16, 92, 5,  21, 92, 5,  24, 92, 5,  25, 92, 5,  28, 92, 5,  29, 92, 5,  32, 92, 5,  34, 92, 5,  35, 92, 5,  37, 92, 5,  40, 92, 5,  41, 92, 5,  44, 92, 5,  45, 92, 5,  1, 93, 5,
		2, 93, 5,  3, 93, 5,  4, 93, 5,  9, 93, 5,  10, 93, 5,  11, 93, 5,  12, 93, 5,  17, 93, 5,  18, 93, 5,  19, 93, 5,  20, 93, 5,  25, 93, 5,  26, 93, 5,  27, 93, 5,  28, 93, 5,  33, 93, 5,  34, 93, 5,  35, 93, 5,  36, 93, 5,  41, 93, 5,  42, 93, 5,  43, 93, 5,  44, 93, 5,

	};

	sys_spritemap.create(SMAP_SIZE);
	int _size = sizeof(sys_sprdata) / sizeof(*sys_sprdata);
	sys_spritemap.fill(0);
	for (int i = 0; i < _size; i += 3) {
		byte _x = sys_sprdata[i];
		byte _y = sys_sprdata[i + 1];
		byte _c = sys_sprdata[i + 2];

		sys_spritemap.poke(_x + _y * SMAP_WIDTH, 0, _c);
	}
}

void editor::render() {
	//option / 3 options * 6 pixels
	int _sectionc = 5;
	int _sectionw = 9;

	//
	draw->fill(_c::dkblue);

	//lines
	draw->rectangle(nvec(0, 0), nvec((float)SCREEN_WIDTH, 7), _c::green);						//upper line
	draw->rectangle(nvec((float)(section * _sectionw), 0), nvec((float)_sectionw - 1, 7), _c::orange);

	//icons
	for (int i = 0; i < _sectionc; i++) {
		draw->sprite(nvec(1 + (float)i * 9, 0), i, _c::black, true);
	}

	//line
	draw->rectangle(nvec(0, (float)SCREEN_HEIGHT - 8), nvec((float)SCREEN_WIDTH, 7), _c::green); //lower line

	//draw->line(nvec((float)(_editor * _sectionw), 7), nvec((float)(_editor * _sectionw) + 7, 7), _c::yellow);

	//check mode change
	for (int i = 0; i < _sectionc; i++) {
		if (_mouse.x >= i * _sectionw && _mouse.x < i * _sectionw + _sectionw) {
			if (_mouse.y < 7) {
				//draw->rectangle(nvec((float)(i * _sectionw), 8), nvec(9, 1), _c::yellow);
				draw->line(nvec((float)(i * _sectionw), 7), nvec((float)(i * _sectionw) + _sectionw - 1, 7), _c::orange);

				if (_mouse.pressed == true) section = i;
				break;
			}
		}
	}

	switch (section) {
		case section::coding: {
			uint j = 0;
			for (int i = (uint)e_code->offset.y; i < std::min(i + 18, (int)e_code->text.size()); i++) { //144 / 8 = 18
				std::string _str = e_code->text[i];
				draw->text(nvec(1 - e_code->offset.x, 7.0f + (float)msheight / 2 + j  * msheight), _str);
				j++;
			}

			draw->text(nvec(1, SCREEN_HEIGHT - (float)msheight), "Line: " + std::to_string(e_code->line + 1) + "  |  Col: " + std::to_string(e_code->col + 1));
			//std::to_string(i) + ". " +
			//draw->text(nvec(0, 7 + (float)msheight / 2), *input, _c::green);
			uint _wadd = 0;
			uint symbol = 0;
			if (e_code->text.size() > 0) {
				std::string _line = e_code->text[e_code->line];

				if (_line.length() > 0) {
					symbol = _line.at(_line.length() - 1);
					for (uint i = 0; i < e_code->col; i++) {
						 _wadd += symbol_size[(_line.at(i) - 32) * 2] + 1;
					}
				}
			}

			//draw->text(nvec(97, 11), "ofy: " + std::to_string(e_code->offset.y));

			if (_wadd < e_code->offset.x)					e_code->offset.x = (float)_wadd;
			if (_wadd > e_code->offset.x + SCREEN_WIDTH)	e_code->offset.x = (float)(_wadd - SCREEN_WIDTH + 1);
			//draw->text(nvec(64, 32), std::to_string(e_code->col < e_code->text[e_code->line].length() && e_code->text[e_code->line].length() > 0));

			//
			if (system_tick % (60 * 3) > (30 * 3)) {
				uint symbol_w = symbol_size[(symbol - 32) * 2];

				draw->line(nvec((float)_wadd - e_code->offset.x, 6 + (float)msheight / 2 + (float)(e_code->line * msheight)            - e_code->offset.y * msheight),
						   nvec((float)_wadd - e_code->offset.x, 6 + (float)msheight / 2 + (float)(e_code->line * msheight + msheight) - e_code->offset.y * msheight), _c::orange);
				//char _symb = (char)symbol;
				//draw->text(nvec((float)_wadd, 7.0f + (float)msheight / 2 + e_code->line * msheight), std::string(1, symbol), _c::black);
				//printf("col: %i\nlen: %i\n", editor_code.col, editor_code.text[editor_code.line].length());
			}
			//draw->text(nvec(55, 55), std::to_string(_wadd));
			//printf("%i\n", system_tick);
		} break;
		case section::spriting: {
			buffers *_buf = !debug_mode ? &sys_spritemap : &memory;

			vec _offset;
			vec _lpos; //local(var) pos

			//key mods
			if (_keyboard.copy) {
				if (copy_data.exists()) {
					copy_data.destroy();
				}

				//8x8 sprite
				copy_data.create(8 * 8);
				_keyboard.dtype = "sprite";
				for (int _y = 0; _y < 8; _y++) {
					for (int _x = 0; _x < 8; _x++) {
						_lpos.x = (float)(selected_region % 12) * 8 + (selected_page % 2) * 96;
						_lpos.y = (float)(selected_region / 12) * 8 + (selected_page / 2) * 96;

						byte _col = _buf->peek(_x + (int)_lpos.x + (_y + (int)_lpos.y) * SMAP_WIDTH);
						copy_data.poke(_x + _y * 8, 0, _col);
					}
				}

				_keyboard.copy = false;
			}
			if (_keyboard.paste) {
				if (copy_data.exists()) {
					if (_keyboard.dtype == "sprite") {
						for (int _y = 0; _y < 8; _y++) {
							for (int _x = 0; _x < 8; _x++) {
								_lpos.x = (float)(selected_region % 12) * 8 + (selected_page % 2) * 96;
								_lpos.y = (float)(selected_region / 12) * 8 + (selected_page / 2) * 96;

								byte _col = copy_data.peek(_x + _y * 8);
								_buf->poke(_x + (int)_lpos.x + (_y + (int)_lpos.y) * SMAP_WIDTH, 0, _col);
							}
						}
					}
				}

				_keyboard.paste = false;
			}

			//drawing section outline
			_offset.x = 1;
			_offset.y = 9;

			draw->rectangle(nvec(_offset.x, _offset.y), nvec(65, 65), _c::black, true);
			for (int _y = 0; _y < 8; _y++) {
				for (int _x = 0; _x < 8; _x++) {
					_lpos.x = (float)(selected_region % 12) * 8 + (selected_page % 2) * 96;
					_lpos.y = (float)(selected_region / 12) * 8 + (selected_page / 2) * 96;

					draw->rectangle(nvec(_offset.x + (float)_x * 8 + 1, _offset.y + (float)_y * 8 + 1), nvec(7, 7), _buf->peek(_x + (int)_lpos.x + (_y + (int)_lpos.y) * SMAP_WIDTH));
				}
			}

			//drawing
			if (_mouse.x > _offset.x && _mouse.x <= _offset.x + 64) {
				if (_mouse.y > _offset.y && _mouse.y <= _offset.y + 64) {
					int _lx = _mouse.x - (int)_offset.x - 1;
					int _ly = _mouse.y - (int)_offset.y - 1;

					_lpos.x = (float)(selected_region % 12) * 8 + (selected_page % 2) * 96;
					_lpos.y = (float)(selected_region / 12) * 8 + (selected_page / 2) * 96;

					if (_mouse.pressing) {

						if (selected_drawmode == drawmode::brush) {
							_buf->poke((int)_lpos.x + (int)(_lx / 8) + ((int)_lpos.y + (int)(_ly / 8)) * 192, 0, selected_color);
						}
					}

					draw->rectangle(nvec(_offset.x + (int)(_lx / 8) * 8, _offset.y + (int)(_ly / 8) * 8), nvec(9, 9), _c::white, true);
					draw->rectangle(nvec(_offset.x + (int)(_lx / 8) * 8 + 1, _offset.y + (int)(_ly / 8) * 8 + 1), nvec(7, 7), _c::black, true);
				}
			}

			//draw mode icons
			_offset.x = 4;
			_offset.y = 88;
			for (int i = 0; i < 4; i++) {
				draw->sprite(nvec(_offset.x + i * 10, _offset.y), 24 + i, 0, true);

				//
				if (_mouse.check_region((int)_offset.x + i * 10, (int)_offset.y, 8, 8)) {
					if (_mouse.pressing) selected_drawmode = i;
				}
			}
			draw->sprite(nvec((_offset.x + selected_drawmode * 10), (_offset.y - 6)), 7, _c::dkblue, true);

			//Selected color
			_offset.x = 1;//(float)SCREEN_WIDTH - 67;
			_offset.y = 101;//9;
			draw->rectangle(nvec(_offset.x, _offset.y), nvec(65, 17), _c::black, true);

			for (int i = 0; i < 16; i++) {
				vec _lpos;
				_lpos.x = (float)(i % 8) * 8;
				_lpos.y = (float)(i / 8) * 8;

				draw->rectangle(nvec(_offset.x + 1 + _lpos.x, _offset.y + 1 + _lpos.y), nvec(7, 7), i);

				if (_mouse.x >= _offset.x + 1 + _lpos.x && _mouse.x < _lpos.x + _offset.x + 8) {
					if (_mouse.y >= _offset.y + _lpos.y + 1 && _mouse.y < _offset.y + _lpos.y + 9) {
						//draw->rectangle(nvec((float)(i * _sectionw), 8), nvec(9, 1), _c::yellow);
						//draw->line(nvec((float)2 + _lpos.x, 101 + _lpos.y + 8), nvec((float)2 + _lpos.x + 7, 101 + _lpos.y + 8), _c::orange);

						if (_mouse.pressing == true) selected_color = i;
					}
				}
			}
			_lpos.x = (float)(selected_color % 8) * 8;
			_lpos.y = (float)(selected_color / 8) * 8;

			draw->rectangle(nvec(_offset.x + 1 + _lpos.x, _offset.y + 1 + _lpos.y), nvec(7, 7), _c::black, true);
			draw->rectangle(nvec(_offset.x + _lpos.x, _offset.y + _lpos.y), nvec(9, 9), _c::white, true);

			//sprite map
			_offset.x = (float)SCREEN_WIDTH - 99;
			_offset.y = 9;

			draw->rectangle(nvec(_offset.x, _offset.y), nvec(97, 97), _c::black, true);
			if (_mouse.x > _offset.x && _mouse.x <= _offset.x + 96) {
				if (_mouse.y > _offset.y && _mouse.y <= _offset.y + 96) {
					if (_mouse.pressing) {
						int _lx = _mouse.x - (int)_offset.x - 1;
						int _ly = _mouse.y - (int)_offset.y - 1;

						selected_region = (byte)(round(_lx / 8) + round(_ly / 8) * 12);
					}
				}
			}

			for (int _y = 0; _y < 96; _y++) {
				for (int _x = 0; _x < 96; _x++) {
					byte _xadd = (selected_page % 2) * 96;
					byte _yadd = (selected_page / 2) * 96;
					draw->point(_offset.x + (float)_x + 1, _offset.y + (float)_y + 1, _buf->peek(_xadd + _x + (_y + _yadd) * SMAP_WIDTH));
				}
			}

			_lpos.x = (float)(selected_region % 12) * 8;
			_lpos.y = (float)(selected_region / 12) * 8;
			draw->rectangle(nvec(_offset.x + _lpos.x, _offset.y + _lpos.y), nvec(9, 9), _c::white, true);
			draw->rectangle(nvec(_offset.x - 1 + _lpos.x, _offset.y - 1 + _lpos.y), nvec(11, 11), _c::black, true);

			//page
			for (int i = 0; i < 4; i++) {
				_offset.x = (float)SCREEN_WIDTH - 8 * 4 + i * 8 - 1;
				_offset.y = 107;

				if (_mouse.pressing) {
					if (_mouse.x > _offset.x - 1 && _mouse.x <= _offset.x + 6) {
						if (_mouse.y > _offset.y && _mouse.y <= _offset.y + 7) {
							selected_page = i;
						}
					}
				}
				draw->sprite(nvec(_offset.x, _offset.y), selected_page == i ? 5 : 6, _c::black, true);
			}
		} break;
		case section::mapping:
		case section::sfxmaking:
		case section::musicmaking:
			draw->text(nvec(1, 7 + (float)msheight / 2), "Work in Progress.", _c::red);
			break;
	}
}

void editor::clean() {
	sys_spritemap.destroy();
}
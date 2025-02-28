# Modified UPROGS variable in Makefile

UPROGS=\
	_cat\
	_cp\
	_echo\
	_testfork\
	_grep\
	_init\
	_kill\
	_ln\
	_ls\
	_mkdir\
	_rm\
	_sh\
	_wc\
	_zombie\
	_shutdown\
	_testfs\
	_testuser\
	_testdevhello\
	_countUD\
	_translate\
	_spaceTranslation\

# Commands for running C files in Linux. Files for each program need to be in another folder called "ramon_bordelies_project02" for CMakeLists to work.

mkdir build
cd build
cmake ..
cmake --build .
./filter ../input.txt

mkdir build
cd build
cmake ..
cmake --build .
./spaceFilter ../input.txt

/* CodeWarrior ARM Runtime Support Library
/*
#include <string.h>
_EWL_BEGIN_EXTERN_C
extern void main(void);
extern void __copy_rom_sections_to_ram(void);
static void zero_fill_bss(void) {
  memset(__START_BSS, 0, (__END_BSS - __START_BSS));
void __thumb_startup(void) _EWL_NAKED;
void __thumb_startup(void) {
_EWL_END_EXTERN_C
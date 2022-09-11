#include "defs.h"
#include "data.h"
#include "decl.h"

static int freereg[4];
static char *reglist[4] = {"r8", "r9", "r10", "r11"};

void freeall_registers(void) {
    freereg[0] = freereg[1] = freereg[2] = freereg[3] = 1;
}

static int alloc_register(void) {
    for (int i=0; i<4; i++) {
        if (freereg[i]) {
            freereg[i] = 0;
            return i;
        }
    }
    fprintf(stderr, "Out of registers!\n");
    exit(1);
}

static void free_register(int reg)
{
  if (freereg[reg] != 0) {
    fprintf(stderr, "Error trying to free register %d\n", reg);
    exit(1);
  }
  freereg[reg]= 1;
}

void cgpreamble()
{
  freeall_registers();
  fputs(
  "default rel\n"
  "bits 64\n"
  "global main\n"
  "global printint\n"
  "extern _CRT_INIT\n"
  "extern ExitProcess\n"
  "extern printf\n"
  "segment . data\n"
  "\tLC0: db \"%d\", 0xd, 0xa, 0\n"
  "\tfirst equ 12\n"
  "\tsecond equ 14\n"
  "segment .text\n"
  "printint:\n"
  "\tpush\trbp\n"
  "\tmov\trbp, rsp\n"
  "\tsub\trsp, 32\n"
  "\tlea\trcx, [LC0]\n"
  "\tmov\trdx, r9\n"
  "\tcall\tprintf\n"
  "\tmov\trsp, rbp\n"
  "\tpop\trbp\n"
  "\tret\n"
  "main:\n"
  "\tpush\trbp\n"
  "\tmov\trbp, rsp\n"
  "\tsub\trsp, 32\n"
  "\tcall _CRT_INIT\n",
  Outfile);
}

void cgpostamble()
{
  fputs(
  "\tmov\trsp, rbp\n"
	"\tpop\trbp\n"
	"\txor\trcx, rcx\n"
	"\tcall\tExitProcess\n",
  Outfile);
}

int cgload(int value) {

    int r = alloc_register();

    fprintf(Outfile, "\tmov\t$%s, %d\n", reglist[r], value);
    return r;
}

int cgadd(int r1, int r2) {
    fprintf(Outfile, "\tadd\t%s, %s\n", reglist[r2], reglist[r1]);
    free_register(r1);
    return r2;
}

int cgmul(int r1, int r2) {
    fprintf(Outfile, "\timul\t%s, %s\n", reglist[r2], reglist[r1]);
    free_register(r1);
    return r2;
}

int cgsub(int r1, int r2) {
    fprintf(Outfile, "\tsub\t%s, %s\n", reglist[r2], reglist[r1]);
    free_register(r2);
    return r1;
}

int cgdiv(int r1, int r2) {
    fprintf(Outfile, "\tmovq\t%s, %%rax\n", reglist[r1]);
    fprintf(Outfile, "\tcqo\n");
    fprintf(Outfile, "\tidivq\t%s\n", reglist[r2]);
    fprintf(Outfile, "\tmovq\t%%rax,%s\n", reglist[r1]);
    free_register(r2);
    return r1;
}

void cgprintint(int r) {
    fprintf(Outfile, "\tmovq\t%s, %%rdi\n", reglist[r]);
    fprintf(Outfile, "\tcall\tprintint\n");
    free_register(r);
}
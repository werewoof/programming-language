#include "defs.h"
#include "data.h"
#include "decl.h"

static int freereg[4];
static char *reglist[4] = {"r8", "r9", "r10", "r11"};
static char *breglist[4] = {"r8b", "r9b", "r10b", "r11b"};

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
  "segment .text\n"
  "printint:\n"
  "\tpush\trbp\n"
  "\tmov\t\trbp, rsp\n"
  "\tsub\t\trsp, 32\n"
  "\tlea\t\trcx, [LC0]\n"
  "\tmov\t\trdx, rdi\n"
  "\tcall\tprintf\n"
  "\tmov\t\trsp, rbp\n"
  "\tpop\t\trbp\n"
  "\tret\n"
  "main:\n"
  "\tpush\trbp\n"
  "\tmov\t\trbp, rsp\n"
  "\tsub\t\trsp, 32\n"
  "\tcall\t_CRT_INIT\n",
  Outfile);
}

void cgpostamble()
{
  fputs(
  "\tmov\t\trsp, rbp\n"
	"\tpop\t\trbp\n"
	"\txor\t\trcx, rcx\n"
	"\tcall\tExitProcess\n",
  Outfile);
}

int cgloadint(int value) {

    int r = alloc_register();

    fprintf(Outfile, "\tmov\t\t%s, %d\n", reglist[r], value);
    return r;
}

int cgadd(int r1, int r2) {
    fprintf(Outfile, "\tadd\t\t%s, %s\n", reglist[r2], reglist[r1]);
    free_register(r1);
    return r2;
}

int cgmul(int r1, int r2) {
    fprintf(Outfile, "\timul\t\t%s, %s\n", reglist[r2], reglist[r1]);
    free_register(r1);
    return r2;
}

int cgsub(int r1, int r2) {
    fprintf(Outfile, "\tsub\t\t%s, %s\n", reglist[r1], reglist[r2]);
    free_register(r2);
    return r1;
}

int cgdiv(int r1, int r2) {
    fprintf(Outfile, "\tmov\t\trax, %s\n", reglist[r1]);
    fprintf(Outfile, "\tcqo\n");
    fprintf(Outfile, "\tidiv\t%s\n", reglist[r2]);
    fprintf(Outfile, "\tmov\t\t%s,rax\n", reglist[r1]);
    free_register(r2);
    return r1;
}

void cgprintint(int r) {
    fprintf(Outfile, "\tmov\t\trdi, %s\n", reglist[r]);
    fprintf(Outfile, "\tcall\tprintint\n");
    free_register(r);
}

int cgloadglob(char *identifier) {
  int r = alloc_register();
  fprintf(Outfile, "\tmov\t%s, [%s]\n", reglist[r], identifier);
  return r;
}

int cgstorglob(int r, char *identifier) {
  fprintf(Outfile, "\tmov\t\tqword [%s], %s\n", identifier, reglist[r]);
  return r;
}

void cgglobsym(char *sym) {
  fprintf(Outfile, "\tcommon\t%s 8\n", sym);
}

static int cgcompare (int r1, int r2, char *how) {
  fprintf(Outfile, "\tcmp\t\t%s, %s\n", reglist[r1], reglist[r2]);
  fprintf(Outfile, "\t%s\t%s\n", how, breglist[r2]);
  fprintf(Outfile, "\tand\t\t%s, 255\n", reglist[r2]); //clear top bits
  free_register(r1);
  return r2;
}

int cgequal(int r1, int r2) { return cgcompare(r1, r2, "sete"); }
int cgnotequal(int r1, int r2) { return cgcompare(r1, r2, "setne"); }
int cglessthan(int r1, int r2) { return cgcompare(r1, r2, "setl"); }
int cggreaterthan(int r1, int r2) { return cgcompare(r1, r2, "setg"); }
int cglessequal(int r1, int r2) { return cgcompare(r1, r2, "setle"); }
int cggreaterequal(int r1, int r2) { return cgcompare(r1, r2, "setge"); }







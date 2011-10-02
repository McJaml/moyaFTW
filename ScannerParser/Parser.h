

#if !defined(COCO_PARSER_H__)
#define COCO_PARSER_H__



#include "Scanner.h"



class Errors {
public:
	int count;			// number of errors detected

	Errors();
	void SynErr(int line, int col, int n);
	void Error(int line, int col, const wchar_t *s);
	void Warning(int line, int col, const wchar_t *s);
	void Warning(const wchar_t *s);
	void Exception(const wchar_t *s);

}; // Errors

class Parser {
private:
	enum {
		_EOF=0,
		_id=1,
		_cte_i=2,
		_cte_char=3,
		_cte_string=4,
		_cte_d=5,
		_int=6,
		_char=7,
		_string=8,
		_if=9,
		_while=10,
		_bool=11,
		_double=12,
		_extends=13,
		_this=14,
		_else=15,
		_false=16,
		_true=17,
		_class=18,
		_for=19,
		_do=20,
		_void=21,
		_return=22,
		_new=23,
		_null=24,
		_super=25,
		_write=26,
		_main=27,
		_ftw=28,
		_read=29,
		_and=30,
		_or=31,
		_lt=32,
		_gt=33,
		_lte=34,
		_gte=35,
		_ne=36,
		_eq=37,
		_ee=38,
		_plus=39,
		_minus=40,
		_times=41,
		_divide=42,
		_not=43,
		_scolon=44,
		_comma=45,
		_dot=46,
		_lbrace=47,
		_rbrace=48,
		_lparent=49,
		_rparent=50,
		_lcorch=51,
		_rcorch=52
	};
	int maxT;

	Token *dummyToken;
	int errDist;
	int minErrDist;

	void SynErr(int n);
	void Get();
	void Expect(int n);
	bool StartOf(int s);
	void ExpectWeak(int n, int follow);
	bool WeakSeparator(int n, int syFol, int repFol);

public:
	Scanner *scanner;
	Errors  *errors;

	Token *t;			// last recognized token
	Token *la;			// lookahead token



	Parser(Scanner *scanner);
	~Parser();
	void SemErr(const wchar_t* msg);

	void moyaFTW();
	void Class();
	void Main();
	void ClassBody();
	void Vars();
	void Metodo();
	void Estatuto();
	void A();
	void Tipo();
	void B();
	void DeclararObj();
	void E();
	void Var_cte();
	void InstanciarList();
	void Expresion();
	void Expresion_Otr();
	void Exp();
	void C();
	void Comparador();
	void Termino();
	void Factor();
	void C_id();
	void F();
	void Parametros();
	void D();
	void If();
	void While();
	void For();
	void For1();
	void Asignar();
	void Instanciar();
	void Read();
	void AsignarLlamar();
	void AsignarLlamarDeclarar();
	void Print();
	void TipoParametros();
	void InstanciarObj();

	void Parse();

}; // end Parser



#endif

